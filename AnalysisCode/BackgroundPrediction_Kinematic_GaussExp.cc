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
#include <TLine.h>

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

void BackgroundPrediction_Kinematic_GaussExp(double plot_lo, double plot_hi, double rebin,
                                             double fit_lo, double fit_hi, 
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
  /*gROOT->LoadMacro("CMS_lumi.C");
  writeExtraText = false;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "2.2 fb^{-1}";  // default is "5.1 fb^{-1}"
  */
  TFile *f_data=new TFile("Histograms_Data_BTagCSV_2015_Skim.root");
  TH1F *h_mX_SR=(TH1F*)f_data->Get(hist.c_str());
  h_mX_SR->Rebin(rebin);
  double nEventsSR=((TH1F*)f_data->Get("h_mX_SR_kinFit"))->GetSumOfWeights();
  
  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred("pred", "Data", RooArgList(*x), h_mX_SR);
  
  RooRealVar bg_p0("bg_p0", "bg_p0", gaussexp_mean_lo, gaussexp_mean_hi);
  RooRealVar bg_p1("bg_p1", "bg_p1", gaussexp_width_lo, gaussexp_width_hi);
  RooRealVar bg_p2("bg_p2", "bg_p2", gaussexp_exp_lo, gaussexp_exp_hi);
  GaussExp bg("background", "Background Prediction PDF", *x, bg_p0, bg_p1, bg_p2);
  RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
  
  RooPlot *data_plot=x->frame();
  pred.plotOn(data_plot);
  bg.plotOn(data_plot, RooFit::VisualizeError(*r_bg, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
  bg.plotOn(data_plot, RooFit::LineColor(kBlack));
  pred.plotOn(data_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
  
  double fitChi2=data_plot->chiSquare();
  std::cout<<"Fit chi2 = "<<fitChi2<<std::endl;
  
  TCanvas *c_Background=new TCanvas("c_Background", "c_Background", 700, 700);
  TPad *p_1=new TPad("p_1", "p_1", 0, 0.35, 1, 1);
  //p_1->SetBottomMargin(0.05);
  //p_2->SetBottomMargin(-.5);
  // p_1->SetFillStyle(4000);
  // p_1->SetFrameFillColor(0);
  TPad *p_2 = new TPad("p_2", "p_2", 0, 0, 1., 0.35);
  p_2->SetFillColor(0);
  p_2->SetBorderMode(0);
  p_2->SetBorderSize(2);
  p_2->SetTopMargin(0.018);
  p_2->SetBottomMargin(0.30);
  p_2->SetFrameBorderMode(0);
  p_1->Draw();
  p_2->Draw();
  p_1->cd();
  
  if (log=="log") data_plot->GetYaxis()->SetRangeUser(1e-4, h_mX_SR->GetMaximum()*1.5);
  else data_plot->GetYaxis()->SetRangeUser(0, h_mX_SR->GetMaximum()*1.5);
  data_plot->Draw();
  data_plot->SetTitle(("; m_{X} (GeV); Events / "+itoa(h_mX_SR->GetBinWidth(1))+" GeV").c_str());
  if (log=="log") p_1->SetLogy();
  
  TPaveText *pave = new TPaveText(0.86,0.7,0.67,0.8,"NDC");
  pave->SetBorderSize(0);
  pave->SetTextSize(0.03);
  pave->SetLineColor(1);
  pave->SetLineStyle(1);
  pave->SetLineWidth(2);
  pave->SetFillColor(0);
  pave->SetFillStyle(0);
  char name[1000];
  if (hist.substr(0,7)=="h_mX_SB") sprintf(name,"SB #chi^{2}/n = %.2f",fitChi2);
  else sprintf(name,"SR #chi^{2}/n = %.2f",fitChi2);  
  pave->AddText(name);
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

  // CMS_lumi( p_1, iPeriod, iPos );

  p_2->cd();
  RooHist *hpull;
  hpull = data_plot->pullHist();
  RooPlot* frameP = x->frame() ;
  frameP->SetTitle("; m_{X} (GeV); Pull");
  frameP->addPlotable(hpull,"P");
  frameP->GetYaxis()->SetTitleSize(0.07);
  frameP->GetYaxis()->SetTitleOffset(0.5);
  frameP->GetXaxis()->SetTitleSize(0.09);
  frameP->GetXaxis()->SetTitleOffset(1.0);
  frameP->GetXaxis()->SetLabelSize(0.07);
  frameP->GetYaxis()->SetLabelSize(0.06);
  frameP->Draw();
  
  TLine *line=new TLine(fit_lo, 0, fit_hi, 0);
  line->SetLineWidth(2);
  line->Draw();
   
  string tag;
  if (hist.substr(0,7)=="h_mX_SB") tag="SB";
  else tag="SR";
  c_Background->SaveAs(("BackgroundFit_"+tag+"_GaussExp.png").c_str());
  c_Background->SaveAs(("BackgroundFit_"+tag+"_GaussExp.pdf").c_str());
  
  // --- Ratio of function to data points ---
  /*
  RooCurve *f_bg_pred=(RooCurve*)aS_plot->findObject("r_bg_prediction");
  TH1F *h_ratio=(TH1F*)h_mX_SR->Clone("h_ratio");
  for (unsigned int i=0; i<h_ratio->GetNbinsX(); ++i)
  {
    double fEval=f_bg_pred->Eval(h_mX_SR->GetBinCenter(i));
    double data=h_mX_SR->GetBinContent(i);
    // std::cout<<"i = "<<i<<", fEval = "<<fEval<<", data = "<<data<<std::endl;
    double binContent=(h_mX_SR->GetBinContent(i))/(f_bg_pred->Eval(h_mX_SR->GetBinCenter(i)));
    double binError=(h_mX_SR->GetBinError(i))/(f_bg_pred->Eval(h_mX_SR->GetBinCenter(i)));
    h_ratio->SetBinContent(i, binContent);
    h_ratio->SetBinError(i, binError);
  }
  h_ratio->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
  h_ratio->SetMaximum(2.5); h_ratio->SetMinimum(-0.5);
  h_ratio->SetTitle("Data/Fit in SR; m_{X} (GeV); Data/Fit");
  h_ratio->Fit("pol1", "", "", SR_lo, SR_hi);
  TCanvas *c_DataFit=new TCanvas("c_DataFit", "c_DataFit", 1000, 700);
  h_ratio->Draw();
  c_DataFit->SaveAs(("c_DataFit_"+tags+"SR.png").c_str());
  */
  // ------------------------------------------
  
   
  RooWorkspace *w_background=new RooWorkspace("HbbHbb");
  w_background->import(bg);
  w_background->SaveAs("w_background_GaussExp.root");
  
  // Normalize h_mX_SB to SR for pretend data
  TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
  h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
  RooDataHist data_obs("data_obs", "Data", RooArgList(*x), h_mX_SR_fakeData);
  
  RooWorkspace *w_data=new RooWorkspace("HbbHbb");
  w_data->import(data_obs);
  w_data->SaveAs("w_data.root");
  
  // For the datacard
  std::cout<<" === RooFit data fit result to be entered in datacard === "<<std::endl;
  std::cout<<" Background number of events = "<<nEventsSR<<std::endl;
  std::cout<< "bg_p0   param   "<<bg_p0.getVal()<<" "<<bg_p0.getError()<<std::endl;
  std::cout<< "bg_p1   param   "<<bg_p1.getVal()<<" "<<bg_p1.getError()<<std::endl;
  std::cout<< "bg_p2   param   "<<bg_p2.getVal()<<" "<<bg_p2.getError()<<std::endl;
  
}
  
  
  

