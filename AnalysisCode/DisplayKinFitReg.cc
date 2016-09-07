#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

#include "TDRStyle.h"

bool first=true;

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

void DisplayKinFitForFile(TFile *file, TFile *fileR, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_kf=(TH1F*)file->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_kf");
  TH1F *h_mX_SR_kf_reg=(TH1F*)fileR->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_kf_reg");

  
  h_mX_SR->Rebin(10);
  h_mX_SR_kf->Rebin(10);
  h_mX_SR_kf_reg->Rebin(10);
  h_mX_SR->GetXaxis()->SetRangeUser(200, 1000);
  h_mX_SR_kf->GetXaxis()->SetRangeUser(200, 1000);
  h_mX_SR_kf_reg->GetXaxis()->SetRangeUser(200, 1000);
  
  h_mX_SR->SetLineWidth(2);
  h_mX_SR_kf->SetLineWidth(2);
  h_mX_SR_kf_reg->SetLineWidth(2);
  
  h_mX_SR->SetLineColor(kBlack);
//  h_mX_SR->Smooth(100);
  h_mX_SR->SetLineStyle(7);
  h_mX_SR_kf->SetLineColor(kBlue+1);
  h_mX_SR_kf->SetLineStyle(7);
 // h_mX_SR_kf_reg->Smooth(200);
  h_mX_SR_kf_reg->SetLineColor(kRed+1);
  
  if (first)
  {
    h_mX_SR_kf_reg->GetYaxis()->SetTitle("Normalized Units");
    h_mX_SR_kf_reg->GetYaxis()->SetTitleOffset(1.4);
    TH1* tmp = h_mX_SR_kf_reg->DrawNormalized("hist");
    tmp->SetMaximum(0.35);
    h_mX_SR_kf_reg->SetMaximum(h_mX_SR_kf_reg->GetMaximum()*1.4);
    TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_mX_SR, "m_{X} Signal Peak");
    leg->AddEntry(h_mX_SR_kf, "m_{X} w/ Kinematic Fit");
    leg->AddEntry(h_mX_SR_kf_reg, "m_{X} w/ Kinematic Fit + Reg.");
    leg->Draw();
    first=false;
  }
  else h_mX_SR_kf_reg->DrawNormalized("hist same");
  h_mX_SR_kf->DrawNormalized("hist same");
  h_mX_SR->DrawNormalized("hist same");
  
  TLine *line=new TLine(xLine, 0, xLine, 0.25);
  line->Draw();
  
}

void Display_mH1_ForFile(TFile *f, TFile *fR, double &mean_H1, double &sigma_H1)
{
  TH1F *h_H1_mass=(TH1F*)f->Get("h_H1_mass");
  TH1F *h_H1_mass_reg=(TH1F*)fR->Get("h_H1_mass");
  
  TF1 *f_H1_mass=new TF1("f_H1_mass", "gaus", h_H1_mass->GetMean()-1*h_H1_mass->GetRMS(), h_H1_mass->GetMean()+1*h_H1_mass->GetRMS());
  TF1 *f_H1_mass_reg=new TF1("f_H1_mass_reg", "gaus", h_H1_mass_reg->GetMean()-1*h_H1_mass_reg->GetRMS(), h_H1_mass_reg->GetMean()+1*h_H1_mass_reg->GetRMS());
  
  h_H1_mass->Rebin(2);
  h_H1_mass_reg->Rebin(2);
  
  h_H1_mass->GetXaxis()->SetRangeUser(50, 200);
  h_H1_mass_reg->GetXaxis()->SetRangeUser(50, 200);
  
  h_H1_mass->Fit(f_H1_mass, "R");
  h_H1_mass_reg->Fit(f_H1_mass_reg, "R");
  
  h_H1_mass->SetLineColor(kBlue);
  f_H1_mass->SetLineColor(kBlue);
  h_H1_mass_reg->SetLineColor(kRed);
  f_H1_mass_reg->SetLineColor(kRed);
  
  h_H1_mass->Draw("");
  h_H1_mass_reg->Draw("same");
  
  TLegend *leg=new TLegend(0.57, 0.89, 0.89, 0.75);
  leg->AddEntry(h_H1_mass, ("Nominal #bar{x}="+ftoa(f_H1_mass->GetParameter(1))+", #sigma="+ftoa(f_H1_mass->GetParameter(2))).c_str());
  leg->AddEntry(h_H1_mass_reg, ("Reg. Corr. #bar{x}="+ftoa(f_H1_mass_reg->GetParameter(1))+", #sigma="+ftoa(f_H1_mass_reg->GetParameter(2))).c_str());
  leg->SetLineColor(0);
  leg->Draw();
  
  mean_H1=f_H1_mass->GetParameter(1);
  sigma_H1=f_H1_mass->GetParameter(2);
}

