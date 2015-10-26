#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

bool first=true;
void DisplayKinFitForFile(TFile *file, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_kinFit=(TH1F*)file->Get("h_mX_SR_kinFit");
  
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

void Display_pT_Resolution(std::vector<TFile*> *v)
{
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_0_1p4");
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5");
  h_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet p_{T}^{reco} - p_{T}^{gen} (GeV)");
  h_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.4);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_pT_res_vs_pT_eta_0_1p4->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_0_1p4"));
    h_jet_pT_res_vs_pT_eta_1p4_2p5->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5"));
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
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetTitleOffset(1.2);
  TF1 *f3=new TF1("f3", "pol1", 0, 2.5);
  h_RMS_jet_eta_res_vs_eta->Fit(f3, "R");
  
  TCanvas *c_eta_Resolution=new TCanvas("c_eta_Resolution", "c_eta_Resolution", 1400, 700);
  c_eta_Resolution->Divide(2,1);
  c_eta_Resolution->cd(1);
  h_jet_eta_res_vs_eta->Draw("colz");
  c_eta_Resolution->cd(2);
  h_RMS_jet_eta_res_vs_eta->Draw();
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
  h_RMS_jet_phi_res_vs_eta->GetYaxis()->SetTitleOffset(1.2);
  TF1 *f4=new TF1("f4", "pol1", 0, 2.5);
  h_RMS_jet_phi_res_vs_eta->Fit(f4, "R");
  
  TCanvas *c_phi_Resolution=new TCanvas("c_phi_Resolution", "c_phi_Resolution", 1400, 700);
  c_phi_Resolution->Divide(2,1);
  c_phi_Resolution->cd(1);
  h_jet_phi_res_vs_eta->Draw("colz");
  c_phi_Resolution->cd(2);
  h_RMS_jet_phi_res_vs_eta->Draw();
  c_phi_Resolution->SaveAs("c_phi_Resolution.png");
} 

void DisplayKinFit()
{
  std::vector<TFile*> v_files;
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
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit();
  
  
  // Display_pT_Resolution(&v_files);
  // Display_eta_ResolutionForFile(&v_files);
  // Display_phi_ResolutionForFile(&v_files);
  
  
  std::vector <double> mean, mean_diff, sigma, sigma_kinFit;
  for (unsigned int i=4; i<v_files.size(); ++i)
  {
    TH1F *h_mX_SR=(TH1F*)v_files.at(i)->Get("h_mX_SR");
    TH1F *h_mX_SR_kinFit=(TH1F*)v_files.at(i)->Get("h_mX_SR_kinFit");
    
    TF1 *f_Gauss0=new TF1("f_Gauss0", "gaus", h_mX_SR->GetMean()-(2*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(2*h_mX_SR->GetRMS()));
    h_mX_SR->Fit(f_Gauss0, "R");
    
    TF1 *f_Gauss1=new TF1("f_Gauss1", "gaus", h_mX_SR_kinFit->GetMean()-(2*h_mX_SR_kinFit->GetRMS()), h_mX_SR_kinFit->GetMean()+(2*h_mX_SR_kinFit->GetRMS()));
    h_mX_SR_kinFit->Fit(f_Gauss1, "R");
    
    mean.push_back(f_Gauss0->GetParameter(1));
    mean_diff.push_back(f_Gauss1->GetParameter(1) - f_Gauss0->GetParameter(1));
    
    sigma.push_back(f_Gauss0->GetParameter(2)/f_Gauss0->GetParameter(1));
    sigma_kinFit.push_back(f_Gauss1->GetParameter(2)/f_Gauss1->GetParameter(1));
  }
  
  TGraph *g_KinFit_meanDiff=new TGraph(v_files.size()-4, &(mean.at(0)), &(mean_diff.at(0)));
  g_KinFit_meanDiff->GetXaxis()->SetLimits(500, 1000);
  g_KinFit_meanDiff->SetTitle("; m_{X} w/o KinFit (GeV); m_{X}^{KinFit} - m_{X} (GeV)"); 
  TGraph *g_KinFit_sigma=new TGraph(v_files.size()-4, &(mean.at(0)), &(sigma.at(0)));
  g_KinFit_sigma->SetTitle("; m_{X} without KinFit (GeV); #sigma(m_{X})/m_{X}");
  g_KinFit_sigma->GetYaxis()->SetRangeUser(0., 0.08);
  g_KinFit_sigma->GetXaxis()->SetLimits(500, 1000);
  TGraph *g_KinFit_sigma_KinFit=new TGraph(v_files.size()-4, &(mean.at(0)), &(sigma_kinFit.at(0)));
  TCanvas *c_meanDiff=new TCanvas("c_meanDiff", "c_meanDiff", 700, 700);
  g_KinFit_meanDiff->Draw("A*");
  TF1 *f_g_0=new TF1("f_g_0", "pol1", 250, 950);
  g_KinFit_meanDiff->Fit(f_g_0, "R");
  c_meanDiff->SaveAs("c_meanDiff.png");
  TCanvas *c_sigma=new TCanvas("c_sigma", "c_sigma", 700, 700);
  g_KinFit_sigma->SetMarkerColor(kBlue);
  g_KinFit_sigma_KinFit->SetMarkerColor(kRed);
  g_KinFit_sigma->Draw("A*");
  g_KinFit_sigma_KinFit->Draw("* same");
  c_sigma->SaveAs("c_sigma.png");
  
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 700, 700);
  // DisplayKinFitForFile(v_files.at(0), 260);
  // DisplayKinFitForFile(v_files.at(1), 270);
  DisplayKinFitForFile(v_files.at(2), 300);
  // DisplayKinFitForFile(v_files.at(3), 350);
  DisplayKinFitForFile(v_files.at(4), 400);
  //DisplayKinFitForFile(v_files.at(5), 450);
  DisplayKinFitForFile(v_files.at(6), 500);
  //DisplayKinFitForFile(v_files.at(7), 550);
  DisplayKinFitForFile(v_files.at(8), 600);
  //DisplayKinFitForFile(v_files.at(9), 650);
  DisplayKinFitForFile(v_files.at(10), 700);
  DisplayKinFitForFile(v_files.at(11), 800);
  DisplayKinFitForFile(v_files.at(12), 900);
  c_KinFit->SaveAs("c_KinFit.png");
  
}
