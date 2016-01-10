#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>

int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

double rebin = 10;
bool blind = true;

double SR_lo=250.; // 350 for MMMM_nominal and 400 for MMMMbar
double SR_hi=1100.;

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f, 0.5);
}

std::string itoa(int i) 
{
  char res[10];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}



TCanvas* comparePlots2(RooPlot *plot_bC, RooPlot *plot_bS, TH1F *data, TH1F *qcd, std::string title, double lo, double hi, std::string title2 )
{


 RooRealVar x("x", "m_{X} (GeV)", lo, hi);

 TCanvas *c=new TCanvas(("c_RooFit_"+title).c_str(), "c", 700, 700);
 TPad *p_1=new TPad("p_1", "p_1", 0, 0.35, 1, 1);
 gStyle->SetPadGridX(0);
 gStyle->SetPadGridY(0);
 gROOT->SetStyle("Plain");
   //p_1->SetBottomMargin(0.05);
 p_1->SetFrameFillColor(0);
   //p_2->SetFrameFillColor(0);

 p_2 = new TPad("p_2", "p_2",0,0.003740648,0.9975278,0.3391022);
   //p_2->Draw();
   //p_2->cd();
 p_2->Range(160.1237,-0.8717948,1008.284,2.051282);
 p_2->SetFillColor(0);
 p_2->SetBorderMode(0);
 p_2->SetBorderSize(2);
 p_2->SetTopMargin(0.01754386);
 p_2->SetBottomMargin(0.2982456);
 p_2->SetFrameBorderMode(0);
 p_2->SetFrameBorderMode(0);

  p_1->Draw();
  p_2->Draw();
  p_1->cd();
  double maxdata=data->GetMaximum();
  double maxqcd=qcd->GetMaximum();
  double maxy=(maxdata>maxqcd) ? maxdata : maxqcd;

  title=";; Events / "+itoa(data->GetBinWidth(1))+" GeV";plot_bC->GetYaxis()->SetLabelSize(0.02);
  p_1->DrawFrame(lo, 0, hi, maxy*1.5, title.c_str());  // p_1->GetYaxis()->SetLabelSize(0.005);
  plot_bC->GetYaxis()->SetRangeUser(0.,maxy*1.5);	
  plot_bC->Draw();
  plot_bS->Draw("same");
 //CMS_lumi( p_1, iPeriod, iPos );

  p_2->cd(); 
  TH1F *h_ratio=(TH1F*)data->Clone("h_ratio");qcd->GetXaxis()->SetRangeUser(lo, hi);
  h_ratio->GetYaxis()->SetTitle(title2.c_str()); h_ratio->GetXaxis()->SetRangeUser(lo, hi-10);
  h_ratio->GetXaxis()->SetTitle("m_{X} (GeV)");
  h_ratio->SetTitle("");
  h_ratio->GetYaxis()->SetTitleSize(0.07);
  h_ratio->GetYaxis()->SetTitleOffset(0.5);
  h_ratio->GetXaxis()->SetTitleSize(0.09);
  h_ratio->GetXaxis()->SetTitleOffset(1.0);
  h_ratio->GetXaxis()->SetLabelSize(0.07);
  h_ratio->GetYaxis()->SetLabelSize(0.06);



  h_ratio->Divide(qcd);
  h_ratio->SetLineColor(1);
  h_ratio->SetMarkerStyle(20);
//  h_ratio->GetXaxis()->SetRangeUser(lo, hi);
  h_ratio->GetYaxis()->SetRangeUser(0, 2.);
  TLine *m_one_line = new TLine(lo,1,hi,1);
  h_ratio->Draw("");
  m_one_line->Draw("same");

  p_1->cd();
  return c;
            }


