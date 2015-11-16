#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

bool first=true;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

std::string ftoa(double i) 
{
  char res[10];
  sprintf(res, "%2.1f", i);
  std::string ret(res);
  return ret;
}

Double_t asymmetricGaussian(Double_t *x, Double_t *par)
{
  double ret;
  if (x[0]<par[0])
  {
    ret=exp(-0.5*pow((x[0]-par[0])/par[1], 2));
  }
  else
  {
    ret=exp(-0.5*pow((x[0]-par[0])/par[2], 2));
  }
  return ret;
} 

void DisplayKinFitForFile(TFile *file, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_kinFit=(TH1F*)file->Get("h_mX_genForKinFitCheck");
  
  double n=h_mX_SR->GetSumOfWeights();
  h_mX_SR->Scale(1./n);
  h_mX_SR_kinFit->Scale(1./n);
  
  h_mX_SR->Rebin(10);
  h_mX_SR_kinFit->Rebin(10);
  
  h_mX_SR->GetXaxis()->SetRangeUser(200, 1100);
  h_mX_SR_kinFit->GetXaxis()->SetRangeUser(200, 1100);
  
  h_mX_SR->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineWidth(2);
  
  h_mX_SR->SetLineColor(kBlue);
  h_mX_SR->SetLineStyle(7);
  h_mX_SR_kinFit->SetLineColor(kRed);
  
  if (first)
  {
    h_mX_SR_kinFit->SetMaximum(h_mX_SR_kinFit->GetMaximum()*1.2);
    h_mX_SR_kinFit->GetYaxis()->SetTitle("Normalized Units");
    h_mX_SR_kinFit->GetYaxis()->SetTitleOffset(1.4);
    h_mX_SR_kinFit->Draw("hist");
    TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_mX_SR, "m_{X} Signal Peak");
    leg->AddEntry(h_mX_SR_kinFit, "m_{X} w/ Kinematic Fit");
    leg->Draw();
    first=false;
  }
  else h_mX_SR_kinFit->Draw("hist same");
  h_mX_SR->Draw("hist same");
  
  TLine *line=new TLine(xLine, 0, xLine, h_mX_SR_kinFit->GetMaximum());
  line->Draw();
  
}

TH1D* RMSY(TH2F *h)
{
  TH1D* h_RMS=h->ProjectionX();
  h_RMS->SetName(("res_"+std::string(h->GetName())).c_str());
  for (int i=1; i<h_RMS->GetNbinsX(); i+=1)
  {
    h_RMS->SetBinContent(i, h->ProjectionY("_px", i, i)->GetRMS());
    h_RMS->SetBinError(i, h->ProjectionY("_px", i, i)->GetRMSError());
  }
  return h_RMS;
}

void SliceAndDraw(TH2F *h)
{
  h->RebinX(10);
  std::cout<<"h->GetNbinsX() = "<<h->GetNbinsX()<<std::endl;
  for (int i=1; i<h->GetNbinsX()-1; i+=1)
  {
    TCanvas *c=new TCanvas("c", "c", 700, 700);
    TH1D *h_Proj=(TH1D*)h->ProjectionY(itoa(i).c_str(), i, i);
    TF1 *f_Proj=new TF1("f_Proj", "gaus", h_Proj->GetMean()-h_Proj->GetRMS(), h_Proj->GetMean()+h_Proj->GetRMS());
    h_Proj->Fit(f_Proj, "R");
    h_Proj->Draw();
    double binLoEdge=(h->GetXaxis()->GetBinCenter(i)+h->GetXaxis()->GetBinCenter(i-1))/2.;
    double binHiEdge=(h->GetXaxis()->GetBinCenter(i)+h->GetXaxis()->GetBinCenter(i+1))/2.;
    TPaveText *leg=new TPaveText(0.55, 0.7, 0.89 ,0.5, "NDC");
    leg->SetBorderSize(0); leg->SetFillColor(0); leg->SetLineColor(0);
    leg->AddText((itoa(binLoEdge)+"GeV < p_{T} < "+itoa(binHiEdge)+" GeV").c_str());
    leg->Draw();
    c->SaveAs(("c_AsymResolution_pTbin"+itoa(i)+".png").c_str());
    delete c;
  }
}

