// Creates the images and HTML 
// for displaying changes in Signal MC
// due to JEC+1-1, and JER+1-1

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TArrow.h>
#include <TColor.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooChebychev.h"
#include "RooDataHist.h"
#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooCBShape.h"
#include "RooGaussian.h"


bool focus=true;

std::string dir_preselection="PreselectedWithoutRegression";
std::string dir_selection="LMRSelection";
std::string file_histograms="Histograms_Graviton";

int rebin=1;
ofstream outfile;

std::string tostr(float t)
{
  std::ostringstream os; 
  os<<t; 
  return os.str(); 
}

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0, double g=0, double h=0, double i=0, double j=0, double k=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f+g*g+h*h+i*i+j*j+k*k, 0.5);
}

struct Params
{
  double sg_p0;
  double sg_p1;
  double sg_p2;
  double sg_p3;
  double sg_p4;	
  double sg_p0_err;
  double sg_p1_err;
  double sg_p2_err;
  double sg_p3_err;
  double sg_p4_err;	
};

TLegend* twoStatBoxes(TH1F* h1, TH1F* h2)
{
  TLegend *leg=new TLegend(0.6, 0.6, 0.9, 0.9);
  double wherepeak=(h2->GetMean())/(h2->GetXaxis()->GetXmax());
  if (wherepeak>0.63) leg=new TLegend(0.1, 0.9, 0.4, 0.6);
  leg->AddEntry(h1, "Baseline");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h1->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h1->GetRMS())).c_str(), "");
  leg->AddEntry((TObject*)0, "", "");
  leg->AddEntry(h2, "JEC +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h2->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h2->GetRMS())).c_str(), "");
  leg->SetFillColor(10);
  return leg;
}

