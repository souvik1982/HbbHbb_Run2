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

void splitStyleBiasPlots_withBias()
{
  TFile *file1=new TFile("ThrowBern6_CatchBern6_CatchGaussExp/f_StrengthBias_Bern6.root");
  TFile *file2=new TFile("ThrowGaussExpCatchGaussExp/f_StrengthBias_GaussExp.root");
  
  TStyle *tdrStyle=setTDRStyle();
  tdrStyle->cd();
  
  std::string injections[]={"0.00", "0.01", "0.05", "0.1", "0.5", "1"};
  int nInjections=sizeof(injections)/sizeof(injections[0]);
  for (unsigned int i_inj=0; i_inj<nInjections; ++i_inj)
  {
   
    double injection=atof((injections[i_inj]).c_str());
    TLine *line=new TLine(400, injection*1000., 1100, injection*1000.); 
    line->SetLineColor(kRed); 
    
    TLatex * tPrel = new TLatex();
    tPrel->SetTextSize(0.04);
    
    TCanvas *c_Bern6_Split=new TCanvas(("c_Bern6_Split_"+injections[i_inj]).c_str(), "c_Bern6_Split", 700, 700);
    
    TGraphAsymmErrors *g_strength_Bern6=file1->Get(("g_strength_Bern6_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_strength_rms_Bern6=file1->Get(("g_strength_rms_Bern6_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_strength_rms_sqrtN_Bern6=file1->Get(("g_strength_rms_sqrtN_Bern6_"+injections[i_inj]).c_str());
    
    g_strength_rms_Bern6->SetTitle("; m_{X} (GeV); Bernstein Signal Strength (fb)");
    g_strength_rms_Bern6->SetFillColor(kYellow);
    g_strength_rms_Bern6->Draw("A3");
    g_strength_rms_sqrtN_Bern6->SetMarkerStyle(20);
    g_strength_rms_sqrtN_Bern6->Draw("LP");
    
    line->Draw();
    tPrel->DrawLatexNDC(0.05, 0.95, "CMS Preliminary; #sqrt{s} = 8 TeV, L = 17.928 fb^{-1}");
    
    c_Bern6_Split->SaveAs(("BiasDistributions/c_Bern6_Split_"+injections[i_inj]+".png").c_str());
    
    TCanvas *c_GaussExp_Split=new TCanvas(("c_GaussExp_Split_"+injections[i_inj]).c_str(), "c_GaussExp_Split", 700, 700);
    
    TGraphAsymmErrors *g_strength_GaussExp=file2->Get(("g_strength_GaussExp_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_strength_rms_GaussExp=file2->Get(("g_strength_rms_GaussExp_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_strength_rms_sqrtN_GaussExp=file2->Get(("g_strength_rms_sqrtN_GaussExp_"+injections[i_inj]).c_str());
    
    g_strength_rms_GaussExp->SetTitle("; m_{X} (GeV); GaussExp Signal Strength (fb)");
    g_strength_rms_GaussExp->SetFillColor(kYellow);
    g_strength_rms_GaussExp->Draw("A3");
    g_strength_rms_sqrtN_GaussExp->SetMarkerStyle(20);
    g_strength_rms_sqrtN_GaussExp->Draw("LP");
    
    line->Draw();
    tPrel->DrawLatexNDC(0.05, 0.95, "CMS Preliminary; #sqrt{s} = 8 TeV, L = 17.928 fb^{-1}");
    
    c_GaussExp_Split->SaveAs(("BiasDistributions/c_GaussExp_Split_"+injections[i_inj]+".png").c_str());
    
    TCanvas *c_Bias_Split=new TCanvas(("c_Bias_Split_"+injections[i_inj]).c_str(), "c_Bias_Split", 700, 700);
    
    TGraphAsymmErrors *g_bias_rms=file2->Get(("g_bias_rms_"+injections[i_inj]).c_str());
    TGraphAsymmErrors *g_bias_rms_sqrtN=file2->Get(("g_bias_rms_sqrtN_"+injections[i_inj]).c_str());
    
    g_bias_rms->SetTitle("; m_{X} (GeV); Bias #Delta#mu (fb)");
    g_bias_rms->SetFillColor(kYellow);
    g_bias_rms->Draw("A3");
    g_bias_rms_sqrtN->SetMarkerStyle(20);
    g_bias_rms_sqrtN->Draw("LP");
    
    line=new TLine(400, 0., 1100, 0.); 
    line->SetLineColor(kRed); 
    line->Draw();
    tPrel->DrawLatexNDC(0.05, 0.95, "CMS Preliminary; #sqrt{s} = 8 TeV, L = 17.928 fb^{-1}");
    
    c_Bias_Split->SaveAs(("BiasDistributions/c_Bias_Split_"+injections[i_inj]+".png").c_str());
    
    
  }
}
