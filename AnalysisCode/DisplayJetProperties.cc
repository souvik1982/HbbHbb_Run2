#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TArrow.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

#include "TDRStyle.h"

bool first;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

// Display histogram for file 
void DisplayHistogram_forFile(TFile *file, std::string histogramName, int color)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());
  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.5);
    h->GetYaxis()->SetTitleOffset(1.6);
    h->Draw("hist");
    first=false;
  }
  h->Draw("hist same");
}

void DisplayJetProperties()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("Histograms_Graviton300GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton400GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton600GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton800GeV.root"));
  v_files.push_back(new TFile("Histograms_Graviton1000GeV.root"));
  TFile *f_data=new TFile("Histograms_Data_BTagCSV_2015_Skim.root");
  TFile *f_ttbar=new TFile("Histograms_TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim.root");
  std::vector <double> mean_gen={300, 400, 600, 800, 1000};
  std::vector<int> v_colors = {kGreen, kGreen+2, kOrange, kOrange+2, kMagenta, kMagenta+2, kBlue, kBlue+2, kCyan, kCyan+2};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  TLegend *leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    leg->AddEntry(v_files.at(i)->Get("h_pTOrder_JetpT_1"), ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
  }
  leg->AddEntry(f_data->Get("h_pTOrder_JetpT_1"), "13 TeV Data");
  leg->AddEntry(f_ttbar->Get("h_pTOrder_JetpT_1"), "t#bar{t}");
  
  // Plot the 1st highest pT jets with |eta| < 2.5  
  first=true;
  TCanvas *c_pTOrder_JetpT_1=new TCanvas("c_pTOrder_JetpT_1", "c_pTOrder_JetpT_1", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_1", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_1", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_1", kRed);
  leg->Draw();
  TArrow *line=new TArrow(40., 0.14, 40., 0); line->SetLineWidth(2);
  line->Draw();
  c_pTOrder_JetpT_1->SaveAs("c_pTOrder_JetpT_1.png");
  
  // Plot the 2nd highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTOrder_JetpT_2=new TCanvas("c_pTOrder_JetpT_2", "c_pTOrder_JetpT_2", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_2", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_2", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_2", kRed);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_2->SaveAs("c_pTOrder_JetpT_2.png");
  
  // Plot the 3rd highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTOrder_JetpT_3=new TCanvas("c_pTOrder_JetpT_3", "c_pTOrder_JetpT_3", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_3", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_3", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_3", kRed);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_3->SaveAs("c_pTOrder_JetpT_3.png");
  
  // Plot the 4th highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTOrder_JetpT_4=new TCanvas("c_pTOrder_JetpT_4", "c_pTOrder_JetpT_4", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_4", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_4", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_4", kRed);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_4->SaveAs("c_pTOrder_JetpT_4.png");
  
  // Plot the 5th highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTOrder_JetpT_5=new TCanvas("c_pTOrder_JetpT_5", "c_pTOrder_JetpT_5", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_5", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_5", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_5", kRed);
  leg->Draw();
  c_pTOrder_JetpT_5->SaveAs("c_pTOrder_JetpT_5.png");
  
  
  // Plot the 1st highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CSVOrder_JetCSV_1=new TCanvas("c_CSVOrder_JetCSV_1", "c_CSVOrder_JetCSV_1", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CSVOrder_JetCSV_1", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CSVOrder_JetCSV_1", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_CSVOrder_JetCSV_1", kRed);
  leg->Draw();
  line=new TArrow(0.898, 0.8, 0.898, 0); line->SetLineWidth(2);
  line->Draw();
  c_CSVOrder_JetCSV_1->SaveAs("c_CSVOrder_JetCSV_1.png");
  
  // Plot the 2nd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CSVOrder_JetCSV_2=new TCanvas("c_CSVOrder_JetCSV_2", "c_CSVOrder_JetCSV_2", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CSVOrder_JetCSV_2", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CSVOrder_JetCSV_2", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_CSVOrder_JetCSV_2", kRed);
  leg->Draw();
  line=new TArrow(0.898, 0.4, 0.898, 0); line->SetLineWidth(2);
  line->Draw();
  c_CSVOrder_JetCSV_2->SaveAs("c_CSVOrder_JetCSV_2.png");
  
  // Plot the 3rd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CSVOrder_JetCSV_3=new TCanvas("c_CSVOrder_JetCSV_3", "c_CSVOrder_JetCSV_3", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CSVOrder_JetCSV_3", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CSVOrder_JetCSV_3", kBlack);
  DisplayHistogram_forFile(f_ttbar, "h_CSVOrder_JetCSV_3", kRed);
  leg->Draw();
  line=new TArrow(0.898, 0.1, 0.898, 0); line->SetLineWidth(2);
  line->Draw();
  c_CSVOrder_JetCSV_3->SaveAs("c_CSVOrder_JetCSV_3.png");
  
  // Plot the 4th highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CSVOrder_JetCSV_4=new TCanvas("c_CSVOrder_JetCSV_4", "c_CSVOrder_JetCSV_4", 700, 700);
  DisplayHistogram_forFile(f_data, "h_CSVOrder_JetCSV_4", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CSVOrder_JetCSV_4", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_ttbar, "h_CSVOrder_JetCSV_4", kRed);
  leg->Draw();
  line=new TArrow(0.898, 0.05, 0.898, 0); line->SetLineWidth(2);
  line->Draw();
  c_CSVOrder_JetCSV_4->SaveAs("c_CSVOrder_JetCSV_4.png");
  
}
  
  
  
  
  
