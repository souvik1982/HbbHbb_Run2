#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TArrow.h>
#include <TArc.h>

#include "../TDRStyle.h"

bool signalpoints=true;
bool data=false;
bool ttbar=false;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void drawRegion(double H_mass, double r1)
{
  TArc *circle1=new TArc(H_mass, H_mass, r1); 
  circle1->SetLineWidth(3); 
  circle1->SetLineColor(kBlack); 
  circle1->SetFillStyle(0);
  circle1->Draw();
}

void DisplaymH1vsmH2_ForFile(TFile *file)
{
  TH2F *h_mH1_mH2_asym=(TH2F*)file->Get("h_mH1_mH2_asym");
  h_mH1_mH2_asym->Draw("colz");
  drawRegion(125, 17.5);
}

void DisplaymH1vsmH2_biasCorrectedForFile(TFile *file)
{
  TH2F *h_mH1_mH2_asym_biasCorrected=(TH2F*)file->Get("h_mH1_mH2_asym_biasCorrected");
  h_mH1_mH2_asym_biasCorrected->Draw("colz");
  drawRegion(125, 17.5);
}

void DisplaymH1vsmH2()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("Histograms_Graviton260GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton270GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton300GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton400GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton600GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton800GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton1000GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton1200GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton1600GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton2000GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton3000GeV.root"));
  std::vector <double> mean_gen={260, 270, 300, 400, 600, 800, 1000};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  for (unsigned int i=3; i<v_files.size(); ++i)
  {
    TCanvas *c_mH1_mH2_asym=new TCanvas("c_mH1_mH2_asym", "c_mH1_mH2_asym", 700, 700);
    DisplaymH1vsmH2_ForFile(v_files.at(i));
    c_mH1_mH2_asym->SaveAs(("c_mH1_mH2_asym_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH1_mH2_asym;
    
    TCanvas *c_mH1_mH2_asym_biasCorrected=new TCanvas("c_mH1_mH2_asym_biasCorrected", "c_mH1_mH2_asym_biasCorrected", 700, 700);
    DisplaymH1vsmH2_biasCorrectedForFile(v_files.at(i));
    c_mH1_mH2_asym_biasCorrected->SaveAs(("c_mH1_mH2_asym_biasCorrected_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH1_mH2_asym_biasCorrected;
  }
}    
  