TLegend* threeStatBoxes(TH1F* h1, TH1F* h2, TH1F *h3)
{
  TLegend *leg=new TLegend(0.6, 0.6, 0.9, 0.9);
  double wherepeak=(h2->GetMean())/(h2->GetXaxis()->GetXmax());
  if (wherepeak>0.63) leg=new TLegend(0.1, 0.9, 0.4, 0.6);
  leg->AddEntry(h1, "Baseline");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h1->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h1->GetRMS())).c_str(), "");
  leg->AddEntry(h2, "JEC +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h2->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h2->GetRMS())).c_str(), "");
  leg->AddEntry(h3, "JEC -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h3->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h3->GetRMS())).c_str(), "");
  leg->SetFillColor(10);
  return leg;
}

TLegend* fiveStatBoxes(TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4, TH1F *h5)
{
  TLegend *leg=new TLegend(0.6, 0.4, 0.9, 0.9);
  double wherepeak=(h2->GetMean())/(h2->GetXaxis()->GetXmax());
  if (wherepeak>0.63) leg=new TLegend(0.1, 0.9, 0.4, 0.6);
  leg->AddEntry(h1, "Baseline");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h1->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h1->GetRMS())).c_str(), "");
  leg->AddEntry(h2, "JEC +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h2->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h2->GetRMS())).c_str(), "");
  leg->AddEntry(h3, "JEC -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h3->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h3->GetRMS())).c_str(), "");
  leg->AddEntry(h4, "JER +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h4->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h4->GetRMS())).c_str(), "");
  leg->AddEntry(h5, "JER -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h5->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h5->GetRMS())).c_str(), "");
  leg->SetFillColor(10);
  return leg;
}

TLegend* elevenStatBoxes(TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4, TH1F *h5, TH1F *h6, TH1F *h7, TH1F *h8, TH1F *h9, TH1F *h10, TH1F *h11)
{
  TLegend *leg=new TLegend(0.7, 0.1, 0.9, 0.9);
  double wherepeak=(h2->GetMean())/(h2->GetXaxis()->GetXmax());
  if (wherepeak>0.63) leg=new TLegend(0.1, 0.9, 0.3, 0.1);
  leg->AddEntry(h1, "Baseline");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h1->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h1->GetRMS())).c_str(), "");
  leg->AddEntry(h2, "JEC +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h2->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h2->GetRMS())).c_str(), "");
  leg->AddEntry(h3, "JEC -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h3->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h3->GetRMS())).c_str(), "");
  leg->AddEntry(h4, "JER +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h4->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h4->GetRMS())).c_str(), "");
  leg->AddEntry(h5, "JER -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h5->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h5->GetRMS())).c_str(), "");
  leg->AddEntry(h6, "SF_{bc} +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h6->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h6->GetRMS())).c_str(), "");
  leg->AddEntry(h7, "SF_{bc} -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h7->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h7->GetRMS())).c_str(), "");
  leg->AddEntry(h8, "SF_{l} +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h8->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h8->GetRMS())).c_str(), "");
  leg->AddEntry(h9, "SF_{l} -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h9->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h9->GetRMS())).c_str(), "");
  leg->AddEntry(h10, "Trig SF +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h10->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h10->GetRMS())).c_str(), "");
  leg->AddEntry(h11, "Trig SF -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h11->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h11->GetRMS())).c_str(), "");
  leg->SetFillColor(10);
  return leg;
}

TLegend* thirteenStatBoxes(TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4, TH1F *h5, TH1F *h6, TH1F *h7, TH1F *h8, TH1F *h9, TH1F *h10, TH1F *h11, TH1F *h12, TH1F *h13)
{
  TLegend *leg=new TLegend(0.7, 0.1, 0.9, 0.9);
  double wherepeak=(h2->GetMean())/(h2->GetXaxis()->GetXmax());
  if (wherepeak>0.63) leg=new TLegend(0.1, 0.9, 0.3, 0.1);
  leg->AddEntry(h1, "Baseline");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h1->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h1->GetRMS())).c_str(), "");
  leg->AddEntry(h2, "JEC +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h2->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h2->GetRMS())).c_str(), "");
  leg->AddEntry(h3, "JEC -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h3->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h3->GetRMS())).c_str(), "");
  leg->AddEntry(h4, "JER +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h4->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h4->GetRMS())).c_str(), "");
  leg->AddEntry(h5, "JER -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h5->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h5->GetRMS())).c_str(), "");
  leg->AddEntry(h6, "SF_{bc} +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h6->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h6->GetRMS())).c_str(), "");
  leg->AddEntry(h7, "SF_{bc} -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h7->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h7->GetRMS())).c_str(), "");
  leg->AddEntry(h8, "SF_{l} +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h8->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h8->GetRMS())).c_str(), "");
  leg->AddEntry(h9, "SF_{l} -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h9->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h9->GetRMS())).c_str(), "");
  leg->AddEntry(h10, "Trig SF (CSV) +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h10->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h10->GetRMS())).c_str(), "");
  leg->AddEntry(h11, "Trig SF (CSV) -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h11->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h11->GetRMS())).c_str(), "");
  leg->AddEntry(h12, "Trig SF (p_{T}) +1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h12->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h12->GetRMS())).c_str(), "");
  leg->AddEntry(h13, "Trig SF (p_{T}) -1 #sigma");
  leg->AddEntry((TObject*)0, ("mean="+tostr(h13->GetMean())).c_str(), "");
  leg->AddEntry((TObject*)0, ("rms="+tostr(h13->GetRMS())).c_str(), "");
  leg->SetFillColor(10);
  return leg;
}

Double_t crystalBall(Double_t *x, Double_t *par)
{
  Double_t std=(x[0]-par[2])/par[3];
  Double_t A=pow(par[1]/par[0], par[1])*exp(-0.5*pow(par[0], 2));
  Double_t B=par[1]/par[0]-par[0];
  Double_t result=0.;
  
  if (std<par[0]) // Gaussian region
  {
    result=exp(-0.5*pow(std, 2));
  }
  else // Power Law region
  {
    result=A/pow(B+std, par[1]);
  }
  
  result=result*par[4];
  
  return result;
}

THStack* drawCombinatorics(std::string mass, TH1F *h_right, TH1F *h_wrong, TH1F *h_no)
{
  std::string s_name=h_right->GetName();
  s_name.replace(0, 1, "s");
  
  double rangeLo=-1, rangeHi=-1;
  if (mass=="300") {rangeLo=200., rangeHi=600.;}
  else if (mass=="400") {rangeLo=200., rangeHi=600.;}
  else if (mass=="500") {rangeLo=470., rangeHi=650.;}
  else if (mass=="600") {rangeLo=580., rangeHi=670.;}
  else if (mass=="700") {rangeLo=650., rangeHi=870.;}
  else if (mass=="800") {rangeLo=750., rangeHi=990.;}
  
  h_right->GetXaxis()->SetRangeUser(rangeLo, rangeHi);
  h_wrong->GetXaxis()->SetRangeUser(rangeLo, rangeHi);
  h_no->GetXaxis()->SetRangeUser(rangeLo, rangeHi);
  
  THStack *stack=new THStack(s_name.c_str(), s_name.c_str());
  stack->Add(h_no);
  stack->Add(h_wrong);
  stack->Add(h_right);
  
  return stack;
}

RooPlot* fitSignal(TH1F *h, std::string mass, int color, TLegend *leg, Params &params, bool kinFit=false)
{
  
  RooRealVar *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3, *sg_p4;
  x=new RooRealVar("x", "m_{X} (GeV)", 250., 1100.);
  // x=new RooRealVar("x", "m_{X} (GeV)", 300., 800.);
  double rangeLo=-1, rangeHi=-1;
  if (!kinFit)
  {

	  if (mass=="270")
          {
                  rangeLo=252, rangeHi=600.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 260., 280.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 5.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 530.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.5, 1.);

          }
          if (mass=="260")
          {
                  rangeLo=252., rangeHi=630.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 250., 270.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 6.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 590.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.5, 1.);
          }
          if (mass=="600")
          {
                  rangeLo=500., rangeHi=670.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 580., 630.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 40.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 500., 650.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.7, 1.);
          }
	        if (mass=="500")
          {
                  rangeLo=300., rangeHi=600.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 480., 520.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 18.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 400., 590.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
          }
          if (mass=="350")
          {
                  rangeLo=250., rangeHi=550.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 320., 380.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 15.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 330., 420.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
          }
          if (mass=="400")
          {
                  rangeLo=300., rangeHi=600.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 370., 430.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 370.,460.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
          }
          if (mass=="450")
          {
                  rangeLo=300., rangeHi=600.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 420., 480.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 410., 490.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
          }
          if (mass=="300")
          {
                  rangeLo=250., rangeHi=550.;
                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 290., 320.);
                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 9.);
                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 250., 360.);
                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
                  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
          }


  }
  else
  {
	  if (mass=="270")
	  {       
		  rangeLo=252, rangeHi=600.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 260., 280.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 5.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 530.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.5, 1.);

	  }
	  if (mass=="260")
	  {       
		  rangeLo=252., rangeHi=630.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 250., 270.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 6.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 590.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.5, 1.);
	  }
	  if (mass=="600")
	  {       
		  rangeLo=580., rangeHi=650.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 580., 630.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 40.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 500., 650.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0.7, 1.);
	  }
	  if (mass=="500")
	  {       
		  rangeLo=300., rangeHi=600.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 480., 520.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 18.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 400., 590.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
	  }
	  if (mass=="350")
	  {
		  rangeLo=250., rangeHi=550.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 320., 380.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 15.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 330., 420.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
	  }
	  if (mass=="400")
	  {
		  rangeLo=300., rangeHi=600.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 370., 430.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 370.,460.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
	  }
	  if (mass=="450")
	  {
		  rangeLo=300., rangeHi=600.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 420., 480.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 410., 490.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
	  }
	  if (mass=="300")
	  {
		  rangeLo=250., rangeHi=550.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 290., 320.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 9.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 250., 360.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
	  }

  }
  x=new RooRealVar("x", "m_{X} (GeV)", rangeLo-50., rangeHi+50.);
  // RevCrystalBall signal("signal", "Signal Prediction", *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3);
  RooGaussian signalCore("signalCore", "Signal Prediction", *x, *sg_p0, *sg_p1);
  RooGaussian signalComb("signalComb", "Combinatoric", *x, *sg_p2, *sg_p3);
  RooAddPdf signal("signal", "signal", RooArgList(signalCore, signalComb), *sg_p4);
  RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), h);
  signal.fitTo(signalHistogram, RooFit::Range(rangeLo, rangeHi), RooFit::Save());
  params.sg_p0=sg_p0->getVal(); params.sg_p0_err=sg_p0->getError();
  params.sg_p1=sg_p1->getVal(); params.sg_p1_err=sg_p1->getError();
  params.sg_p2=sg_p2->getVal(); params.sg_p2_err=sg_p2->getError();
  params.sg_p3=sg_p3->getVal(); params.sg_p3_err=sg_p3->getError();
  params.sg_p4=sg_p4->getVal(); params.sg_p4_err=sg_p4->getError();
  RooPlot *plot=x->frame();
  if (color==kBlack)
  {
	  signalHistogram.plotOn(plot, RooFit::MarkerColor(color), RooFit::MarkerSize(1.2));
	  signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(3));
  }
  else 
  {
	  signalHistogram.plotOn(plot, RooFit::MarkerColor(color));
	  signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(0));
  }
  // leg->AddEntry((TObject*)0, ("norm="+tostr(h->GetSumOfWeights())).c_str(), "");
  // leg->AddEntry((TObject*)0, ("mean="+tostr(sg_p2->getVal())+"#pm"+tostr(sg_p2->getError())).c_str(), "");
  // leg->AddEntry((TObject*)0, ("rms="+tostr(sg_p3->getVal())+"#pm"+tostr(sg_p3->getError())).c_str(), "");
  // std::cout<<"chi2/dof = "<<plot->chiSquare()<<std::endl;

  // Save modified signal shape to workspace
  if (color==kBlack)
  {
	  RooRealVar signal_p0("signal_p0", "signal_p0", sg_p0->getVal());
	  RooRealVar signal_p1("signal_p1", "signal_p1", sg_p1->getVal());
	  RooRealVar signal_p2("signal_p2", "signal_p2", sg_p2->getVal());
	  RooRealVar signal_p3("signal_p3", "signal_p3", sg_p3->getVal());
          RooRealVar signal_p4("signal_p4", "signal_p4", sg_p4->getVal());
          RooGaussian signalCore_fixed("signalCore_fixed", "Signal Prediction", *x, signal_p0, signal_p1);
          RooGaussian signalComb_fixed("signalComb_fixed", "Combinatoric", *x, signal_p2, signal_p3);
          RooAddPdf signal_fixed("signal_fixed", "signal", RooArgList(signalCore_fixed, signalComb_fixed), signal_p4);

	  RooWorkspace *w=new RooWorkspace("HbbHbb");
	  w->import(signal_fixed);
	  if (!kinFit) w->SaveAs(("SignalShapes/w_signal_"+mass+".root").c_str());
	  if (kinFit) w->SaveAs(("SignalShapes_KinFit/w_signal_"+mass+".root").c_str());
  }
  return plot;
}

RooPlot* fitSignal_Gaussian(TH1F *h, std::string mass, int color, TLegend *leg, Params &params, bool kinFit=false)
{ 
	RooRealVar *x, *sg_p0, *sg_p1;
	double rangeLo=-1, rangeHi=-1;
	if (!kinFit)
	{
		if (mass=="270")
		{
			rangeLo=170., rangeHi=470.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 250., 290.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 60.);
		}
		else if (mass=="300")
		{
			rangeLo=200., rangeHi=600.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 280., 320.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 60.);
		}
		else if (mass=="350")
		{
			rangeLo=250., rangeHi=650.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 330., 370.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 60.);
		}
		else if (mass=="400")
		{
			rangeLo=300., rangeHi=600.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 380., 420.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 50.);
		}
		else if (mass=="450")
		{
			rangeLo=350., rangeHi=650.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 430., 470.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 50.);
		}
		else if (mass=="500")
		{
			rangeLo=300., rangeHi=700.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 470., 530.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="550")
		{
			rangeLo=350., rangeHi=750.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 530., 580.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="600")
		{
			rangeLo=400., rangeHi=800.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 580., 620.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 20., 30.);
		}
		else if (mass=="650")
		{
			rangeLo=450., rangeHi=850.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 630., 680.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 20., 30.);
		}
		else if (mass=="700")
		{
			rangeLo=500., rangeHi=900.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 680., 720.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 35.);
		}
		else if (mass=="800")
		{
			rangeLo=600., rangeHi=1000.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 780., 850.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 40.);
		}
		else if (mass=="900")
		{
			rangeLo=700., rangeHi=1100.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 880., 950.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 40.);
		}
		else if (mass=="1000")
		{
			rangeLo=800., rangeHi=1200.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 980., 1050.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 40.);
		}
		else if (mass=="1100")
		{
			rangeLo=900., rangeHi=1300.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 1080., 1150.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 40.);
		}
	}
	else
	{
		if (mass=="270")
		{
			rangeLo=200., rangeHi=400.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 250., 290.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 60.);
		}
		else if (mass=="300")
		{
			rangeLo=250., rangeHi=350.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 280., 320.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 60.);
		}
		else if (mass=="350")
		{
			rangeLo=300., rangeHi=400.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 330., 370.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 60.);
		}
		else if (mass=="400")
		{
			// rangeLo=300., rangeHi=600.;
			rangeLo=380., rangeHi=440.;
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 390., 410.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 15.);
		}
		else if (mass=="450")
		{
			rangeLo=430., rangeHi=480.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 430., 470.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 50.);
		}
		else if (mass=="500")
		{
			// rangeLo=300., rangeHi=700.;
			rangeLo=475., rangeHi=540.;
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 470., 530.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="550")
		{
			rangeLo=520., rangeHi=600.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 530., 580.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="600")
		{
			// rangeLo=400., rangeHi=800.;
			rangeLo=575., rangeHi=650.;
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 600., 620.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="650")
		{
			rangeLo=630., rangeHi=700.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 630., 680.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 10., 30.);
		}
		else if (mass=="700")
		{
			// rangeLo=500., rangeHi=900.;
			rangeLo=675., rangeHi=750.;
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 680., 750.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 15., 30.);
		}
		else if (mass=="800")
		{
			// rangeLo=600., rangeHi=1000.; 
			rangeLo=770., rangeHi=860.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 780., 850.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 15., 30.);
		}
		else if (mass=="900")
		{
			rangeLo=860., rangeHi=970.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 880., 950.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 20., 40.);
		}
		else if (mass=="1000")
		{
			rangeLo=950., rangeHi=1080.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 980., 1050.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 25., 40.);
		}
		else if (mass=="1100")
		{
			rangeLo=1040., rangeHi=1180.; 
			sg_p0=new RooRealVar("sg_p0", "sg_p0", 1080., 1150.);
			sg_p1=new RooRealVar("sg_p1", "sg_p1", 30., 50.);
		}
	}
	x=new RooRealVar("x", "m_{X} (GeV)", rangeLo-50, rangeHi+50);
	RooGaussian signal("signal", "Signal Prediction", *x, *sg_p0, *sg_p1);
	RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), h);
	signal.fitTo(signalHistogram, RooFit::Range(rangeLo, rangeHi), RooFit::Save());
	params.sg_p0=sg_p0->getVal(); params.sg_p0_err=sg_p0->getError();
	params.sg_p1=sg_p1->getVal(); params.sg_p1_err=sg_p1->getError();
	params.sg_p2=-1;
	params.sg_p3=-1;
	RooPlot *plot=x->frame();
	if (color==kBlack)
	{
		signalHistogram.plotOn(plot, RooFit::MarkerColor(color), RooFit::MarkerSize(1.2));
		signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(3));
	}
	else 
	{
		signalHistogram.plotOn(plot, RooFit::MarkerColor(color));
		signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(0));
	}
	// leg->AddEntry((TObject*)0, ("norm="+tostr(h->GetSumOfWeights())).c_str(), "");
	// leg->AddEntry((TObject*)0, ("mean="+tostr(sg_p0->getVal())+"#pm"+tostr(sg_p0->getError())).c_str(), "");
	// leg->AddEntry((TObject*)0, ("rms="+tostr(sg_p1->getVal())+"#pm"+tostr(sg_p1->getError())).c_str(), "");
	// std::cout<<"chi2/dof = "<<plot->chiSquare()<<std::endl;

	// Save modified signal shape to workspace
	if (color==kBlack)
	{
		RooRealVar signal_p0("signal_p0", "signal_p0", sg_p0->getVal());
		RooRealVar signal_p1("signal_p1", "signal_p1", sg_p1->getVal());
		RooGaussian signal_fixed("signal", "Signal Prediction Fixed", *x, signal_p0, signal_p1);
		RooWorkspace *w=new RooWorkspace("HbbHbb");
		w->import(signal_fixed);
		if (!kinFit) w->SaveAs(("SignalShapes/w_signal_Gaussian_"+mass+".root").c_str());
		if (kinFit) w->SaveAs(("SignalShapes_KinFit/w_signal_Gaussian_"+mass+".root").c_str());
	}
	return plot;
}