TH1D* MEANY(TH2F *h)
{
  TH1D* h_MEAN=h->ProjectionX();
  h_MEAN->SetName(("mean_"+std::string(h->GetName())).c_str());
  for (int i=1; i<h_MEAN->GetNbinsX(); i+=1)
  {
    h_MEAN->SetBinContent(i, h->ProjectionY("_px", i, i)->GetMean());
    h_MEAN->SetBinError(i, h->ProjectionY("_px", i, i)->GetMeanError());
  }
  return h_MEAN;
}

TH1D* RESYperAVGY(TH2F *h1, TH2F *h2)
{
  TH1D *h_RESYperAVGY=h1->ProjectionX();
  h_RESYperAVGY->SetName(("res_"+std::string(h1->GetName())).c_str());
  for (int i=1; i<h_RESYperAVGY->GetNbinsX(); i+=1)
  {
    // std::cout<<"i = "<<i<<" h2->ProjectionY(\"_px\", i, i)->GetMean() = "<<h2->ProjectionY("_px", i, i)->GetMean()<<std::endl;
    h_RESYperAVGY->SetBinContent(i, (h1->ProjectionY("_px", i, i)->GetRMS()/h2->ProjectionY("_px", i, i)->GetMean()));
    h_RESYperAVGY->SetBinError(i, (h1->ProjectionY("_px", i, i)->GetRMSError()/h2->ProjectionY("_px", i, i)->GetMean()));
  }
  return h_RESYperAVGY;
}

TH1D* COVYZ(TH3F *h)
{
  TH1D *h_COVYZ=(TH1D*)h->Project3D("x");
  h_COVYZ->SetName(("cov_"+std::string(h->GetName())).c_str());
  for (int i=1; i<h_COVYZ->GetNbinsX(); ++i)
  {
    h->GetXaxis()->SetRange(i, i);
    TH2D *h_SliceYZ=(TH2D*)h->Project3D("yz");
    double sumOfWeights=h_SliceYZ->GetSumOfWeights();
    if (sumOfWeights>10)
    {
      double covariance=h_SliceYZ->GetCovariance();
      double covarianceError=covariance/pow(sumOfWeights, 0.5);
      h_COVYZ->SetBinContent(i, covariance);
      h_COVYZ->SetBinError(i, covarianceError);
    }
  }
  return h_COVYZ;
}