void Display_mH2_ForFile(TFile *f,TFile *fR, double &mean_H2, double &sigma_H2)
{
  TH1F *h_H2_mass=(TH1F*)f->Get("h_H2_mass");
  TH1F *h_H2_mass_biasCorrected=(TH1F*)f->Get("h_H2_mass_biasCorrected");
  
  TF1 *f_H2_mass=new TF1("f_H2_mass", "gaus", h_H2_mass->GetMean()-1*h_H2_mass->GetRMS(), h_H2_mass->GetMean()+1*h_H2_mass->GetRMS());
  TF1 *f_H2_mass_biasCorrected=new TF1("f_H2_mass_biasCorrected", "gaus", h_H2_mass_biasCorrected->GetMean()-1*h_H2_mass_biasCorrected->GetRMS(), h_H2_mass_biasCorrected->GetMean()+1*h_H2_mass_biasCorrected->GetRMS());
  
  h_H2_mass->Rebin(2);
  h_H2_mass_biasCorrected->Rebin(2);
  
  h_H2_mass->GetXaxis()->SetRangeUser(50, 200);
  h_H2_mass_biasCorrected->GetXaxis()->SetRangeUser(50, 200);
  
  h_H2_mass->Fit(f_H2_mass, "R");
  h_H2_mass_biasCorrected->Fit(f_H2_mass_biasCorrected, "R");
  
  h_H2_mass->SetLineColor(kBlue);
  f_H2_mass->SetLineColor(kBlue);
  h_H2_mass_biasCorrected->SetLineColor(kRed);
  f_H2_mass_biasCorrected->SetLineColor(kRed);
  
  h_H2_mass->Draw("");
  h_H2_mass_biasCorrected->Draw("same");
  
  TLegend *leg=new TLegend(0.57, 0.89, 0.89, 0.75);
  leg->AddEntry(h_H2_mass, ("Nominal #bar{x}="+ftoa(f_H2_mass->GetParameter(1))+", #sigma="+ftoa(f_H2_mass->GetParameter(2))).c_str());
  leg->AddEntry(h_H2_mass_biasCorrected, ("Bias Corr. #bar{x}="+ftoa(f_H2_mass_biasCorrected->GetParameter(1))+", #sigma="+ftoa(f_H2_mass_biasCorrected->GetParameter(2))).c_str());
  leg->SetLineColor(0);
  leg->Draw();
  
  mean_H2=f_H2_mass->GetParameter(1);
  sigma_H2=f_H2_mass->GetParameter(2);
}

void DisplayXpT_ForFile(TFile *f, TFile *fR )
{
  TH1F *h_HH_balance=(TH1F*)f->Get("h_HH_balance");
  TH1F *h_HH_balance_reg=(TH1F*)fR->Get("h_HH_balance")->Clone("h_HH_balance_reg");
  TH1F *h_HH_balance_kinFit=(TH1F*)fR->Get("h_HH_balance_kinFit");
  
  h_HH_balance->SetLineColor(kBlue);
  h_HH_balance_reg->SetLineColor(kGreen+1);
  h_HH_balance_kinFit->SetLineColor(kRed);
  
  h_HH_balance_kinFit->Rebin(5);
  h_HH_balance->Rebin(5);
  h_HH_balance_reg->Rebin(5);
  
  h_HH_balance->GetXaxis()->SetRangeUser(0, 100);
  h_HH_balance_reg->GetXaxis()->SetRangeUser(0, 100);
  h_HH_balance_kinFit->GetXaxis()->SetRangeUser(0, 100);
  
  h_HH_balance_kinFit->SetMaximum(h_HH_balance_kinFit->GetMaximum()*1.2);
  h_HH_balance_kinFit->Draw("hist");
  h_HH_balance->Draw("hist same");
  h_HH_balance_reg->Draw("hist same");
  h_HH_balance_kinFit->Draw("hist same");
  
  TLegend *leg=new TLegend(0.4, 0.89, 0.89, 0.7);
  leg->AddEntry(h_HH_balance, ("Nominal balance, #bar{x} = "+ftoa(h_HH_balance->GetMean())+", #sigma = "+ftoa(h_HH_balance->GetRMS())).c_str());
  leg->AddEntry(h_HH_balance_kinFit, ("Kinematic fit balance, #bar{x} = "+ftoa(h_HH_balance_kinFit->GetMean())+", #sigma = "+ftoa(h_HH_balance_kinFit->GetRMS())).c_str());
  leg->SetLineColor(0);
  leg->Draw();
}