double lnN(double b, double a, double c)
{
	// std::cout<<"a = "<<a<<", b = "<<b<<", c = "<<c<<std::endl;
	// std::cout<<"1.+(a-c)/(2.*b) = "<<1.+fabs(a-c)/(2.*b)<<std::endl;
	double err=0;
	if (b>0) err=1.+fabs(a-c)/(2.*b);
	return err;
}

int Display_SignalFits_LMR()
{

	std::vector<std::string> masses;
	masses.push_back("260");
	masses.push_back("270");
	masses.push_back("300");
	masses.push_back("400");
	masses.push_back("600");
	masses.push_back("800");
//	masses.push_back("1000");
	// masses.push_back("1200");

	gROOT->SetStyle("Plain");
	gStyle->SetOptStat(000000000);
	gSystem->Load("PDFs/ExpGaussExp_cxx.so");

	// Calculate nSignal events given production cross section, branching fractions and efficiency
	double totalLumi=2150; // /pb
	double prodXsec_1=1.; // pb

	// Interpolation Plots
	std::vector<double> v_sg_p0, v_sg_p0_err;
	std::vector<double> v_sg_p1, v_sg_p1_err;
	std::vector<double> v_sg_p2, v_sg_p2_err;
	std::vector<double> v_sg_p3, v_sg_p3_err;
	std::vector<double> v_sg_p4, v_sg_p4_err;
	std::vector<double> v_zero;

	// Write to an HTML File
	outfile.open("SignalFits_LMR/index.html");
	outfile<<"<html>"<<std::endl;
	outfile<<"<head>"<<std::endl;
	// outfile<<"<base href=\"https://cmslpcweb.fnal.gov/uscms_data/souvik/SignalSystematics\" target=\"_blank\">"<<std::endl;
	outfile<<"<script type=\"text/javascript\">"<<std::endl;
	outfile<<"function toggleMe(a){"<<std::endl;
	outfile<<"var e=document.getElementById(a);"<<std::endl;
	outfile<<"if(!e)return true;"<<std::endl;
	outfile<<"if(e.style.display==\"none\"){"<<std::endl;
	outfile<<"e.style.display=\"block\""<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else{"<<std::endl;
	outfile<<"e.style.display=\"none\""<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"</script>"<<std::endl;
	outfile<<"</head>"<<std::endl;
	outfile<<"<body>"<<std::endl;
	outfile<<"<h1> Signal with JEC, JER Systematic Uncertainties</h1>"<<std::endl;

	for (unsigned int i=0; i<masses.size(); ++i)
	{
		v_zero.push_back(0);

		TFile *file=new TFile((dir_preselection+"/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		TH1F *h_H1_mass=(TH1F*)file->Get("h_H1_mass");
		TH1F *h_H2_mass=(TH1F*)file->Get("h_H2_mass");
		TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
		TH1F *h_mX_SR_KinFit=(TH1F*)file->Get("h_mX_SR_kinFit");
		TH1F *h_Count=(TH1F*)file->Get("Count");
		double nSignal_init=h_Count->GetBinContent(1);
		std::cout<<"nSignal_init = "<<nSignal_init<<std::endl;

		TFile *file_JECp1;
		if (focus) file_JECp1=file;
		else file_JECp1=new TFile((dir_preselection+"_JECp1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		TH1F *h_H1_mass_JECp1=(TH1F*)file_JECp1->Get("h_H1_mass");
		TH1F *h_H2_mass_JECp1=(TH1F*)file_JECp1->Get("h_H2_mass");
		TH1F *h_mX_SR_JECp1=(TH1F*)file_JECp1->Get("h_mX_SR");
		TH1F *h_mX_SR_JECp1_KinFit=(TH1F*)file_JECp1->Get("h_mX_SR_kinFit");

		TFile *file_JECm1;
		if (focus) file_JECm1=file;
		else file_JECm1=new TFile((dir_preselection+"_JECm1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		TH1F *h_H1_mass_JECm1=(TH1F*)file_JECm1->Get("h_H1_mass");
		TH1F *h_H2_mass_JECm1=(TH1F*)file_JECm1->Get("h_H2_mass");
		TH1F *h_mX_SR_JECm1=(TH1F*)file_JECm1->Get("h_mX_SR");
		TH1F *h_mX_SR_JECm1_KinFit=(TH1F*)file_JECm1->Get("h_mX_SR_kinFit");

		TCanvas *c_H1_mass=new TCanvas("c_H1_mass", "c_H1_mass", 700, 700);
		h_H1_mass->SetLineWidth(2);
		h_H1_mass_JECp1->SetLineStyle(9); h_H1_mass_JECp1->SetLineColor(kRed);
		h_H1_mass_JECm1->SetLineStyle(9); h_H1_mass_JECm1->SetLineColor(kRed+2);
		h_H1_mass->Draw("same");
		h_H1_mass_JECp1->Draw("same");
		h_H1_mass_JECm1->Draw("same");
		threeStatBoxes(h_H1_mass, 
				h_H1_mass_JECp1, 
				h_H1_mass_JECm1)->Draw();
		c_H1_mass->SaveAs(("SignalFits/c_H1_mass_"+masses.at(i)+".png").c_str());

		TCanvas *c_H2_mass=new TCanvas("c_H2_mass", "c_H2_mass", 700, 700);
		h_H2_mass->SetLineWidth(2);
		h_H2_mass_JECp1->SetLineStyle(9); h_H2_mass_JECp1->SetLineColor(kRed);
		h_H2_mass_JECm1->SetLineStyle(9); h_H2_mass_JECm1->SetLineColor(kRed+2);
		h_H2_mass->Draw("same");
		h_H2_mass_JECp1->Draw("same");
		h_H2_mass_JECm1->Draw("same");
		threeStatBoxes(h_H2_mass, 
				           h_H2_mass_JECp1, 
				           h_H2_mass_JECm1)->Draw();
		c_H2_mass->SaveAs(("SignalFits/c_H2_mass_"+masses.at(i)+".png").c_str());

		TCanvas *c_mX_SR=new TCanvas(("c_mX_SR_"+masses.at(i)).c_str(), ("c_mX_SR_"+masses.at(i)).c_str(), 700, 700);
		h_mX_SR->SetTitle(("m_{X} Peak in Signal MC (m_{X}="+masses.at(i)+" GeV); m_{X} (GeV)").c_str());
		h_mX_SR->Rebin(rebin);
		h_mX_SR_JECp1->Rebin(rebin);
		h_mX_SR_JECm1->Rebin(rebin);
		h_mX_SR_JECp1->SetLineColor(kRed);
		h_mX_SR_JECm1->SetLineColor(kRed+2);
		h_mX_SR->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECp1->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECm1->GetXaxis()->SetRangeUser(0, 1200);
		TLegend *leg=new TLegend(0.7, 0.5, 0.9, 0.9);
		leg->AddEntry(h_mX_SR, "Baseline");
		Params par, par_JECp1, par_JECm1;
		RooPlot *plot=fitSignal(h_mX_SR, masses.at(i), kBlack, leg, par);
		RooPlot *plot_JECp1, *plot_JECm1;
		if (!focus)
		{
			leg->AddEntry(h_mX_SR_JECp1, "JEC +1 #sigma");
			leg->AddEntry(h_mX_SR_JECm1, "JEC -1 #sigma");

			plot_JECp1=fitSignal(h_mX_SR_JECp1, masses.at(i), kRed, leg, par_JECp1);
			plot_JECm1=fitSignal(h_mX_SR_JECm1, masses.at(i), kRed+2, leg, par_JECm1);
		}
		plot->SetMaximum(plot->GetMaximum()*1.2);
		plot->Draw();
		if (!focus)
		{
			plot_JECp1->Draw("same");
			plot_JECm1->Draw("same");
		}
		plot->Draw("same");
		leg->SetFillColor(0);
		leg->Draw();
		c_mX_SR->SaveAs(("SignalFits/c_mX_SR_"+masses.at(i)+".png").c_str());

		TCanvas *c_mX_SR_KinFit=new TCanvas(("c_mX_SR_KinFit_"+masses.at(i)).c_str(), ("c_mX_SR_KinFit_"+masses.at(i)).c_str(), 700, 700);
		h_mX_SR_KinFit->SetTitle(("m_{X} Peak in Signal MC (m_{X}="+masses.at(i)+" GeV); m_{X} (GeV)").c_str());
		h_mX_SR_KinFit->Rebin(rebin);
		h_mX_SR_JECp1_KinFit->Rebin(rebin);
		h_mX_SR_JECm1_KinFit->Rebin(rebin);
		h_mX_SR_JECp1_KinFit->SetLineColor(kRed);
		h_mX_SR_JECm1_KinFit->SetLineColor(kRed+2);
		h_mX_SR_KinFit->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECp1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECm1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
		leg=new TLegend(0.7, 0.5, 0.9, 0.9);
		leg->AddEntry(h_mX_SR_KinFit, "Baseline");
		Params par_KinFit, par_JECp1_KinFit, par_JECm1_KinFit;
		RooPlot *plot_KinFit=fitSignal(h_mX_SR_KinFit, masses.at(i), kBlack, leg, par_KinFit, true);
		v_sg_p0.push_back(par_KinFit.sg_p0); v_sg_p0_err.push_back(par_KinFit.sg_p0_err);
		v_sg_p1.push_back(par_KinFit.sg_p1); v_sg_p1_err.push_back(par_KinFit.sg_p1_err);
		v_sg_p2.push_back(par_KinFit.sg_p2); v_sg_p2_err.push_back(par_KinFit.sg_p2_err);
		v_sg_p3.push_back(par_KinFit.sg_p3); v_sg_p3_err.push_back(par_KinFit.sg_p3_err);
		v_sg_p4.push_back(par_KinFit.sg_p4); v_sg_p4_err.push_back(par_KinFit.sg_p4_err);	
		RooPlot *plot_JECp1_KinFit, *plot_JECm1_KinFit;
		if (!focus) {
			leg->AddEntry(h_mX_SR_JECp1_KinFit, "JEC +1 #sigma");
			leg->AddEntry(h_mX_SR_JECm1_KinFit, "JEC -1 #sigma");

			plot_JECp1_KinFit=fitSignal(h_mX_SR_JECp1_KinFit, masses.at(i), kRed, leg, par_JECp1_KinFit, true);
			plot_JECm1_KinFit=fitSignal(h_mX_SR_JECm1_KinFit, masses.at(i), kRed+2, leg, par_JECm1_KinFit, true);
		}
		plot_KinFit->SetMaximum(plot_KinFit->GetMaximum()*1.2);
		plot_KinFit->Draw();
		if (!focus) 
		{
			plot_JECp1_KinFit->Draw("same");
			plot_JECm1_KinFit->Draw("same");
		}
		plot_KinFit->Draw("same");
		leg->SetFillColor(0);
		leg->Draw();
		c_mX_SR_KinFit->SaveAs(("SignalFits/c_mX_SR_KinFit_"+masses.at(i)+".png").c_str());

		outfile<<"<br/><hr/>"<<std::endl;
		outfile<<"<h2> mX = "<<masses.at(i)<<" </h2>"<<std::endl;
		outfile<<"<table border='1'>"<<std::endl;
		outfile<<" <tr>"<<std::endl;
		outfile<<"  <td>"<<std::endl;
		outfile<<"   Higgs 1 mass"<<std::endl;
		outfile<<"   <img src='"<<("c_H1_mass_"+masses.at(i)+".png")<<"'/>"<<std::endl;
		outfile<<"  </td>"<<std::endl;
		outfile<<"  <td>"<<std::endl;
		outfile<<"   Higgs 2 mass"<<std::endl;
		outfile<<"   <img src='"<<("c_H2_mass_"+masses.at(i)+".png")<<"'/>"<<std::endl;
		outfile<<"  </td>"<<std::endl;
		outfile<<"  <td>"<<std::endl;
		outfile<<"   <img src='"<<("c_mX_SR_"+masses.at(i)+".png")<<"'/><br/>"<<std::endl;
		outfile<<"   <h2 align='center'>Without Kin-Fit. Fitted to an Exp-Gauss-Exp function.</h2><br/>"<<std::endl;
		outfile<<"   === Baseline plot === </br>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR->GetSumOfWeights()*totalLumi*prodXsec_1/nSignal_init<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par.sg_p0<<" +- "<<par.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par.sg_p1<<" +- "<<par.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par.sg_p2<<" +- "<<par.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par.sg_p3<<" +- "<<par.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par.sg_p4<<" +- "<<par.sg_p4_err<<" <br/>"<<std::endl;
		if (!focus) 
		{
			outfile<<"   <center><input type='button' onclick=\"return toggleMe('"<<masses.at(i)<<"')\" value='Systematics'></center><br/>"<<std::endl;
			outfile<<"   <div id=\""<<masses.at(i)<<"\" style=\"display:none\">"<<std::endl;
			outfile<<"   === JEC +1 sigma === <br/>"<<std::endl;
			outfile<<"   norm = "<<h_mX_SR_JECp1->GetSumOfWeights()<<" <br/>"<<std::endl;
			outfile<<"   sg_p0 = "<<par_JECp1.sg_p0<<" +- "<<par_JECp1.sg_p0_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p1 = "<<par_JECp1.sg_p1<<" +- "<<par_JECp1.sg_p1_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p2 = "<<par_JECp1.sg_p2<<" +- "<<par_JECp1.sg_p2_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p3 = "<<par_JECp1.sg_p3<<" +- "<<par_JECp1.sg_p3_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p4 = "<<par_JECp1.sg_p4<<" +- "<<par_JECp1.sg_p4_err<<" <br/>"<<std::endl;
			outfile<<"   === JEC -1 sigma === <br/>"<<std::endl;
			outfile<<"   norm = "<<h_mX_SR_JECm1->GetSumOfWeights()<<" <br/>"<<std::endl;
			outfile<<"   sg_p0 = "<<par_JECm1.sg_p0<<" +- "<<par_JECm1.sg_p0_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p1 = "<<par_JECm1.sg_p1<<" +- "<<par_JECm1.sg_p1_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p2 = "<<par_JECm1.sg_p2<<" +- "<<par_JECm1.sg_p2_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p3 = "<<par_JECm1.sg_p3<<" +- "<<par_JECm1.sg_p3_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p4 = "<<par_JECm1.sg_p4<<" +- "<<par_JECm1.sg_p4_err<<" <br/>"<<std::endl;
			outfile<<"   === === <br/>"<<std::endl;
			outfile<<"   </div>"<<std::endl;

		}
		outfile<<"  </td>"<<std::endl;
		outfile<<"  <td>"<<std::endl;
		outfile<<"   <img src='"<<("c_mX_SR_KinFit_"+masses.at(i)+".png")<<"'/><br/>"<<std::endl;
		outfile<<"   <h2 align='center'>With Kin-Fit. Fitted to an Exp-Gauss-Exp function.</h2><br/>"<<std::endl;
		outfile<<"   === Baseline plot === </br>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_KinFit->GetSumOfWeights()*totalLumi*prodXsec_1/nSignal_init<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_KinFit.sg_p0<<" +- "<<par_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_KinFit.sg_p1<<" +- "<<par_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_KinFit.sg_p2<<" +- "<<par_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_KinFit.sg_p3<<" +- "<<par_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_KinFit.sg_p4<<" +- "<<par_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		if (!focus) 
		{
			outfile<<"   <center><input type='button' onclick=\"return toggleMe('"<<masses.at(i)<<"_KinFit')\" value='Systematics'></center><br/>"<<std::endl;
			outfile<<"   <div id=\""<<masses.at(i)<<"_KinFit\" style=\"display:none\">"<<std::endl;
			outfile<<"   === JEC +1 sigma === <br/>"<<std::endl;
			outfile<<"   norm = "<<h_mX_SR_JECp1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
			// outfile<<"   chi2/ndof = "<<plot_JECp1_KinFit->chiSquare()<<" <br/>"<<std::endl;
			outfile<<"   sg_p0 = "<<par_JECp1_KinFit.sg_p0<<" +- "<<par_JECp1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p1 = "<<par_JECp1_KinFit.sg_p1<<" +- "<<par_JECp1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p2 = "<<par_JECp1_KinFit.sg_p2<<" +- "<<par_JECp1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p3 = "<<par_JECp1_KinFit.sg_p3<<" +- "<<par_JECp1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p4 = "<<par_JECp1_KinFit.sg_p4<<" +- "<<par_JECp1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
			outfile<<"   === JEC -1 sigma === <br/>"<<std::endl;
			outfile<<"   norm = "<<h_mX_SR_JECm1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
			// outfile<<"   chi2/ndof = "<<plot_JECm1_KinFit->chiSquare()<<" <br/>"<<std::endl;
			outfile<<"   sg_p0 = "<<par_JECm1_KinFit.sg_p0<<" +- "<<par_JECm1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p1 = "<<par_JECm1_KinFit.sg_p1<<" +- "<<par_JECm1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p2 = "<<par_JECm1_KinFit.sg_p2<<" +- "<<par_JECm1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p3 = "<<par_JECm1_KinFit.sg_p3<<" +- "<<par_JECm1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
			outfile<<"   sg_p4 = "<<par_JECm1_KinFit.sg_p4<<" +- "<<par_JECm1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
			outfile<<"   === === <br/>"<<std::endl;
			outfile<<"   </div>"<<std::endl;
		}
		outfile<<"   </div>"<<std::endl;
		outfile<<"  </td>"<<std::endl;

		outfile<<" </tr>"<<std::endl;
		outfile<<"</table>"<<std::endl;

		// Close all files
		file->Close();
		file_JECp1->Close();
		file_JECm1->Close();
	}

	/*
	   std::vector<double> masses_d;
	   for (unsigned int i=0; i<masses.size(); ++i) masses_d.push_back(atof(masses.at(i).c_str()));
	   TGraphErrors *g_sg_p0=new TGraphErrors(masses.size()-4, &masses_d[4], &v_sg_p0[4], &v_zero[0], &v_sg_p0_err[4]);
	   TGraphErrors *g_sg_p1=new TGraphErrors(masses.size()-4, &masses_d[4], &v_sg_p1[4], &v_zero[0], &v_sg_p1_err[4]);
	   TGraphErrors *g_sg_p2=new TGraphErrors(masses.size()-4, &masses_d[4], &v_sg_p2[4], &v_zero[0], &v_sg_p2_err[4]);
	   TGraphErrors *g_sg_p3=new TGraphErrors(masses.size()-4, &masses_d[4], &v_sg_p3[4], &v_zero[0], &v_sg_p3_err[4]);

	// TSpline3 *sp_sg_p0=new TGraphErrors("sp_sg_p0", &masses_d[4], &v_sg_p0[4], masses.size()-4, "b2e2", 0, 0);

	TCanvas *c_sg_p0=new TCanvas("c_sg_p0", "c_sg_p0", 700, 700);
	g_sg_p0->SetTitle("Signal Mean Interpolation; m_{X} (GeV); Signal Mean");
	g_sg_p0->Draw("AC*");
	// g_sg_p0->Fit("pol1");
	c_sg_p0->SaveAs("SignalSystematics/c_sg_p0.png");

	TCanvas *c_sg_p1=new TCanvas("c_sg_p1", "c_sg_p1", 700, 700);
	g_sg_p1->SetTitle("Signal RMS Interpolation; m_{X} (GeV); Signal RMS");
	g_sg_p1->Draw("AC*");
	// g_sg_p1->Fit("pol1");
	c_sg_p1->SaveAs("SignalSystematics/c_sg_p1.png");

	TCanvas *c_sg_p2=new TCanvas("c_sg_p2", "c_sg_p2", 700, 700);
	g_sg_p2->SetTitle("Signal Right Exponential Interpolation; m_{X} (GeV); Signal k_{right}");
	g_sg_p2->Draw("AC*");
	// g_sg_p2->Fit("pol1");
	c_sg_p2->SaveAs("SignalSystematics/c_sg_p2.png");

	TCanvas *c_sg_p3=new TCanvas("c_sg_p3", "c_sg_p3", 700, 700);
	g_sg_p3->SetTitle("Signal Left Exponential Interpolation; m_{X} (GeV); Signal k_{left}");
	g_sg_p3->Draw("AC*");
	// g_sg_p3->Fit("pol1");
	c_sg_p3->SaveAs("SignalSystematics/c_sg_p3.png");

	outfile<<"<h1> Signal Mean Interpolation Plot </h1>"<<std::endl;
	outfile<<"<img src='c_sg_p0.png'/> <br/> <hr/>"<<std::endl;
	outfile<<"<h1> Signal RMS Interpolation Plot </h1>"<<std::endl;
	outfile<<"<img src='c_sg_p1.png'/> <br/> <hr/>"<<std::endl;
	outfile<<"<h1> Signal Right Exponential Interpolation Plot </h1>"<<std::endl;
	outfile<<"<img src='c_sg_p2.png'/> <br/> <hr/>"<<std::endl;
	outfile<<"<h1> Signal Left Exponential Interpolation Plot </h1>"<<std::endl;
	outfile<<"<img src='c_sg_p3.png'/> <br/> <hr/>"<<std::endl;
	outfile<<"</body>"<<std::endl;
	outfile<<"</html>"<<std::endl;
	*/

	return 0;
}