void Display_pT_Resolution(std::vector<TFile*> *v)
{
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_0_1p4");
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5");
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4_Corrected=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_0_1p4_Corrected");
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected");
  h_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet p_{T}^{reco} - p_{T}^{gen} (GeV)");
  h_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.4);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_pT_res_vs_pT_eta_0_1p4->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_0_1p4"));
    h_jet_pT_res_vs_pT_eta_1p4_2p5->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5"));
    h_jet_pT_res_vs_pT_eta_0_1p4_Corrected->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_0_1p4_Corrected"));
    h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected"));
  }
  h_jet_pT_res_vs_pT_eta_0_1p4->RebinX(1);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 800);
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_0_1p4=RMSY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet #sigma(p_{T}^{reco} - p_{T}^{gen}) (GeV)");
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleSize(0.03);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f1=new TF1("f1", "pol1", 0, 600);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Fit(f1, "R");
  
  h_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 800);
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=RMSY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  TF1 *f2=new TF1("f2", "pol1", 0, 350);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f2, "R");
  
  // Draw a couple of projections
  SliceAndDraw(h_jet_pT_res_vs_pT_eta_0_1p4);
  
  // Also create the bias distributions
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_0_1p4=MEANY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{gen})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_0_1p4", "pol1", 0, 700);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_MEAN_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=MEANY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{gen})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5", "pol1", 0, 700);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5, "R");
  
  TCanvas *c_pT_Resolution_eta_0_1p4=new TCanvas("c_pT_Resolution_eta_0_1p4", "c_pT_Resolution_eta_0_1p4", 2100, 700);
  c_pT_Resolution_eta_0_1p4->Divide(3,1);
  c_pT_Resolution_eta_0_1p4->cd(1);
  h_jet_pT_res_vs_pT_eta_0_1p4->Draw("colz");
  c_pT_Resolution_eta_0_1p4->cd(2);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Draw();
  c_pT_Resolution_eta_0_1p4->cd(3);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Draw();
  c_pT_Resolution_eta_0_1p4->SaveAs("c_pT_Resolution_eta_0_1p4.png");
  
  TCanvas *c_pT_Resolution_eta_1p4_2p5=new TCanvas("c_pT_Resolution_eta_1p4_2p5", "c_pT_Resolution_eta_1p4_2p5", 2100, 700);
  c_pT_Resolution_eta_1p4_2p5->Divide(3,1);
  c_pT_Resolution_eta_1p4_2p5->cd(1);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->Draw("colz");
  c_pT_Resolution_eta_1p4_2p5->cd(2);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Draw();
  c_pT_Resolution_eta_1p4_2p5->cd(3);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->Draw();
  c_pT_Resolution_eta_1p4_2p5->SaveAs("c_pT_Resolution_eta_1p4_2p5.png");
  
  // Check the corrected jet bias distribution
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected=MEANY(h_jet_pT_res_vs_pT_eta_0_1p4_Corrected);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetTitle("|#eta| < 1.4; Jet p_{T}^{reco} (GeV); Corrected Jet <(p_{T}^{reco} - p_{T}^{gen})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->GetXaxis()->SetRangeUser(0, 800);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetTitleSize(0.03);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetTitleOffset(1.4);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetTitleOffset(1.2);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetMinimum(-40); h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->SetMaximum(40);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected", "pol0", 0, 700);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->Fit(f_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected, "R");
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected=MEANY(h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetTitle("1.4 < |#eta| < 2.5; Jet p_{T}^{reco} (GeV); Corrected Jet <(p_{T}^{reco} - p_{T}^{gen})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->GetXaxis()->SetRangeUser(0, 800);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetTitleSize(0.03);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetTitleOffset(1.4);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetTitleOffset(1.2);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetMinimum(-40); h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->SetMaximum(40);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected", "pol0", 0, 700);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->Fit(f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected, "R");
  TCanvas *c_CorrectedJetpT=new TCanvas("c_CorrectedJetpT", "c_CorrectedJetpT", 1400, 700);
  c_CorrectedJetpT->Divide(2,1);
  c_CorrectedJetpT->cd(1);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4_Corrected->Draw();
  c_CorrectedJetpT->cd(2);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->Draw();
  c_CorrectedJetpT->SaveAs("c_CorrectedJetpT.png");
  
  // Plot the recoJet - genJet, and the genJet - parton resolutions
  TH2F *h_recopT_minus_genpT_vs_recopT=(TH2F*)v->at(0)->Get("h_recopT_minus_genpT_vs_recopT");
  TH2F *h_genpT_minus_partpT_vs_recopT=(TH2F*)v->at(0)->Get("h_genpT_minus_partpT_vs_recopT");
  TH2F *h_recopT_minus_partpT_vs_recopT=(TH2F*)v->at(0)->Get("h_recopT_minus_partpT_vs_recopT");
  h_recopT_minus_genpT_vs_recopT->GetYaxis()->SetTitleOffset(1.4);
  h_recopT_minus_genpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_genpT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.4);
  h_genpT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_recopT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.4);
  h_recopT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_recopT_minus_genpT_vs_recopT->Add((TH2F*)v->at(i)->Get("h_recopT_minus_genpT_vs_recopT"));
    h_genpT_minus_partpT_vs_recopT->Add((TH2F*)v->at(i)->Get("h_genpT_minus_partpT_vs_recopT"));
    h_recopT_minus_partpT_vs_recopT->Add((TH2F*)v->at(i)->Get("h_recopT_minus_partpT_vs_recopT"));
  }
  TH1D *h_MEAN_recopT_minus_genpT_vs_recopT=MEANY(h_recopT_minus_genpT_vs_recopT);
  h_MEAN_recopT_minus_genpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{gen})> (GeV)");
  h_MEAN_recopT_minus_genpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_recopT_minus_genpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_recopT_minus_genpT_vs_recopT->GetYaxis()->SetRangeUser(-60, 60);
  h_MEAN_recopT_minus_genpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_MEAN_recopT_minus_genpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  TH1D *h_RMS_recopT_minus_genpT_vs_recopT=RMSY(h_recopT_minus_genpT_vs_recopT);
  h_RMS_recopT_minus_genpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet #sigma(p_{T}^{reco} - p_{T}^{gen}) (GeV)");
  h_RMS_recopT_minus_genpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_RMS_recopT_minus_genpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_recopT_minus_genpT_vs_recopT->GetYaxis()->SetRangeUser(0, 100);
  h_RMS_recopT_minus_genpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_RMS_recopT_minus_genpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  
  TH1D *h_MEAN_genpT_minus_partpT_vs_recopT=MEANY(h_genpT_minus_partpT_vs_recopT);
  h_MEAN_genpT_minus_partpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{gen} - p_{T}^{part})> (GeV)");
  h_MEAN_genpT_minus_partpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_genpT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_genpT_minus_partpT_vs_recopT->GetYaxis()->SetRangeUser(-60, 60);
  h_MEAN_genpT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_MEAN_genpT_minus_partpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  TH1D *h_RMS_genpT_minus_partpT_vs_recopT=RMSY(h_genpT_minus_partpT_vs_recopT);
  h_RMS_genpT_minus_partpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet #sigma(p_{T}^{gen} - p_{T}^{part}) (GeV)");
  h_RMS_genpT_minus_partpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_RMS_genpT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_genpT_minus_partpT_vs_recopT->GetYaxis()->SetRangeUser(0, 100);
  h_RMS_genpT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_RMS_genpT_minus_partpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  
  TH1D *h_MEAN_recopT_minus_partpT_vs_recopT=MEANY(h_recopT_minus_partpT_vs_recopT);
  h_MEAN_recopT_minus_partpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{part})> (GeV)");
  h_MEAN_recopT_minus_partpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_recopT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_recopT_minus_partpT_vs_recopT->GetYaxis()->SetRangeUser(-60, 60);
  h_MEAN_recopT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_MEAN_recopT_minus_partpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  TH1D *h_RMS_recopT_minus_partpT_vs_recopT=RMSY(h_recopT_minus_partpT_vs_recopT);
  h_RMS_recopT_minus_partpT_vs_recopT->SetTitle("; Jet p_{T}^{reco} (GeV); Jet #sigma(p_{T}^{reco} - p_{T}^{part}) (GeV)");
  h_RMS_recopT_minus_partpT_vs_recopT->GetYaxis()->SetTitleSize(0.03);
  h_RMS_recopT_minus_partpT_vs_recopT->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_recopT_minus_partpT_vs_recopT->GetYaxis()->SetRangeUser(0, 100);
  h_RMS_recopT_minus_partpT_vs_recopT->GetXaxis()->SetTitleOffset(1.2);
  h_RMS_recopT_minus_partpT_vs_recopT->GetXaxis()->SetRangeUser(0, 800);
  
  
  TCanvas *c_recopT_minus_genpT_vs_recopT=new TCanvas("c_recopT_minus_genpT_vs_recopT", "c_recopT_minus_genpT_vs_recopT", 2100, 700);
  c_recopT_minus_genpT_vs_recopT->Divide(3,1);
  c_recopT_minus_genpT_vs_recopT->cd(1);
  h_recopT_minus_genpT_vs_recopT->Draw("colz");
  c_recopT_minus_genpT_vs_recopT->cd(2);
  h_RMS_recopT_minus_genpT_vs_recopT->Draw();
  c_recopT_minus_genpT_vs_recopT->cd(3);
  h_MEAN_recopT_minus_genpT_vs_recopT->Draw();
  c_recopT_minus_genpT_vs_recopT->SaveAs("c_recopT_minus_genpT_vs_recopT.png");
  
  TCanvas *c_genpT_minus_partpT_vs_recopT=new TCanvas("c_genpT_minus_partpT_vs_recopT", "c_genpT_minus_partpT_vs_recopT", 2100, 700);
  c_genpT_minus_partpT_vs_recopT->Divide(3,1);
  c_genpT_minus_partpT_vs_recopT->cd(1);
  h_genpT_minus_partpT_vs_recopT->Draw("colz");
  c_genpT_minus_partpT_vs_recopT->cd(2);
  h_RMS_genpT_minus_partpT_vs_recopT->Draw();
  c_genpT_minus_partpT_vs_recopT->cd(3);
  h_MEAN_genpT_minus_partpT_vs_recopT->Draw();
  c_genpT_minus_partpT_vs_recopT->SaveAs("c_genpT_minus_partpT_vs_recopT.png");
  
  TCanvas *c_recopT_minus_partpT_vs_recopT=new TCanvas("c_recopT_minus_partpT_vs_recopT", "c_recopT_minus_partpT_vs_recopT", 2100, 700);
  c_recopT_minus_partpT_vs_recopT->Divide(3,1);
  c_recopT_minus_partpT_vs_recopT->cd(1);
  h_recopT_minus_partpT_vs_recopT->Draw("colz");
  c_recopT_minus_partpT_vs_recopT->cd(2);
  h_RMS_recopT_minus_partpT_vs_recopT->Draw();
  c_recopT_minus_partpT_vs_recopT->cd(3);
  h_MEAN_recopT_minus_partpT_vs_recopT->Draw();
  c_recopT_minus_partpT_vs_recopT->SaveAs("c_recopT_minus_partpT_vs_recopT.png");
  
}

