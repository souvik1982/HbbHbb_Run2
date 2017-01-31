#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

#include "TDRStyle.h"

bool first=true;

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0, double g=0, double h=0, double i=0, double j=0, double k=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f+g*g+h*h+i*i+j*j+k*k, 0.5);
}

TH1D* RMSY(TH2F *h)
{
  TH1D* h_RMS=h->ProjectionX();
  h_RMS->SetName(("res_"+std::string(h->GetName())).c_str());
  // std::cout<<"h_RMS->GetName() = "<<h_RMS->GetName()<<std::endl;
  for (int i=1; i<=h_RMS->GetNbinsX(); i+=1)
  {
    TH1F *h_ProjectionY_temp=(TH1F*)h->ProjectionY("_px", i, i);
    // std::cout<<"bin "<<i<<" h_ProjectionY_temp->GetEntries() = "<<h_ProjectionY_temp->GetEntries()<<std::endl;
    if (h_ProjectionY_temp->GetEntries()>100)
    {
      h_RMS->SetBinContent(i, h_ProjectionY_temp->GetRMS());
      h_RMS->SetBinError(i, h_ProjectionY_temp->GetRMSError());
    }
    else
    {
      h_RMS->SetBinContent(i, 0);
      h_RMS->SetBinError(i, 0);
    }
  }
  return h_RMS;
}

TH1D* MEANY(TH2F *h)
{
  TH1D* h_MEAN=h->ProjectionX();
  h_MEAN->SetName(("mean_"+std::string(h->GetName())).c_str());
  for (int i=1; i<=h_MEAN->GetNbinsX(); i+=1)
  {
    TH1F *h_ProjectionY_temp=(TH1F*)h->ProjectionY("_px", i, i);
    if (h_ProjectionY_temp->GetEntries()>100)
    {
      h_MEAN->SetBinContent(i, h_ProjectionY_temp->GetMean());
      h_MEAN->SetBinError(i, h_ProjectionY_temp->GetMeanError());
    }
    else
    {
      h_MEAN->SetBinContent(i, 0);
      h_MEAN->SetBinError(i, 0);
    }
  }
  return h_MEAN;
}

Double_t fit_calorimeter(Double_t *x, Double_t *par)
{
  // Double_t result=quad(par[0]*pow(x[0], 0.5), par[1]); //, par[3]*(x[0]-par[1]));
  Double_t result=par[0]*pow(x[0], 0.5);
  return result;
}

void Display_pT_Resolution(std::vector<TFile*> *v)
{
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_0_1p4");
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5=(TH2F*)v->at(0)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5");
  h_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; Jet p_{T}^{reco} (GeV); Jet p_{T}^{reco} - p_{T}^{parton} (GeV)");
  h_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.4);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_pT_res_vs_pT_eta_0_1p4->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_0_1p4"));
    h_jet_pT_res_vs_pT_eta_1p4_2p5->Add((TH2F*)v->at(i)->Get("h_jet_pT_res_vs_pT_eta_1p4_2p5"));
  }
  h_jet_pT_res_vs_pT_eta_0_1p4->RebinX(2);
  h_jet_pT_res_vs_pT_eta_0_1p4->RebinY(2);
  h_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 650);
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_0_1p4=MEANY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetRangeUser(-100, 200);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_0_1p4", "pol2", 40, 500);
  // h_MEAN_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_MEAN_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_0_1p4=RMSY(h_jet_pT_res_vs_pT_eta_0_1p4);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)");
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetRangeUser(0, 120);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 600);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_pT_res_vs_pT_eta_0_1p4=new TF1("f_RMS_jet_pT_res_vs_pT_eta_0_1p4", "pol2", 40, 550);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Fit(f_RMS_jet_pT_res_vs_pT_eta_0_1p4, "R");
  
  h_jet_pT_res_vs_pT_eta_1p4_2p5->RebinX(2);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->RebinY(2);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 500);
  
  TH1D *h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=MEANY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)");
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetRangeUser(-100, 100);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5=new TF1("f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5", "pol2", 40, 550);
  // h_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f_MEAN_jet_pT_res_vs_pT_eta_1p4_2p5, "R");
  
  TH1D *h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=RMSY(h_jet_pT_res_vs_pT_eta_1p4_2p5);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)");
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetRangeUser(0, 60);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 400);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=new TF1("f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5", "pol1", 40, 350);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Fit(f_RMS_jet_pT_res_vs_pT_eta_1p4_2p5, "R");
  
  TCanvas *c_jet_pT_res_vs_pT_eta_0_1p4=new TCanvas("c_jet_pT_res_vs_pT_eta_0_1p4", "c_jet_pT_res_vs_pT_eta_0_1p4", 700, 700);
  h_jet_pT_res_vs_pT_eta_0_1p4->Draw("colz");
  c_jet_pT_res_vs_pT_eta_0_1p4->SaveAs("c_jet_pT_res_vs_pT_eta_0_1p4.png");
  
  TCanvas *c_RMS_jet_pT_res_vs_pT_eta_0_1p4=new TCanvas("c_RMS_jet_pT_res_vs_pT_eta_0_1p4", "c_RMS_jet_pT_res_vs_pT_eta_0_1p4", 700, 700);
  h_RMS_jet_pT_res_vs_pT_eta_0_1p4->Draw();
  c_RMS_jet_pT_res_vs_pT_eta_0_1p4->SaveAs("c_RMS_jet_pT_res_vs_pT_eta_0_1p4.png");
  
  TCanvas *c_jet_pT_res_vs_pT_eta_1p4_2p5=new TCanvas("c_jet_pT_res_vs_pT_eta_1p4_2p5", "c_jet_pT_res_vs_pT_eta_1p4_2p5", 700, 700);
  h_jet_pT_res_vs_pT_eta_1p4_2p5->Draw("colz");
  c_jet_pT_res_vs_pT_eta_1p4_2p5->SaveAs("c_jet_pT_res_vs_pT_eta_1p4_2p5.png");
  
  TCanvas *c_RMS_jet_pT_res_vs_pT_eta_1p4_2p5=new TCanvas("c_RMS_jet_pT_res_vs_pT_eta_1p4_2p5", "c_RMS_jet_pT_res_vs_pT_eta_1p4_2p5", 700, 700);
  h_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->Draw();
  c_RMS_jet_pT_res_vs_pT_eta_1p4_2p5->SaveAs("c_RMS_jet_pT_res_vs_pT_eta_1p4_2p5.png");
}

