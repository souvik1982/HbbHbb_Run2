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

void Display_pT_Resolution(std::vector<TFile*> *v)
{
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_0_1p4");
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5");
  h_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet p_{T}^{reco} - p_{T}^{parton} (GeV)");
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
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)");
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
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleSize(0.03);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_0_1p4", "pol1", 0, 700);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_MEAN_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=MEANY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; Jet p_{T}^{reco} (GeV); Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
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
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Draw();
  c_pT_Resolution_eta_0_1p4->cd(3);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Draw();
  c_pT_Resolution_eta_0_1p4->SaveAs("c_pT_Resolution_eta_0_1p4.png");
  
  TCanvas *c_pT_Resolution_eta_1p4_2p5=new TCanvas("c_pT_Resolution_eta_1p4_2p5", "c_pT_Resolution_eta_1p4_2p5", 2100, 700);
  c_pT_Resolution_eta_1p4_2p5->Divide(3,1);
  c_pT_Resolution_eta_1p4_2p5->cd(1);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->Draw("colz");
  c_pT_Resolution_eta_1p4_2p5->cd(2);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->Draw();
  c_pT_Resolution_eta_1p4_2p5->cd(3);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Draw();
  c_pT_Resolution_eta_1p4_2p5->SaveAs("c_pT_Resolution_eta_1p4_2p5.png");
}

void Display_eta_ResolutionForFile(std::vector<TFile*> *v)
{

  TH2F *h_jet_eta_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_eta_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_eta_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_eta_res_vs_pT"));
  }
  h_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-1, 1);
  h_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_jet_eta_res_vs_pT->RebinX(2);
  TH1D *h_RMS_jet_eta_res_vs_pT=RMSY(h_jet_eta_res_vs_pT);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.1);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitle("Jet #sigma(#eta^{reco} - #eta^{parton})");
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  
  TH1D *h_MEAN_jet_eta_res_vs_pT=MEANY(h_jet_eta_res_vs_pT);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitle("Jet <(#eta^{reco} - #eta^{parton}>");
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  
  TCanvas *c_eta_Resolution_pT=new TCanvas("c_eta_Resolution_pT", "c_eta_Resolution_pT", 2100, 700);
  c_eta_Resolution_pT->Divide(3,1);
  c_eta_Resolution_pT->cd(1);
  h_jet_eta_res_vs_pT->Draw("colz");
  c_eta_Resolution_pT->cd(2);
  h_MEAN_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->cd(3);
  h_RMS_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->SaveAs("c_eta_Resolution_pT.png");

  TH2F *h_jet_eta_res_vs_eta = (TH2F*)v->at(0)->Get("h_jet_eta_res_vs_eta");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_eta_res_vs_eta->Add((TH2F*)v->at(i)->Get("h_jet_eta_res_vs_eta"));
  }
  h_jet_eta_res_vs_eta->RebinX(1);
  TH1D *h_RMS_jet_eta_res_vs_eta=RMSY(h_jet_eta_res_vs_eta);
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetRangeUser(0, 0.1);
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetTitle("Jet #sigma(#eta^{reco} - #eta^{parton})");
  h_RMS_jet_eta_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f3=new TF1("f3", "pol1", 0, 2.5);
  h_RMS_jet_eta_res_vs_eta->Fit(f3, "R");
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_eta_res_vs_eta=MEANY(h_jet_eta_res_vs_eta);
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetRangeUser(-0.01, 0.01);
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetTitle("Jet <(#eta^{reco} - #eta^{parton}>");
  h_MEAN_jet_eta_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_eta_res_vs_eta=new TF1("f_MEAN_jet_eta_res_vs_eta", "pol1", 0, 2.5);
  h_MEAN_jet_eta_res_vs_eta->Fit(f_MEAN_jet_eta_res_vs_eta, "R");
  
  TCanvas *c_eta_Resolution=new TCanvas("c_eta_Resolution", "c_eta_Resolution", 2100, 700);
  c_eta_Resolution->Divide(3,1);
  c_eta_Resolution->cd(1);
  h_jet_eta_res_vs_eta->Draw("colz");
  c_eta_Resolution->cd(2);
  h_MEAN_jet_eta_res_vs_eta->Draw();
  c_eta_Resolution->cd(3);
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
  
  // Also create the bias distribution
  TH1D *h_MEAN_jet_phi_res_vs_eta=MEANY(h_jet_phi_res_vs_eta);
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetRangeUser(-0.01, 0.01);
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetTitle("Jet <(#phi^{reco} - #phi^{gen}>");
  h_MEAN_jet_phi_res_vs_eta->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_phi_res_vs_eta=new TF1("f_MEAN_jet_phi_res_vs_eta", "pol1", 0, 2.5);
  h_MEAN_jet_phi_res_vs_eta->Fit(f_MEAN_jet_phi_res_vs_eta, "R");
  
  TCanvas *c_phi_Resolution=new TCanvas("c_phi_Resolution", "c_phi_Resolution", 2100, 700);
  c_phi_Resolution->Divide(3,1);
  c_phi_Resolution->cd(1);
  h_jet_phi_res_vs_eta->Draw("colz");
  c_phi_Resolution->cd(2);
  h_RMS_jet_phi_res_vs_eta->Draw();
  c_phi_Resolution->cd(3);
  h_MEAN_jet_phi_res_vs_eta->Draw();
  c_phi_Resolution->SaveAs("c_phi_Resolution.png");
} 

void DisplayResolutionBias()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("ResolutionHistograms_Graviton260GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton270GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton300GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton400GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton600GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton800GeV.root"));
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit();
  
  Display_pT_Resolution(&v_files);
  Display_eta_ResolutionForFile(&v_files);
  Display_phi_ResolutionForFile(&v_files);
  
}
