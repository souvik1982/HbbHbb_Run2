#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <TStyle.h>
#include <THStack.h>
#include <TArrow.h>
#include <TArc.h>

#include "TDRStyle.h"

bool first;

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

// Display histogram for file 
void DisplayHistogram_mH_forFile(TFile *file, std::string histogramName, int color, TLegend *leg, std::string name)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());
  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  h->Rebin(2);
  h->GetXaxis()->SetRangeUser(50, 250);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.2);
    h->GetYaxis()->SetTitleOffset(1.6);
    h->Draw("");
    first=false;
  }
  h->Draw("same");
  TF1 *f=new TF1("f", "gaus", h->GetMean()-(1.5*h->GetRMS()), h->GetMean()+(1.5*h->GetRMS()));
  f->SetParLimits(1, h->GetMean()-(3*h->GetRMS()), h->GetMean()+(3*h->GetRMS()));
  f->SetParLimits(2, 0, 3*h->GetRMS());
  f->SetLineColor(color);
  h->Fit(f, "R");
  leg->AddEntry(h, (name+" #bar{x}="+ftoa(f->GetParameter(1))+", #sigma="+ftoa(f->GetParameter(2))).c_str());
}

void DisplaymH_regressed_biasCorrected()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton300GeV.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton400GeV.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton600GeV.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton800GeV.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton1000GeV.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Graviton1200GeV.root"));
  
  std::vector<TFile*> v_files_regressed;
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton300GeV_regressed.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton400GeV_regressed.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton600GeV_regressed.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton800GeV_regressed.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton1000GeV_regressed.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection/Histograms_Graviton1200GeV_regressed.root"));
  
  std::vector <double> mean_gen={300, 400, 600, 800, 1000, 1200};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  // Plot mH1
  for (int i=v_files.size()-1; i>=0; --i)
  {
    TCanvas *c_H1_mass=new TCanvas("c_H1_mass", "c_H1_mass", 700, 700);
    TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    first=true;
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass", kBlue, leg, "AK4");
    first=false;
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass_biasCorrected", kRed, leg, "BiasCorr");
    DisplayHistogram_mH_forFile(v_files_regressed.at(i), "h_H1_mass", kGreen, leg, "Regressed");
    leg->Draw();
    c_H1_mass->SaveAs(("c_H1_mass_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_H1_mass;
  }
  
}
  
  
