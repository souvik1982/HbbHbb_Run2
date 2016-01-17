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

#include "TDRStyle.h"

double mean_H1_mass_=124;
double sigma_H1_mass_=15; // 12;
double mean_H2_mass_=117;
double sigma_H2_mass_=20; // 13;

double chi_1=1;
double chi_2=2;

double marg=19;

bool signalpoints=true;
bool data=false;
bool ttbar=false;

bool first;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

// Display histogram for file 
void DisplayHistogram_mH_forFile(TFile *file, std::string histogramName, int color)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());
  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  h->Rebin(2);
  h->GetXaxis()->SetRangeUser(50, 200);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.2);
    h->GetYaxis()->SetTitleOffset(1.6);
    h->Draw("hist");
    first=false;
  }
  h->Draw("hist same");
}

void drawRegion(bool isData=false)
{
  TEllipse *circle1=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_1, sigma_H2_mass_*chi_1); 
  circle1->SetLineWidth(3); 
  circle1->SetLineColor(kBlack);
  circle1->SetFillColor(kRed);
  if (!isData) circle1->SetFillStyle(0);
  circle1->Draw();
  
  TEllipse *circle2=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 90., 180.); circle2->SetLineWidth(3); circle2->SetNoEdges(); circle2->SetLineColor(kBlack); circle2->SetFillStyle(0); circle2->Draw();
  TEllipse *circle3=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 270., 360.); circle3->SetLineWidth(3); circle3->SetNoEdges(); circle3->SetLineColor(kBlack); circle3->SetFillStyle(0); circle3->Draw();
  TLine *line1=new TLine(mean_H1_mass_-sigma_H1_mass_*chi_2, mean_H2_mass_, mean_H1_mass_-sigma_H1_mass_*chi_1, mean_H2_mass_); line1->SetLineWidth(3); line1->SetLineColor(kBlack); line1->Draw();
  TLine *line2=new TLine(mean_H1_mass_+sigma_H1_mass_*chi_2, mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_1, mean_H2_mass_); line2->SetLineWidth(3); line2->SetLineColor(kBlack); line2->Draw();
  TLine *line3=new TLine(mean_H1_mass_, mean_H2_mass_-sigma_H2_mass_*chi_2, mean_H1_mass_, mean_H2_mass_-sigma_H2_mass_*chi_1); line3->SetLineWidth(3); line3->SetLineColor(kBlack); line3->Draw();
  TLine *line4=new TLine(mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_2, mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_1); line4->SetLineWidth(3); line4->SetLineColor(kBlack); line4->Draw();
  
  TArrow *arrow1=new TArrow(mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_2*4., mean_H1_mass_, mean_H2_mass_, 0.02); arrow1->SetLineWidth(3); arrow1->SetLineColor(kBlack); arrow1->Draw();
  TPaveText *mod1=new TPaveText(mean_H1_mass_-marg, mean_H2_mass_+sigma_H2_mass_*chi_2*4.-marg, mean_H1_mass_+marg, mean_H2_mass_+sigma_H2_mass_*chi_2*4.+marg);
  mod1->SetBorderSize(0); mod1->SetFillColor(0); mod1->AddText("SR"); mod1->SetLineColor(kBlue); mod1->Draw("ARC");
  TArrow *arrow2_1=new TArrow(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_-sigma_H1_mass_*chi_2/2., mean_H2_mass_+sigma_H2_mass_*chi_2/2., 0.02); arrow2_1->SetLineWidth(3); arrow2_1->SetLineColor(kBlack);     
  TArrow *arrow2_2=new TArrow(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_2/2., mean_H2_mass_-sigma_H2_mass_*chi_2/2., 0.02); arrow2_2->SetLineWidth(3); arrow2_2->SetLineColor(kBlack);
  TLine *arrow2_3=new TLine(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_2*5., mean_H2_mass_); arrow2_3->SetLineWidth(3); arrow2_3->SetLineColor(kBlack);
  arrow2_1->Draw(); arrow2_2->Draw(); arrow2_3->Draw();
  TPaveText *mod2=new TPaveText(mean_H1_mass_+sigma_H1_mass_*chi_2*5.-marg, mean_H2_mass_+marg, mean_H1_mass_+sigma_H1_mass_*chi_2*5.+marg, mean_H2_mass_-marg);
  mod2->SetBorderSize(0); mod2->SetFillColor(0); mod2->AddText("SB"); mod2->SetLineColor(kBlack); mod2->Draw("ARC");
  
}