void Display_eta_ResolutionForFile(std::vector<TFile*> *v)
{
  TH2F *h_jet_eta_res_vs_eta = (TH2F*)v->at(0)->Get("h_jet_eta_res_vs_eta");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_eta_res_vs_eta->Add((TH2F*)v->at(i)->Get("h_jet_eta_res_vs_eta"));
  }
  h_jet_eta_res_vs_eta->RebinX(1);
  TH1D *h_RMS_jet_eta_res_vs_eta=RMSY(h_jet_eta_res_vs_eta);
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetRangeUser(0, 0.1);
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetTitle("Jet #sigma(#eta^{reco} - #eta^{gen})");
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f3=new TF1("f3", "pol1", 0, 2.5);
  h_RMS_jet_eta_res_vs_eta->Fit(f3, "R");
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_eta_res_vs_eta=MEANY(h_jet_eta_res_vs_eta);
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetRangeUser(-0.01, 0.01);
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetTitle("Jet <(#eta^{reco} - #eta^{gen})>");
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_eta_res_vs_eta=new TF1("f_MEAN_jet_eta_res_vs_eta", "pol0", 0, 2.5);
  h_MEAN_jet_eta_res_vs_eta->Fit(f_MEAN_jet_eta_res_vs_eta, "R");
  
  TH2F *h_jet_eta_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_eta_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_eta_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_eta_res_vs_pT"));
  }
  h_jet_eta_res_vs_pT->RebinX(2);
  TH1D *h_RMS_jet_eta_res_vs_pT=RMSY(h_jet_eta_res_vs_pT);
  h_RMS_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 800.);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.2);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitle("Jet #sigma(#eta^{reco} - #eta^{gen})");
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_RMS_jet_eta_res_vs_pT=new TF1("f_RMS_jet_eta_res_vs_pT", "[0]+([1]/x)+([2]/(x*x))", 40, 800);
  h_RMS_jet_eta_res_vs_pT->Fit(f_RMS_jet_eta_res_vs_pT, "R");
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_eta_res_vs_pT=MEANY(h_jet_eta_res_vs_pT);
  h_MEAN_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 800.);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitle("Jet <(#eta^{reco} - #eta^{gen})>");
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_eta_res_vs_pT=new TF1("f_MEAN_jet_eta_res_vs_pT", "pol0", 40, 800);
  h_MEAN_jet_eta_res_vs_pT->Fit(f_MEAN_jet_eta_res_vs_pT, "R");
  
  TCanvas *c_eta_Resolution=new TCanvas("c_eta_Resolution", "c_eta_Resolution", 2100, 1400);
  c_eta_Resolution->Divide(3,2);
  c_eta_Resolution->cd(1);
  h_jet_eta_res_vs_eta->Draw("colz");
  c_eta_Resolution->cd(2);
  h_RMS_jet_eta_res_vs_eta->Draw();
  c_eta_Resolution->cd(3);
  h_MEAN_jet_eta_res_vs_eta->Draw();
  c_eta_Resolution->cd(4);
  h_jet_eta_res_vs_pT->Draw("colz");
  c_eta_Resolution->cd(5);
  h_RMS_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution->cd(6);
  h_MEAN_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution->SaveAs("c_eta_Resolution.png");
  
  
}

