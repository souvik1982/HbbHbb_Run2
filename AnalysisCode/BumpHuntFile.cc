#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <TStyle.h>
#include <TF1.h>
#include <TMath.h>
#include <TEllipse.h>
#include <TLine.h>
#include <TArrow.h>
#include <TPaveText.h>
#include <fstream>

#include "TDRStyle.h"

double rebin = 20;

double marg=19;

std::string ftoa(double i) 
{
  char res[10];
  sprintf(res, "%2.0f", i);
  std::string ret(res);
  return ret;
}

void drawRegion(double mean_H1_mass_, double mean_H2_mass_, double sigma_H1_mass_=15, double sigma_H2_mass_=15, double chi_1=1, double chi_2=2)
{
  TEllipse *circle1=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_1, sigma_H2_mass_*chi_1); 
  circle1->SetLineWidth(3); 
  circle1->SetLineColor(kBlack);
  circle1->SetFillStyle(0);
  circle1->Draw();
  
  TEllipse *circle2=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 90., 180.); circle2->SetLineWidth(3); circle2->SetNoEdges(); circle2->SetLineColor(kBlack); circle2->SetFillStyle(0); circle2->Draw();
  TEllipse *circle3=new TEllipse(mean_H1_mass_, mean_H2_mass_, sigma_H1_mass_*chi_2, sigma_H2_mass_*chi_2, 270., 360.); circle3->SetLineWidth(3); circle3->SetNoEdges(); circle3->SetLineColor(kBlack); circle3->SetFillStyle(0); circle3->Draw();
  TLine *line1=new TLine(mean_H1_mass_-sigma_H1_mass_*chi_2, mean_H2_mass_, mean_H1_mass_-sigma_H1_mass_*chi_1, mean_H2_mass_); line1->SetLineWidth(3); line1->SetLineColor(kBlack); line1->Draw();
  TLine *line2=new TLine(mean_H1_mass_+sigma_H1_mass_*chi_2, mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_1, mean_H2_mass_); line2->SetLineWidth(3); line2->SetLineColor(kBlack); line2->Draw();
  TLine *line3=new TLine(mean_H1_mass_, mean_H2_mass_-sigma_H2_mass_*chi_2, mean_H1_mass_, mean_H2_mass_-sigma_H2_mass_*chi_1); line3->SetLineWidth(3); line3->SetLineColor(kBlack); line3->Draw();
  TLine *line4=new TLine(mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_2, mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_1); line4->SetLineWidth(3); line4->SetLineColor(kBlack); line4->Draw();
  
  TArrow *arrow1=new TArrow(mean_H1_mass_, mean_H2_mass_+sigma_H2_mass_*chi_2*4., mean_H1_mass_, mean_H2_mass_, 0.02); arrow1->SetLineWidth(3); arrow1->SetLineColor(kBlack); arrow1->Draw();
  TPaveText *mod1=new TPaveText(mean_H1_mass_-marg, mean_H2_mass_+sigma_H2_mass_*chi_2*4.-marg, mean_H1_mass_+marg, mean_H2_mass_+sigma_H2_mass_*chi_2*4.+marg);
  mod1->SetBorderSize(0); mod1->SetFillColor(0); mod1->AddText("SR"); mod1->SetLineColor(kBlue); mod1->Draw("ARC");
  TArrow *arrow2_1=new TArrow(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_-sigma_H1_mass_*chi_2/2., mean_H2_mass_+sigma_H2_mass_*chi_2/2., 0.02); arrow2_1->SetLineWidth(3); arrow2_1->SetLineColor(kBlack);     
  TArrow *arrow2_2=new TArrow(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_2/2., mean_H2_mass_-sigma_H2_mass_*chi_2/2., 0.02); arrow2_2->SetLineWidth(3); arrow2_2->SetLineColor(kBlack);
  TLine *arrow2_3=new TLine(mean_H1_mass_+sigma_H1_mass_*chi_2*4., mean_H2_mass_, mean_H1_mass_+sigma_H1_mass_*chi_2*5., mean_H2_mass_); arrow2_3->SetLineWidth(3); arrow2_3->SetLineColor(kBlack);
  arrow2_1->Draw(); arrow2_2->Draw(); arrow2_3->Draw();
  TPaveText *mod2=new TPaveText(mean_H1_mass_+sigma_H1_mass_*chi_2*5.-marg, mean_H2_mass_+marg, mean_H1_mass_+sigma_H1_mass_*chi_2*5.+marg, mean_H2_mass_-marg);
  mod2->SetBorderSize(0); mod2->SetFillColor(0); mod2->AddText("SB"); mod2->SetLineColor(kBlack); mod2->Draw("ARC");
}

