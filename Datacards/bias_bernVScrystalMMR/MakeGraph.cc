#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TStyle.h"
std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void MakeGraph()
{
  const unsigned int nPoints=5;
  double xsec[nPoints]={.9707, .9765, .9742, .9682, .9567};
   double mass[nPoints]={500, 600, 700, 800, 900};
  
  
 
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

  TGraph *g_xsec=new TGraph(nPoints, mass, xsec);
  g_xsec->SetTitle("Trigger Efficiency wrt ATLAS evt selection criteria; m_{X} (GeV); Eff (%)");
  g_xsec->SetLineWidth(2);
  g_xsec->SetLineStyle(2);

 TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
  //c_xsec->SetLogy();
  g_xsec->SetMaximum(1.0); g_xsec->SetMinimum(0.8);
  g_xsec->Draw("AL*");
  g_xsec->Draw("L*");
  // g_obs->Draw("L* SAME");
  TLegend *leg=new TLegend(0.45, 0.6, 0.9, 0.85);
  // TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
  leg->SetFillStyle(0);
  leg->AddEntry((TObject*)0, "CMS Experiment. #sqrt{s} = 8 TeV, L = 17.9 fb^{-1}", "");
  leg->AddEntry((TObject*)0, "X#rightarrowH(b#bar{b}) H(b#bar{b})", "");
  c_xsec->SaveAs("UpperLimit.png");
  c_xsec->SaveAs("UpperLimit.eps");
 return; 
  
}
    
