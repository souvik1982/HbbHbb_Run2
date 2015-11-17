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

#include "../TDRStyle.h"

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

void DisplayKinFitForFile(TFile *file, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_biasCorrected=(TH1F*)file->Get("h_mX_SR_biasCorrected");
  TH1F *h_mX_SR_kinFit=(TH1F*)file->Get("h_mX_SR_kinFit");
  
  double n=h_mX_SR->GetSumOfWeights();
  h_mX_SR->Scale(1./n);
  h_mX_SR_biasCorrected->Scale(1./n);
  h_mX_SR_kinFit->Scale(1./n);
  
  h_mX_SR->Rebin(10);
  h_mX_SR_biasCorrected->Rebin(10);
  h_mX_SR_kinFit->Rebin(10);
  
  h_mX_SR->GetXaxis()->SetRangeUser(200, 1100);
  h_mX_SR_biasCorrected->GetXaxis()->SetRangeUser(200, 1100);
  h_mX_SR_kinFit->GetXaxis()->SetRangeUser(200, 1100);
  
  h_mX_SR->SetLineWidth(2);
  h_mX_SR_biasCorrected->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineWidth(2);
  
  h_mX_SR->SetLineColor(kBlue);
  h_mX_SR->SetLineStyle(7);
  h_mX_SR_biasCorrected->SetLineColor(kGreen);
  h_mX_SR_biasCorrected->SetLineStyle(7);
  h_mX_SR_kinFit->SetLineColor(kRed);
  
  if (first)
  {
    h_mX_SR_kinFit->SetMaximum(h_mX_SR_kinFit->GetMaximum()*1.2);
    h_mX_SR_kinFit->GetYaxis()->SetTitle("Normalized Units");
    h_mX_SR_kinFit->GetYaxis()->SetTitleOffset(1.4);
    h_mX_SR_kinFit->Draw("hist");
    TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_mX_SR, "m_{X} Signal Peak");
    leg->AddEntry(h_mX_SR_biasCorrected, "m_{X} w/ Bias Correct.");
    leg->AddEntry(h_mX_SR_kinFit, "m_{X} w/ Kinematic Fit");
    leg->Draw();
    first=false;
  }
  else h_mX_SR_kinFit->Draw("hist same");
  h_mX_SR_biasCorrected->Draw("hist same");
  h_mX_SR->Draw("hist same");
  
  TLine *line=new TLine(xLine, 0, xLine, h_mX_SR_kinFit->GetMaximum()*0.9);
  line->Draw();
  
}

void Display_mH_ForFile(TFile *f)
{
  TH1F *h_H1_mass=(TH1F*)f->Get("h_H1_mass");
  TH1F *h_H1_mass_biasCorrected=(TH1F*)f->Get("h_H1_mass_biasCorrected");
  
  TF1 *f_H1_mass=new TF1("f_H1_mass", "gaus", h_H1_mass->GetMean()-1*h_H1_mass->GetRMS(), h_H1_mass->GetMean()+1*h_H1_mass->GetRMS());
  TF1 *f_H1_mass_biasCorrected=new TF1("f_H1_mass_biasCorrected", "gaus", h_H1_mass_biasCorrected->GetMean()-1*h_H1_mass_biasCorrected->GetRMS(), h_H1_mass_biasCorrected->GetMean()+1*h_H1_mass_biasCorrected->GetRMS());
  
  h_H1_mass->Fit(f_H1_mass, "R");
  h_H1_mass_biasCorrected->Fit(f_H1_mass_biasCorrected, "R");
  
  h_H1_mass->SetLineColor(kBlue);
  f_H1_mass->SetLineColor(kBlue);
  h_H1_mass_biasCorrected->SetLineColor(kRed);
  f_H1_mass_biasCorrected->SetLineColor(kRed);
  
  h_H1_mass_biasCorrected->Draw("");
  h_H1_mass->Draw("same");
  
  TLegend *leg=new TLegend(0.6, 0.89, 0.89, 0.6);
  leg->AddEntry(h_H1_mass, ("#bar{x}="+ftoa(f_H1_mass->GetParameter(1))+", #sigma="+ftoa(f_H1_mass->GetParameter(2))).c_str());
  leg->AddEntry(h_H1_mass_biasCorrected, ("#bar{x}="+ftoa(f_H1_mass_biasCorrected->GetParameter(1))+", #sigma="+ftoa(f_H1_mass_biasCorrected->GetParameter(2))).c_str());
  leg->SetLineColor(0);
  leg->Draw();
  
} 

