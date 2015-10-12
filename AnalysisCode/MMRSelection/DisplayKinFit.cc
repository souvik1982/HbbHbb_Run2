#include <TH1F.h>
#include <TLegend.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

bool first=true;
void DisplayKinFitForFile(TFile *file, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_kinFit=(TH1F*)file->Get("h_mX_SR_kinFit");
  
  double n=h_mX_SR->GetSumOfWeights();
  h_mX_SR->Scale(1./n);
  h_mX_SR_kinFit->Scale(1./n);
  
  h_mX_SR->Rebin(10);
  h_mX_SR_kinFit->Rebin(10);
  
  h_mX_SR->GetXaxis()->SetRangeUser(200, 1100);
  h_mX_SR_kinFit->GetXaxis()->SetRangeUser(200, 1100);
  
  h_mX_SR->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineWidth(2);
  
  h_mX_SR->SetLineColor(kBlue);
  h_mX_SR->SetLineStyle(7);
  h_mX_SR_kinFit->SetLineColor(kRed);
  
  if (first)
  {
    h_mX_SR_kinFit->GetYaxis()->SetTitle("Normalized Units");
    h_mX_SR_kinFit->GetYaxis()->SetTitleOffset(1.4);
    h_mX_SR_kinFit->Draw("hist");
    TLegend *leg=new TLegend(0.5, 0.7, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_mX_SR, "m_{X} Signal Peak");
    leg->AddEntry(h_mX_SR_kinFit, "m_{X} w/ Kinematic Fit");
    leg->Draw();
    first=false;
  }
  else h_mX_SR_kinFit->Draw("hist same");
  h_mX_SR->Draw("hist same");
  
  TLine *line=new TLine(xLine, 0, xLine, h_mX_SR_kinFit->GetMaximum());
  line->Draw();
  
}

void DisplayKinFit()
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
  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 700, 700);
  // DisplayKinFitForFile(f_Radion260GeV, 260);
  // DisplayKinFitForFile(f_Radion270GeV, 270);
  DisplayKinFitForFile(f_Radion300GeV, 300);
  // DisplayKinFitForFile(f_Radion350GeV, 350);
  DisplayKinFitForFile(f_Radion400GeV, 400);
  //DisplayKinFitForFile(f_Radion450GeV, 450);
  DisplayKinFitForFile(f_Radion500GeV, 500);
  //DisplayKinFitForFile(f_Radion550GeV, 550);
  DisplayKinFitForFile(f_Radion600GeV, 600);
  //DisplayKinFitForFile(f_Radion650GeV, 650);
  DisplayKinFitForFile(f_Radion700GeV, 700);
  DisplayKinFitForFile(f_Radion800GeV, 800);
  DisplayKinFitForFile(f_Radion900GeV, 900);
  c_KinFit->SaveAs("c_KinFit.png");
}