void Display_phi_ResolutionForFile(std::vector<TFile*> *v)
{
  TH2F *h_jet_phi_res_vs_eta = (TH2F*)v->at(0)->Get("h_jet_phi_res_vs_eta");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_phi_res_vs_eta->Add((TH2F*)v->at(i)->Get("h_jet_phi_res_vs_eta"));
  }
  h_jet_phi_res_vs_eta->RebinX(1);
  TH1D *h_RMS_jet_phi_res_vs_eta=RMSY(h_jet_phi_res_vs_eta);
  h_RMS_jet_phi_res_vs_eta->GetYaxis()->SetRangeUser(0, 0.1);
  h_RMS_jet_phi_res_vs_eta->GetYaxis()->SetTitle("Jet #sigma(#phi^{reco} - #phi^{gen})");
  h_RMS_jet_phi_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f4=new TF1("f4", "pol1", 0, 2.5);
  h_RMS_jet_phi_res_vs_eta->Fit(f4, "R");
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_phi_res_vs_eta=MEANY(h_jet_phi_res_vs_eta);
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetRangeUser(-0.01, 0.01);
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetTitle("Jet <(#phi^{reco} - #phi^{gen})>");
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_phi_res_vs_eta=new TF1("f_MEAN_jet_phi_res_vs_eta", "pol0", 0, 2.5);
  h_MEAN_jet_phi_res_vs_eta->Fit(f_MEAN_jet_phi_res_vs_eta, "R");
  
  TH2F *h_jet_phi_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_phi_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_phi_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_phi_res_vs_pT"));
  }
  h_jet_phi_res_vs_pT->RebinX(1);
  TH1D *h_RMS_jet_phi_res_vs_pT=RMSY(h_jet_phi_res_vs_pT);
  h_RMS_jet_phi_res_vs_pT->GetXaxis()->SetRangeUser(0, 800.);
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.2);
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetTitle("Jet #sigma(#phi^{reco} - #phi^{gen})");
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_RMS_jet_phi_res_vs_pT=new TF1("f_RMS_jet_phi_res_vs_pT", "[0]+([1]/x)+([2]/(x*x))", 40, 800);
  h_RMS_jet_phi_res_vs_pT->Fit(f_RMS_jet_phi_res_vs_pT, "R");
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_phi_res_vs_pT=MEANY(h_jet_phi_res_vs_pT);
  h_MEAN_jet_phi_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetTitle("Jet <(#phi^{reco} - #phi^{gen})>");
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_phi_res_vs_pT=new TF1("f_MEAN_jet_phi_res_vs_pT", "pol0", 40, 800);
  h_MEAN_jet_phi_res_vs_pT->Fit(f_MEAN_jet_phi_res_vs_pT, "R");
  
  TCanvas *c_phi_Resolution=new TCanvas("c_phi_Resolution", "c_phi_Resolution", 2100, 1400);
  c_phi_Resolution->Divide(3,2);
  c_phi_Resolution->cd(1);
  h_jet_phi_res_vs_eta->Draw("colz");
  c_phi_Resolution->cd(2);
  h_RMS_jet_phi_res_vs_eta->Draw();
  c_phi_Resolution->cd(3);
  h_MEAN_jet_phi_res_vs_eta->Draw();
  c_phi_Resolution->cd(4);
  h_jet_phi_res_vs_pT->Draw("colz");
  c_phi_Resolution->cd(5);
  h_RMS_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution->cd(6);
  h_MEAN_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution->SaveAs("c_phi_Resolution.png");
}