void DisplayKinFit()
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
  std::vector <double> mean_gen={260, 270, 300, 400, 600, 800, 1000}; // , 1200, 1600, 2000, 3000};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  // myStyle->SetOptFit();
  
  std::vector <double> mean, meanDiff_biasCorrected, meanDiff_kinFit, sigma, sigma_biasCorrected, sigma_kinFit;
  int dontwant=3;
  std::cout<<"Fitting peaks"<<std::endl;
  for (unsigned int i=dontwant; i<v_files.size(); ++i)
  {
    TH1F *h_mX_SR=(TH1F*)v_files.at(i)->Get("h_mX_SR");
    TH1F *h_mX_SR_biasCorrected=(TH1F*)v_files.at(i)->Get("h_mX_SR_biasCorrected");
    TH1F *h_mX_SR_kinFit=(TH1F*)v_files.at(i)->Get("h_mX_SR_kinFit");
    
    TF1 *f_mX_SR=new TF1("f_mX_SR", "gaus", h_mX_SR->GetMean()-(2*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(2*h_mX_SR->GetRMS()));
    f_mX_SR->SetParLimits(1, h_mX_SR->GetMean()-(2*h_mX_SR->GetRMS()), h_mX_SR->GetMean()+(2*h_mX_SR->GetRMS()));
    f_mX_SR->SetParLimits(2, 0, 50);
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV"<<std::endl;
    h_mX_SR->Fit(f_mX_SR, "R0");
    std::cout<<"=== ==="<<std::endl;
    
    TF1 *f_mX_SR_biasCorrected=new TF1("f_mX_SR_biasCorrected", "gaus", h_mX_SR_biasCorrected->GetMean()-(2*h_mX_SR_biasCorrected->GetRMS()), h_mX_SR_biasCorrected->GetMean()+(2*h_mX_SR_biasCorrected->GetRMS()));
    f_mX_SR_biasCorrected->SetParLimits(1, h_mX_SR_biasCorrected->GetMean()-(2*h_mX_SR_biasCorrected->GetRMS()), h_mX_SR_biasCorrected->GetMean()+(2*h_mX_SR_biasCorrected->GetRMS()));
    f_mX_SR_biasCorrected->SetParLimits(2, 0, 50);
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV, bias Corrected"<<std::endl;
    h_mX_SR_biasCorrected->Fit(f_mX_SR_biasCorrected, "R0");
    std::cout<<"=== ==="<<std::endl;
    
    TF1 *f_mX_SR_kinFit=new TF1("f_mX_SR_kinFit", "gaus", h_mX_SR_kinFit->GetMean()-(2*h_mX_SR_kinFit->GetRMS()), h_mX_SR_kinFit->GetMean()+(2*h_mX_SR_kinFit->GetRMS()));
    f_mX_SR_kinFit->SetParLimits(1, h_mX_SR_kinFit->GetMean()-(2*h_mX_SR_kinFit->GetRMS()), h_mX_SR_kinFit->GetMean()+(2*h_mX_SR_kinFit->GetRMS()));
    f_mX_SR_kinFit->SetParLimits(2, 0, 50);
    std::cout<<"Fitting: "<<mean_gen.at(i)<<" GeV, KinFitted"<<std::endl;
    h_mX_SR_kinFit->Fit(f_mX_SR_kinFit, "R0");
    std::cout<<"=== ==="<<std::endl;
    
    TCanvas *c_Canvas=new TCanvas("c_Canvas", "c_Canvas", 2100, 700);
    c_Canvas->Divide(3,1);
    c_Canvas->cd(1);
    h_mX_SR->Draw();
    c_Canvas->cd(2);
    h_mX_SR_biasCorrected->Draw();
    c_Canvas->cd(3);
    h_mX_SR_kinFit->Draw();
    c_Canvas->SaveAs(("c_Fit_"+itoa(mean_gen.at(i))+".png").c_str());
    delete c_Canvas;
    
    mean.push_back(f_mX_SR->GetParameter(1) - mean_gen.at(i));
    meanDiff_biasCorrected.push_back(f_mX_SR_biasCorrected->GetParameter(1) - mean_gen.at(i));
    meanDiff_kinFit.push_back(f_mX_SR_kinFit->GetParameter(1) - mean_gen.at(i));
    
    sigma.push_back(f_mX_SR->GetParameter(2)/f_mX_SR->GetParameter(1));
    sigma_biasCorrected.push_back(f_mX_SR_biasCorrected->GetParameter(2)/f_mX_SR_biasCorrected->GetParameter(1));
    sigma_kinFit.push_back(f_mX_SR_kinFit->GetParameter(2)/f_mX_SR_kinFit->GetParameter(1));
  }
  
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 1000, 700);
  for (unsigned int i=2; i<v_files.size(); ++i)
  {
    DisplayKinFitForFile(v_files.at(i), mean_gen.at(i));
  }
  c_KinFit->SaveAs("c_KinFit.png");
  
  TGraph *g_mean=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(mean.at(0)));
  g_mean->GetYaxis()->SetRangeUser(-100, 100);
  g_mean->GetXaxis()->SetLimits(300, 1100);
  g_mean->SetTitle("; m_{X}^{gen} (GeV); m_{X}^{KinFit} - m_{X} (GeV)");
  g_mean->SetMarkerColor(kBlue);
  TGraph *g_meanDiff_biasCorrected = new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(meanDiff_biasCorrected.at(0)));
  g_meanDiff_biasCorrected->SetMarkerColor(kGreen);
  TGraph *g_meanDiff_kinFit = new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(meanDiff_kinFit.at(0)));
  g_meanDiff_kinFit->SetMarkerColor(kRed);
  TCanvas *c_meanDiff=new TCanvas("c_meanDiff", "c_meanDiff", 700, 700);
  g_mean->Draw("A*");
  g_meanDiff_biasCorrected->Draw("SAME*");
  g_meanDiff_kinFit->Draw("SAME*");
  TF1 *f_meanDiff_kinFit=new TF1("f_meanDiff_kinFit", "pol1", 400, 1000);
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
  
  /*
  TGraph *g_KinFit_sigma=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma.at(0)));
  g_KinFit_sigma->SetTitle("; m_{X}^{gen} (GeV); #sigma(m_{X})/m_{X}");
  g_KinFit_sigma->GetYaxis()->SetRangeUser(0., 0.08);
  g_KinFit_sigma->GetXaxis()->SetLimits(250, 1000);
  TGraph *g_KinFit_sigma_KinFit=new TGraph(v_files.size()-dontwant, &(mean_gen.at(dontwant)), &(sigma_kinFit.at(0)));
  TCanvas *c_sigma=new TCanvas("c_sigma", "c_sigma", 700, 700);
  g_KinFit_sigma->SetMarkerColor(kBlue);
  g_KinFit_sigma_KinFit->SetMarkerColor(kRed);
  g_KinFit_sigma->Draw("A*");
  g_KinFit_sigma_KinFit->Draw("* same");
  c_sigma->SaveAs("c_sigma.png");
  c_sigma->SaveAs("c_sigma.root");
  */
  
}
