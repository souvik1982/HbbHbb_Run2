#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLine.h"
#include <TStyle.h>
std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void DrawEff()
{
  const unsigned int nPoints=5;
    double xsec[5]={0.14,0.39,1.05,1.99,2.87};
    double expNeg1[5]={0.06,0.19,0.49,0.87,1.03};
    double mass[5] ={270,300,350,400,450};

  gROOT->SetStyle("Plain");
  // gStyle->SetOptStat(000000000);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetTextFont(4);
  gStyle->SetTextSize(.05);//.055
  gStyle->SetTextFont(42);
  gStyle->SetStatFont(42);
  gStyle->SetTitleFont(42,"");
  gStyle->SetTitleFont(42,"Z");
  gStyle->SetTitleFont(42,"X");
  gStyle->SetTitleFont(42,"Y");
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelFont(42,"Z");

 
  TGraphAsymmErrors *g_xsec_1sigma=new TGraphAsymmErrors(nPoints, mass, xsec, 0, 0, expNeg1, expNeg1);
  g_xsec_1sigma->SetLineColor(kBlue+3);
  g_xsec_1sigma->SetFillColor(kBlue+3);
 
  TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
  //c_xsec->SetLogy();
  g_xsec_1sigma->Draw("AL*");
  /*TLine * a = new TLine();
  a->SetLineColor(kRed);
  a->SetLineStyle(2);
  a->DrawLine(0.,0., 10., 10.); 
  */// g_obs->Draw("L* SAME");
  TLegend *leg=new TLegend(0.45, 0.6, 0.9, 0.85);
  // TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  //leg->SetTextFont(4);
  leg->AddEntry((TObject*)0, "CMS Experiment #sqrt{s} = 8 TeV, L = 18.6 fb^{-1}", "");
  leg->AddEntry((TObject*)0, "X#rightarrowH(b#bar{b}) H(b#bar{b})", "");
  leg->AddEntry(g_xsec_1sigma, "signal efficiency");
  // leg->AddEntry(g_xsec_2sigma, "#mu X(400)");
  // leg->AddEntry(g_obs, "Observed Limit with fake data (background + 1 pb signal)", "LP");
  leg->Draw();
  c_xsec->SaveAs("signalEff.root");
  
  
}
    
