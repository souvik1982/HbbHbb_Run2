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

#include "../TDRStyle.h"

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
  h_jet_pT_res_vs_pT_eta_0_1p4->RebinX(2);
  h_jet_pT_res_vs_pT_eta_0_1p4->RebinY(2);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 800);
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_0_1p4=MEANY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetRangeUser(-20, 100);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_0_1p4", "pol2", 40, 600);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_MEAN_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_0_1p4=RMSY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)");
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetRangeUser(0, 70);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_RMS_jet_pT_res_vs_pT_eta_0_1p4", "pol1", 40, 600);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_RMS_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  h_jet_pT_res_vs_pT_eta_1p4_2p5->RebinX(2);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->RebinY(2);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 500);
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=MEANY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetRangeUser(-20, 100);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5", "pol2", 40, 420);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5, "R");
  
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=RMSY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)");
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetRangeUser(0, 70);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=new TF1("f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5", "pol1", 40, 420);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5, "R");
  
  
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
  h_jet_eta_res_vs_pT->RebinX(2);
  h_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-1, 1);
  h_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet (#eta^{reco} - #eta^{parton})");
  h_jet_eta_res_vs_pT->GetXaxis()->SetTitleOffset(1.4);
  h_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  
  TH1D *h_MEAN_jet_eta_res_vs_pT=MEANY(h_jet_eta_res_vs_pT);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet <(#eta^{reco} - #eta^{parton})>");
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_eta_res_vs_pT=new TF1("f_MEAN_jet_eta_res_vs_pT", "pol0", 40, 600);
  h_MEAN_jet_eta_res_vs_pT->Fit(f_MEAN_jet_eta_res_vs_pT, "R");
  
  TH1D *h_RMS_jet_eta_res_vs_pT=RMSY(h_jet_eta_res_vs_pT);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.1);
  h_RMS_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet #sigma(#eta^{reco} - #eta^{parton})");
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_RMS_jet_eta_res_vs_pT=new TF1("f_RMS_jet_eta_res_vs_pT", "[0]+[1]/x", 40, 600);
  h_RMS_jet_eta_res_vs_pT->Fit(f_RMS_jet_eta_res_vs_pT, "R");
  
  TCanvas *c_eta_Resolution_pT=new TCanvas("c_eta_Resolution_pT", "c_eta_Resolution_pT", 2100, 700);
  c_eta_Resolution_pT->Divide(3,1);
  c_eta_Resolution_pT->cd(1);
  h_jet_eta_res_vs_pT->Draw("colz");
  c_eta_Resolution_pT->cd(2);
  h_MEAN_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->cd(3);
  h_RMS_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->SaveAs("c_eta_Resolution_pT.png");

}

void Display_phi_ResolutionForFile(std::vector<TFile*> *v)
{
  TH2F *h_jet_phi_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_phi_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_phi_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_phi_res_vs_pT"));
  }
  h_jet_phi_res_vs_pT->RebinX(2);
  h_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(-1, 1);
  h_jet_phi_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet (#phi^{reco} - #phi^{parton})");
  h_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  
  TH1D *h_MEAN_jet_phi_res_vs_pT=MEANY(h_jet_phi_res_vs_pT);
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(#phi^{reco} - #phi^{parton})>");
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_phi_res_vs_pT=new TF1("f_MEAN_jet_phi_res_vs_pT", "pol0", 40, 600);
  h_MEAN_jet_phi_res_vs_pT->Fit(f_MEAN_jet_phi_res_vs_pT, "R");
  
  TH1D *h_RMS_jet_phi_res_vs_pT=RMSY(h_jet_phi_res_vs_pT);
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.15);
  h_RMS_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(#phi^{reco} - #phi^{parton})");
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_phi_res_vs_pT=new TF1("f_RMS_jet_phi_res_vs_pT", "[0] + [1]/x", 40, 600);
  h_RMS_jet_phi_res_vs_pT->Fit(f_RMS_jet_phi_res_vs_pT, "R");
  
  TCanvas *c_phi_Resolution_pT=new TCanvas("c_phi_Resolution_pT", "c_phi_Resolution_pT", 2100, 700);
  c_phi_Resolution_pT->Divide(3,1);
  c_phi_Resolution_pT->cd(1);
  h_jet_phi_res_vs_pT->Draw("colz");
  c_phi_Resolution_pT->cd(2);
  h_MEAN_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution_pT->cd(3);
  h_RMS_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution_pT->SaveAs("c_phi_Resolution_pT.png");
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
  v_files.push_back(new TFile("ResolutionHistograms_Graviton1000GeV.root"));
  v_files.push_back(new TFile("ResolutionHistograms_Graviton1200GeV.root"));
  
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  myStyle->SetOptFit();
  
  Display_pT_Resolution(&v_files);
  Display_eta_ResolutionForFile(&v_files);
  Display_phi_ResolutionForFile(&v_files);
  
}