Double_t fit_background(Double_t *x, Double_t *par)
{
  Double_t ret=TMath::Exp(-(x[0]-par[0])*par[1])*par[2];
  return ret;
}

Double_t fit_signal(Double_t *x, Double_t *par)
{
  Double_t ret=TMath::Exp(-0.5*pow((x[0]-par[0])/par[1], 2))*par[2];
  return ret;
}

Double_t fit_signalBackground(Double_t *x, Double_t *par)
{
  return fit_background(x, par)+fit_signal(x, &par[3]);
}

struct FitParameters
{
  double backgroundOnly_chi2;
  double backgroundOnly_ndof;
  double best_range_min;
  double best_exponent;
  double best_backgroundNorm;
  double best_mean;
  double best_sigma;
  double best_signalNorm;
  double best_SB;
  double best_B;
  double best_chi2;
  double best_ndof;
};

FitParameters backgroundOnlyFit(TH1F *h)
{
  double range_min=h->GetBinCenter(h->GetMaximumBin());
  double range_max=h->GetBinCenter(h->FindLastBinAbove(0));
  
  h->GetXaxis()->SetRangeUser(0, range_max+250);
  
  TF1 *f_backgroundOnly=new TF1("f_backgroundOnly", fit_background, range_min, range_max, 3);
  f_backgroundOnly->SetLineColor(kBlack);
  f_backgroundOnly->SetParLimits(0, range_min-100, range_min+100);
  f_backgroundOnly->SetParLimits(1, 0.001, 1.);
  h->Fit(f_backgroundOnly, "QRN");
  
  h->SetMarkerStyle(20);
  h->SetLineColor(kBlack);
  h->Draw("");
  f_backgroundOnly->Draw("same");
  
  FitParameters fitParameters;
  fitParameters.backgroundOnly_chi2=f_backgroundOnly->GetChisquare();
  fitParameters.backgroundOnly_ndof=f_backgroundOnly->GetNDF();
  
  return fitParameters;
}