void Display_pTeta_covariantResolutionForFile(std::vector<TFile*> *v)
{
  TH3F *h_jet_pTres_vs_etares_vs_pT = (TH3F*)v->at(0)->Get("h_jet_pTres_vs_etares_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_pTres_vs_etares_vs_pT->Add((TH3F*)v->at(i)->Get("h_jet_pTres_vs_etares_vs_pT"));
  }
  h_jet_pTres_vs_etares_vs_pT->RebinX(2);
  TH1D *h_COVYZ_jet_pTres_vs_etares_vs_pT=COVYZ(h_jet_pTres_vs_etares_vs_pT);
  TCanvas *c_COVYZ_jet_pTres_vs_etares_vs_pT=new TCanvas("c_COVYZ_jet_pTres_vs_etares_vs_pT", "c_COVYZ_jet_pTres_vs_etares_vs_pT", 700, 700);
  h_COVYZ_jet_pTres_vs_etares_vs_pT->Draw();
  c_COVYZ_jet_pTres_vs_etares_vs_pT->SaveAs("c_COVYZ_jet_pTres_vs_etares_vs_pT.png");
}

void Display_mH_ForFile(TFile *f)
{
  TH1F *h_H1_mass=(TH1F*)f->Get("h_H1_mass");
  TH1F *h_H1_mass_biasCorrected=(TH1F*)f->Get("h_H1_mass_biasCorrected");
  
  TF1 *f_H1_mass=new TF1("f_H1_mass", "gaus", h_H1_mass->GetMean()-1*h_H1_mass->GetRMS(), h_H1_mass->GetMean()+1*h_H1_mass->GetRMS());
  TF1 *f_H1_mass_biasCorrected=new TF1("f_H1_mass_biasCorrected", "gaus", h_H1_mass_biasCorrected->GetMean()-1*h_H1_mass_biasCorrected->GetRMS(), h_H1_mass_biasCorrected->GetMean()+1*h_H1_mass_biasCorrected->GetRMS());
  
  h_H1_mass->Fit(f_H1_mass, "R");
  h_H1_mass_biasCorrected->Fit(f_H1_mass_biasCorrected, "R");
  
  h_H1_mass->SetLineColor(kBlue);
  f_H1_mass->SetLineColor(kBlue);
  h_H1_mass_biasCorrected->SetLineColor(kRed);
  f_H1_mass_biasCorrected->SetLineColor(kRed);
  
  
  h_H1_mass_biasCorrected->Draw("");
  h_H1_mass->Draw("same");
  
  TLegend *leg=new TLegend(0.6, 0.89, 0.89, 0.6);
  leg->AddEntry(h_H1_mass, ("#bar{x}="+ftoa(f_H1_mass->GetParameter(1))+", #sigma="+ftoa(f_H1_mass->GetParameter(2))).c_str());
  leg->AddEntry(h_H1_mass_biasCorrected, ("#bar{x}="+ftoa(f_H1_mass_biasCorrected->GetParameter(1))+", #sigma="+ftoa(f_H1_mass_biasCorrected->GetParameter(2))).c_str());
  leg->SetLineColor(0);
  leg->Draw();
  
} 