void BackgroundPrediction_AntiTag_GaussExp()
{

  gROOT->LoadMacro("tdrstyle.C");
  //   setTDRStyle();
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetOptStat(0000);
  //gROOT->LoadMacro("CMS_lumi.C");

  /*writeExtraText = false;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "17.9 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_13TeV  = "2.2 fb^{-1}";  // default is "5.1 fb^{-1}"
 */

  TFile *f=new TFile("PreselectedWithoutRegression/MMRSelection/Histograms_Data_BTagCSV_2015_Skim_AntiTag.root");
  f->cd();

  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", SR_lo, SR_hi);

  std::cout<<" === Background Prediction ==== "<<std::endl;
  TH1F *h_mX_SB=(TH1F*)f->Get("h_mX_SB");
  TH1F *h_mX_SR=(TH1F*)f->Get("h_mX_SR");

  h_mX_SB->Rebin(rebin);
  h_mX_SR->Rebin(rebin);
  double bC=h_mX_SB->Integral();
  double bS=h_mX_SR->Integral();	
  h_mX_SR->Scale(bC/bS);
 
  RooRealVar bC_p0("bC_p0", "bC_p0", 250., 550.);
  RooRealVar bC_p1("bC_p1", "bC_p1", 15., 100.1);
  RooRealVar bC_p2("bC_p2", "bC_p2", 0.1, 10.1);
  GaussExp bC_fit("bC_fit", "bC Fit", *x, bC_p0, bC_p1, bC_p2);
  h_mX_SB->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
  RooDataHist bC_data("bC_data", "bC Data", RooArgList(*x), h_mX_SB);
  RooFitResult *r_bC_fit=bC_fit.fitTo(bC_data, RooFit::Range(SR_lo, SR_hi), RooFit::Save());
  RooPlot *bC_plot=x->frame();
  bC_data.plotOn(bC_plot);
  bC_fit.plotOn(bC_plot, RooFit::VisualizeError(*r_bC_fit), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
  bC_fit.plotOn(bC_plot, RooFit::LineColor(kBlack));
  bC_data.plotOn(bC_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));

  // bS
  RooRealVar bS_p0("bS_p0", "bS_p0", 250., 550.);
  RooRealVar bS_p1("bS_p1", "bS_p1", 15., 100.1);
  RooRealVar bS_p2("bS_p2", "bS_p2", 0.1, 10.1);
  GaussExp bS_fit("bS_fit", "bS Fit", *x, bS_p0, bS_p1, bS_p2);
  h_mX_SR->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
  RooDataHist bS_data("bS_data", "bS Data", RooArgList(*x), h_mX_SR);
  RooFitResult *r_bS_fit=bS_fit.fitTo(bS_data, RooFit::Range(SR_lo, SR_hi), RooFit::Save()); // RooFit::SumW2Error(kTRUE), 
  RooPlot *bS_plot=x->frame();
  bS_data.plotOn(bS_plot);
  bS_fit.plotOn(bS_plot,RooFit::VisualizeError(*r_bS_fit), RooFit::FillColor(kBlue+1), RooFit::FillStyle(3001));
  bS_fit.plotOn(bS_plot, RooFit::LineColor(kBlue+1));
  bS_data.plotOn(bS_plot, RooFit::LineColor(kBlue+1), RooFit::MarkerColor(kBlue+1));


  bC_plot->SetAxisRange(SR_lo, SR_hi, "X");
  bS_plot->SetAxisRange(SR_lo, SR_hi, "X");

  TCanvas *c_bC=comparePlots2(bC_plot, bS_plot, h_mX_SR, h_mX_SB, "Kinematic Extrapolation in the AntiTag Region of Data; m_{X} GeV", SR_lo, SR_hi, "SR/SB ratio");

  TLatex * tPrel = new TLatex();
  tPrel->SetNDC();
  tPrel->SetTextColor(kBlack);
  tPrel->SetTextSize(0.04027386);
 

  TPaveText *pave = new TPaveText(0.85625,0.55,0.5765625,0.73,"NDC");
  TLegend *leg = new TLegend(0.85625,0.7321654,0.5765625,0.8603839,NULL,"brNDC");

 pave->SetBorderSize(0);
 pave->SetTextSize(0.035);
 pave->SetLineColor(1);
 pave->SetLineStyle(1);
 pave->SetLineWidth(2);
 pave->SetFillColor(0);
 pave->SetFillStyle(0);

 char name[1000];
 sprintf(name,"LMR AntiTag selection");
 pave->AddText(name);
 sprintf(name,"SB #chi^{2}/ndof = %.2f",bC_plot->chiSquare());
 pave->AddText(name);
 sprintf(name,"SR #chi^{2}/ndof = %.2f",bS_plot->chiSquare());
 pave->AddText(name);
 pave->Draw();




   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   h_mX_SB->SetMarkerStyle(20);
   h_mX_SB->SetMarkerColor(kBlack);
   leg->AddEntry(h_mX_SB, "Data in SB", "lep");
   h_mX_SR->SetLineColor(kBlue+1);
   h_mX_SR->SetMarkerColor(kBlue+1);	
   h_mX_SR->SetMarkerStyle(20);
   leg->AddEntry(h_mX_SR, "Data in SR", "lep");
   leg->Draw();



   
  std::cout<<" === === "<<std::endl;
  std::cout<<"chi^2/ndof of bC = "<<bC_plot->chiSquare()<<std::endl;
  std::cout<<"chi^2/ndof of bS = "<<bS_plot->chiSquare()<<std::endl;
  std::cout<<" === === "<<std::endl;


  c_bC->SaveAs("AntiTag_RooFit_GaussExp.pdf");

 
  
}
  
  
  
