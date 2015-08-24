#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TArrow.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

void DisplayPurityForFile(TFile *file, float xmin, float xmax, int rebin)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_purity0=(TH1F*)file->Get("h_mX_SR_purity0");
  TH1F *h_mX_SR_purity1=(TH1F*)file->Get("h_mX_SR_purity1");
  TH1F *h_mX_SR_purity2=(TH1F*)file->Get("h_mX_SR_purity2");
  TH1F *h_mX_SR_purity3=(TH1F*)file->Get("h_mX_SR_purity3");
  TH1F *h_mX_SR_purity4=(TH1F*)file->Get("h_mX_SR_purity4");
  TH1F *h_mX_SR_purity5=(TH1F*)file->Get("h_mX_SR_purity5");
  
  h_mX_SR->Rebin(rebin);
  h_mX_SR_purity0->Rebin(rebin);
  h_mX_SR_purity1->Rebin(rebin);
  h_mX_SR_purity2->Rebin(rebin);
  h_mX_SR_purity3->Rebin(rebin);
  h_mX_SR_purity4->Rebin(rebin);
  h_mX_SR_purity5->Rebin(rebin);
  
  h_mX_SR->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity0->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity1->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity2->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity3->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity4->GetXaxis()->SetRangeUser(xmin, xmax);
  h_mX_SR_purity5->GetXaxis()->SetRangeUser(xmin, xmax);
  
  h_mX_SR_purity5->SetFillColor(kOrange);
  h_mX_SR_purity0->SetFillColor(kViolet);
  h_mX_SR_purity1->SetFillColor(kCyan);
  h_mX_SR_purity2->SetFillColor(kRed);
  h_mX_SR_purity3->SetFillColor(kBlue);
  h_mX_SR_purity4->SetFillColor(kGreen);
  
  THStack *s_mX_purity=new THStack("s_mX_purity", "");
  s_mX_purity->Add(h_mX_SR_purity5 ,"hist");
  s_mX_purity->Add(h_mX_SR_purity0 ,"hist");
  s_mX_purity->Add(h_mX_SR_purity1 ,"hist");
  s_mX_purity->Add(h_mX_SR_purity2 ,"hist");
  s_mX_purity->Add(h_mX_SR_purity3 ,"hist");
  s_mX_purity->Add(h_mX_SR_purity4 ,"hist");
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  
  std::string name=file->GetName();
  TCanvas *c=new TCanvas("c", "c", 700, 700);
  h_mX_SR->Draw();
  s_mX_purity->Draw("same");
  h_mX_SR->Draw("same");
  TLegend *leg=new TLegend(0.6, 0.6, 0.89, 0.89);
  leg->SetBorderSize(0);
  leg->AddEntry(h_mX_SR, "Selected events");
  leg->AddEntry(h_mX_SR_purity4, "4 matched jets");
  leg->AddEntry(h_mX_SR_purity3, "3 matched jets");
  leg->AddEntry(h_mX_SR_purity2, "2 matched jets");
  leg->AddEntry(h_mX_SR_purity1, "1 matched jets");
  leg->AddEntry(h_mX_SR_purity0, "0 matched jets");
  leg->AddEntry(h_mX_SR_purity5, "Multiple jets to same b");
  leg->Draw();
  c->SaveAs((name.substr(0, name.size()-5)+".png").c_str());
  
  
  delete c;
}

void DisplayPurity()
{
  TFile *f_Radion260GeV=new TFile("Histograms_Radion260GeV.root");
  TFile *f_Radion270GeV=new TFile("Histograms_Radion270GeV.root");
  TFile *f_Radion300GeV=new TFile("Histograms_Radion300GeV.root");
  TFile *f_Radion350GeV=new TFile("Histograms_Radion350GeV.root");
  TFile *f_Radion400GeV=new TFile("Histograms_Radion400GeV.root");
  TFile *f_Radion450GeV=new TFile("Histograms_Radion450GeV.root");
  TFile *f_Radion500GeV=new TFile("Histograms_Radion500GeV.root");
  TFile *f_Radion550GeV=new TFile("Histograms_Radion550GeV.root");
  TFile *f_Radion600GeV=new TFile("Histograms_Radion600GeV.root");
  TFile *f_Radion650GeV=new TFile("Histograms_Radion650GeV.root");
  TFile *f_Radion700GeV=new TFile("Histograms_Radion700GeV.root");
  TFile *f_Radion800GeV=new TFile("Histograms_Radion800GeV.root");
  TFile *f_Radion900GeV=new TFile("Histograms_Radion900GeV.root");

  DisplayPurityForFile(f_Radion260GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion270GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion300GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion350GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion400GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion450GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion500GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion550GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion600GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion650GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion700GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion800GeV, 200, 1500, 1);
  DisplayPurityForFile(f_Radion900GeV, 200, 1500, 1);
}