void DisplayKinFit()
{
  std::vector<TFile*> v_files;
  /*
  v_files.push_back(new TFile("Histograms_Radion260GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion270GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion300GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion350GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion400GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion450GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion500GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion550GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion600GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion650GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion700GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion800GeV.root"));
  v_files.push_back(new TFile("Histograms_Radion900GeV.root"));
  */
  v_files.push_back(new TFile("Histograms_Graviton260GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton300GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton600GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton800GeV.root"));
  std::vector <double> mean_gen={260, 300, 600, 800};
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit();
  
  
  Display_pT_Resolution(&v_files);
  /*Display_eta_ResolutionForFile(&v_files);
  Display_phi_ResolutionForFile(&v_files);
  Display_pTeta_covariantResolutionForFile(&v_files);
  */
  
  
  // std::vector <double> mean_gen={260, 270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900};
  std::vector <double> mean, mean_diff, sigma, sigma_kinFit;
  int dontwant=2;
  std::cout<<"Fitting peaks"<<std::endl;
  for (unsigned int i=dontwant; i<v_files.size(); ++i)
  {
    TH1F *h_mX_SR=(TH1F*)v_files.at(i)->Get("h_mX_SR");
    TH1F *h_mX_SR_kinFit=(TH1F*)v_files.at(i)->Get("h_mX_SR_kinFit");
    
    TF1 *f_Gauss0=new TF1("f_Gauss0", "gaus", h_mX_SR->GetMean()-(2*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(2*h_mX_SR->GetRMS()));
    f_Gauss0->SetParLimits(1, h_mX_SR->GetMean()-(2*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(2*h_mX_SR->GetRMS()));
    f_Gauss0->SetParLimits(2, 0, 50);
    h_mX_SR->Fit(f_Gauss0, "R");
    
    TF1 *f_Gauss1=new TF1("f_Gauss1", "gaus", h_mX_SR_kinFit->GetMean()-(2*h_mX_SR_kinFit->GetRMS()), h_mX_SR_kinFit->GetMean()+(2*h_mX_SR_kinFit->GetRMS()));
    f_Gauss1->SetParLimits(1, h_mX_SR_kinFit->GetMean()-(2*h_mX_SR_kinFit->GetRMS()), h_mX_SR_kinFit->GetMean()+(2*h_mX_SR_kinFit->GetRMS()));
    f_Gauss1->SetParLimits(2, 0, 50);
    h_mX_SR_kinFit->Fit(f_Gauss1, "R");
    
    TCanvas *c_Canvas=new TCanvas("c_Canvas", "c_Canvas", 1400, 700);
    c_Canvas->Divide(2,1);
    c_Canvas->cd(1);
    h_mX_SR->Draw();
    c_Canvas->cd(2);
    h_mX_SR_kinFit->Draw("same");
    c_Canvas->SaveAs(("c_Fit_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_Canvas;
    
    mean.push_back(f_Gauss0->GetParameter(1));
    mean_diff.push_back(f_Gauss1->GetParameter(1) - mean_gen.at(i)); // f_Gauss0->GetParameter(1));
    
    sigma.push_back(f_Gauss0->GetParameter(2)/f_Gauss0->GetParameter(1));
    sigma_kinFit.push_back(f_Gauss1->GetParameter(2)/f_Gauss1->GetParameter(1));
  }
  
  TGraph *g_KinFit_meanDiff=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(mean_diff.at(0)));
  g_KinFit_meanDiff->GetYaxis()->SetRangeUser(0, 50);
  g_KinFit_meanDiff->GetXaxis()->SetLimits(250, 1000);
  g_KinFit_meanDiff->SetTitle("; m_{X}^{gen} (GeV); m_{X}^{KinFit} - m_{X} (GeV)"); 
  TGraph *g_KinFit_sigma=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma.at(0)));
  g_KinFit_sigma->SetTitle("; m_{X}^{gen} (GeV); #sigma(m_{X})/m_{X}");
  g_KinFit_sigma->GetYaxis()->SetRangeUser(0., 0.08);
  g_KinFit_sigma->GetXaxis()->SetLimits(250, 1000);
  TGraph *g_KinFit_sigma_KinFit=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma_kinFit.at(0)));
  TCanvas *c_meanDiff=new TCanvas("c_meanDiff", "c_meanDiff", 700, 700);
  g_KinFit_meanDiff->Draw("A*");
  TF1 *f_g_0=new TF1("f_g_0", "pol0", 400, 950);
  g_KinFit_meanDiff->Fit(f_g_0, "R");
  c_meanDiff->SaveAs("c_meanDiff.png");
  c_meanDiff->SaveAs("c_meanDiff.root");
  TCanvas *c_sigma=new TCanvas("c_sigma", "c_sigma", 700, 700);
  g_KinFit_sigma->SetMarkerColor(kBlue);
  g_KinFit_sigma_KinFit->SetMarkerColor(kRed);
  g_KinFit_sigma->Draw("A*");
  g_KinFit_sigma_KinFit->Draw("* same");
  c_sigma->SaveAs("c_sigma.png");
  c_sigma->SaveAs("c_sigma.root");
  
  
  /*gStyle->SetOptFit(0);
  // Draw mH
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    TCanvas *c_mH=new TCanvas("c_mH", "c_mH", 700, 700);
    Display_mH_ForFile(v_files.at(i));
    c_mH->SaveAs(("c_mH_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH;
  }*/
  
  
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 700, 700);
  DisplayKinFitForFile(v_files.at(0), 260);
  // DisplayKinFitForFile(v_files.at(1), 270);
  DisplayKinFitForFile(v_files.at(1), 300);
  // DisplayKinFitForFile(v_files.at(3), 350);
  // DisplayKinFitForFile(v_files.at(4), 400);
  //DisplayKinFitForFile(v_files.at(5), 450);
  // DisplayKinFitForFile(v_files.at(6), 500);
  //DisplayKinFitForFile(v_files.at(7), 550);
  DisplayKinFitForFile(v_files.at(2), 600);
  //DisplayKinFitForFile(v_files.at(9), 650);
  // DisplayKinFitForFile(v_files.at(10), 700);
  DisplayKinFitForFile(v_files.at(3), 800);
  // DisplayKinFitForFile(v_files.at(12), 900);
  c_KinFit->SaveAs("c_KinFit.png");
  
  // Draw the smearing functions
  TCanvas *c_gaussian=new TCanvas("c_gaussian", "c_gaussian", 700, 700);
  TF1 *f_Gauss=new TF1("f_xgauss", asymmetricGaussian, -25*3, 25*3, 3);
  f_Gauss->SetParameter(0, 0);
  f_Gauss->SetParameter(1, 5);
  f_Gauss->SetParameter(2, 5);
  f_Gauss->Draw();
  c_gaussian->SaveAs("c_gaussian.png");
  
  TCanvas *c_asymGaussian=new TCanvas("c_asymGaussian", "c_asymGaussian", 700, 700);
  TF1 *f_asymGauss=new TF1("f_asymGauss", asymmetricGaussian, -25*3, 25*3, 3);
  f_asymGauss->SetParameter(0, 0);
  f_asymGauss->SetParameter(1, 25);
  f_asymGauss->SetParameter(2, 5);
  f_asymGauss->Draw();
  c_asymGaussian->SaveAs("c_asymGaussian.png");
  
  
}
