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
  h->GetXaxis()->SetRangeUser(mean-5.*rms, mean+5.*rms);
}

void fixPositiveTH1F(TH1F *h)
{
  double mean=h->GetMean();
  h->GetXaxis()->SetRangeUser(0.0, 2.*mean);
}

void BiasStudy()
{
  std::string mass[]={"450", "500", "550", "600", "650", "700", "800", "900", "1000", "1100"};
  double cols[]={kRed-2, kRed, kRed+2, kGreen, kBlue, kOrange, kBlack, kViolet, kCyan, kMagenta, kBlue+2};
  int nPoints=sizeof(mass)/sizeof(mass[0]);
  
  std::string injections[]={"0.00", "0.01", "0.05", "0.1", "0.5", "1"};
  int nInjections=sizeof(injections)/sizeof(injections[0]);
  
  int toys=200;
  
  std::cout<<"nPoints = "<<nPoints<<std::endl;
  std::cout<<"nInjections = "<<nInjections<<std::endl;
  
  ofstream outfile;
  outfile.open("PullDistributions/PullDistributions.html");
  outfile<<"<html>"<<std::endl;
  outfile<<"<head>"<<std::endl;
  outfile<<"</head>"<<std::endl;
  outfile<<"<body>"<<std::endl;
  outfile<<"<h1> Fitted Signal Strength Distributions </h1>"<<std::endl;
  TFile *f_StrengthBias=new TFile("f_StrengthBias.root", "recreate");
  for (unsigned int i_inj=0; i_inj<nInjections; ++i_inj)
  {
    double injection=atof((injections[i_inj]).c_str());
    std::cout<<"Injection Strength = "<<injection<<std::endl;
    
    std::vector<double> masses;
    std::vector<double> strength_mean;
    std::vector<double> strength_rms;
    std::vector<double> strength_rms_sqrtN;
    std::vector<double> strength_err;
    std::vector<double> strength_0;
    
    TH1F *h_strength[12], *h_strength_err[12];
    
    outfile<<"<table border='1'>"<<std::endl;
    outfile<<" <tr>"<<std::endl;
    outfile<<"  <td>"<<std::endl;
    outfile<<"   <h2>Injected signal strength = "<<injection*1000.<<" (fb) </h2>"<<std::endl;
    outfile<<"   <img src='c_BiasStudy_Split_"<<injections[i_inj]<<".png'/>"<<std::endl;
    outfile<<"  </td>"<<std::endl;
    
    for (int i_mass=0; i_mass<nPoints; ++i_mass)
    {
      h_strength[i_mass]=new TH1F(("h_strength_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed #mu; #mu (fb)", 40., 1, -1);
      h_strength_err[i_mass]=new TH1F(("h_strength_err_"+mass[i_mass]+"_"+injections[i_inj]).c_str(), "Reconstructed #delta#mu; #delta#mu (fb)", 40., 1, -1);
      
      TFile *file=new TFile(("Injection_"+injections[i_inj]+"pb/higgsCombineFit_higgsCombineHbbHbb_19invfb_mX"+mass[i_mass]+"_Output.root").c_str());
      TTree *t_limit=(TTree*)file->Get("limit");
      double limit;
      double limitErr;
      t_limit->SetBranchAddress("limit", &limit);
      t_limit->SetBranchAddress("limitErr", &limitErr);
      double nToys=t_limit->GetEntries();
      // nToys=250;
      for (unsigned int toy=0; toy<nToys; ++toy)
      {
        t_limit->GetEvent(toy);
        if (limitErr*1000 < (injection*0.13+47)*10.0 &&
             limit>-0.1)
        {
          h_strength[i_mass]->Fill(limit*1000.);
          h_strength_err[i_mass]->Fill(limitErr*1000.);
        }
      }
      file->Close();
      
      TCanvas *c_strength=new TCanvas(("c_strength_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength", 700, 700);
      fixTH1F(h_strength[i_mass]);
      h_strength[i_mass]->Fit("gaus", "Q");
      double mean=h_strength[i_mass]->GetFunction("gaus")->GetParameter(1);
      double rms=h_strength[i_mass]->GetFunction("gaus")->GetParameter(2);
      if (rms>h_strength[i_mass]->GetRMS()*3. || rms<h_strength[i_mass]->GetRMS()*3.) rms=h_strength[i_mass]->GetRMS();
      double p=0.5, median; h_strength[i_mass]->GetQuantiles(1, &median, &p);
      double median_err=1.253*rms/sqrt(nToys);
      TPaveText *t_strength=new TPaveText(0.6, 0.5, 0.9, 0.75, "NDC"); t_strength->SetFillColor(kWhite);
      t_strength->AddText(("mean = "+ftoa(mean)).c_str());
      t_strength->AddText(("rms = "+ftoa(rms)).c_str());
      t_strength->AddText(("rms/sqrt(N) = "+ftoa(rms/sqrt(nToys))).c_str());
      t_strength->AddText(("median = "+ftoa(median)).c_str());
      t_strength->AddText(("median_err = "+ftoa(median_err)).c_str());
      t_strength->Draw();
      TLine *line=new TLine(injection*1000., 0, injection*1000., h_strength[i_mass]->GetMaximum()); line->SetLineColor(kRed); line->Draw();
      TLine *line_med=new TLine(median, 0, median, h_strength[i_mass]->GetMaximum()); line_med->SetLineColor(kBlue); line_med->Draw();
      TLine *line_med_err1=new TLine(median+median_err, 0, median+median_err, h_strength[i_mass]->GetMaximum()); line_med_err1->SetLineColor(kGreen); line_med_err1->Draw();
      TLine *line_med_err2=new TLine(median-median_err, 0, median-median_err, h_strength[i_mass]->GetMaximum()); line_med_err2->SetLineColor(kGreen); line_med_err2->Draw();
      c_strength->SaveAs(("PullDistributions/c_strength_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      TCanvas *c_strength_err=new TCanvas(("c_strength_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str(), "c_strength_err", 700, 700);
      // fixTH1F(h_strength_err[i_mass]);
      h_strength_err[i_mass]->Draw();
      c_strength_err->SaveAs(("PullDistributions/c_strength_err_"+mass[i_mass]+"_"+injections[i_inj]+".png").c_str());
      
      masses.push_back(atof(mass[i_mass].c_str())); // +i_inj*5.
      
      // strength_mean.push_back(mean);
      // strength_rms.push_back(rms);
      // strength_rms_sqrtN.push_back(rms/sqrt(nToys));
      
      strength_mean.push_back(median);
      strength_rms.push_back(rms);
      strength_rms_sqrtN.push_back(median_err);
      
      strength_err.push_back(h_strength_err[i_mass]->GetMean());
      strength_0.push_back(0);
      
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h2 align='center'> Mass = "<<mass[i_mass]<<"</h2>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"   <img src='"<<("c_strength_err_"+mass[i_mass]+"_"+injections[i_inj]+".png")<<"'/>"<<std::endl;
      outfile<<"  </td>"<<std::endl;
      
    }
    outfile<<" </tr>"<<std::endl;
    outfile<<"</table>"<<std::endl;
    
    TGraphAsymmErrors *g_strength=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean[0], &strength_0[0], &strength_0[0], &strength_err[0], &strength_err[0]);
    TGraphAsymmErrors *g_strength_rms=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean[0], &strength_0[0], &strength_0[0], &strength_rms[0], &strength_rms[0]);
    TGraphAsymmErrors *g_strength_rms_sqrtN=new TGraphAsymmErrors(nPoints, &masses[0], &strength_mean[0], &strength_0[0], &strength_0[0], &strength_rms_sqrtN[0], &strength_rms_sqrtN[0]);
    g_strength->SetName(("g_strength_"+injections[i_inj]).c_str());
    g_strength_rms->SetName(("g_strength_rms_"+injections[i_inj]).c_str());
    g_strength_rms_sqrtN->SetName(("g_strength_rms_sqrtN_"+injections[i_inj]).c_str());
    f_StrengthBias->cd();
    g_strength->Write();
    g_strength_rms->Write();
    g_strength_rms_sqrtN->Write();
    
  }
  outfile<<"</body>"<<std::endl;
  outfile<<"</html>"<<std::endl;
  f_StrengthBias->Close();
}