// Display histogram for file 
TH1* DisplayHistogram_forFile(TFile *file, std::string histogramName, int color, bool reg = false)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());
  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  if( reg ) h->SetLineStyle(2);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.5);
    h->GetYaxis()->SetTitleOffset(1.6);
    h->Draw("hist");
    first=false;
  }
  h->Draw("hist same");
  return h;
}



void DisplayKinFitReg()
{
  std::vector<TFile*> v_files;
 // v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  //v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root"));
v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
 // v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root"));
    v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
 // v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
    v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
//  v_files.push_back(new TFile("PreselectedWithoutRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));

std::vector<TFile*> v_files_reg;
 // v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  //v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
 // v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegression/LMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
 // v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root"));
    v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
 // v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
    v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
//  v_files_reg.push_back(new TFile("PreselectedWithRegression/MMRSelection_chi2/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));
//
  TFile *f_data=new TFile("PreselectedWithoutRegression/Histograms_BTagCSV.root");
  TFile *f_data_reg=new TFile("PreselectedWithRegression/Histograms_BTagCSV.root");
  // v_files_reg.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1600_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-2000_narrow_13TeV-madgraph.root"));
  // v_files.push_back(new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-3000_narrow_13TeV-madgraph.root"));
  std::vector <double> mean_gen={300,450,600, 750, 900 };// , 1200, 1600, 2000, 3000};
 
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  std::vector <double> mean, meanDiff_biasCorrected, meanDiff_kinFit, sigma, sigma_biasCorrected, sigma_kinFit;
  int dontwant=3;
  std::cout<<"Fitting peaks"<<std::endl;
  for (unsigned int i=dontwant; i<v_files.size(); ++i)
  {
    TH1F *h_mX_SR=(TH1F*)v_files.at(i)->Get("h_mX_SR");
    TH1F *h_mX_SR_kf=(TH1F*)v_files.at(i)->Get("h_mX_SR_kinFit");
    TH1F *h_mX_SR_kf_reg=(TH1F*)v_files_reg.at(i)->Get("h_mX_SR_kinFit");
    
    h_mX_SR->Rebin(10);
    h_mX_SR_kf->Rebin(10);
    h_mX_SR_kf_reg->Rebin(10);
    
    TF1 *f_mX_SR=new TF1("f_mX_SR", "gaus", h_mX_SR->GetMean()-(1.5*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(1.5*h_mX_SR->GetRMS()));
    f_mX_SR->SetParLimits(1, h_mX_SR->GetMean()-(3*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(3*h_mX_SR->GetRMS()));
    f_mX_SR->SetParLimits(2, 0, 3*h_mX_SR->GetRMS());
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV"<<std::endl;
    h_mX_SR->Fit(f_mX_SR, "R");
    std::cout<<"=== ==="<<std::endl;
    
    TF1 *f_mX_SR_biasCorrected=new TF1("f_mX_SR_biasCorrected", "gaus", h_mX_SR_kf->GetMean()-(1.5*h_mX_SR_kf->GetRMS()), h_mX_SR_kf->GetMean()+(1.5*h_mX_SR_kf->GetRMS()));
    f_mX_SR_biasCorrected->SetParLimits(1, h_mX_SR_kf->GetMean()-(3*h_mX_SR_kf->GetRMS()), h_mX_SR_kf->GetMean()+(3*h_mX_SR_kf->GetRMS()));
    f_mX_SR_biasCorrected->SetParLimits(2, 0, 3*h_mX_SR_kf->GetRMS());
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV, bias Corrected"<<std::endl;
    h_mX_SR_kf->Fit(f_mX_SR_biasCorrected, "R");
    std::cout<<"=== ==="<<std::endl;
    
    TF1 *f_mX_SR_kinFit=new TF1("f_mX_SR_kinFit", "gaus", h_mX_SR_kf_reg->GetMean()-(1.5*h_mX_SR_kf_reg->GetRMS()), h_mX_SR_kf_reg->GetMean()+(1.5*h_mX_SR_kf_reg->GetRMS()));
    f_mX_SR_kinFit->SetParLimits(1, h_mX_SR_kf_reg->GetMean()-(3*h_mX_SR_kf_reg->GetRMS()), h_mX_SR_kf_reg->GetMean()+(3*h_mX_SR_kf_reg->GetRMS()));
    f_mX_SR_kinFit->SetParLimits(2, 0, 3*h_mX_SR_kf_reg->GetRMS());
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV, KinFitted"<<std::endl;
    h_mX_SR_kf_reg->Fit(f_mX_SR_kinFit, "R");
    std::cout<<"=== ==="<<std::endl;
    
    TCanvas *c_Canvas=new TCanvas("c_Canvas", "c_Canvas", 2100, 700);
    c_Canvas->Divide(3,1);
    c_Canvas->cd(1);
    h_mX_SR->Draw();
    c_Canvas->cd(2);
    h_mX_SR_kf->Draw();
    c_Canvas->cd(3);
    h_mX_SR_kf_reg->Draw();
    c_Canvas->SaveAs(("c_Fit_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_Canvas;
    
    mean.push_back(f_mX_SR->GetParameter(1) - mean_gen.at(i));
    meanDiff_biasCorrected.push_back(f_mX_SR_biasCorrected->GetParameter(1) - mean_gen.at(i));
    meanDiff_kinFit.push_back(f_mX_SR_kinFit->GetParameter(1) - mean_gen.at(i));
    
    sigma.push_back(f_mX_SR->GetParameter(2)/mean_gen.at(i));
    sigma_biasCorrected.push_back(f_mX_SR_biasCorrected->GetParameter(2)/mean_gen.at(i));
    sigma_kinFit.push_back(f_mX_SR_kinFit->GetParameter(2)/mean_gen.at(i));
    
    delete h_mX_SR;
    delete h_mX_SR_kf;
    delete h_mX_SR_kf_reg;
  }
  
  std::vector<double> v_mean_H1, v_sigma_H1;
  std::vector<double> v_mean_H2, v_sigma_H2;
  for (unsigned int i=dontwant; i<v_files.size(); ++i)
  {
    TCanvas *c_mH1=new TCanvas("c_mH1", "c_mH1", 700, 700);
    double mean_H1, sigma_H1;
    Display_mH1_ForFile(v_files.at(i), v_files_reg.at(i), mean_H1, sigma_H1);
    c_mH1->SaveAs(("c_mH1_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH1;
    v_mean_H1.push_back(mean_H1);
    v_sigma_H1.push_back(sigma_H1);
    
    TCanvas *c_mH2=new TCanvas("c_mH2", "c_mH2", 700, 700);
    double mean_H2, sigma_H2;
    Display_mH2_ForFile(v_files.at(i), v_files_reg.at(i),  mean_H2, sigma_H2);
    c_mH2->SaveAs(("c_mH2_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_mH2;
    v_mean_H2.push_back(mean_H2);
    v_sigma_H2.push_back(sigma_H2);
  }
  TGraph *g_mean_H1=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(v_mean_H1.at(0)));
  TGraph *g_sigma_H1=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(v_sigma_H1.at(0)));
  TGraph *g_mean_H2=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(v_mean_H2.at(0)));
  TGraph *g_sigma_H2=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(v_sigma_H2.at(0)));
  g_mean_H1->SetTitle("; m_{X}^{gen} (GeV); <m_{H1}>");
  g_sigma_H1->SetTitle("; m_{X}^{gen} (GeV); #sigma(m_{H1})");
  g_mean_H2->SetTitle("; m_{X}^{gen} (GeV); <m_{H2}>");
  g_sigma_H2->SetTitle("; m_{X}^{gen} (GeV); #sigma(m_{H1})");
  TF1 *f_mean_H1=new TF1("f_mean_H1", "pol0", 400, 1200);
  TF1 *f_sigma_H1=new TF1("f_sigma_H1", "pol0", 400, 1200);
  TF1 *f_mean_H2=new TF1("f_mean_H2", "pol0", 400, 1200);
  TF1 *f_sigma_H2=new TF1("f_sigma_H2", "pol0", 400, 1200);
  g_mean_H1->Fit(f_mean_H1, "R");
  g_sigma_H1->Fit(f_sigma_H1, "R");
  g_mean_H2->Fit(f_mean_H2, "R");
  g_sigma_H2->Fit(f_sigma_H2, "R");
  TCanvas *c_H1H2_meanSigma=new TCanvas("c_H1H2_meanSigma", "c_H1H2_meanSigma", 700, 700);
  c_H1H2_meanSigma->Divide(2,2);
  c_H1H2_meanSigma->cd(1);
  g_mean_H1->Draw("A*");
  c_H1H2_meanSigma->cd(2);
  g_sigma_H1->Draw("A*");
  c_H1H2_meanSigma->cd(3);
  g_mean_H2->Draw("A*");
  c_H1H2_meanSigma->cd(4);
  g_sigma_H2->Draw("A*");
  c_H1H2_meanSigma->SaveAs("c_H1H2_meanSigma.png");
  
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 1000, 700);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayKinFitForFile(v_files.at(i), v_files_reg.at(i), mean_gen.at(i));
  }
  c_KinFit->SaveAs("c_KinFit.png");
  
  TGraph *g_mean=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(mean.at(0)));
  g_mean->GetYaxis()->SetRangeUser(-100, 100);
  g_mean->GetXaxis()->SetLimits(300, 1300);
  g_mean->SetTitle("; m_{X}^{gen} (GeV); m_{X}^{KinFit} - m_{X} (GeV)");
  g_mean->SetMarkerColor(kBlue);
  TGraph *g_meanDiff_biasCorrected = new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(meanDiff_biasCorrected.at(0)));
  g_meanDiff_biasCorrected->SetMarkerColor(kGreen);
  TGraph *g_meanDiff_kinFit = new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(meanDiff_kinFit.at(0)));
  g_meanDiff_kinFit->SetMarkerColor(kRed+1);
  TCanvas *c_meanDiff=new TCanvas("c_meanDiff", "c_meanDiff", 700, 700);
  g_mean->Draw("A*");
  g_meanDiff_biasCorrected->Draw("SAME*");
  g_meanDiff_kinFit->Draw("SAME*");
  TF1 *f_meanDiff_kinFit=new TF1("f_meanDiff_kinFit", "pol0", 400, 1200);
  f_meanDiff_kinFit->SetLineColor(kRed); f_meanDiff_kinFit->SetLineWidth(1); f_meanDiff_kinFit->SetLineStyle(7);
  g_meanDiff_kinFit->Fit(f_meanDiff_kinFit, "R");
  TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(g_mean, "m_{X}^{reco} - m_{X}^{gen}", "p");
  leg->AddEntry(g_meanDiff_biasCorrected, "m_{X}^{biasCorr} - m_{X}^{gen}", "p");
  leg->AddEntry(g_meanDiff_kinFit, "m_{X}^{kinFit} - m_{X}^{gen}", "p");
  leg->Draw();
  c_meanDiff->SaveAs("c_meanDiff.png");
  c_meanDiff->SaveAs("c_meanDiff.root");
  
  TGraph *g_sigma=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma.at(0)));
  g_sigma->SetTitle("; m_{X}^{gen} (GeV); #sigma(m_{X})/m_{X}");
  g_sigma->GetYaxis()->SetRangeUser(0., 0.08);
  g_sigma->GetXaxis()->SetLimits(300, 1300);
  TGraph *g_sigma_biasCorrected=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma_biasCorrected.at(0)));
  TGraph *g_sigma_kinFit=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma_kinFit.at(0)));
  TCanvas *c_sigma=new TCanvas("c_sigma", "c_sigma", 700, 700);
  g_sigma->SetMarkerColor(kBlue);
  g_sigma_biasCorrected->SetMarkerColor(kGreen);
  g_sigma_kinFit->SetMarkerColor(kRed);
  g_sigma->Draw("A*");
  g_sigma_biasCorrected->Draw("SAME*");
  g_sigma_kinFit->Draw("SAME*");
  leg=new TLegend(0.5, 0.7, 0.89, 0.89);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(g_sigma, "nominal resolution", "p");
  leg->AddEntry(g_sigma_biasCorrected, "bias reconstructed resolution", "p");
  leg->AddEntry(g_sigma_kinFit, "kinematic fitted resolution", "p");
  leg->Draw();
  c_sigma->SaveAs("c_sigma.png");
  c_sigma->SaveAs("c_sigma.root");
  
  // Display jet pT balance
  for (unsigned int i=2; i<v_files.size(); ++i)
  {
    TCanvas *c_HH_balance=new TCanvas("c_HH_balance", "c_HH_balance", 700, 700);
    DisplayXpT_ForFile(v_files.at(i),v_files_reg.at(i));
    c_HH_balance->SaveAs(("c_HH_balance_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_HH_balance;
  }


  std::vector<TFile*> v_files1;
 // v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  //v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root"));
v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
 // v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root"));
    v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
 // v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
    v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root"));
  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
//  v_files1.push_back(new TFile("PreselectedWithoutRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));

std::vector<TFile*> v_files_reg1;
 // v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root"));
  //v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root"));
  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
 // v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
 // v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root"));
    v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
 // v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root"));
    v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root"));
  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
//  v_files_reg1.push_back(new TFile("PreselectedWithRegression/Histograms_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root"));

  std::vector<int> v_colors = {kAzure+1, kAzure+3, kRed+1, kPink+1, kPink+3, kGreen+2, kGreen+3, kBlue+1, kGray+2, kCyan, kCyan+2, kRed-4, kRed-7, kYellow-4, kGreen-4, kGreen };
  leg=new TLegend(0.6, 0.5, 0.89, 0.89);
  // Plot the 1st highest pT jets with |eta| < 2.5  
  first=true;
  TCanvas *c_pTOrder_JetpT_1=new TCanvas("c_pTOrder_JetpT_1", "c_pTOrder_JetpT_1", 700, 700);
  for (unsigned int i=0; i<v_files1.size(); ++i)
  {
    TH1* h = DisplayHistogram_forFile(v_files1.at(i), "h_pTreg_JetpT_1", v_colors.at(i));
    DisplayHistogram_forFile(v_files_reg1.at(i), "h_pTreg_JetpT_1", v_colors.at(i), true );
    leg->AddEntry(h, ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
    
  }
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_1", kBlack);
  DisplayHistogram_forFile(f_data_reg, "h_pTreg_JetpT_1", kBlack, true);
  leg->AddEntry(f_data->Get("h_pTOrder_JetpT_1"), "13 TeV Data");
  leg->Draw();
  TArrow *line=new TArrow(30., 0.14, 30., 0); line->SetLineWidth(3);
  line->Draw();
  c_pTOrder_JetpT_1->SaveAs("c_reg_JetpT_1.pdf");
 
  first=true;
  for (unsigned int i=0; i<v_files1.size(); ++i)
  {
    DisplayHistogram_forFile(v_files1.at(i), "h_pTreg_JetpT_2", v_colors.at(i));
    DisplayHistogram_forFile(v_files_reg1.at(i), "h_pTreg_JetpT_2", v_colors.at(i), true );
    
  }
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_2", kBlack);
  DisplayHistogram_forFile(f_data_reg, "h_pTreg_JetpT_2", kBlack, true);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_1->SaveAs("c_reg_JetpT_2.pdf");

  first=true;
  for (unsigned int i=0; i<v_files1.size(); ++i)
  {
    DisplayHistogram_forFile(v_files1.at(i), "h_pTreg_JetpT_3", v_colors.at(i));
    DisplayHistogram_forFile(v_files_reg1.at(i), "h_pTreg_JetpT_3", v_colors.at(i), true );
    
  }
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_3", kBlack);
  DisplayHistogram_forFile(f_data_reg, "h_pTreg_JetpT_3", kBlack, true);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_1->SaveAs("c_reg_JetpT_3.pdf");

  first=true;
  for (unsigned int i=0; i<v_files1.size(); ++i)
  {
    DisplayHistogram_forFile(v_files1.at(i), "h_pTreg_JetpT_4", v_colors.at(i));
    DisplayHistogram_forFile(v_files_reg1.at(i), "h_pTreg_JetpT_4", v_colors.at(i), true );
    
  }
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_4", kBlack);
  DisplayHistogram_forFile(f_data_reg, "h_pTreg_JetpT_4", kBlack, true);
  leg->Draw();
  line->Draw();
  c_pTOrder_JetpT_1->SaveAs("c_reg_JetpT_4.pdf");
 
}
