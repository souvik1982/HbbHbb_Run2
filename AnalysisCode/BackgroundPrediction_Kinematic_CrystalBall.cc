#include <iostream>

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>

#include "CMS_lumi.c"

// Plot cosmetics
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

std::string itoa(int i) 
{
  char res[10];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void BackgroundPrediction_Kinematic_CrystalBall(std::string filename,
                                             double plot_lo, double plot_hi, double rebin,
                                             double fit_lo, double fit_hi, 
                                             double crystalball_mean_lo, double crystalball_mean_hi, 
                                             double crystalball_width_lo, double crystalball_width_hi,
                                             double crystalball_exp_lo, double crystalball_exp_hi,
                                             double crystalball_switch_lo, double crystalball_switch_hi,
					      double gaussexp_mean_lo, double gaussexp_mean_hi,
                                             double gaussexp_width_lo, double gaussexp_width_hi,
                                             double gaussexp_exp_lo, double gaussexp_exp_hi,
                                             std::string hist="h_mX_SB_kinFit", 
                                             std::string log="lin")
{

  gROOT->SetStyle("Plain");
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetOptStat(0000);
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV = "35.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  
  TFile *f_data=new TFile(filename.c_str());
  TH1F *h_mX_SR=(TH1F*)f_data->Get(hist.c_str());
  h_mX_SR->Rebin(rebin);
  double nEventsSR=((TH1F*)f_data->Get("h_mX_SR_kinFit"))->GetSumOfWeights();
  
  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred("pred", "Data", RooArgList(*x), h_mX_SR);
  
  RooRealVar bg_p0("bg_p0", "bg_p0", crystalball_switch_lo, crystalball_switch_hi);
  RooRealVar bg_p1("bg_p1", "bg_p1", crystalball_exp_lo, crystalball_exp_hi);
  RooRealVar bg_p2("bg_p2", "bg_p2", crystalball_mean_lo, crystalball_mean_hi);
  RooRealVar bg_p3("bg_p3", "bg_p3", crystalball_width_lo, crystalball_width_hi);
  RevCrystalBall bg("background", "Background Prediction PDF", *x, bg_p0, bg_p1, bg_p2, bg_p3);
  RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
  
  RooPlot *data_plot=x->frame();
  pred.plotOn(data_plot);
  bg.plotOn(data_plot, RooFit::VisualizeError(*r_bg, 1), RooFit::FillColor(kGreen+1), RooFit::FillStyle(3001));
  bg.plotOn(data_plot, RooFit::LineColor(kBlack));
  pred.plotOn(data_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));

  RooRealVar bg_p00("bg_p00", "bg_p00", gaussexp_mean_lo, gaussexp_mean_hi);
  RooRealVar bg_p11("bg_p11", "bg_p11", gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bg_p22("bg_p22", "bg_p22", gaussexp_exp_lo, gaussexp_exp_hi);




  GaussExp bg_exp("bg_exp", "Background Prediction PDF", *x, bg_p00, bg_p11, bg_p22);

  RooPlot *data_plot2=x->frame();
  RooFitResult *r_bg_exp=bg_exp.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
  pred.plotOn(data_plot2);

  //bg_exp.plotOn(data_plot2, RooFit::VisualizeError(*r_bg_exp, 1, kFALSE), RooFit::FillColor(kCyan+1), RooFit::FillStyle(3001));
  bg_exp.plotOn(data_plot2, RooFit::LineColor(kBlue+1));
  pred.plotOn(data_plot2, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));


  
  double fitChi2=data_plot->chiSquare();
  std::cout<<"Fit chi2 = "<<fitChi2<<std::endl;

  
    RooAbsReal* chi2_data    = bg.createChi2(pred);
  double pvalue=TMath::Prob(chi2_data->getVal(),int((fit_hi-fit_lo)/rebin)-3);
  std::cout<<"p-value = "<<TMath::Prob(chi2_data->getVal(),int((fit_hi-fit_lo)/rebin)-3)<<std::endl;


  double xPad = 0.3;
  TCanvas *c_Background=new TCanvas("c_Background", "c_Background", 700*(1.-xPad), 700);
  c_Background->SetFillStyle(4000);
  c_Background->SetFrameFillColor(0);

 TPad *p_1=new TPad("p_1", "p_1", 0, xPad, 1, 1);
        p_1->SetFillStyle(4000);
        p_1->SetFrameFillColor(0);
        p_1->SetBottomMargin(0.02);

        TPad* p_2 = new TPad("p_2", "p_2",0,0,1,xPad);
        p_2->SetBottomMargin((1.-xPad)/xPad*0.13);
        p_2->SetTopMargin(0.03);
        p_2->SetFillColor(0);
        p_2->SetBorderMode(0);
        p_2->SetBorderSize(2);
        p_2->SetFrameBorderMode(0);
        p_2->SetFrameBorderMode(0);
  p_1->Draw();
  p_2->Draw();
  p_1->cd();


  if (log=="log") data_plot->GetYaxis()->SetRangeUser(1e-4, h_mX_SR->GetMaximum()*5.);
  else data_plot->GetYaxis()->SetRangeUser(0, h_mX_SR->GetMaximum()*1.5);
  data_plot->Draw();
  data_plot->GetXaxis()->SetLabelOffset(0.03);
  data_plot->GetYaxis()->SetLabelFont(42);
  data_plot->GetYaxis()->SetTitleFont(42);
  data_plot2->Draw("same");
  data_plot->GetYaxis()->SetTitleOffset(1.25);
  data_plot->SetTitle(("; m_{X} (GeV); Events / "+itoa(h_mX_SR->GetBinWidth(1))+" GeV").c_str());
  if (log=="log") p_1->SetLogy();

  TPaveText *pave = new TPaveText(0.86,0.6,0.67,0.7,"NDC");
  pave->SetBorderSize(0);
  pave->SetTextSize(0.03);
  pave->SetLineColor(1);
  pave->SetLineStyle(1);
  pave->SetLineWidth(2);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  char name[1000];
  char name1[1000];
  if (hist.substr(0,7)=="h_mX_SB") {
                sprintf(name,"SB #chi^{2}/n = %.2f",fitChi2);
                sprintf(name1,"p-value = %.2f",pvalue);
        }
  else sprintf(name,"SR #chi^{2}/n = %.2f",fitChi2);
  pave->AddText(name);
  pave->AddText(name1);
  pave->Draw();


  TLatex * tPrel = new TLatex();
  tPrel->SetNDC();
  tPrel->SetTextColor(kBlack);
  tPrel->SetTextSize(0.04);

  TLegend *leg = new TLegend(0.85625,0.7721654,0.6765625,0.8903839,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  h_mX_SR->SetMarkerStyle(20);
  if (hist.substr(0,7)=="h_mX_SB") leg->AddEntry(h_mX_SR, "Data in SB", "lep");
   else leg->AddEntry(h_mX_SR, "Data in SR", "lep"); 
  leg->Draw();

  CMS_lumi( p_1, iPeriod, iPos );

  p_2->cd();
  RooHist *hpull;
  hpull = data_plot->pullHist();
  RooPlot* frameP = x->frame() ;
	
  frameP->SetTitle("; m_{X} (GeV); Pull");
  frameP->addPlotable(hpull,"P");
  frameP->GetYaxis()->SetRangeUser(-5,5);
  frameP->GetXaxis()->SetRangeUser(fit_lo, fit_hi);
  frameP->SetTitle("");
  frameP->GetYaxis()->SetTitle("Pull");
  frameP->GetYaxis()->SetTitleFont(42);
  frameP->GetYaxis()->SetLabelFont(42);
  frameP->GetXaxis()->SetTitleFont(42);
  frameP->GetXaxis()->SetLabelFont(42);	
  frameP->GetYaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
  frameP->GetYaxis()->SetTitleOffset(1.2/((1.-xPad)/xPad));
  frameP->GetXaxis()->SetTitleSize((1.-xPad)/xPad*0.055);
  frameP->GetXaxis()->SetLabelSize((1.-xPad)/xPad*0.045);
  frameP->GetYaxis()->SetLabelSize((1.-xPad)/xPad*0.027);
  frameP->Draw();



  frameP->Draw();


  TLine *line=new TLine(fit_lo, 0, fit_hi, 0);
  line->SetLineWidth(2);
  line->Draw();

  string tag;
  if (hist.substr(0,7)=="h_mX_SB") tag="SB";
  else tag="SR";
  c_Background->SaveAs(("BackgroundFit_"+tag+"_CrystalBall.png").c_str());
  c_Background->SaveAs(("BackgroundFit_"+tag+"_CrystalBall.pdf").c_str());



    RooWorkspace *w_background=new RooWorkspace("HbbHbb");

  w_background->import(bg);
  w_background->import(bg_exp);

  // Normalize h_mX_SB to SR for pretend data
  TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
  h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
  RooDataHist data_obs("data_obs", "Data", RooArgList(*x), h_mX_SR_fakeData);
  
  w_background->import(data_obs);
  w_background->SaveAs("w_background_Crystal.root");

  // For the datacard
  std::cout<<" === RooFit data fit result to be entered in datacard === "<<std::endl;
  std::cout<<" Background number of events = "<<nEventsSR<<std::endl;
  std::cout<<"crystalball_mean param "<<bg_p2.getVal()<<" "<<bg_p2.getError()<<std::endl;
  std::cout<<"crystalball_width param "<<bg_p3.getVal()<<" "<<bg_p3.getError()<<std::endl;
  std::cout<<"crystalball_switch param "<<bg_p0.getVal()<<" "<<bg_p0.getError()<<std::endl;
  std::cout<<"crystalball_exponent param "<<bg_p1.getVal()<<" "<<bg_p1.getError()<<std::endl;

}