FitParameters bumpHunter(TH1F *h)
{
  double range_min=h->GetBinCenter(h->GetMaximumBin());
  double range_max=h->GetBinCenter(h->FindLastBinAbove(0));
  
  h->GetXaxis()->SetRangeUser(0, range_max+250);
  
  std::cout<<"range_min = "<<range_min<<std::endl;
  std::cout<<"range_max = "<<range_max<<std::endl;
  
  FitParameters bestFitParameters;
  
  TF1 *f_backgroundOnly=new TF1("f_backgroundOnly", fit_background, range_min, range_max, 3);
  f_backgroundOnly->SetLineColor(kBlack);
  f_backgroundOnly->SetParLimits(0, range_min-100, range_min+100);
  f_backgroundOnly->SetParLimits(1, 0.001, 1.);
  h->Fit(f_backgroundOnly, "QRN");
  bestFitParameters.backgroundOnly_chi2=f_backgroundOnly->GetChisquare();
  bestFitParameters.backgroundOnly_ndof=f_backgroundOnly->GetNDF();
  
  TF1 *f_signalBackground=new TF1("f_signalBackground", fit_signalBackground, range_min, range_max, 6);
  f_signalBackground->SetLineColor(kRed);
  TF1 *f_background=new TF1("f_background", fit_background, range_min, range_max, 3);
  f_background->SetLineColor(kBlue);
  double d_mean=100;
  double d_sigma=10;
  double old_significance=0;
  double old_chi2=9999;
  for (double mean=range_min+3.*d_mean; mean<range_max-3.*d_mean; mean+=d_mean)
  {
    for (double sigma=10; sigma<d_mean; sigma+=d_sigma)
    {
      f_signalBackground->SetParLimits(0, range_min-100, range_min+100);
      f_signalBackground->SetParLimits(1, 0.001, 1.);
      f_signalBackground->SetParLimits(2, 0.5*h->GetMaximum(), 2.*h->GetMaximum());
      f_signalBackground->SetParLimits(3, mean, mean+d_mean);
      f_signalBackground->SetParLimits(4, sigma-10, sigma+10);
      f_signalBackground->SetParLimits(5, 0, 100);
      h->Fit(f_signalBackground, "QRN");
      double chi2=f_signalBackground->GetChisquare();
      double ndof=double(f_signalBackground->GetNDF());
      double chi2_norm=chi2/ndof;
      
      f_background->FixParameter(0, f_signalBackground->GetParameter(0));
      f_background->FixParameter(1, f_signalBackground->GetParameter(1));
      f_background->FixParameter(2, f_signalBackground->GetParameter(2));
      
      double mean_fit=f_signalBackground->GetParameter(3);
      double sigma_fit=f_signalBackground->GetParameter(4);
      double SB=f_signalBackground->Integral(mean_fit-sigma_fit*4., mean_fit+sigma_fit*4.)/rebin;
      double B=f_background->Integral(mean_fit-sigma_fit*4., mean_fit+sigma_fit*4.)/rebin;
      double significance=(SB-B)/pow(SB, 0.5);
      // if (significance>old_significance) 
      if (chi2_norm<old_chi2)
      {
        bestFitParameters.best_range_min=f_signalBackground->GetParameter(0);
        bestFitParameters.best_exponent=f_signalBackground->GetParameter(1);
        bestFitParameters.best_backgroundNorm=f_signalBackground->GetParameter(2);
        bestFitParameters.best_mean=mean_fit;
        bestFitParameters.best_sigma=sigma_fit;
        bestFitParameters.best_signalNorm=f_signalBackground->GetParameter(5);
        bestFitParameters.best_SB=SB;
        bestFitParameters.best_B=B;
        bestFitParameters.best_chi2=chi2;
        bestFitParameters.best_ndof=ndof;
        old_significance=significance;
        old_chi2=chi2_norm;
      }
    }
  }
  
  f_signalBackground->FixParameter(0, bestFitParameters.best_range_min);
  f_signalBackground->FixParameter(1, bestFitParameters.best_exponent);
  f_signalBackground->FixParameter(2, bestFitParameters.best_backgroundNorm);
  f_signalBackground->FixParameter(3, bestFitParameters.best_mean);
  f_signalBackground->FixParameter(4, bestFitParameters.best_sigma);
  f_signalBackground->FixParameter(5, bestFitParameters.best_signalNorm);
  f_background->FixParameter(0, bestFitParameters.best_range_min);
  f_background->FixParameter(1, bestFitParameters.best_exponent);
  f_background->FixParameter(2, bestFitParameters.best_backgroundNorm);
  h->SetMarkerStyle(20);
  h->SetLineColor(kBlack);
  h->Draw("");
  f_backgroundOnly->Draw("same");
  f_signalBackground->Draw("same");
  f_background->Draw("same");
  
  TLegend *leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  leg->AddEntry(f_backgroundOnly, "Background Only");
  leg->AddEntry(f_background, "Background in S+B");
  leg->AddEntry(f_signalBackground, "Signal");
  leg->SetFillColor(0);
  leg->Draw();
  
  return bestFitParameters;
} 

