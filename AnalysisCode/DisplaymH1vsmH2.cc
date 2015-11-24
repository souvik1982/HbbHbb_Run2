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

double mean_H1_mass_=132;
double sigma_H1_mass_=12;
double mean_H2_mass_=128;
double sigma_H2_mass_=13;
double chi_1=1;
double chi_2=2;

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



void drawRegion()
{
  TEllipse *circle1=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_1, sigma_H2_mass_*chi_1); 
  circle1->SetLineWidth(3); 
  circle1->SetLineColor(kBlack); 
  circle1->SetFillStyle(0);
  circle1->Draw();
  
  TEllipse *circle2=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 90., 180.); circle2->SetLineWidth(2); circle2->SetNoEdges(); circle2->SetLineColor(kBlack); circle2->SetFillStyle(0); circle2->Draw();
  TEllipse *circle3=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 270., 360.); circle3->SetLineWidth(3); circle3->SetNoEdges(); circle3->SetLineColor(kBlack); circle3->SetFillStyle(0); circle3->Draw();
  /*TLine *line1=new TLine(H_mass-r2, H_mass, H_mass-r1, H_mass); line1->SetLineWidth(2); line1->SetLineColor(kBlack); line1->Draw();
  TLine *line2=new TLine(H_mass+r2, H_mass, H_mass+r1, H_mass); line2->SetLineWidth(2); line2->SetLineColor(kBlack); line2->Draw();
  TLine *line3=new TLine(H_mass, H_mass-r2, H_mass, H_mass-r1); line3->SetLineWidth(2); line3->SetLineColor(kBlack); line3->Draw();
  TLine *line4=new TLine(H_mass, H_mass+r2, H_mass, H_mass+r1); line4->SetLineWidth(2); line4->SetLineColor(kBlack); line4->Draw();
  TArrow *arrow1=new TArrow(H_mass, H_mass+r2*5, H_mass, H_mass, 0.02); arrow1->SetLineWidth(2); arrow1->SetLineColor(kBlack); arrow1->Draw();
  TPaveText *mod1=new TPaveText(H_mass-marg, H_mass+r2*5-marg, H_mass+marg, H_mass+r2*5+marg);
  mod1->SetBorderSize(0); mod1->SetFillColor(0); mod1->AddText(sr.c_str()); mod1->SetLineColor(kBlue); mod1->Draw("ARC");
  TArrow *arrow2_1=new TArrow(H_mass+r2*4., H_mass, H_mass-r2/2., H_mass+r2/2., 0.02); arrow2_1->SetLineWidth(2); arrow2_1->SetLineColor(kBlack);     
  TArrow *arrow2_2=new TArrow(H_mass+r2*4., H_mass, H_mass+r2/2., H_mass-r2/2., 0.02); arrow2_2->SetLineWidth(2); arrow2_2->SetLineColor(kBlack);
  TLine *arrow2_3=new TLine(H_mass+r2*4., H_mass, H_mass+r2*5., H_mass); arrow2_3->SetLineWidth(2); arrow2_3->SetLineColor(kBlack);
  arrow2_1->Draw(); arrow2_2->Draw(); arrow2_3->Draw();
  TPaveText *mod2=new TPaveText(H_mass+r2*5.-marg, H_mass+marg, H_mass+r2*5.+marg, H_mass-marg);
  mod2->SetBorderSize(0); mod2->SetFillColor(0); mod2->AddText(cr.c_str()); mod2->SetLineColor(kBlack); mod2->Draw("ARC");*/
  
}

void DisplaymH1vsmH2_ForFile(TFile *file)
{
  TH2F *h_mH1_mH2_asym=(TH2F*)file->Get("h_mH1_mH2_asym");
  h_mH1_mH2_asym->Draw("colz");
  drawRegion();
}

void DisplaymH1vsmH2_biasCorrectedForFile(TFile *file)
{
  TH2F *h_mH1_mH2_asym_biasCorrected=(TH2F*)file->Get("h_mH1_mH2_asym_biasCorrected");
  h_mH1_mH2_asym_biasCorrected->Draw("colz");
  drawRegion();
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
  v_files.push_back(new TFile("Histograms_Graviton1200GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton1600GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton2000GeV.root"));
  // v_files.push_back(new TFile("Histograms_Graviton3000GeV.root"));
  std::vector <double> mean_gen={260, 270, 300, 400, 600, 800, 1000, 1200};
  
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
  
