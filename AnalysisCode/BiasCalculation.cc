#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "math.h"

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0, double g=0, double h=0, double i=0, double j=0, double k=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f+g*g+h*h+i*i+j*j+k*k, 0.5);
}

struct PullInfo
{
  double mean;
  double std;
  double strength;
  double strength_m1;
  double strength_p1;
};

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
  sprintf(res, "%f", i);
  std::string ret(res);
  return ret;
}

void fixTH1F(TH1F *h)
{
  double mean=h->GetMean();
  double rms=h->GetRMS();
  h->GetXaxis()->SetRangeUser(mean-7.*rms, mean+7.*rms);
}

void fixPositiveTH1F(TH1F *h)
{
  double mean=h->GetMean();
  h->GetXaxis()->SetRangeUser(0.0, 2.*mean);
}

void BiasCalculation()
{
  // std::string mass[]={"450", "500", "550", "600", "650", "700", "800", "900", "1000", "1100"};
  std::string mass[]={"450", "500", "550", "600", "650", "700", "800"};
  
  int nPoints=sizeof(mass)/sizeof(mass[0]);
  
  // std::string injections[]={"0.00", "0.01", "0.05", "0.1", "0.5", "1"};
  std::string injections[]={"0.00"};
  int nInjections=sizeof(injections)/sizeof(injections[0]);
  
  std::cout<<"nPoints = "<<nPoints<<std::endl;
  std::cout<<"nInjections = "<<nInjections<<std::endl;
  
  ofstream outfile;
  outfile.open("BiasDistributions/BiasDistributions.html");
  outfile<<"<html>"<<std::endl;
  outfile<<"<head>"<<std::endl;
  outfile<<"</head>"<<std::endl;
  outfile<<"<body>"<<std::endl;
  outfile<<"<h1> Bias Distributions </h1>"<<std::endl;
  TFile *f_StrengthBias_Bern6=new TFile("f_StrengthBias_Bern6.root", "recreate");
  TFile *f_StrengthBias_GaussExp=new TFile("f_StrengthBias_GaussExp.root", "recreate");
  for (unsigned int i_inj=0; i_inj<nInjections; ++i_inj)
  {
    double injection=atof((injections[i_inj]).c_str());
    std::cout<<"Injection Strength = "<<injection<<std::endl;
    
    std::vector<double> masses;
    std::vector<double> strength_mean_Bern6, strength_mean_GaussExp;
    std::vector<double> strength_rms_Bern6, strength_rms_GaussExp;
    std::vector<double> strength_rms_sqrtN_Bern6, strength_rms_sqrtN_GaussExp;
    std::vector<double> strength_err_Bern6, strength_err_GaussExp;
    std::vector<double> strength_0;
    std::vector<double> bias_mean;
    std::vector<double> bias_rms;
    std::vector<double> bias_rms_sqrtN;
    
    TH1F *h_strength_Bern6[12], *h_strength_Bern6_err[12];
    TH1F *h_strength_GaussExp[12], *h_strength_GaussExp_err[12];
    TH1F *h_bias[12];
    
    outfile<<"<table border='1'>"<<std::endl;
    outfile<<" <tr>"<<std::endl;
    outfile<<"  <td>"<<std::endl;
    outfile<<"   <h2>Injected signal strength = "<<injection*1000.<<" (fb) </h2>"<<std::endl;
    outfile<<"   <img src='c_Bern6_Split_"<<injections[i_inj]<<".png'/>"<<std::endl;
    outfile<<"   <img src='c_GaussExp_Split_"<<injections[i_inj]<<".png'/>"<<std::endl;
    outfile<<"   <img src='c_Bias_Split_"<<injections[i_inj]<<".png'/>"<<std::endl;
    outfile<<"  </td>"<<std::endl;
    
    for (int i_mass=0; i_mass<nPoints; ++i_mass)
    {
      h_strength_Bern6[i_mass]=new TH1F(("h_strength_Bern6_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed Bernstein #mu; #mu (fb)", 50., 1, -1);
      h_strength_Bern6_err[i_mass]=new TH1F(("h_strength_Bern6_err_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed Bernstein #delta#mu; #delta#mu (fb)", 50., 1, -1);
      h_strength_GaussExp[i_mass]=new TH1F(("h_strength_GaussExp_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed GaussExp #mu; #mu (fb)", 50., 1, -1);
      h_strength_GaussExp_err[i_mass]=new TH1F(("h_strength_GaussExp_err_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed GaussExp #delta#mu; #delta#mu (fb)", 50., 1, -1);
      h_bias[i_mass]=new TH1F(("h_bias_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Bias #Delta#mu; Bias (GaussExp - Bernstein) #mu (fb)", 50., 1, -1); 
      
      TFile *file_Bern6=new TFile(("Injection_"+injections[i_inj]+"pb/higgsCombineFitBern6_higgsCombineHbbHbb_19invfb_mX"+mass[i_mass]+"_Output.root").c_str());
      TFile *file_GaussExp=new TFile(("Injection_"+injections[i_inj]+"pb/higgsCombineFitGaussExp_higgsCombineHbbHbb_19invfb_mX"+mass[i_mass]+"_Output.root").c_str());
      TTree *t_limit_Bern6=(TTree*)file_Bern6->Get("limit");
      TTree *t_limit_GaussExp=(TTree*)file_GaussExp->Get("limit");
      
      double limit_Bern6, limit_GaussExp;
      double limitErr_Bern6, limitErr_GaussExp;
      int iToy_Bern6;
      int iToy_GaussExp;
      t_limit_Bern6->SetBranchAddress("limit", &limit_Bern6);
      t_limit_Bern6->SetBranchAddress("limitErr", &limitErr_Bern6);
      t_limit_Bern6->SetBranchAddress("iToy", &iToy_Bern6);
      t_limit_GaussExp->SetBranchAddress("limit", &limit_GaussExp);
      t_limit_GaussExp->SetBranchAddress("limitErr", &limitErr_GaussExp);
      t_limit_GaussExp->SetBranchAddress("iToy", &iToy_GaussExp);
      double nToys_Bern6=t_limit_Bern6->GetEntries();
      double nToys_GaussExp=t_limit_GaussExp->GetEntries();
      for (unsigned int toy_Bern6=0; toy_Bern6<nToys_Bern6; ++toy_Bern6)
      {
        t_limit_Bern6->GetEvent(toy_Bern6);
        if (limitErr_Bern6*1000 < (injection*0.13+47)*10.0 && limit_Bern6 > -0.1)
        {
          h_strength_Bern6[i_mass]->Fill(limit_Bern6*1000.);
          h_strength_Bern6_err[i_mass]->Fill(limitErr_Bern6*1000.);
          
          // Check for this i_Toy in the Gauss-Exp tree
          for (unsigned int toy_GaussExp=0; toy_GaussExp<nToys_GaussExp; ++toy_GaussExp)
          {
            t_limit_GaussExp->GetEvent(toy_GaussExp);
            if (iToy_Bern6 == iToy_GaussExp)
            {
              if (limitErr_GaussExp*1000 < (injection*0.13+47)*10.0)
              {
                h_strength_GaussExp[i_mass]->Fill(limit_GaussExp*1000.);
                h_strength_GaussExp_err[i_mass]->Fill(limitErr_GaussExp*1000.);
                
                h_bias[i_mass]->Fill((limit_GaussExp-limit_Bern6)*1000.);
              }
            }
          }
        }
      }
      file_Bern6->Close();
      file_GaussExp->Close();
      
      
      // Fill Bernstein plots
      
      TCanvas *c_strength_Bern6=new TCanvas(("c_strength_Bern6_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength_Bern6", 700, 700);
      fixTH1F(h_strength_Bern6[i_mass]);
      h_strength_Bern6[i_mass]->Fit("gaus", "Q");
      double mean_Bern6=h_strength_Bern6[i_mass]->GetFunction("gaus")->GetParameter(1);
      double rms_Bern6=h_strength_Bern6[i_mass]->GetFunction("gaus")->GetParameter(2);
      if (rms_Bern6>h_strength_Bern6[i_mass]->GetRMS()*3. || rms_Bern6<h_strength_Bern6[i_mass]->GetRMS()*3.) rms_Bern6=h_strength_Bern6[i_mass]->GetRMS();
      double p=0.5, median_Bern6; h_strength_Bern6[i_mass]->GetQuantiles(1, &median_Bern6, &p);
      double median_Bern6_err=1.253*rms_Bern6/sqrt(nToys_Bern6);
      TPaveText *t_strength_Bern6=new TPaveText(0.6, 0.5, 0.9, 0.75, "NDC"); t_strength_Bern6->SetFillColor(kWhite);
      t_strength_Bern6->AddText(("mean = "+ftoa(mean_Bern6)).c_str());
      t_strength_Bern6->AddText(("rms = "+ftoa(rms_Bern6)).c_str());
      t_strength_Bern6->AddText(("rms/sqrt(N) = "+ftoa(rms_Bern6/sqrt(nToys_Bern6))).c_str());
      t_strength_Bern6->AddText(("median = "+ftoa(median_Bern6)).c_str());
      t_strength_Bern6->AddText(("median_err = "+ftoa(median_Bern6_err)).c_str());
      t_strength_Bern6->Draw();
      TLine *line=new TLine(injection*1000., 0, injection*1000., h_strength_Bern6[i_mass]->GetMaximum()); line->SetLineColor(kRed); line->Draw();
      TLine *line_med=new TLine(median_Bern6, 0, median_Bern6, h_strength_Bern6[i_mass]->GetMaximum()); line_med->SetLineColor(kBlue); line_med->Draw();
      TLine *line_med_err1=new TLine(median_Bern6+median_Bern6_err, 0, median_Bern6+median_Bern6_err, h_strength_Bern6[i_mass]->GetMaximum()); line_med_err1->SetLineColor(kGreen); line_med_err1->Draw();
      TLine *line_med_err2=new TLine(median_Bern6-median_Bern6_err, 0, median_Bern6-median_Bern6_err, h_strength_Bern6[i_mass]->GetMaximum()); line_med_err2->SetLineColor(kGreen); line_med_err2->Draw();
      c_strength_Bern6->SaveAs(("BiasDistributions/c_strength_Bern6_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      TCanvas *c_strength_Bern6_err=new TCanvas(("c_strength_Bern6_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength_Bern6_err", 700, 700);
      h_strength_Bern6_err[i_mass]->Draw();
      c_strength_Bern6_err->SaveAs(("BiasDistributions/c_strength_Bern6_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      
      // Fill Gauss-Exp plots
      
      TCanvas *c_strength_GaussExp=new TCanvas(("c_strength_GaussExp_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength_GaussExp", 700, 700);
      h_strength_GaussExp[i_mass]->Fit("gaus", "Q");
      double mean_GaussExp=h_strength_GaussExp[i_mass]->GetFunction("gaus")->GetParameter(1);
      double rms_GaussExp=h_strength_GaussExp[i_mass]->GetFunction("gaus")->GetParameter(2);
      if (rms_GaussExp>h_strength_GaussExp[i_mass]->GetRMS()*3. || rms_GaussExp<h_strength_GaussExp[i_mass]->GetRMS()*3.) rms_GaussExp=h_strength_GaussExp[i_mass]->GetRMS();
      double median_GaussExp; h_strength_GaussExp[i_mass]->GetQuantiles(1, &median_GaussExp, &p);
      double median_GaussExp_err=1.253*rms_GaussExp/sqrt(nToys_GaussExp);
      TPaveText *t_strength_GaussExp=new TPaveText(0.6, 0.5, 0.9, 0.75, "NDC"); t_strength_GaussExp->SetFillColor(kWhite);
      t_strength_GaussExp->AddText(("mean = "+ftoa(mean_GaussExp)).c_str());
      t_strength_GaussExp->AddText(("rms = "+ftoa(rms_GaussExp)).c_str());
      t_strength_GaussExp->AddText(("rms/sqrt(N) = "+ftoa(rms_GaussExp/sqrt(nToys_GaussExp))).c_str());
      t_strength_GaussExp->AddText(("median = "+ftoa(median_GaussExp)).c_str());
      t_strength_GaussExp->AddText(("median_err = "+ftoa(median_GaussExp_err)).c_str());
      t_strength_GaussExp->Draw();
      line=new TLine(injection*1000., 0, injection*1000., h_strength_GaussExp[i_mass]->GetMaximum()); line->SetLineColor(kRed); line->Draw();
      line_med=new TLine(median_GaussExp, 0, median_GaussExp, h_strength_GaussExp[i_mass]->GetMaximum()); line_med->SetLineColor(kBlue); line_med->Draw();
      line_med_err1=new TLine(median_GaussExp+median_GaussExp_err, 0, median_GaussExp+median_GaussExp_err, h_strength_GaussExp[i_mass]->GetMaximum()); line_med_err1->SetLineColor(kGreen); line_med_err1->Draw();
      line_med_err2=new TLine(median_GaussExp-median_GaussExp_err, 0, median_GaussExp-median_GaussExp_err, h_strength_GaussExp[i_mass]->GetMaximum()); line_med_err2->SetLineColor(kGreen); line_med_err2->Draw();
      c_strength_GaussExp->SaveAs(("BiasDistributions/c_strength_GaussExp_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      TCanvas *c_strength_GaussExp_err=new TCanvas(("c_strength_GaussExp_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength_GaussExp_err", 700, 700);
      // fixTH1F(h_strength_GaussExp_err[i_mass]);
      h_strength_GaussExp_err[i_mass]->Draw();
      c_strength_GaussExp_err->SaveAs(("BiasDistributions/c_strength_GaussExp_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      
      // Fill bias plots
      TCanvas *c_bias=new TCanvas(("c_bias_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_bias", 700, 700);
      h_bias[i_mass]->Fit("gaus", "Q");
      double mean_bias= h_bias[i_mass]->GetFunction("gaus")->GetParameter(1);
      double rms_bias=h_bias[i_mass]->GetFunction("gaus")->GetParameter(2);
      double median_bias; h_bias[i_mass]->GetQuantiles(1, &median_bias, &p);
      double median_bias_err=1.253*rms_bias/sqrt(nToys_GaussExp);
      TPaveText *t_strength_bias=new TPaveText(0.6, 0.5, 0.9, 0.75, "NDC"); t_strength_bias->SetFillColor(kWhite);
      t_strength_bias->AddText(("mean = "+ftoa(mean_bias)).c_str());
      t_strength_bias->AddText(("rms = "+ftoa(rms_bias)).c_str());
      t_strength_bias->AddText(("rms/sqrt(N) = "+ftoa(rms_bias/sqrt(nToys_GaussExp))).c_str());
      t_strength_bias->AddText(("median = "+ftoa(median_bias)).c_str());
      t_strength_bias->AddText(("median_err = "+ftoa(median_bias_err)).c_str());
      t_strength_bias->Draw();
      line=new TLine(0, 0, 0, h_strength_GaussExp[i_mass]->GetMaximum()); line->SetLineColor(kRed); line->Draw();
      line_med=new TLine(median_bias, 0, median_bias, h_bias[i_mass]->GetMaximum()); line_med->SetLineColor(kBlue); line_med->Draw();
      line_med_err1=new TLine(median_bias+median_bias_err, 0, median_bias+median_bias_err, h_bias[i_mass]->GetMaximum()); line_med_err1->SetLineColor(kGreen); line_med_err1->Draw();
      line_med_err2=new TLine(median_bias-median_bias_err, 0, median_bias-median_bias_err, h_bias[i_mass]->GetMaximum()); line_med_err2->SetLineColor(kGreen); line_med_err2->Draw();
      c_bias->SaveAs(("BiasDistributions/c_bias_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      
      masses.push_back(atof(mass[i_mass].c_str())); // +i_inj*5.
      strength_0.push_back(0);
      
      strength_mean_Bern6.push_back(median_Bern6);
      strength_rms_Bern6.push_back(rms_Bern6);
      strength_rms_sqrtN_Bern6.push_back(median_Bern6_err);
      strength_err_Bern6.push_back(h_strength_Bern6_err[i_mass]->GetMean());
      
      strength_mean_GaussExp.push_back(median_GaussExp);
      strength_rms_GaussExp.push_back(rms_GaussExp);
      strength_rms_sqrtN_GaussExp.push_back(median_GaussExp_err);
      strength_err_GaussExp.push_back(h_strength_GaussExp_err[i_mass]->GetMean());
      
      bias_mean.push_back(median_bias);
      bias_rms.push_back(rms_bias);
      bias_rms_sqrtN.push_back(median_bias_err);
      
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h2 align='center'> Mass = "<<mass[i_mass]<<"</h2>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_Bern6_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_Bern6_err_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_GaussExp_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_GaussExp_err_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"   <img src='"<<("c_bias_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"  </td>"<<std::endl;
      
    }
    outfile<<" </tr>"<<std::endl;
    outfile<<"</table>"<<std::endl;
    
    TGraphAsymmErrors *g_strength_Bern6=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_Bern6[0], &strength_0[0], &strength_0[0], &strength_err_Bern6[0], &strength_err_Bern6[0]);
    TGraphAsymmErrors *g_strength_rms_Bern6=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_Bern6[0], &strength_0[0], &strength_0[0], &strength_rms_Bern6[0], &strength_rms_Bern6[0]);
    TGraphAsymmErrors *g_strength_rms_sqrtN_Bern6=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_Bern6[0], &strength_0[0], &strength_0[0], &strength_rms_sqrtN_Bern6[0], &strength_rms_sqrtN_Bern6[0]);
    g_strength_Bern6->SetName(("g_strength_Bern6_"+injections[i_inj]).c_str());
    g_strength_rms_Bern6->SetName(("g_strength_rms_Bern6_"+injections[i_inj]).c_str());
    g_strength_rms_sqrtN_Bern6->SetName(("g_strength_rms_sqrtN_Bern6_"+injections[i_inj]).c_str());
    f_StrengthBias_Bern6->cd();
    g_strength_Bern6->Write();
    g_strength_rms_Bern6->Write();
    g_strength_rms_sqrtN_Bern6->Write();
    
    TGraphAsymmErrors *g_strength_GaussExp=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_GaussExp[0], &strength_0[0], &strength_0[0], &strength_err_GaussExp[0], &strength_err_GaussExp[0]);
    TGraphAsymmErrors *g_strength_rms_GaussExp=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_GaussExp[0], &strength_0[0], &strength_0[0], &strength_rms_GaussExp[0], &strength_rms_GaussExp[0]);
    TGraphAsymmErrors *g_strength_rms_sqrtN_GaussExp=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean_GaussExp[0], &strength_0[0], &strength_0[0], &strength_rms_sqrtN_GaussExp[0], &strength_rms_sqrtN_GaussExp[0]);
    TGraphAsymmErrors *g_bias_rms=new TGraphAsymmErrors(nPoints, &masses[0], &bias_mean[0], &strength_0[0], &strength_0[0], &bias_rms[0], &bias_rms[0]);
    TGraphAsymmErrors *g_bias_rms_sqrtN=new TGraphAsymmErrors(nPoints, &masses[0], &bias_mean[0], &strength_0[0], &strength_0[0], &bias_rms_sqrtN[0], &bias_rms_sqrtN[0]);
    g_strength_GaussExp->SetName(("g_strength_GaussExp_"+injections[i_inj]).c_str());
    g_strength_rms_GaussExp->SetName(("g_strength_rms_GaussExp_"+injections[i_inj]).c_str());
    g_strength_rms_sqrtN_GaussExp->SetName(("g_strength_rms_sqrtN_GaussExp_"+injections[i_inj]).c_str());
    g_bias_rms->SetName(("g_bias_rms_"+injections[i_inj]).c_str());
    g_bias_rms_sqrtN->SetName(("g_bias_rms_sqrtN_"+injections[i_inj]).c_str());
    f_StrengthBias_GaussExp->cd();
    g_strength_GaussExp->Write();
    g_strength_rms_GaussExp->Write();
    g_strength_rms_sqrtN_GaussExp->Write();
    g_bias_rms->Write();
    g_bias_rms_sqrtN->Write();
  }
  outfile<<"</body>"<<std::endl;
  outfile<<"</html>"<<std::endl;
  f_StrengthBias_Bern6->Close();
  f_StrengthBias_GaussExp->Close();
}
