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
    h->SetMinimum(0);
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

void DisplaymH_regressed()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));
  
  std::vector<TFile*> v_files_regressed;
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
  v_files_regressed.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));
  
  std::vector <double> mean_gen={260,300,400,500, 600, 700, 800, 1000, 1400};
  
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
    leg->AddEntry((TObject*)0, ("m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str(), "");
    first=true;
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass", kBlue, leg, "AK4");
    first=false;
    //DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass_biasCorrected", kRed, leg, "BiasCorr");
    DisplayHistogram_mH_forFile(v_files_regressed.at(i), "h_H1_mass", kGreen, leg, "Regressed");
    leg->Draw();
    c_H1_mass->SaveAs(("c_H1_mass_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_H1_mass;
  }
  
}
  
  
