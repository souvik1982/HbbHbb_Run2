#include <TH2F.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

void DisplaymH1vsmH2()
{
  TFile *f_Radion260GeV=new TFile("Histograms_Radion260GeV.root");
  
  TH2F *h_mH1_mH2_asym1=(TH2F*)f_Radion260GeV->Get("h_mH1_mH2_asym1");
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  
  TCanvas *c=new TCanvas("c", "c", 700, 700);
  h_mH1_mH2_asym1->Draw("colz");
  c->SaveAs("mH1vsmH2_asym1.png");
}
