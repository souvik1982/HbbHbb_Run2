#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "string.h"
#include "TColor.h"
#include "TLatex.h"
#include "TLine.h"
#include "TAxis.h"

#include "/Users/souvik/HbbHbb/Analysis/TDRStyle.h"

void splitStyleBiasPlots()
{
  // TFile *file1=new TFile("ThrowBernstein8/f_StrengthBias.root");
  // TFile *file1=new TFile("ThrowGaussExp/f_StrengthBias.root");
  TFile *file1=new TFile("f_StrengthBias.root");
  
  TStyle *tdrStyle=setTDRStyle();
  tdrStyle->cd();
  
  // std::string injections[]={"0.00", "0.01", "0.05", "0.1", "0.5", "1"};
  std::string injections[]={"0.00", "0.01", "0.05", "0.1", "0.5", "1"};
  int nInjections=sizeof(injections)/sizeof(injections[0]);
  for (unsigned int i_inj=0; i_inj<nInjections; ++i_inj)
  {
   
    TCanvas *c_BiasStudy_Split=new TCanvas(("c_BiasStudy_Split_"+injections[i_inj]).c_str(), "c_BiasStudy_Split", 700, 700);
    TGraphAsymmErrors *g_file1=file1->Get(("g_strength_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_file1_rms=file1->Get(("g_strength_rms_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_file1_rms_sqrtN=file1->Get(("g_strength_rms_sqrtN_"+injections[i_inj]).c_str());
    
    // g_file1->SetTitle("; m_{X} (GeV); Signal Strength (fb)");
    // g_file1->SetFillColor(kYellow);
    // g_file1->Draw("A3");
    
    g_file1_rms->SetTitle("; m_{X} (GeV); Signal Strength (fb)");
    g_file1_rms->SetFillColor(kYellow);
    g_file1_rms->Draw("A3");
    
    g_file1_rms_sqrtN->SetMarkerStyle(20); g_file1_rms_sqrtN->Draw("LP");
    
    double injection=atof((injections[i_inj]).c_str());
    TLine *line=new TLine(400, injection*1000., 1100, injection*1000.); 
    line->SetLineColor(kRed); 
    line->Draw();
    
    TLatex * tPrel = new TLatex();
    tPrel->SetTextSize(0.04);
    tPrel->DrawLatexNDC(0.05, 0.95, "CMS Preliminary; #sqrt{s} = 8 TeV, L = 17.928 fb^{-1}");
    
    c_BiasStudy_Split->SaveAs(("PullDistributions/c_BiasStudy_Split_"+injections[i_inj]+".png").c_str());
    c_BiasStudy_Split->SaveAs(("PullDistributions/c_BiasStudy_Split_"+injections[i_inj]+".root").c_str());
  }
}