void Display_pT_Resolution_vsPartonpT(std::vector<TFile*> *v)
{
  TH2F *h_recopT_minus_partpT_vs_partpT_eta_0_1p4=(TH2F*)v->at(0)->Get("h_recopT_minus_partpT_vs_partpT_eta_0_1p4");
  TH2F *h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=(TH2F*)v->at(0)->Get("h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5");
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetTitle("; Jet p_{T}^{parton} (GeV); Jet p_{T}^{reco} - p_{T}^{parton} (GeV)");
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.4);
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_recopT_minus_partpT_vs_partpT_eta_0_1p4->Add((TH2F*)v->at(i)->Get("h_recopT_minus_partpT_vs_partpT_eta_0_1p4"));
    h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->Add((TH2F*)v->at(i)->Get("h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5"));
  }
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->RebinX(2);
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->RebinY(2);
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 650);
  
  TH1D *h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4=MEANY(h_recopT_minus_partpT_vs_partpT_eta_0_1p4);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetTitle("; b Jet p_{T}^{parton} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)"); // Souvik
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetYaxis()->SetRangeUser(-100, 200);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TF1("f_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4", "pol0", 40, 500);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4->Fit(f_MEAN_recopT_minus_partpT_vs_partpT_eta_0_1p4, "R");
  
  TH1D *h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4=RMSY(h_recopT_minus_partpT_vs_partpT_eta_0_1p4);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetTitle("; b Jet p_{T}^{parton} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)"); // Souvik
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetYaxis()->SetRangeUser(0, 80);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetXaxis()->SetRangeUser(0, 600);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->GetXaxis()->SetTitleOffset(1.2);
  /*TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4", "[0]+[1]*(1-exp(-[2]*x))", 40, 600);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(0, 5, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(1, 40, 50);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(2, 0.0, 0.01);*/
  /*TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4", "[0]+[1]*sqrt(x-[2])+[3]*(x-[2])", 40, 500);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(0, -200, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(1, 1, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(2, -200, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SetParLimits(3, -20, 10);*/
  TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4", fit_calorimeter, 40, 500, 1);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->Fit(f_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4, "R");
  
  h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->RebinX(2);
  h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->RebinY(2);
  h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 650);
  
  TH1D *h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=MEANY(h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{parton} (GeV); b Jet <(p_{T}^{reco} - p_{T}^{parton})> (GeV)"); // Souvik
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetYaxis()->SetRangeUser(-100, 200);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TF1("f_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", "pol0", 40, 350);
  h_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->Fit(f_MEAN_recopT_minus_partpT_vs_partpT_eta_1p4_2p5, "R");
  
  TH1D *h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=RMSY(h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetTitle("; b Jet p_{T}^{parton} (GeV); b Jet #sigma(p_{T}^{reco} - p_{T}^{parton}) (GeV)"); // Souvik
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetYaxis()->SetRangeUser(0, 80);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetXaxis()->SetRangeUser(0, 400);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->GetXaxis()->SetTitleOffset(1.2);
  /*TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", "[0]+[1]*(1-exp(-[2]*x))", 40, 600);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(0, 1, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(1, 20, 50);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(2, 0.0, 0.02);*/
  /*TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", "[0]+[1]*sqrt(x-[2])", 40, 350);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(0, -10, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(1, 1, 10);
  f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SetParLimits(2, -10, 10);*/
  TF1 *f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TF1("f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", fit_calorimeter, 40, 350, 1);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->Fit(f_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5, "R");
  
  TCanvas *c_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TCanvas("c_recopT_minus_partpT_vs_partpT_eta_0_1p4", "c_recopT_minus_partpT_vs_partpT_eta_0_1p4", 700, 700);
  h_recopT_minus_partpT_vs_partpT_eta_0_1p4->Draw("colz");
  c_recopT_minus_partpT_vs_partpT_eta_0_1p4->SaveAs("c_recopT_minus_partpT_vs_partpT_eta_0_1p4.png");
  
  TCanvas *c_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4=new TCanvas("c_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4", "c_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4", 700, 700);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->Draw();
  c_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4->SaveAs("c_RMS_recopT_minus_partpT_vs_partpT_eta_0_1p4.png");
  
  TCanvas *c_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TCanvas("c_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", "c_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", 700, 700);
  h_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->Draw("colz");
  c_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SaveAs("c_recopT_minus_partpT_vs_partpT_eta_1p4_2p5.png");
  
  TCanvas *c_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5=new TCanvas("c_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", "c_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5", 700, 700);
  h_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->Draw("colz");
  c_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5->SaveAs("c_RMS_recopT_minus_partpT_vs_partpT_eta_1p4_2p5.png");
  
}

void Display_eta_ResolutionForFile(std::vector<TFile*> *v)
{

  TH2F *h_jet_eta_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_eta_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_eta_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_eta_res_vs_pT"));
  }
  h_jet_eta_res_vs_pT->RebinX(2);
  h_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-1, 1);
  h_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet (#eta^{reco} - #eta^{parton})");
  h_jet_eta_res_vs_pT->GetXaxis()->SetTitleOffset(1.4);
  h_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  
  TH1D *h_MEAN_jet_eta_res_vs_pT=MEANY(h_jet_eta_res_vs_pT);
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet <(#eta^{reco} - #eta^{parton})>");
  h_MEAN_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_MEAN_jet_eta_res_vs_pT=new TF1("f_MEAN_jet_eta_res_vs_pT", "pol0", 40, 500);
  h_MEAN_jet_eta_res_vs_pT->Fit(f_MEAN_jet_eta_res_vs_pT, "R");
  
  TH1D *h_RMS_jet_eta_res_vs_pT=RMSY(h_jet_eta_res_vs_pT);
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.15);
  h_RMS_jet_eta_res_vs_pT->GetXaxis()->SetRangeUser(0, 600);
  h_RMS_jet_eta_res_vs_pT->SetTitle("; b Jet p_{T}^{reco}; b Jet #sigma(#eta^{reco} - #eta^{parton})");
  h_RMS_jet_eta_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  TF1 *f_RMS_jet_eta_res_vs_pT=new TF1("f_RMS_jet_eta_res_vs_pT", "[0]+[1]/x+[2]/(sqrt(x))", 40, 500);
  h_RMS_jet_eta_res_vs_pT->Fit(f_RMS_jet_eta_res_vs_pT, "R");
  
  TCanvas *c_jet_eta_res_vs_pT=new TCanvas("c_jet_eta_res_vs_pT", "c_jet_eta_res_vs_pT", 700, 700);
  h_jet_eta_res_vs_pT->Draw("colz");
  c_jet_eta_res_vs_pT->SaveAs("c_jet_eta_res_vs_pT.png");
  
  TCanvas *c_RMS_jet_eta_res_vs_pT=new TCanvas("c_RMS_jet_eta_res_vs_pT", "c_RMS_jet_eta_res_vs_pT", 700, 700);
  h_RMS_jet_eta_res_vs_pT->Draw();
  c_RMS_jet_eta_res_vs_pT->SaveAs("c_RMS_jet_eta_res_vs_pT.png");
  
  TCanvas *c_eta_Resolution_pT=new TCanvas("c_eta_Resolution_pT", "c_eta_Resolution_pT", 2100, 700);
  c_eta_Resolution_pT->Divide(3,1);
  c_eta_Resolution_pT->cd(1);
  h_jet_eta_res_vs_pT->Draw("colz");
  c_eta_Resolution_pT->cd(2);
  h_MEAN_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->cd(3);
  h_RMS_jet_eta_res_vs_pT->Draw();
  c_eta_Resolution_pT->SaveAs("c_eta_Resolution_pT.png");

}