void DisplaymH1vsmH2_ForFile(TFile *file, bool isData=false)
{
  TH2F *h_mH1_mH2_asym=(TH2F*)file->Get("h_mH1_mH2_asym");
  h_mH1_mH2_asym->RebinX(2);
  h_mH1_mH2_asym->RebinY(2);
  h_mH1_mH2_asym->Draw("colz");
  drawRegion(isData);
}

void DisplaymHmX(std::vector<std::string> files)
{
  std::vector<TFile*> v_files;
  for (unsigned int i=0; i<files.size(); ++i) v_files.push_back(new TFile(files.at(i).c_str()));
  TFile *f_data=new TFile("Histograms_Data_BTagCSV_2015_Skim.root");
  TFile *f_ttbar=new TFile("Histograms_TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim.root");
  std::vector <double> mean_gen={300, 400, 600, 800, 1000, 1200, 1600};
  std::vector<int> v_colors = {kGreen, kGreen+2, kOrange, kOrange+2, kMagenta, kMagenta+2, kBlue, kBlue+2, kCyan, kCyan+2};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  TLegend *leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    TH1F *h_pTOrder_JetpT_1=(TH1F*)v_files.at(i)->Get("h_pTOrder_JetpT_1");
    h_pTOrder_JetpT_1->SetLineColor(v_colors.at(i));
    h_pTOrder_JetpT_1->SetLineWidth(2);
    leg->AddEntry(h_pTOrder_JetpT_1, ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
  }
  h_pTOrder_JetpT_1=(TH1F*)f_data->Get("h_pTOrder_JetpT_1");
  h_pTOrder_JetpT_1->SetLineColor(kBlack);
  h_pTOrder_JetpT_1->SetLineWidth(2);
  leg->AddEntry(h_pTOrder_JetpT_1, "13 TeV Data");
  h_pTOrder_JetpT_1=(TH1F*)f_ttbar->Get("h_pTOrder_JetpT_1");
  h_pTOrder_JetpT_1->SetLineColor(kRed);
  h_pTOrder_JetpT_1->SetLineWidth(2);
  leg->AddEntry(h_pTOrder_JetpT_1, "t#bar{t}");
  
  // Plot mH1
  first=true;
  TCanvas *c_H1_mass=new TCanvas("c_H1_mass", "c_H1_mass", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass", v_colors.at(i));
  }
  DisplayHistogram_mH_forFile(f_data, "h_H1_mass", kBlack);
  DisplayHistogram_mH_forFile(f_ttbar, "h_H1_mass", kRed);
  leg->Draw();
  c_H1_mass->SaveAs("c_H1_mass.png");
  delete c_H1_mass;
  
  first=true;
  TCanvas *c_H1_mass_biasCorrected=new TCanvas("c_H1_mass_biasCorrected", "c_H1_mass_biasCorrected", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass_biasCorrected", v_colors.at(i));
  }
  DisplayHistogram_mH_forFile(f_data, "h_H1_mass_biasCorrected", kBlack);
  DisplayHistogram_mH_forFile(f_ttbar, "h_H1_mass_biasCorrected", kRed);
  leg->Draw();
  c_H1_mass_biasCorrected->SaveAs("c_H1_mass_biasCorrected.png");
  delete c_H1_mass_biasCorrected;
  
  // Plot mH2
  first=true;
  TCanvas *c_H2_mass=new TCanvas("c_H2_mass", "c_H2_mass", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H2_mass", v_colors.at(i));
  }
  DisplayHistogram_mH_forFile(f_data, "h_H2_mass", kBlack);
  DisplayHistogram_mH_forFile(f_ttbar, "h_H2_mass", kRed);
  leg->Draw();
  c_H2_mass->SaveAs("c_H2_mass.png");
  delete c_H2_mass;
  
  first=true;
  TCanvas *c_H2_mass_biasCorrected=new TCanvas("c_H2_mass_biasCorrected", "c_H2_mass_biasCorrected", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H2_mass_biasCorrected", v_colors.at(i));
  }
  DisplayHistogram_mH_forFile(f_data, "h_H2_mass_biasCorrected", kBlack);
  DisplayHistogram_mH_forFile(f_ttbar, "h_H2_mass_biasCorrected", kRed);
  leg->Draw();
  c_H2_mass_biasCorrected->SaveAs("c_H2_mass_biasCorrected.png");
  delete c_H2_mass_biasCorrected;
  
  
  // Plot mH1 vs mH2
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    TCanvas *c_mH1_mH2_asym=new TCanvas("c_mH1_mH2_asym", "c_mH1_mH2_asym", 700, 700);
    DisplaymH1vsmH2_ForFile(v_files.at(i));
    c_mH1_mH2_asym->SaveAs(("c_mH1_mH2_asym_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH1_mH2_asym;
  }
  
  TCanvas *c_mH1_mH2_asym_Data=new TCanvas("c_mH1_mH2_asym_Data", "c_mH1_mH2_asym_Data", 700, 700);
  DisplaymH1vsmH2_ForFile(f_data, true);
  c_mH1_mH2_asym_Data->SaveAs("c_mH1_mH2_asym_Data.png");
  delete c_mH1_mH2_asym_Data;
  
  TCanvas *c_mH1_mH2_asym_ttbar=new TCanvas("c_mH1_mH2_asym_ttbar", "c_mH1_mH2_asym_ttbar", 700, 700);
  DisplaymH1vsmH2_ForFile(f_ttbar);
  c_mH1_mH2_asym_ttbar->SaveAs("c_mH1_mH2_asym_ttbar.png");
  delete c_mH1_mH2_asym_ttbar;
  
  
  // Plot mX in SB region for Data and ttbar
  first=true;
  double lumi=2150; // /pb
  double xsec_ttbar=831.76; // pb
  double init_ttbar=((TH1F*)f_ttbar->Get("Count"))->GetBinContent(1);
  TH1F *h_mX_SB_kinFit_data=(TH1F*)f_data->Get("h_mX_SB_kinFit");
  TH1F *h_mX_SB_kinFit_ttbar=(TH1F*)f_ttbar->Get("h_mX_SB_kinFit");
  h_mX_SB_kinFit_data->Rebin(40);
  h_mX_SB_kinFit_ttbar->Rebin(40);
  h_mX_SB_kinFit_data->GetXaxis()->SetRangeUser(150, 1600);
  h_mX_SB_kinFit_ttbar->GetXaxis()->SetRangeUser(150, 1600);
  h_mX_SB_kinFit_data->SetLineColor(kBlack);
  h_mX_SB_kinFit_ttbar->SetLineColor(kRed+2);
  h_mX_SB_kinFit_ttbar->SetFillColor(kRed);
  h_mX_SB_kinFit_data->SetLineWidth(2);
  h_mX_SB_kinFit_ttbar->SetLineWidth(2);
  h_mX_SB_kinFit_ttbar->Scale(lumi*xsec_ttbar/init_ttbar);
  TCanvas *c_mX_SB_kinFit=new TCanvas("c_mX_SB_kinFit", "c_mX_SB_kinFit", 700, 700);
  h_mX_SB_kinFit_data->Draw("ep9");
  h_mX_SB_kinFit_ttbar->Draw("hist same");
  leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  leg->AddEntry(h_mX_SB_kinFit_data, "13 TeV Data");
  leg->AddEntry(h_mX_SB_kinFit_ttbar, "t#bar{t} MC at NLO");
  leg->Draw();
  c_mX_SB_kinFit->SaveAs("c_mX_SB_kinFit.png");
  int bin1=h_mX_SB_kinFit_data->FindBin(200.);
  int bin2=h_mX_SB_kinFit_data->FindBin(1600.);
  double nDataEvents=h_mX_SB_kinFit_data->Integral(bin1, bin2);
  double nttbarEvents=h_mX_SB_kinFit_ttbar->Integral(bin1, bin2);
  std::cout<<"nttbarEvents/nDataEvents = "<<nttbarEvents<<"/"<<nDataEvents<<" = "<<nttbarEvents/nDataEvents<<std::endl;
  
}    
  