void BumpHuntFile()
{
  ofstream outfile("Stethoscope/index.html");
  outfile<<"<html>"<<std::endl;
  outfile<<"<body>"<<std::endl;
  outfile<<"<h1> <img src=\"stethoscope.png\" width=\"300\" height=\"300\" align=\"middle\"/> The X -> YY -> (bb)(bb) Bump Hunting Stethoscope </h1>"<<std::endl;
  outfile<<"<br/>"<<std::endl;
  outfile<<"<table border='1'>"<<std::endl;
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  for (double mH1=50.; mH1<200.; mH1+=15)
  {
    for (double mH2=50.; mH2<200.; mH2+=15)
    {
    
      std::string histfilename="Histograms_Data_BTagCSV_2015_Skim_"+ftoa(mH1)+"_"+ftoa(mH2)+".root";
      TFile *f_data=new TFile(histfilename.c_str());
      TH2F *h_mH1_mH2_asym=(TH2F*)f_data->Get("h_mH1_mH2_asym");
      TH1F *h_mX_SR=(TH1F*)f_data->Get("h_mX_SR");
      TH1F *h_mX_SR_KinFit=(TH1F*)f_data->Get("h_mX_SR_kinFit");
      TH1F *h_mX_SB=(TH1F*)f_data->Get("h_mX_SB");
      TH1F *h_mX_SB_KinFit=(TH1F*)f_data->Get("h_mX_SB_kinFit");
      
      h_mH1_mH2_asym->RebinX(2);
      h_mH1_mH2_asym->RebinY(2);
      h_mX_SR->Rebin(rebin);
      h_mX_SR_KinFit->Rebin(rebin);
      h_mX_SB->Rebin(rebin);
      h_mX_SB_KinFit->Rebin(rebin);
      
      TCanvas *c_mH1_mH2_asym=new TCanvas("c_mH1_mH2_asym", "c_mH1_mH2_asym", 700, 700);
      h_mH1_mH2_asym->Draw("colz");
      drawRegion(mH1, mH2);
      c_mH1_mH2_asym->SaveAs(("Stethoscope/c_mH1_mH2_asym_"+ftoa(mH1)+"_"+ftoa(mH2)+".png").c_str());
      delete c_mH1_mH2_asym;
      
      FitParameters bestFitParameters_SB, 
                    bestFitParameters_SB_KinFit,
                    bestFitParameters_SR,
                    bestFitParameters_SR_KinFit;
      
      TCanvas *c_mX_SB=new TCanvas("c_mX_SB", "c_mX_SB", 700, 700);
      h_mX_SB->SetMinimum(0.01);
      c_mX_SB->SetLogy();
      bestFitParameters_SB=backgroundOnlyFit(h_mX_SB);
      c_mX_SB->SaveAs(("Stethoscope/c_mX_SB_"+ftoa(mH1)+"_"+ftoa(mH2)+".png").c_str());
      
      TCanvas *c_mX_SB_KinFit=new TCanvas("c_mX_SB_KinFit", "c_mX_SB_KinFit", 700, 700);
      h_mX_SB_KinFit->SetMinimum(0.01);
      c_mX_SB_KinFit->SetLogy();
      bestFitParameters_SB_KinFit=backgroundOnlyFit(h_mX_SB_KinFit);
      c_mX_SB_KinFit->SaveAs(("Stethoscope/c_mX_SB_KinFit_"+ftoa(mH1)+"_"+ftoa(mH2)+".png").c_str());
  
      TCanvas *c_mX_SR=new TCanvas("c_mX_SR", "c_mX_SR", 700, 700);
      h_mX_SR->SetMinimum(0.01);
      c_mX_SR->SetLogy();
      bestFitParameters_SR=bumpHunter(h_mX_SR);
      c_mX_SR->SaveAs(("Stethoscope/c_mX_SR_"+ftoa(mH1)+"_"+ftoa(mH2)+".png").c_str());
      
      TCanvas *c_mX_SR_KinFit=new TCanvas("c_mX_SR_KinFit", "c_mX_SR_KinFit", 700, 700);
      h_mX_SR_KinFit->SetMinimum(0.01);
      c_mX_SR_KinFit->SetLogy();
      bestFitParameters_SR_KinFit=bumpHunter(h_mX_SR_KinFit);
      c_mX_SR_KinFit->SaveAs(("Stethoscope/c_mX_SR_KinFit_"+ftoa(mH1)+"_"+ftoa(mH2)+".png").c_str());
      
      f_data->Close();
      
      outfile<<" <tr>"<<std::endl;
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h3> mH1 vs mH2 </h3> "<<std::endl;
      outfile<<"    <img src=\""<<("c_mH1_mH2_asym_"+ftoa(mH1)+"_"+ftoa(mH2)+".png")<<"\"/>"<<std::endl;
      outfile<<"    mH1 = "<<mH1<<", mH2 = "<<mH2<<std::endl;
      outfile<<"  </td>"<<std::endl;
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h3 align=\"center\"> SB </h3>"<<std::endl;
      outfile<<"   <img src=\""<<("c_mX_SB_"+ftoa(mH1)+"_"+ftoa(mH2)+".png")<<"\"/>"<<std::endl;
      outfile<<"   Background only fit chi2/ndof = "<<bestFitParameters_SB.backgroundOnly_chi2<<"/"<<bestFitParameters_SB.backgroundOnly_ndof<<" = "<<bestFitParameters_SB.backgroundOnly_chi2/bestFitParameters_SB.backgroundOnly_ndof<<std::endl;
      outfile<<"  </td>"<<std::endl;
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h3 align=\"center\"> SB KinFit </h3>"<<std::endl;
      outfile<<"   <img src=\""<<("c_mX_SB_KinFit_"+ftoa(mH1)+"_"+ftoa(mH2)+".png")<<"\"/>"<<std::endl;
      outfile<<"   Background only fit chi2/ndof = "<<bestFitParameters_SB_KinFit.backgroundOnly_chi2<<"/"<<bestFitParameters_SB_KinFit.backgroundOnly_ndof<<" = "<<bestFitParameters_SB_KinFit.backgroundOnly_chi2/bestFitParameters_SB_KinFit.backgroundOnly_ndof<<std::endl;
      outfile<<"  </td>"<<std::endl;
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h3 align=\"center\"> SR </h3>"<<std::endl;
      outfile<<"   <img src=\""<<("c_mX_SR_"+ftoa(mH1)+"_"+ftoa(mH2)+".png")<<"\"/>"<<std::endl;
      outfile<<"   Background only fit chi2/ndof = "<<bestFitParameters_SR.backgroundOnly_chi2<<"/"<<bestFitParameters_SR.backgroundOnly_ndof<<" = "<<bestFitParameters_SR.backgroundOnly_chi2/bestFitParameters_SR.backgroundOnly_ndof<<"<br/>"<<std::endl;
      outfile<<"   S+B fit chi2/ndof = "<<bestFitParameters_SR.best_chi2<<"/"<<bestFitParameters_SR.best_ndof<<" = "<<bestFitParameters_SR.best_chi2/bestFitParameters_SR.best_ndof<<"<br/>"<<std::endl;
      outfile<<"   S = "<<bestFitParameters_SR.best_SB-bestFitParameters_SR.best_B<<", B = "<<bestFitParameters_SR.best_B<<", S/sqrt(S+B) = "<<(bestFitParameters_SR.best_SB-bestFitParameters_SR.best_B)/pow(bestFitParameters_SR.best_SB, 0.5)<<"<br/>"<<std::endl;
      outfile<<"   Signal mean = "<<bestFitParameters_SR.best_mean<<", sigma = "<<bestFitParameters_SR.best_sigma<<std::endl;
      outfile<<"  </td>"<<std::endl;
      outfile<<"  <td>"<<std::endl;
      outfile<<"   <h3 align=\"center\"> SR KinFit </h3>"<<std::endl;
      outfile<<"   <img src=\""<<("c_mX_SR_KinFit_"+ftoa(mH1)+"_"+ftoa(mH2)+".png")<<"\"/>"<<std::endl;
      outfile<<"   Background only fit chi2/ndof = "<<bestFitParameters_SR_KinFit.backgroundOnly_chi2<<"/"<<bestFitParameters_SR_KinFit.backgroundOnly_ndof<<" = "<<bestFitParameters_SR_KinFit.backgroundOnly_chi2/bestFitParameters_SR_KinFit.backgroundOnly_ndof<<"<br/>"<<std::endl;
      outfile<<"   S+B fit chi2/ndof = "<<bestFitParameters_SR_KinFit.best_chi2<<"/"<<bestFitParameters_SR_KinFit.best_ndof<<" = "<<bestFitParameters_SR_KinFit.best_chi2/bestFitParameters_SR_KinFit.best_ndof<<"<br/>"<<std::endl;
      outfile<<"   S = "<<bestFitParameters_SR_KinFit.best_SB-bestFitParameters_SR_KinFit.best_B<<", B = "<<bestFitParameters_SR_KinFit.best_B<<", S/sqrt(S+B) = "<<(bestFitParameters_SR_KinFit.best_SB-bestFitParameters_SR_KinFit.best_B)/pow(bestFitParameters_SR_KinFit.best_SB, 0.5)<<"<br/>"<<std::endl;
      outfile<<"   Signal mean = "<<bestFitParameters_SR_KinFit.best_mean<<", sigma = "<<bestFitParameters_SR_KinFit.best_sigma<<std::endl;
      outfile<<"  </td>"<<std::endl;
      outfile<<" </tr>"<<std::endl;
      
    }
  }
  
  outfile<<"</table>"<<std::endl;
  outfile<<"</body>"<<std::endl;
  outfile<<"</html>"<<std::endl;
  
}