void Display_phi_ResolutionForFile(std::vector<TFile*> *v)
{
  TH2F *h_jet_phi_res_vs_pT = (TH2F*)v->at(0)->Get("h_jet_phi_res_vs_pT");
  for (unsigned int i=1; i<v->size(); ++i)
  {
    h_jet_phi_res_vs_pT->Add((TH2F*)v->at(i)->Get("h_jet_phi_res_vs_pT"));
  }
  h_jet_phi_res_vs_pT->RebinX(2);
  h_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(-1, 1);
  h_jet_phi_res_vs_pT->GetXaxis()->SetRangeUser(0, 800);
  h_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet (#phi^{reco} - #phi^{parton})");
  h_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  
  TH1D *h_MEAN_jet_phi_res_vs_pT=MEANY(h_jet_phi_res_vs_pT);
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(-0.1, 0.1);
  h_MEAN_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet <(#phi^{reco} - #phi^{parton})>");
  h_MEAN_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_MEAN_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_MEAN_jet_phi_res_vs_pT=new TF1("f_MEAN_jet_phi_res_vs_pT", "pol0", 40, 500);
  h_MEAN_jet_phi_res_vs_pT->Fit(f_MEAN_jet_phi_res_vs_pT, "R");
  
  TH1D *h_RMS_jet_phi_res_vs_pT=RMSY(h_jet_phi_res_vs_pT);
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetRangeUser(0, 0.15);
  h_RMS_jet_phi_res_vs_pT->GetXaxis()->SetRangeUser(0, 600);
  h_RMS_jet_phi_res_vs_pT->SetTitle("; b Jet p_{T}^{reco} (GeV); b Jet #sigma(#phi^{reco} - #phi^{parton})");
  h_RMS_jet_phi_res_vs_pT->GetYaxis()->SetTitleOffset(1.6);
  h_RMS_jet_phi_res_vs_pT->GetXaxis()->SetTitleOffset(1.2);
  TF1 *f_RMS_jet_phi_res_vs_pT=new TF1("f_RMS_jet_phi_res_vs_pT", "[0] + [1]/x + [2]/(sqrt(x))", 40, 500);
  h_RMS_jet_phi_res_vs_pT->Fit(f_RMS_jet_phi_res_vs_pT, "R");
  
  TCanvas *c_jet_phi_res_vs_pT=new TCanvas("c_jet_phi_res_vs_pT", "c_jet_phi_res_vs_pT", 700, 700);
  h_jet_phi_res_vs_pT->Draw("colz");
  c_jet_phi_res_vs_pT->SaveAs("c_jet_phi_res_vs_pT.root");
  
  TCanvas *c_RMS_jet_phi_res_vs_pT=new TCanvas("c_RMS_jet_phi_res_vs_pT", "c_RMS_jet_phi_res_vs_pT", 700, 700);
  h_RMS_jet_phi_res_vs_pT->Draw();
  c_RMS_jet_phi_res_vs_pT->SaveAs("c_RMS_jet_phi_res_vs_pT.root");
  
  TCanvas *c_phi_Resolution_pT=new TCanvas("c_phi_Resolution_pT", "c_phi_Resolution_pT", 2100, 700);
  c_phi_Resolution_pT->Divide(3,1);
  c_phi_Resolution_pT->cd(1);
  h_jet_phi_res_vs_pT->Draw("colz");
  c_phi_Resolution_pT->cd(2);
  h_MEAN_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution_pT->cd(3);
  h_RMS_jet_phi_res_vs_pT->Draw();
  c_phi_Resolution_pT->SaveAs("c_phi_Resolution_pT.root");
} 

void DisplayResolutionBias(std::vector<std::string> files)
{
  std::vector<TFile*> v_files;
  for (unsigned int i=0; i<files.size(); ++i)
  {
    v_files.push_back(new TFile(files.at(i).c_str()));
  }
  
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  myStyle->SetOptFit();
  
  Display_pT_Resolution(&v_files);
  Display_pT_Resolution_vsPartonpT(&v_files);
  Display_eta_ResolutionForFile(&v_files);
  Display_phi_ResolutionForFile(&v_files);
  
}
