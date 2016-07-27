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
 v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root"));
 // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
  //   v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
 v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
 //v_files.push_back(new TFile("Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
 v_files.push_back(new TFile("Histograms_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
  //v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
 // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1000_narrow_13TeV-madgraph.root"));
 // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1200_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1600_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-2000_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-3000_narrow_13TeV-madgraph.root"));
  TFile *f_data=new TFile("Histograms_BTagCSV.root");
  //TFile *f_ttbar=new TFile("Histograms_TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim.root");
  std::vector <double> mean_gen={260, 300, 350, 450, 550, 700, 800, 900, 1200};//, 1600, 2000, 3000};
  std::vector<int> v_colors = {kAzure+1, kAzure+3, kRed+1, kPink+1, kPink+3, kGreen+2, kGreen+3, kBlue+1, kGray+2};//, kCyan, kCyan+2};
  
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
 // leg->AddEntry(f_ttbar->Get("h_pTOrder_JetpT_1"), "t#bar{t}");
  
  // Plot the 1st highest pT jets with |eta| < 2.5  
  first=true;
  TCanvas *c_pTOrder_JetpT_1=new TCanvas("c_pTOrder_JetpT_1", "c_pTOrder_JetpT_1", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTOrder_JetpT_1", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_pTOrder_JetpT_1", kBlack);
  //DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_1", kRed);
  leg->Draw();
  TArrow *line=new TArrow(40., 0.14, 40., 0); line->SetLineWidth(3);
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
  //DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_2", kRed);
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
  //DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_3", kRed);
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
  //DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_4", kRed);
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
  //DisplayHistogram_forFile(f_ttbar, "h_pTOrder_JetpT_5", kRed);
  leg->Draw();
  c_pTOrder_JetpT_5->SaveAs("c_pTOrder_JetpT_5.png");
  
  
  // Plot the 1st highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_1=new TCanvas("c_CMVAOrder_JetCMVA_1", "c_CMVAOrder_JetCMVA_1", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_1", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_1", kBlack);
 //DisplayHistogram_forFile(f_ttbar, "h_CMVAOrder_JetCMVA_1", kRed);
  leg->Draw();
  line=new TArrow(0.185, 0.8, 0.185, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_1->SaveAs("c_CMVAOrder_JetCMVA_1.png");
  
  // Plot the 2nd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_2=new TCanvas("c_CMVAOrder_JetCMVA_2", "c_CMVAOrder_JetCMVA_2", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_2", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_2", kBlack);
 // DisplayHistogram_forFile(f_ttbar, "h_CMVAOrder_JetCMVA_2", kRed);
  leg->Draw();
  line=new TArrow(0.185, 0.4, 0.185, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_2->SaveAs("c_CMVAOrder_JetCMVA_2.png");
  
  // Plot the 3rd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_3=new TCanvas("c_CMVAOrder_JetCMVA_3", "c_CMVAOrder_JetCMVA_3", 700, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_3", v_colors.at(i));
  }
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_3", kBlack);
 // DisplayHistogram_forFile(f_ttbar, "h_CMVAOrder_JetCMVA_3", kRed);
  leg->Draw();
  line=new TArrow(0.185, 0.1, 0.185, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_3->SaveAs("c_CMVAOrder_JetCMVA_3.png");
  
  // Plot the 4th highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_4=new TCanvas("c_CMVAOrder_JetCMVA_4", "c_CMVAOrder_JetCMVA_4", 700, 700);
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_4", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_4", v_colors.at(i));
  }
 // DisplayHistogram_forFile(f_ttbar, "h_CMVAOrder_JetCMVA_4", kRed);
  leg->Draw();
  line=new TArrow(0.185, 0.1, 0.185, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_4->SaveAs("c_CMVAOrder_JetCMVA_4.png");
  
  
  // Plot the nCbJets distribution
  first=true;
  TCanvas *c_nCbJets=new TCanvas("c_nCbJets", "c_nCbJets", 700, 700);
  DisplayHistogram_forFile(f_data, "h_nCbJets", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_nCbJets", v_colors.at(i));
  }
  //DisplayHistogram_forFile(f_ttbar, "h_nCbJets", kRed);
  leg->Draw();
  line=new TArrow(4, 0.5, 4, 0); line->SetLineWidth(3);
  line->Draw();
  c_nCbJets->SaveAs("c_nCbJets.png");
  
  
  // Plot the dR distribution between gen b quarks from a Higgs
  first=true;
  TCanvas *c_dR_genHbb=new TCanvas("c_dR_genHbb", "c_dR_genHbb", 700, 700);
  for (unsigned int i=v_files.size()-1; i>0; --i)
  {
    ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Rebin(2);
    ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->GetXaxis()->SetRangeUser(0, 2.);
    DisplayHistogram_forFile(v_files.at(i), "h_dR_genHbb", v_colors.at(i));
    int binx0=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(0.);
    int binx1=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(0.4);
    int binx2=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(2.0);
    double integral1 = ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Integral(binx0, binx2);
    double integral2 = ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Integral(binx1, binx2);
    std::cout<<"mX = "<<mean_gen.at(i)<<", % of events with dR > 0.4 = "<<integral2/integral1*100.<<"%"<<std::endl;
  }
  leg->Draw();
  line=new TArrow(0.4, 0.12, 0.4, 0); line->SetLineWidth(3);
  line->Draw();
  c_dR_genHbb->SaveAs("c_dR_genHbb.png");
  
}
  
  
  
  
  
