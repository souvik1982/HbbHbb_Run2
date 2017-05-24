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
#include <RooPolynomial.h>



int iPeriod = 4;
int iPos = 11;

#include "CMS_lumi.h"
#include <iostream>

void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
    bool outOfFrame    = false;
    if( iPosX/10==0 )
    {
        outOfFrame = true;
    }
    int alignY_=3;
    int alignX_=2;
    if( iPosX/10==0 ) alignX_=1;
    if( iPosX==0    ) alignX_=1;
    if( iPosX==0    ) alignY_=1;
    if( iPosX/10==1 ) alignX_=1;
    if( iPosX/10==2 ) alignX_=2;
    if( iPosX/10==3 ) alignX_=3;
    if( iPosX == 0  ) relPosX = 0.14;
    int align_ = 10*alignX_ + alignY_;
    
    float H = pad->GetWh();
    float W = pad->GetWw();
    float l = pad->GetLeftMargin();
    float t = pad->GetTopMargin();
    float r = pad->GetRightMargin();
    float b = pad->GetBottomMargin();
    
    pad->cd();
    
    TString lumiText;
    if( iPeriod==1 )
    {
        lumiText += lumi_7TeV;
        lumiText += " (7 TeV)";
    }
    else if ( iPeriod==2 )
    {
        lumiText += lumi_8TeV;
        lumiText += " (8 TeV)";
    }
    else if( iPeriod==3 )
    {
        lumiText = lumi_8TeV;
        lumiText += " (8 TeV)";
        lumiText += " + ";
        lumiText += lumi_7TeV;
        lumiText += " (7 TeV)";
    }
    else if ( iPeriod==4 )
    {
        lumiText += lumi_13TeV;
        lumiText += " (13 TeV)";
    }
    else if ( iPeriod==7 )
    {
        if( outOfFrame ) lumiText += "#scale[0.85]{";
        lumiText += lumi_13TeV;
        lumiText += " (13 TeV)";
        lumiText += " + ";
        lumiText += lumi_8TeV;
        lumiText += " (8 TeV)";
        lumiText += " + ";
        lumiText += lumi_7TeV;
        lumiText += " (7 TeV)";
        if( outOfFrame) lumiText += "}";
    }
    else if ( iPeriod==12 )
    {
        lumiText += "8 TeV";
    }
    else if ( iPeriod==0 )
    {
        lumiText += lumi_sqrtS;
    }
    
    std::cout << lumiText << endl;
    
    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    
    float extraTextSize = extraOverCmsTextSize*cmsTextSize;
    
    latex.SetTextFont(42);
    latex.SetTextAlign(31);
    latex.SetTextSize(lumiTextSize*t);
    latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);
    
    if( outOfFrame )
    {
        latex.SetTextFont(cmsTextFont);
        latex.SetTextAlign(11);
        latex.SetTextSize(cmsTextSize*t);
        latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
    
    pad->cd();
    
    float posX_=0;
    if( iPosX%10<=1 )
    {
        posX_ =   l + relPosX*(1-l-r);
    }
    else if( iPosX%10==2 )
    {
        posX_ =  l + 0.5*(1-l-r);
    }
    else if( iPosX%10==3 )
    {
        posX_ =  1-r - relPosX*(1-l-r);
    }
    float posY_ = 1-t - relPosY*(1-t-b);
    if( !outOfFrame )
    {
        if( drawLogo )
        {
            posX_ =   l + 0.045*(1-l-r)*W/H;
            posY_ = 1-t - 0.045*(1-t-b);
            float xl_0 = posX_;
            float yl_0 = posY_ - 0.15;
            float xl_1 = posX_ + 0.15*H/W;
            float yl_1 = posY_;
            TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
            TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
            pad_logo->Draw();
            pad_logo->cd();
            CMS_logo->Draw("X");
            pad_logo->Modified();
            pad->cd();
        }
        else
        {
            latex.SetTextFont(cmsTextFont);
            latex.SetTextSize(cmsTextSize*t);
            latex.SetTextAlign(align_);
            latex.DrawLatex(posX_, posY_, cmsText);
            if( writeExtraText )
            {
                latex.SetTextFont(extraTextFont);
                latex.SetTextAlign(align_);
                latex.SetTextSize(extraTextSize*t);
                latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
    else if( writeExtraText )
    {
        if( iPosX==0)
        {
            posX_ =   l +  relPosX*(1-l-r);
            posY_ =   1-t+lumiTextOffset*t;
        }
        latex.SetTextFont(extraTextFont);
        latex.SetTextSize(extraTextSize*t);
        latex.SetTextAlign(align_);
        latex.DrawLatex(posX_, posY_, extraText);
    }
    return;
}


std::string itoa(int i)
{
    char res[10];
    sprintf(res, "%d", i);
    std::string ret(res);
    return ret;
}

void BackgroundPrediction_Kinematic_Split_malara_old(double plot_lo, double plot_hi, double rebin,
                                                double fit_lo, double fit_hi,
                                                double crystalball_mean_lo, double crystalball_mean_hi,
                                                double crystalball_width_lo, double crystalball_width_hi,
                                                double crystalball_exp_lo, double crystalball_exp_hi,
                                                double crystalball_switch_lo, double crystalball_switch_hi,
                                                std::string hist="h_mX_SB_kinFit",
                                                std::string log="lin",
                                                std::string filename="Histograms_BTagall.root",
                                                std::string dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit")
{
    gROOT->SetStyle("Plain");
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    writeExtraText = true;
    extraText  = "Preliminary";
    lumi_13TeV  = "35.9 fb^{-1}";
    
    TFile *f_data=new TFile((filename).c_str());
    TH1F *h_mX_SR=(TH1F*)f_data->Get(hist.c_str());
    h_mX_SR->Rebin(rebin);
    TH1F *h_tmp=(TH1F*)f_data->Get("h_mX_SR_kinFit");
    double nEventsSR= h_tmp->Integral();
   
    RooRealVar *x = new RooRealVar("x", "m_{X} (GeV)", 252, 455);
    RooRealVar *x_2 = new RooRealVar("x_2", "m_{X} (GeV)", plot_lo, 550);
    RooDataHist pred("pred", "Data", RooArgList(*x), h_mX_SR);
    RooDataHist pred_2("pred_2", "pred_2", RooArgList(*x_2), h_mX_SR);
    double fit_mass = 400;
    
    
    RooRealVar* bg_pol0 = new RooRealVar("bg_pol0", "bg_pol0", 1.01772e+03, 2e+03, 3e+03);
    RooRealVar* bg_pol1 = new RooRealVar("bg_pol1", "bg_pol1", -2.76596e+00, -20., 10.);
    RooRealVar* bg_pol2 = new RooRealVar("bg_pol2", "bg_pol2", 1.94974e-03, -0.1, 0.1);

    RooRealVar* bg_comp0 = new RooRealVar("bg_comp0", "bg_comp0", 1.01772e+03, 2e+03, 3e+03);
    RooRealVar* bg_comp1 = new RooRealVar("bg_comp1", "bg_comp1", -2.76596e+00, -20., 10.);
    RooRealVar* bg_comp2 = new RooRealVar("bg_comp2", "bg_comp2", 1.94974e-03, -0.1, 0.1);

    //RooPlot *data_plot_test=x_2->frame();
    //pred_2.plotOn(data_plot_test);
    RooPolynomial* bg_temp;
    int comp_ii=100;
    TH1* hh_pdf_1;

    bg_temp = new RooPolynomial(Form("px_%d",comp_ii),Form("px_%d",comp_ii), *x_2 ,RooArgList(*bg_comp0, *bg_comp1, *bg_comp2), 0);
    x_2->setRange("comp",fit_mass-comp_ii,fit_mass+comp_ii);
    bg_temp->setNormRange("comp");
    RooFitResult *r_temp=bg_temp->fitTo(pred_2, RooFit::Range("comp"), RooFit::Save());
    TH1* hh_pdf_6 = bg_temp->createHistogram("comp",*x_2, RooFit::Binning(1000,fit_lo,650)) ;
    hh_pdf_6->Scale(rebin/hh_pdf_6->GetBinWidth(1)*pred_2.sumEntries(0,"comp")/hh_pdf_6->Integral((hh_pdf_6->FindBin(fit_mass-comp_ii)), (hh_pdf_6->FindBin(fit_mass+comp_ii))));
    RooPlot *data_plot_comp=x_2->frame();
    pred_2.plotOn(data_plot_comp);
    bg_temp->plotOn(data_plot_comp, RooFit::VisualizeError(*r_temp, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_temp->plotOn(data_plot_comp, RooFit::LineColor(kRed));
    //new TCanvas;
    //data_plot_comp->Draw("same"); hh_pdf_6->Draw("same");


    TLegend *leg_ratio = new TLegend(0.5,0.1,0.67,0.45,NULL,"brNDC");
    int color=1;
    //TCanvas *c_comp=new TCanvas(Form("c_%d",comp_ii), Form("c_%d",comp_ii), 800, 800);
    //c_comp->SetGrid();
    for(int ii=30; ii < 155; ii+=10){
      int range = comp_ii;
      //TCanvas *c_temp=new TCanvas(Form("c_%d_%d",range,ii), Form("c_%d_%d",range,ii), 800, 800);
      RooPolynomial bg_falling(Form("px_%d",ii),Form("px_%d",ii), *x_2 ,RooArgList(*bg_pol0, *bg_pol1, *bg_pol2), 0);
      x_2->setRange("small",fit_mass-ii,fit_mass+ii);
      x_2->setRange("total",fit_lo,fit_hi);
      bg_falling.setNormRange("small");
      RooFitResult *r_falling=bg_falling.fitTo(pred_2, RooFit::Range("small"), RooFit::Save());
      RooPlot *data_plot_test=x_2->frame();
      pred_2.plotOn(data_plot_test);
      bg_falling.plotOn(data_plot_test, RooFit::VisualizeError(*r_falling, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
      bg_falling.plotOn(data_plot_test, RooFit::LineColor(color));
      double fitChi2_4=data_plot_test->chiSquare(3);
      std::cout<<"Fit chi2 test case " << ii << " = "<<fitChi2_4<<std::endl;
      TH1* hh_pdf = bg_falling.createHistogram("px", *x_2, RooFit::Binning(1000,fit_lo,650)) ;
      TH1* hh_pdf_2 = bg_falling.createHistogram("difference_1",*x_2, RooFit::Binning(1000,fit_lo,650)) ;
      TH1* hh_pdf_4 = bg_falling.createHistogram("sum",*x_2, RooFit::Binning(1000,fit_lo,650)) ;
      TH1* hh_pdf_5 = bg_falling.createHistogram("ratio",*x_2, RooFit::Binning(1000,fit_lo,650)) ;
      hh_pdf_5->SetTitle(Form("ratio %d %d",range,ii));
      if (color==10) color=40;
      hh_pdf_5->SetLineColor(color);
      hh_pdf->SetLineColor(color); color++;

      //x_2->setVal(fit_mass);
      RooRealVar *x_3 = new RooRealVar("x_3", "m_{X} (GeV)", fit_mass-ii,fit_mass+ii );
      RooArgSet obs(*x_2);
      x_2->Print();
      x_3->Print();
      RooAbsReal* igx = bg_falling.createIntegral(*x_2) ;
      RooAbsReal* igx_sig = bg_falling.createIntegral(*x_3,RooFit::NormSet(*x_3),RooFit::Range("small")) ;
      std::cout << "AA " << bg_falling.getVal(&obs) << " " << bg_falling.getVal()<< " " << igx->getVal() << " " << igx_sig->getVal() <<  std::endl;
      std::cout << "CAA " << hh_pdf->GetBinContent(hh_pdf->FindBin(fit_mass)) << " " << hh_pdf->GetBinWidth(100) <<  std::endl;
      std::cout << "AA " << pred_2.sumEntries(0,"small") << " " << ii <<std::endl;
      std::cout << "AA " << bg_falling.getValV(&obs) <<std::endl;
      std::cout << "AAA " << bg_falling.getVal(&obs) * pred_2.sumEntries(0,"small") <<std::endl;

      std::cout << "ANDREA " << hh_pdf->GetBinContent(hh_pdf->FindBin(fit_mass)) <<std::endl;
      std::cout <<std::endl;
      std::cout << "range " << ii <<std::endl;
      std::cout << "pred " << pred_2.sumEntries(0,"small") <<std::endl;
      std::cout << "int pre scale " << hh_pdf->Integral() <<std::endl;
      std::cout << "pre scale " << hh_pdf->Integral((hh_pdf->FindBin(fit_mass-ii)), (hh_pdf->FindBin(fit_mass+ii))) <<std::endl;
      std::cout << "bin width " << hh_pdf->GetBinWidth(1) <<std::endl;
      //hh_pdf->Scale(bg_falling.getVal(&obs)/hh_pdf->GetBinContent(hh_pdf->FindBin(fit_mass)));
      //hh_pdf->Scale(bg_falling.getVal(&obs)/hh_pdf->Integral());
      hh_pdf->Scale( pred_2.sumEntries(0,"small")/hh_pdf->Integral((hh_pdf->FindBin(fit_mass-ii)), (hh_pdf->FindBin(fit_mass+ii))));

      std::cout << "int subrange " << hh_pdf->Integral((hh_pdf->FindBin(fit_mass-ii)), (hh_pdf->FindBin(fit_mass+ii))) <<std::endl;
      std::cout << "int tot " << hh_pdf->Integral() <<std::endl;
      hh_pdf->Scale(rebin/hh_pdf->GetBinWidth(1)); 
      std::cout << "int subrange " << hh_pdf->Integral((hh_pdf->FindBin(fit_mass-ii)), (hh_pdf->FindBin(fit_mass+ii))) <<std::endl;
      std::cout << "int tot " << hh_pdf->Integral() <<std::endl;
      std::cout << "fit_mass " << hh_pdf->GetBinContent(hh_pdf->FindBin(fit_mass)) <<std::endl;

      hh_pdf_2->Scale(rebin/hh_pdf_2->GetBinWidth(1)*pred_2.sumEntries(0,"small")/hh_pdf_2->Integral((hh_pdf_2->FindBin(fit_mass-ii)), (hh_pdf_2->FindBin(fit_mass+ii))));
      hh_pdf_4->Scale(rebin/hh_pdf_4->GetBinWidth(1)*pred_2.sumEntries(0,"small")/hh_pdf_4->Integral((hh_pdf_4->FindBin(fit_mass-ii)), (hh_pdf_4->FindBin(fit_mass+ii))));
      hh_pdf_5->Scale(rebin/hh_pdf_5->GetBinWidth(1)*pred_2.sumEntries(0,"small")/hh_pdf_5->Integral((hh_pdf_5->FindBin(fit_mass-ii)), (hh_pdf_5->FindBin(fit_mass+ii))));

if(ii==30){
hh_pdf_1 = bg_falling.createHistogram("crystal",*x_2, RooFit::Binning(1000,fit_lo,650)) ;
      hh_pdf_1->Scale(rebin/hh_pdf_1->GetBinWidth(1)*pred_2.sumEntries(0,"small")/hh_pdf_1->Integral((hh_pdf_1->FindBin(fit_mass-ii)), (hh_pdf_1->FindBin(fit_mass+ii))));
}
      //data_plot_test->Draw("same");
      //hh_pdf->Draw("same");
      //hh_pdf_1->Draw("same");
      //hh_pdf_2->Draw("same");
      //hh_pdf_4->Draw("same");
      //hh_pdf_5->Draw("same");
      //hh_pdf_6->Draw("same");
      
      //bg_temp = new RooPolynomial(Form("px_%d",range),Form("px_%d",range), *x_2 ,RooArgList(*bg_pol0, *bg_pol1, *bg_pol2), 0);
      //x_2->setRange("prev",fit_mass-range,fit_mass+range);
      //bg_falling.setNormRange("prev");
      //RooFitResult *r_temp=bg_temp->fitTo(pred_2, RooFit::Range("prev"), RooFit::Save());
      //cout<<"ANDREA " << range << " " << ii << endl;
      //r_temp->Print();
      //r_falling->Print();

      //TH1* hh_pdf_1 = bg_temp->createHistogram("crystal",*x_2, RooFit::Binning(1000,fit_mass-range,fit_mass+range)) ;
      //hh_pdf_1->Scale(pred_2.sumEntries(0,"prev"));
      //data_plot_test->Draw("same"); hh_pdf->Draw("same"); //hh_pdf_1->SetLineColor(kRed) ;hh_pdf_1->Draw("same");  data_plot_test->Draw("same"); 

      //hh_pdf_2->Add(hh_pdf_1,-1);
      hh_pdf_2->Add(hh_pdf_6,-1);

      //hh_pdf_4->Add(hh_pdf_1,1);
      hh_pdf_4->Add(hh_pdf_6,1);
      hh_pdf_4->Scale(0.5);

      hh_pdf_5->Add(hh_pdf,-1);
      hh_pdf_5->Add(hh_pdf_2,1);
      hh_pdf_5->Divide(hh_pdf_4);
      hh_pdf_5->Scale(100);
      hh_pdf->GetXaxis()->SetRangeUser(fit_mass-ii, fit_mass+ii);
      hh_pdf_5->GetXaxis()->SetRangeUser(fit_mass-ii, fit_mass+ii);
      //hh_pdf->GetYaxis()->SetRangeUser(-10,10);
      hh_pdf_5->GetYaxis()->SetRangeUser(-10,10);
      //TCanvas *c_temp=new TCanvas(Form("c_%d_%d",range,ii), Form("c_%d_%d",range,ii), 800, 800);
      std::cout << "ccc " << hh_pdf_5->GetBinContent(hh_pdf_5->FindBin(fit_mass)) << " " << hh_pdf_5->Integral() <<  std::endl;

      hh_pdf_1 = bg_falling.createHistogram("crystal",*x_2, RooFit::Binning(1000,fit_lo,650)) ; 
      hh_pdf_1->Scale(rebin/hh_pdf_1->GetBinWidth(1)*pred_2.sumEntries(0,"small")/hh_pdf_1->Integral((hh_pdf_1->FindBin(fit_mass-ii)), (hh_pdf_1->FindBin(fit_mass+ii))));
     TLine* l_1=new TLine(fit_mass-(20),-180,fit_mass-(20),280); 
     TLine* l_2=new TLine(fit_mass+(20),-180,fit_mass+(20),280); 
     //l_1->Draw("same");
     //l_2->Draw("same");

     leg_ratio->SetBorderSize(0);
     leg_ratio->SetTextSize(0.030);
     leg_ratio->SetLineColor(1);
     leg_ratio->SetLineStyle(1);
     leg_ratio->SetLineWidth(2);
     leg_ratio->SetFillColor(0);
     leg_ratio->SetFillStyle(0);
     leg_ratio->AddEntry(hh_pdf_5, Form("%d %d", range, ii), "l");

    }
 
    //leg_ratio->Draw("same");
    RooRealVar* bg_pol0_1 = new RooRealVar("bg_pol0_1", "bg_pol0_1", 1.01772e+03, 2e+03, 3e+03);
    RooRealVar* bg_pol1_1 = new RooRealVar("bg_pol1_1", "bg_pol1_1", -2.76596e+00, -20., 10.);
    RooRealVar* bg_pol2_1 = new RooRealVar("bg_pol2_1", "bg_pol2_1", 1.94974e-03, -0.1, 0.1);

      int pol_1=50;
    RooRealVar* x_4 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-pol_1, fit_mass+pol_1); 
      RooPolynomial bg_falling_1("bg_falling_1", "bg_falling_1", *x_4 ,RooArgList(*bg_pol0_1, *bg_pol1_1, *bg_pol2_1), 0);
      x_4->setRange("small",fit_mass-pol_1,fit_mass+pol_1);
      x_4->setRange("total",fit_lo,650);
      bg_falling_1.setNormRange("small");
    RooDataHist pred_4("pred_4", "pred_4", RooArgList(*x_4), h_mX_SR);
      RooFitResult *r_falling_1=bg_falling_1.fitTo(pred_4, RooFit::Range("small"), RooFit::Save());
      RooPlot *data_plot_test_2=x_4->frame();
      pred_4.plotOn(data_plot_test_2);
      bg_falling_1.plotOn(data_plot_test_2, RooFit::VisualizeError(*r_falling_1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
      bg_falling_1.plotOn(data_plot_test_2, RooFit::LineColor(kRed));
//new TCanvas; data_plot_test_2->Draw();

RooRealVar* bg_pol0_2 = new RooRealVar("bg_pol0_2", "bg_pol0_2", 1.01772e+03, 2e+03, 3e+03);
    RooRealVar* bg_pol1_2 = new RooRealVar("bg_pol1_2", "bg_pol1_2", -2.76596e+00, -20., 10.);
    RooRealVar* bg_pol2_2 = new RooRealVar("bg_pol2_2", "bg_pol2_2", 1.94974e-03, -0.1, 0.1);

      int pol_2=110;
    RooRealVar* x_5 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-pol_2, fit_mass+pol_2);
      RooPolynomial bg_falling_2("bg_falling_2", "bg_falling_2", *x_5 ,RooArgList(*bg_pol0_2, *bg_pol1_2, *bg_pol2_2), 0);
      x_5->setRange("small",fit_mass-pol_2,fit_mass+pol_2);
      x_5->setRange("total",fit_lo,650);
      bg_falling_2.setNormRange("small");
    RooDataHist pred_5("pred_5", "pred_5", RooArgList(*x_5), h_mX_SR);
      RooFitResult *r_falling_2=bg_falling_2.fitTo(pred_5, RooFit::Range("small"), RooFit::Save());
      RooPlot *data_plot_test_3=x_5->frame();
      pred_5.plotOn(data_plot_test_3);
      bg_falling_2.plotOn(data_plot_test_3, RooFit::VisualizeError(*r_falling_2, 10), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
      bg_falling_2.plotOn(data_plot_test_3, RooFit::LineColor(kRed));
//new TCanvas; data_plot_test_3->Draw();


    int polexp_1 = 90;
    RooRealVar* x_6 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-polexp_1, fit_mass+polexp_1);
    RooRealVar* bg_polexp0_1 = new RooRealVar("bg_polexp0_1", "bg_polexp0_1", 1.e-03, -1, 1);
    RooRealVar* bg_polexp1_1 = new RooRealVar("bg_polexp1_1", "bg_polexp1_1", -2.e-03, -1., 1.);
    RooRealVar* bg_polexp2_1 = new RooRealVar("bg_polexp2_1", "bg_polexp2_1", 1.94974e-03, -0.1, 0.1);
    Falling bg_falling1_1("bg_falling1_1", "bg_falling1_1", *x_6 ,*bg_polexp0_1, *bg_polexp1_1, *bg_polexp2_1);
    x_6->setRange("small",fit_mass-polexp_1,fit_mass+polexp_1);
    x_6->setRange("total",fit_lo,650);
    bg_falling1_1.setNormRange("small");
    RooDataHist pred_6("pred_6", "pred_6", RooArgList(*x_6), h_mX_SR);
    RooFitResult *r_falling1_1=bg_falling1_1.fitTo(pred_6, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling1_1=x_6->frame();
    pred_6.plotOn(data_plot_falling1_1);
    bg_falling1_1.plotOn(data_plot_falling1_1, RooFit::VisualizeError(*r_falling1_1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling1_1.plotOn(data_plot_falling1_1, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling1_1->Draw();


    int polexp_2 = 100;
    RooRealVar* x_7 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-polexp_2, fit_mass+polexp_2);
    RooRealVar* bg_polexp0_2 = new RooRealVar("bg_polexp0_2", "bg_polexp0_2", 1.e-03, -1, 1);
    RooRealVar* bg_polexp1_2 = new RooRealVar("bg_polexp1_2", "bg_polexp1_2", -2.e-03, -1., 1.);
    RooRealVar* bg_polexp2_2 = new RooRealVar("bg_polexp2_2", "bg_polexp2_2", 1.94974e-03, -0.1, 0.1);
    Falling bg_falling1_2("bg_falling1_2", "bg_falling1_2", *x_7 ,*bg_polexp0_2, *bg_polexp1_2, *bg_polexp2_2);
    x_7->setRange("small",fit_mass-polexp_2,fit_mass+polexp_2);
    x_7->setRange("total",fit_lo,650);
    bg_falling1_2.setNormRange("small");
    RooDataHist pred_7("pred_7", "pred_7", RooArgList(*x_7), h_mX_SR);
    RooFitResult *r_falling1_2=bg_falling1_2.fitTo(pred_7, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling1_2=x_7->frame();
    pred_7.plotOn(data_plot_falling1_2);
    bg_falling1_2.plotOn(data_plot_falling1_2, RooFit::VisualizeError(*r_falling1_2, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling1_2.plotOn(data_plot_falling1_2, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling1_2->Draw();


    int powerlaw_1 = 90;
    RooRealVar* x_8 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-powerlaw_1, fit_mass+powerlaw_1);
    RooRealVar* bg_powerlaw0_1 = new RooRealVar("bg_powerlaw0_1", "bg_powerlaw0_1", 1.e-03, -1, 1);
    RooRealVar* bg_powerlaw1_1 = new RooRealVar("bg_powerlaw1_1", "bg_powerlaw1_1", -2.e-03, -1., 1.);
    RooRealVar* bg_powerlaw2_1 = new RooRealVar("bg_powerlaw2_1", "bg_powerlaw2_1", 1.94974e-03, -0.1, 0.1);
    Falling_1 bg_falling2_1("bg_falling2_1", "bg_falling2_1", *x_8 ,*bg_powerlaw0_1, *bg_powerlaw1_1, *bg_powerlaw2_1);
    x_8->setRange("small",fit_mass-powerlaw_1,fit_mass+powerlaw_1);
    x_8->setRange("total",fit_lo,650);
    bg_falling2_1.setNormRange("small");
    RooDataHist pred_8("pred_8", "pred_8", RooArgList(*x_8), h_mX_SR);
    RooFitResult *r_falling2_1=bg_falling2_1.fitTo(pred_8, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling2_1=x_8->frame();
    pred_8.plotOn(data_plot_falling2_1);
    bg_falling2_1.plotOn(data_plot_falling2_1, RooFit::VisualizeError(*r_falling2_1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling2_1.plotOn(data_plot_falling2_1, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling2_1->Draw();


    int powerlaw_2 = 100;
    RooRealVar* x_9 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-powerlaw_2, fit_mass+powerlaw_2);
    RooRealVar* bg_powerlaw0_2 = new RooRealVar("bg_powerlaw0_2", "bg_powerlaw0_2", 1.e-03, -1, 1);
    RooRealVar* bg_powerlaw1_2 = new RooRealVar("bg_powerlaw1_2", "bg_powerlaw1_2", -2.e-03, -1., 1.);
    RooRealVar* bg_powerlaw2_2 = new RooRealVar("bg_powerlaw2_2", "bg_powerlaw2_2", 1.94974e-03, -0.1, 0.1);
    Falling_1 bg_falling2_2("bg_falling2_2", "bg_falling2_2", *x_9 ,*bg_powerlaw0_2, *bg_powerlaw1_2, *bg_powerlaw2_2);
    x_9->setRange("small",fit_mass-powerlaw_2,fit_mass+powerlaw_2);
    x_9->setRange("total",fit_lo,650);
    bg_falling2_2.setNormRange("small");
    RooDataHist pred_9("pred_9", "pred_9", RooArgList(*x_9), h_mX_SR);
    RooFitResult *r_falling2_2=bg_falling2_2.fitTo(pred_9, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling2_2=x_9->frame();
    pred_9.plotOn(data_plot_falling2_2);
    bg_falling2_2.plotOn(data_plot_falling2_2, RooFit::VisualizeError(*r_falling2_2, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling2_2.plotOn(data_plot_falling2_2, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling2_2->Draw();

   
    int crystal_1 = 100; 
    RooRealVar* x_10 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-crystal_1, fit_mass+crystal_1);
    RooRealVar bg_crystal0_1("bg_crystal0_1", "bg_crystal0_1", 0.01, 5.1);
    RooRealVar bg_crystal1_1("bg_crystal1_1", "bg_crystal1_1", 0.01, 5.1);
    RooRealVar bg_crystal2_1("bg_crystal2_1", "bg_crystal2_1", 240, 280);
    RooRealVar bg_crystal3_1("bg_crystal3_1", "bg_crystal3_1", 3, 30);
    RevCrystalBall bg_falling3_1("bg_falling3_1", "Background Prediction PDF", *x_10, bg_crystal0_1, bg_crystal1_1, bg_crystal2_1, bg_crystal3_1);
    x_10->setRange("small",fit_mass-crystal_1,fit_mass+crystal_1);
    x_10->setRange("total",fit_lo,650);
    bg_falling3_1.setNormRange("small");
    RooDataHist pred_10("pred_10", "pred_10", RooArgList(*x_10), h_mX_SR);
    RooFitResult *r_falling3_1=bg_falling3_1.fitTo(pred_10, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling3_1=x_10->frame();
    pred_10.plotOn(data_plot_falling3_1);
    bg_falling3_1.plotOn(data_plot_falling3_1, RooFit::VisualizeError(*r_falling3_1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling3_1.plotOn(data_plot_falling3_1, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling3_1->Draw();



    int crystal_2 = 110;
    RooRealVar* x_11 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-crystal_2, fit_mass+crystal_2);
    RooRealVar bg_crystal0_2("bg_crystal0_2", "bg_crystal0_2", 0.01, 5.1);
    RooRealVar bg_crystal1_2("bg_crystal1_2", "bg_crystal1_2", 0.01, 5.1);
    RooRealVar bg_crystal2_2("bg_crystal2_2", "bg_crystal2_2", 240, 280);
    RooRealVar bg_crystal3_2("bg_crystal3_2", "bg_crystal3_2", 3, 30);
    RevCrystalBall bg_falling3_2("bg_falling3_2", "Background Prediction PDF", *x_11, bg_crystal0_2, bg_crystal1_2, bg_crystal2_2, bg_crystal3_2);
    x_11->setRange("small",fit_mass-crystal_2,fit_mass+crystal_2);
    x_11->setRange("total",fit_lo,650);
    bg_falling3_2.setNormRange("small");
    RooDataHist pred_11("pred_11", "pred_11", RooArgList(*x_11), h_mX_SR);
    RooFitResult *r_falling3_2=bg_falling3_2.fitTo(pred_11, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling3_2=x_11->frame();
    pred_11.plotOn(data_plot_falling3_2);
    bg_falling3_2.plotOn(data_plot_falling3_2, RooFit::VisualizeError(*r_falling3_2, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling3_2.plotOn(data_plot_falling3_2, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling3_2->Draw();



    int crystal_3 = 50;
    RooRealVar* x_12 =new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
    RooRealVar bg_crystal0_3("bg_crystal0_3", "bg_crystal0_3", 0.01, 5.1);
    RooRealVar bg_crystal1_3("bg_crystal1_3", "bg_crystal1_3", 0.01, 5.1);
    RooRealVar bg_crystal2_3("bg_crystal2_3", "bg_crystal2_3", 240, 280);
    RooRealVar bg_crystal3_3("bg_crystal3_3", "bg_crystal3_3", 3, 30);
    RevCrystalBall bg_falling3_3("bg_falling3_3", "Background Prediction PDF", *x_12, bg_crystal0_3, bg_crystal1_3, bg_crystal2_3, bg_crystal3_3);
    x_12->setRange("small",fit_lo, fit_hi);
    x_12->setRange("total",fit_lo,650);
    bg_falling3_3.setNormRange("small");
    RooDataHist pred_12("pred_12", "pred_12", RooArgList(*x_12), h_mX_SR);
    RooFitResult *r_falling3_3=bg_falling3_3.fitTo(pred_12, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling3_3=x_12->frame();
    pred_12.plotOn(data_plot_falling3_3);
    bg_falling3_3.plotOn(data_plot_falling3_3, RooFit::VisualizeError(*r_falling3_3, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling3_3.plotOn(data_plot_falling3_3, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling3_3->Draw();
    
    RooRealVar* x_13 =new RooRealVar("x", "m_{X} (GeV)", fit_mass-crystal_3, fit_mass+crystal_3); 
    RooRealVar bg_crystal0_4("bg_crystal0_4", "bg_crystal0_4", 0.01, 5.1);
    RooRealVar bg_crystal1_4("bg_crystal1_4", "bg_crystal1_4", 0.01, 5.1);
    RooRealVar bg_crystal2_4("bg_crystal2_4", "bg_crystal2_4", 240, 280);
    RooRealVar bg_crystal3_4("bg_crystal3_4", "bg_crystal3_4", 3, 30);
    RevCrystalBall bg_falling3_4(Form("bg_falling3_%d", crystal_3), "Background Prediction PDF", *x_13, bg_crystal0_4, bg_crystal1_4, bg_crystal2_4, bg_crystal3_4);
    bg_crystal0_4.setVal(bg_crystal0_3.getVal());
    bg_crystal1_4.setVal(bg_crystal1_3.getVal());
    bg_crystal2_4.setVal(bg_crystal2_3.getVal());
    bg_crystal3_4.setVal(bg_crystal3_3.getVal());
    RooDataHist pred_13("pred_13", "pred_13", RooArgList(*x_13), h_mX_SR);
    //RooFitResult *r_falling3_4=bg_falling3_4.fitTo(pred_13, RooFit::Range("small"), RooFit::Save());
    RooPlot *data_plot_falling3_4=x_13->frame();
    pred_13.plotOn(data_plot_falling3_4);
    //bg_falling3_4.plotOn(data_plot_falling3_4, RooFit::VisualizeError(*r_falling3_4, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg_falling3_4.plotOn(data_plot_falling3_4, RooFit::LineColor(kRed));
    //new TCanvas; data_plot_falling3_4->Draw();


    RooRealVar bg_gauss_1_0("bg_gauss_1_0", "bg_gauss_1_0", 275, 270, 285);
    RooRealVar bg_gauss_1_1("bg_gauss_1_1", "bg_gauss_1_1", 2, 1, 10);
    RooRealVar bg_gauss_2_0("bg_gauss_2_0", "bg_gauss_2_0", 400, 370, 420);
    RooRealVar bg_gauss_2_1("bg_gauss_2_1", "bg_gauss_2_1", 100, 100, 150);
    RooRealVar bg_gauss_add("bg_gauss_add", "bg_gauss_add", 0.25, -1, 1);
    
    RooGaussian* bg_gauss_1 = new RooGaussian("gauss_1", "gauss_1", *x, bg_gauss_1_0, bg_gauss_1_1);
    //RooGaussian* bg_sum_gauss = new RooGaussian("gauss_1", "gauss_1", *x, bg_gauss_1_0, bg_gauss_1_1);
    RooGaussian* bg_gauss_2 = new RooGaussian("gauss_2", "gauss_2", *x, bg_gauss_2_0, bg_gauss_2_1);
    //RooGaussian* bg_sum_gauss = new RooGaussian("gauss_2", "gauss_2", *x, bg_gauss_2_0, bg_gauss_2_1);
    
    RooAddPdf* bg_sum_gauss = new RooAddPdf("sum_gauss", "sum_gauss", RooArgList(*bg_gauss_1, *bg_gauss_2), bg_gauss_add); 
    RooFitResult *r_bg_sum_gauss=bg_sum_gauss->fitTo(pred, RooFit::Range(255, 300), RooFit::Save());
    RooPlot *data_plot3=x->frame();
    pred.plotOn(data_plot3);
    bg_sum_gauss->plotOn(data_plot3, RooFit::LineColor(kBlue+1));
    //new TCanvas;
    //data_plot3->Draw();




    RooRealVar* x_novo =new RooRealVar("x", "m_{X} (GeV)", 0 , 650); 
    RooRealVar bg_novo_0("bg_novo_0", "bg_novo_0", 275, 10, 285);
    RooRealVar bg_novo_1("bg_novo_1", "bg_novo_1", 10, 10, 100); 
    RooRealVar bg_novo_2("bg_novo_2", "bg_novo_2", -1e+01, -100, 1); 
    RooNovosibirsk bg_novo("bg_novo", "Background Prediction PDF", *x, bg_novo_0, bg_novo_1, bg_novo_2);

    RooPlot *data_plot4=x->frame();
    int fit_novo_0=275;
    int fit_novo_1=450;
    RooFitResult *r_bg_novo=bg_novo.fitTo(pred, RooFit::Range(fit_novo_0, fit_novo_1), RooFit::Save());
    pred.plotOn(data_plot4, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    bg_novo.plotOn(data_plot4, RooFit::LineColor(kBlue+1));
    //bg_novo.plotOn(data_plot4, RooFit::VisualizeError(*r_bg_novo, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    double fitChi2_novo=data_plot4->chiSquare();
    //new TCanvas;
    //data_plot4->Draw();



    TPaveText *pave_1 = new TPaveText(0.90,0.6,0.67,0.8,"NDC");
    pave_1->SetBorderSize(0);
    pave_1->SetTextSize(0.03);
    pave_1->SetLineColor(1);
    pave_1->SetLineStyle(1);
    pave_1->SetLineWidth(2);
    pave_1->SetFillColor(0);
    pave_1->SetFillStyle(0);
    char value[1000];
    sprintf(value,"mean = %2.1f",bg_novo_0.getVal());
    pave_1->AddText(value);
    sprintf(value,"sigma = %2.1f",bg_novo_1.getVal());
    pave_1->AddText(value);
    sprintf(value,"tail = %2.1f",bg_novo_2.getVal());
    pave_1->AddText(value);
    sprintf(value,"range [%d,%d]",fit_novo_0, fit_novo_1);
    pave_1->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_novo);
    pave_1->AddText(value);
    //pave_1->Draw();




    RooRealVar bg_novo1_0("bg_novo1_0", "bg_novo1_0", 275, 1, 285);
    RooRealVar bg_novo1_1("bg_novo1_1", "bg_novo1_1", 10, 1, 100);
    RooRealVar bg_novo1_2("bg_novo1_2", "bg_novo1_2", -1e+02, -10000, 1);
    RooNovosibirsk bg_nov1("bg_novo_1", "Background Prediction PDF", *x, bg_novo1_0, bg_novo1_1, bg_novo1_2);

    RooRealVar bg_erf_0("bg_erf_0", "bg_erf_0", 0.05, 0, 1000);
    RooRealVar bg_erf_1("bg_erf_1", "bg_erf_1", 275, 10, 285);
    NovoErf bg_erf("bg_erf", "Background Prediction PDF", *x, bg_erf_0, bg_erf_1);

    RooProdPdf bg_novo1("bg_novo1", "bg_novo1", bg_nov1, bg_erf);

    RooPlot *data_plot5=x->frame();
    int fit_novo1_0=350;
    int fit_novo1_1=550;
    RooFitResult *r_bg_novo1=bg_novo1.fitTo(pred, RooFit::Range(fit_novo1_0, fit_novo1_1), RooFit::Save());
    pred.plotOn(data_plot5, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    bg_novo1.plotOn(data_plot5, RooFit::LineColor(kBlue+1));
    //bg_novo.plotOn(data_plot5, RooFit::VisualizeError(*r_bg_novo1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    double fitChi2_novo1=data_plot5->chiSquare();
    //new TCanvas;
    //data_plot5->Draw();



    TPaveText *pave_2 = new TPaveText(0.90,0.6,0.67,0.8,"NDC");
    pave_2->SetBorderSize(0);
    pave_2->SetTextSize(0.03);
    pave_2->SetLineColor(1);
    pave_2->SetLineStyle(1);
    pave_2->SetLineWidth(2);
    pave_2->SetFillColor(0);
    pave_2->SetFillStyle(0);
    sprintf(value,"mean = %2.1f",bg_novo1_0.getVal());
    pave_2->AddText(value);
    sprintf(value,"sigma = %2.1f",bg_novo1_1.getVal());
    pave_2->AddText(value);
    sprintf(value,"tail = %2.1f",bg_novo1_2.getVal());
    pave_2->AddText(value);
    sprintf(value,"p0 = %2.1f",bg_erf_0.getVal());
    pave_2->AddText(value);
    sprintf(value,"p1 = %2.1f",bg_erf_1.getVal());
    pave_2->AddText(value);
    sprintf(value,"range [%d,%d]",fit_novo1_0, fit_novo1_1);
    pave_2->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_novo1);
    pave_2->AddText(value);
    //pave_2->Draw();


    


    RooRealVar bg_novo2_0("bg_novo2_0", "bg_novo2_0", 275, 1, 285);
    RooRealVar bg_novo2_1("bg_novo2_1", "bg_novo2_1", 10, 1, 100);
    RooRealVar bg_novo2_2("bg_novo2_2", "bg_novo2_2", -1e+02, -10000, 1);
    RooNovosibirsk bg_nov2("bg_novo_1", "Background Prediction PDF", *x, bg_novo2_0, bg_novo2_1, bg_novo2_2);

    RooRealVar bg_erf2_0("bg_erf2_0", "bg_erf2_0", 0.05, 0, 1);
    RooRealVar bg_erf2_1("bg_erf2_1", "bg_erf2_1", 275, 10, 285);
    NovoErf bg_erf2("bg_erf2", "Background Prediction PDF", *x, bg_erf2_0, bg_erf2_1);

    RooFFTConvPdf nxe("nxe","Novo (X) Erf",*x,bg_nov1, bg_erf2) ;

    RooPlot *data_plot6=x->frame();
    int fit_novo2_0=375;
    int fit_novo2_1=650;
    RooFitResult *r_bg_novo2=nxe.fitTo(pred, RooFit::Range(fit_novo2_0, fit_novo2_1), RooFit::Save());
    //pred.plotOn(data_plot6, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    bg_erf.plotOn(data_plot6, RooFit::LineColor(kGreen+1));
    bg_nov1.plotOn(data_plot6, RooFit::LineColor(kRed+1));
    nxe.plotOn(data_plot6, RooFit::LineColor(kBlue+1));
    //bg_novo.plotOn(data_plot5, RooFit::VisualizeError(*r_bg_novo1, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    double fitChi2_novo2=data_plot6->chiSquare();
    //new TCanvas;
    //data_plot6->Draw();


    TPaveText *pave_3 = new TPaveText(0.90,0.6,0.67,0.8,"NDC");
    pave_3->SetBorderSize(0);
    pave_3->SetTextSize(0.03);
    pave_3->SetLineColor(1);
    pave_3->SetLineStyle(1);
    pave_3->SetLineWidth(2);
    pave_3->SetFillColor(0);
    pave_3->SetFillStyle(0);
    sprintf(value,"mean = %2.1f",bg_novo2_0.getVal());
    pave_3->AddText(value);
    sprintf(value,"sigma = %2.1f",bg_novo2_1.getVal());
    pave_3->AddText(value);
    sprintf(value,"tail = %2.1f",bg_novo2_2.getVal());
    pave_3->AddText(value);
    sprintf(value,"p0 = %2.1f",bg_erf2_0.getVal());
    pave_3->AddText(value);
    sprintf(value,"p1 = %2.1f",bg_erf2_1.getVal());
    pave_3->AddText(value);
    sprintf(value,"range [%d,%d]",fit_novo2_0, fit_novo2_1);
    pave_3->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_novo2);
    pave_3->AddText(value);
    //pave_3->Draw();







    RooRealVar* bg_pol3_0 = new RooRealVar("bg_pol3_0", "bg_pol3_0", -2.33851e+04, -6e+04, -2e+03);
    RooRealVar* bg_pol3_1 = new RooRealVar("bg_pol3_1", "bg_pol3_1", 1.42946e+02, 3.1e+01, 3.2e+02);
    RooRealVar* bg_pol3_2 = new RooRealVar("bg_pol3_2", "bg_pol3_2", -6.5e-02, -6.6e-02, -6.4e-02);
    RooRealVar* bg_pol3_3 = new RooRealVar("bg_pol3_3", "bg_pol3_3", 4.38162e-05, 4.3e-05, 4.4e-05);
    RooPolynomial bg_pol3("bg_pol3", "bg_pol3", *x, RooArgList(*bg_pol3_0, *bg_pol3_1, *bg_pol3_2, *bg_pol3_3), 0);

    RooRealVar ml("ml","mean landau",2.74e+02,2.5e+02,2.8e+02) ;
    RooRealVar sl("sl","sigma landau",2.5e+01,18,30) ;
    RooLandau landau("lx","lx",*x,ml,sl) ;

    int fit_pol_land_0=270;
    int fit_pol_land_1=300;
    RooRealVar bg_land_pol_add("bg_land_pol_add", "bg_land_pol_add", 1, 0, 1);
    RooAddPdf* bg_landau_pol = new RooAddPdf(Form("bg_landau_pol_%d_%d",fit_pol_land_0,fit_pol_land_1), "bg_landau_pol", RooArgList(landau, bg_pol3), bg_land_pol_add); 

    RooPlot *data_plot7=x->frame();
    x->setRange("small",fit_pol_land_0, fit_pol_land_1);
    //bg_pol3.setNormRange("small");
    //landau.setNormRange("small");
    //bg_landau_pol->setNormRange("small");
    RooFitResult *r_bg_landau_pol=bg_landau_pol->fitTo(pred, RooFit::Range("small"), RooFit::Save());
    pred.plotOn(data_plot7, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    bg_landau_pol->plotOn(data_plot7, RooFit::LineColor(kBlue+1));
    //bg_landau_pol->plotOn(data_plot7, RooFit::VisualizeError(*r_bg_landau_pol, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    double fitChi2_land_pol=data_plot7->chiSquare();
    //new TCanvas;
    //data_plot7->Draw();


    TPaveText *pave_4 = new TPaveText(0.90,0.6,0.67,0.8,"NDC");
    pave_4->SetBorderSize(0);
    pave_4->SetTextSize(0.03);
    pave_4->SetLineColor(1);
    pave_4->SetLineStyle(1);
    pave_4->SetLineWidth(2);
    pave_4->SetFillColor(0);
    pave_4->SetFillStyle(0);
    sprintf(value,"land0 = %2.1f",ml.getVal());
    pave_4->AddText(value);
    sprintf(value,"land1 = %2.1f",sl.getVal());
    pave_4->AddText(value);
    sprintf(value,"p0 = %2.1f",bg_pol3_0->getVal());
    pave_4->AddText(value);
    sprintf(value,"p1 = %2.1f",bg_pol3_1->getVal());
    pave_4->AddText(value);
    sprintf(value,"p2= %2.5f",bg_pol3_2->getVal());
    pave_4->AddText(value);
    sprintf(value,"p3 = %2.7f",bg_pol3_3->getVal());
    pave_4->AddText(value);
    sprintf(value,"range [%d,%d]",fit_pol_land_0,fit_pol_land_1);
    pave_4->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_land_pol);
    pave_4->AddText(value);
    //pave_4->Draw();


   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////

    int range_lo = 252; //285; //252;
    int range_hi = 324; //324 //550; //354; //456;
    string type;

    RooRealVar *x_test = new RooRealVar("x", "m_{X} (GeV)", range_lo, range_hi);
    RooDataHist pred_test("pred_test", "Data", RooArgList(*x_test), h_mX_SR);

    RooRealVar par_gaus_bern_0("par_gaus_bern_0", "par_gaus_bern_0", 0.);
    par_gaus_bern_0.setConstant(1);
    RooRealVar par_gaus_bern_1("par_gaus_bern_1", "par_gaus_bern_1", 10, 1. , 100.);
    RooRealVar par_gaus_bern_2("par_gaus_bern_2", "par_gaus_bern_2", 260, 160., 600. );
    RooRealVar *par_gaus_bern_3, *par_gaus_bern_4, *par_gaus_bern_5, *par_gaus_bern_6, *par_gaus_bern_7, *bpar_gaus_bern_8;
    par_gaus_bern_3=new RooRealVar("par_gaus_bern_3", "par_gaus_bern_3", 5.);
    par_gaus_bern_3->setConstant(1);
    par_gaus_bern_4=new RooRealVar("par_gaus_bern_4", "par_gaus_bern_4", 3, -10., 10.);
    par_gaus_bern_5=new RooRealVar("par_gaus_bern_5", "par_gaus_bern_5", 1, -10., 10.);
    par_gaus_bern_6=new RooRealVar("par_gaus_bern_6", "par_gaus_bern_6", -10., 10.);
    par_gaus_bern_7=new RooRealVar("par_gaus_bern_7", "par_gaus_bern_7", -10., 10.);
    par_gaus_bern_8=new RooRealVar("par_gaus_bern_8", "par_gaus_bern_8", -10., 5.);


    RooGaussStepBernstein f_gaus_bern("f_gaus_bern","f_gaus_bern",*x_test, par_gaus_bern_0, par_gaus_bern_1, par_gaus_bern_2, RooArgList(*par_gaus_bern_3, *par_gaus_bern_4, *par_gaus_bern_5, *par_gaus_bern_6));
    RooFitResult *r_gaus_bern=f_gaus_bern.fitTo(pred_test, RooFit::Range(range_lo, range_hi), RooFit::Save());


    RooPlot *frame_gaus_bern=x_test->frame();
    pred_test.plotOn(frame_gaus_bern, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_gaus_bern.plotOn(frame_gaus_bern, RooFit::VisualizeError(*r_gaus_bern, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_gaus_bern.plotOn(frame_gaus_bern, RooFit::LineColor(kBlue+1));
    double fitChi2_gaus_bern=frame_gaus_bern->chiSquare();
    TCanvas *c_gaus_bern=new TCanvas("c_gaus_bern", "c_gaus_bern", 800, 800);
    frame_gaus_bern->Draw();



    TPaveText *pave_gaus_bern = new TPaveText(0.90,0.7,0.67,0.9,"NDC");
    pave_gaus_bern->SetBorderSize(0);
    pave_gaus_bern->SetTextSize(0.03);
    pave_gaus_bern->SetLineColor(1);
    pave_gaus_bern->SetLineStyle(1);
    pave_gaus_bern->SetLineWidth(2);
    pave_gaus_bern->SetFillColor(0);
    pave_gaus_bern->SetFillStyle(0);
    pave_gaus_bern->AddText("Gaus_Bern");
    sprintf(value,"range [%d,%d]",range_lo,range_hi);
    pave_gaus_bern->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_gaus_bern);
    pave_gaus_bern->AddText(value);
    pave_gaus_bern->Draw();
    type= "SB_gaus_bern_"+to_string(range_lo)+"_"+to_string(range_hi);
    c_gaus_bern->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());


    RooRealVar par_crystal_0("par_crystal_0", "par_crystal_0", crystalball_switch_lo, crystalball_switch_hi);
    RooRealVar par_crystal_1("par_crystal_1", "par_crystal_1", crystalball_exp_lo, crystalball_exp_hi);
    RooRealVar par_crystal_2("par_crystal_2", "par_crystal_2", crystalball_mean_lo, crystalball_mean_hi);
    RooRealVar par_crystal_3("par_crystal_3", "par_crystal_3", crystalball_width_lo, crystalball_width_hi);
    RevCrystalBall f_crystal("f_crystal","f_crystal", *x_test, par_crystal_0, par_crystal_1, par_crystal_2, par_crystal_3);
    RooFitResult *r_crystal=f_crystal.fitTo(pred_test, RooFit::Range(range_lo, range_hi), RooFit::Save());

    RooPlot *frame_crystal=x_test->frame();
    pred_test.plotOn(frame_crystal, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_crystal.plotOn(frame_crystal, RooFit::VisualizeError(*r_crystal, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_crystal.plotOn(frame_crystal, RooFit::LineColor(kBlue+1));
    double fitChi2_crystal=frame_crystal->chiSquare();
    TCanvas *c_crystal=new TCanvas("c_crystal", "c_crystal", 800, 800);
    frame_crystal->Draw();

    TPaveText *pave_crystal = new TPaveText(0.90,0.7,0.67,0.9,"NDC");
    pave_crystal->SetBorderSize(0);
    pave_crystal->SetTextSize(0.03);
    pave_crystal->SetLineColor(1);
    pave_crystal->SetLineStyle(1);
    pave_crystal->SetLineWidth(2);
    pave_crystal->SetFillColor(0);
    pave_crystal->SetFillStyle(0);
    pave_crystal->AddText("RevCrystal");
    sprintf(value,"par_crystal_0 = %2.2f +- %2.2f",par_crystal_0.getVal(),par_crystal_0.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_1 = %2.2f +- %2.2f",par_crystal_1.getVal(),par_crystal_1.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_2 = %2.2f +- %2.2f",par_crystal_2.getVal(),par_crystal_2.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_3 = %2.2f +- %2.2f",par_crystal_3.getVal(),par_crystal_3.getError());
    pave_crystal->AddText(value);
    sprintf(value,"range [%d,%d]",range_lo,range_hi);
    pave_crystal->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_crystal);
    pave_crystal->AddText(value);
    pave_crystal->Draw();
    type= "SB_crystal_"+to_string(range_lo)+"_"+to_string(range_hi);
    c_crystal->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());


    RooRealVar par_gaus_exp_0("par_gaus_exp_0", "par_gaus_exp_0", 260, 300);
    RooRealVar par_gaus_exp_1("par_gaus_exp_1", "par_gaus_exp_1", 9, 40);
    RooRealVar par_gaus_exp_2("par_gaus_exp_2", "par_gaus_exp_2", 0.05, 3.1);
    GaussExp f_gaus_exp("f_gaus_exp", "Background Prediction PDF", *x_test, par_gaus_exp_0, par_gaus_exp_1, par_gaus_exp_2);
    RooFitResult *r_gaus_exp=f_gaus_exp.fitTo(pred_test, RooFit::Range(range_lo, range_hi), RooFit::Save());

    RooPlot *frame_gaus_exp=x_test->frame();
    pred_test.plotOn(frame_gaus_exp, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_gaus_exp.plotOn(frame_gaus_exp, RooFit::VisualizeError(*r_gaus_exp, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_gaus_exp.plotOn(frame_gaus_exp, RooFit::LineColor(kBlue+1));
    double fitChi2_gaus_exp=frame_gaus_exp->chiSquare();
    TCanvas *c_gaus_exp=new TCanvas("c_gaus_exp", "c_gaus_exp", 800, 800);
    frame_gaus_exp->Draw();

    TPaveText *pave_gaus_exp = new TPaveText(0.7,0.7,0.9,0.9,"NDC");
    pave_gaus_exp->SetBorderSize(0);
    pave_gaus_exp->SetTextSize(0.03);
    pave_gaus_exp->SetLineColor(1);
    pave_gaus_exp->SetLineStyle(1);
    pave_gaus_exp->SetLineWidth(2);
    pave_gaus_exp->SetFillColor(0);
    pave_gaus_exp->SetFillStyle(0);
    pave_gaus_exp->AddText("Gaus_Exp");
    sprintf(value,"par_gaus_exp_0 = %2.2f +- %2.2f",par_gaus_exp_0.getVal(),par_gaus_exp_0.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"par_gaus_exp_1 = %2.2f +- %2.2f",par_gaus_exp_1.getVal(),par_gaus_exp_1.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"par_gaus_exp_2 = %2.2f +- %2.2f",par_gaus_exp_2.getVal(),par_gaus_exp_2.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"range [%d,%d]",range_lo,range_hi);
    pave_gaus_exp->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_gaus_exp);
    pave_gaus_exp->AddText(value);
    pave_gaus_exp->Draw();
    type= "SB_gaus_exp_"+to_string(range_lo)+"_"+to_string(range_hi);
    c_gaus_exp->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());



    RooRealVar par_novo0("par_novo0", "par_novo0", 275, 10, 285);
    RooRealVar par_novo1("par_novo1", "par_novo1", 10, 10, 100);
    RooRealVar par_novo2("par_novo2", "par_novo2", -1e+01, -100, 1);
    RooNovosibirsk f_novo("f_novo", "Background Prediction PDF", *x_test, par_novo0, par_novo1, par_novo2);
    RooFitResult *r_novo=f_novo.fitTo(pred_test, RooFit::Range(range_lo, range_hi), RooFit::Save());

    RooPlot *frame_novo=x_test->frame();
    pred_test.plotOn(frame_novo, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_novo.plotOn(frame_novo, RooFit::VisualizeError(*r_novo, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_novo.plotOn(frame_novo, RooFit::LineColor(kBlue+1));
    double fitChi2_Novo=frame_novo->chiSquare();
    TCanvas *c_novo=new TCanvas("c_novo", "c_novo", 800, 800);
    frame_novo->Draw();

    TPaveText *pave_novo = new TPaveText(0.90,0.7,0.67,0.9,"NDC");
    pave_novo->SetBorderSize(0);
    pave_novo->SetTextSize(0.03);
    pave_novo->SetLineColor(1);
    pave_novo->SetLineStyle(1);
    pave_novo->SetLineWidth(2);
    pave_novo->SetFillColor(0);
    pave_novo->SetFillStyle(0);
    pave_novo->AddText("Novo");
    sprintf(value,"range [%d,%d]",range_lo,range_hi);
    pave_novo->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_Novo);
    pave_novo->AddText(value);
    pave_novo->Draw();
    type= "SB_novo_"+to_string(range_lo)+"_"+to_string(range_hi);
    c_novo->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());




      TH1* hh_pdf = f_crystal.createHistogram("px", *x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      //TH1* hh_pdf = f_novo.createHistogram("px", *x_test, RooFit::Binning(1000,range_lo,range_hi)) ;

      //TH1* hh_pdf_11 = f_gaus_bern.createHistogram("px1", *x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      TH1* hh_pdf_11 = f_gaus_exp.createHistogram("px1", *x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      //TH1* hh_pdf_11 = f_novo.createHistogram("px1", *x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      TH1* hh_pdf_2 = f_crystal.createHistogram("difference_1",*x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      TH1* hh_pdf_4 = f_crystal.createHistogram("sum",*x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      TH1* hh_pdf_5 = f_crystal.createHistogram("ratio",*x_test, RooFit::Binning(1000,range_lo,range_hi)) ;
      hh_pdf_5->SetLineColor(kRed);
      hh_pdf->SetLineColor(kBlue); 
      hh_pdf_2->Add(hh_pdf_11,-1);

      hh_pdf_4->Add(hh_pdf_11,1);
      hh_pdf_4->Scale(0.5);
      hh_pdf_5->Add(hh_pdf,-1);
      hh_pdf_5->Add(hh_pdf_2,1);
      hh_pdf_5->Divide(hh_pdf_4);
      hh_pdf_5->Scale(100);
new TCanvas; hh_pdf_5->Draw();

   /////////////////////////////////////////////////////////
   //
   //
   //
   //
   //
     
    RooRealVar bg_p0("bg_p0", "bg_p0", 0.);
    bg_p0.setConstant(1);
    RooRealVar bg_p1("bg_p1", "bg_p1",1. , 100.);
    RooRealVar bg_p2("bg_p2", "bg_p2", 160., 600. );
    RooRealVar *bg_p3, *bg_p4, *bg_p5, *bg_p6, *bg_p7, *bg_p8;
    bg_p3=new RooRealVar("bg_p3", "bg_p3", 5.);
    bg_p3->setConstant(1);
    bg_p4=new RooRealVar("bg_p4", "bg_p4", -10., 10.);
    bg_p5=new RooRealVar("bg_p5", "bg_p5", -10., 10.);
    bg_p6=new RooRealVar("bg_p6", "bg_p6", -10., 10.);
    bg_p7=new RooRealVar("bg_p7", "bg_p7", -10., 10.);
    bg_p8=new RooRealVar("bg_p8", "bg_p8", -10., 5.);
    
    
    RooGaussStepBernstein bg("bg","bg",*x, bg_p0, bg_p1, bg_p2, RooArgList(*bg_p3, *bg_p4, *bg_p5, *bg_p6));
    RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
    
    RooRealVar bg_p00("bg_p00", "bg_p00", crystalball_switch_lo, crystalball_switch_hi);
    RooRealVar bg_p11("bg_p11", "bg_p11", crystalball_exp_lo, crystalball_exp_hi);
    RooRealVar bg_p22("bg_p22", "bg_p22", crystalball_mean_lo, crystalball_mean_hi);
    RooRealVar bg_p33("bg_p33", "bg_p33", crystalball_width_lo, crystalball_width_hi);
    RevCrystalBall bg_exp("bg_exp", "Background Prediction PDF", *x, bg_p00, bg_p11, bg_p22, bg_p33);
    
    RooPlot *data_plot2=x->frame();
    pred_2.plotOn(data_plot2);
    RooFitResult *r_bg_exp=bg_exp.fitTo(pred, RooFit::Range(fit_lo, fit_hi), RooFit::Save());
    pred.plotOn(data_plot2);
    pred_2.plotOn(data_plot2);
    
    bg_exp.plotOn(data_plot2, RooFit::LineColor(kBlue+1));
    pred.plotOn(data_plot2, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    
    
    RooPlot *data_plot=x->frame();
    pred_2.plotOn(data_plot);
    pred.plotOn(data_plot);
    bg.plotOn(data_plot, RooFit::VisualizeError(*r_bg, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg.plotOn(data_plot, RooFit::LineColor(kBlack));
    pred.plotOn(data_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    pred_2.plotOn(data_plot);
    
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
    //data_plot->Draw();
    data_plot->GetXaxis()->SetLabelOffset(0.03);
    data_plot->GetYaxis()->SetLabelFont(42);
    data_plot->GetYaxis()->SetTitleFont(42);
    data_plot2->Draw("same");
    //data_plot3->Draw("same");
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
    
    TLegend *leg = new TLegend(0.85625,0.721654,0.6165625,0.8903839,NULL,"brNDC");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(2);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    h_mX_SR->SetMarkerStyle(20);
    if (hist.substr(0,7)=="h_mX_SB"){
        h_mX_SR->SetLineColor(kBlack);
        h_mX_SR->SetMarkerColor(kBlack);
        leg->AddEntry(h_mX_SR, "Data in SB", "ep");
        
    }
    else leg->AddEntry(h_mX_SR, "Data in SR", "ep");
    TH1F * temp = new TH1F("temp", "temp", 100, 0,1); temp->SetLineWidth(2);  temp->SetLineColor(kBlack);
    leg->AddEntry(temp, "GaussBern fit", "l");
    TH1F * temp1 = new TH1F("temp1", "temp1", 100, 0,1); temp1->SetLineWidth(2);
    temp1->SetLineColor(kBlue+1);
    leg->AddEntry(temp1, "CrystalBall fit", "l");
    leg->Draw();
    
    CMS_lumi( p_1, iPeriod, iPos );
    
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
    c_Background->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.png").c_str());
    c_Background->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.pdf").c_str());
    
    
    RooWorkspace *w_background=new RooWorkspace("HbbHbb");
    w_background->import(bg);
    w_background->import(bg_exp);
    
    TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
    h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
    RooDataHist data_obs("data_obs", "Data", RooArgList(*x), h_mX_SR_fakeData);
    RooDataHist data_obs_falling_1("data_obs_falling_1", "Data", RooArgList(*x_4), h_mX_SR_fakeData);
    RooDataHist data_obs_falling_2("data_obs_falling_2", "Data", RooArgList(*x_5), h_mX_SR_fakeData);
    RooDataHist data_obs_falling1_1("data_obs_falling1_1", "Data", RooArgList(*x_6), h_mX_SR_fakeData);
    RooDataHist data_obs_falling1_2("data_obs_falling1_2", "Data", RooArgList(*x_7), h_mX_SR_fakeData);
    RooDataHist data_obs_falling2_1("data_obs_falling2_1", "Data", RooArgList(*x_8), h_mX_SR_fakeData);
    RooDataHist data_obs_falling2_2("data_obs_falling2_2", "Data", RooArgList(*x_9), h_mX_SR_fakeData);
    RooDataHist data_obs_falling3_1("data_obs_falling3_1", "Data", RooArgList(*x_10), h_mX_SR_fakeData);
    RooDataHist data_obs_landau_pol(Form("data_obs_landau_pol_%d_%d",fit_pol_land_0, fit_pol_land_1), "Data", RooArgList(*x), h_mX_SR_fakeData);
    RooDataHist data_obs_gaus_bern(Form("data_obs_gaus_bern_%d_%d",range_lo, range_hi), "Data", RooArgList(*x_test), h_mX_SR_fakeData);
    RooDataHist data_obs_crystal(Form("data_obs_crystal_%d_%d",range_lo, range_hi), "Data", RooArgList(*x_test), h_mX_SR_fakeData);
    RooDataHist data_obs_gaus_exp(Form("data_obs_gaus_exp_%d_%d",range_lo, range_hi), "Data", RooArgList(*x_test), h_mX_SR_fakeData);
    RooDataHist data_obs_novo(Form("data_obs_novo_%d_%d",range_lo, range_hi), "Data", RooArgList(*x_test), h_mX_SR_fakeData);
    
    w_background->import(data_obs);
    w_background->SaveAs((dest_dir+"/"+"w_background_Split.root").c_str());

    RooWorkspace *w_background_falling_1=new RooWorkspace("HbbHbb");
    w_background_falling_1->import(data_obs_falling_1);
    w_background_falling_1->import(bg_falling_1);
    w_background_falling_1->SaveAs((dest_dir+"/"+"w_background_falling_1.root").c_str());

    RooWorkspace *w_background_falling_2=new RooWorkspace("HbbHbb");
    w_background_falling_2->import(data_obs_falling_2);
    w_background_falling_2->import(bg_falling_2);
    w_background_falling_2->SaveAs((dest_dir+"/"+"w_background_falling_2.root").c_str());

    RooWorkspace *w_background_falling1_1=new RooWorkspace("HbbHbb");
    w_background_falling1_1->import(data_obs_falling1_1);
    w_background_falling1_1->import(bg_falling1_1);
    w_background_falling1_1->SaveAs((dest_dir+"/"+"w_background_falling1_1.root").c_str());

    RooWorkspace *w_background_falling1_2=new RooWorkspace("HbbHbb");
    w_background_falling1_2->import(data_obs_falling1_2);
    w_background_falling1_2->import(bg_falling1_2);
    w_background_falling1_2->SaveAs((dest_dir+"/"+"w_background_falling1_2.root").c_str());

    RooWorkspace *w_background_falling3_1=new RooWorkspace("HbbHbb");
    w_background_falling3_1->import(data_obs_falling3_1);
    w_background_falling3_1->import(bg_falling3_4);
    w_background_falling3_1->SaveAs((dest_dir+"/"+Form("w_background_falling3_%d.root",crystal_3)).c_str());

    RooWorkspace *w_background_landau_pol=new RooWorkspace("HbbHbb");
    w_background_landau_pol->import(data_obs_landau_pol);
    w_background_landau_pol->import(*bg_landau_pol);
    w_background_landau_pol->SaveAs((dest_dir+"/"+Form("w_background_landau_pol_%d_%d.root",fit_pol_land_0,fit_pol_land_1)).c_str());


    RooWorkspace *w_background_gaus_bern=new RooWorkspace("HbbHbb");
    w_background_gaus_bern->import(data_obs_gaus_bern);
    w_background_gaus_bern->import(f_gaus_bern);
    w_background_gaus_bern->SaveAs((dest_dir+"/"+Form("w_background_gaus_bern_%d_%d.root",range_lo,range_hi)).c_str());

    RooWorkspace *w_background_crystal=new RooWorkspace("HbbHbb");
    w_background_crystal->import(data_obs_crystal);
    w_background_crystal->import(f_crystal);
    w_background_crystal->SaveAs((dest_dir+"/"+Form("w_background_crystal_%d_%d.root",range_lo,range_hi)).c_str());

    RooWorkspace *w_background_gaus_exp=new RooWorkspace("HbbHbb");
    w_background_gaus_exp->import(data_obs_gaus_exp);
    w_background_gaus_exp->import(f_gaus_exp);
    w_background_gaus_exp->SaveAs((dest_dir+"/"+Form("w_background_gaus_exp_%d_%d.root",range_lo,range_hi)).c_str());


    RooWorkspace *w_background_novo=new RooWorkspace("HbbHbb");
    w_background_novo->import(data_obs_novo);
    w_background_novo->import(f_novo);
    w_background_novo->SaveAs((dest_dir+"/"+Form("w_background_novo_%d_%d.root",range_lo,range_hi)).c_str());


    //w_background->import(data_obs_falling2_1);
    //w_background->import(bg_falling2_1);
    //w_background->import(data_obs_falling2_2);
    //w_background->import(bg_falling2_2);

    
    RooWorkspace *w_data=new RooWorkspace("HbbHbb");
    w_data->import(data_obs);
    w_data->SaveAs((dest_dir+"/"+"w_data_Split.root").c_str());
    
    
    std::cout<<" === RooFit data fit result to be entered in datacard === "<<std::endl;
    std::cout<<" Background number of events = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_lo),h_mX_SR_fakeData->FindBin(fit_hi))<<std::endl;
    std::cout<<" Background number of falling_1 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-pol_1),h_mX_SR_fakeData->FindBin(fit_mass+pol_1))<<std::endl;
    std::cout<<" Background number of falling_2 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-pol_2),h_mX_SR_fakeData->FindBin(fit_mass+pol_2))<<std::endl;
    std::cout<<" Background number of falling1_1 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-polexp_1),h_mX_SR_fakeData->FindBin(fit_mass+polexp_1))<<std::endl;
    std::cout<<" Background number of falling1_2 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-polexp_2),h_mX_SR_fakeData->FindBin(fit_mass+polexp_2))<<std::endl;
    std::cout<<" Background number of falling2_1 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-powerlaw_1),h_mX_SR_fakeData->FindBin(fit_mass+powerlaw_1))<<std::endl;
    std::cout<<" Background number of falling2_2 = "<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-powerlaw_2),h_mX_SR_fakeData->FindBin(fit_mass+powerlaw_2))<<std::endl;
    std::cout<<Form(" Background number of falling3_%d = ", crystal_3)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_mass-crystal_3),h_mX_SR_fakeData->FindBin(fit_mass+crystal_3))<<std::endl;
    std::cout<<Form(" Background number of landau_pol_%d_%d = ", fit_pol_land_0, fit_pol_land_1)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(fit_pol_land_0),h_mX_SR_fakeData->FindBin(fit_pol_land_1))<<std::endl;



    std::cout<<Form(" Background number of crystal_%d_%d = ", range_lo, range_hi)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo),h_mX_SR_fakeData->FindBin(range_hi))<<std::endl;
    std::cout<<Form(" Background number of gaus_bern_%d_%d = ", range_lo, range_hi)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo),h_mX_SR_fakeData->FindBin(range_hi))<<std::endl;
    std::cout<<Form(" Background number of gaus_exp_%d_%d = ", range_lo, range_hi)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo),h_mX_SR_fakeData->FindBin(range_hi))<<std::endl;
    std::cout<<Form(" Background number of novo_%d_%d = ", range_lo, range_hi)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo),h_mX_SR_fakeData->FindBin(range_hi))<<std::endl;


    std::cout<<"bg_p0   param   "<<bg_p0.getVal()<<" "<<bg_p0.getError()<<std::endl;
    std::cout<<"bg_p1   param   "<<bg_p1.getVal()<<" "<<bg_p1.getError()<<std::endl;
    std::cout<<"bg_p2   param   "<<bg_p2.getVal()<<" "<<bg_p2.getError()<<std::endl;
    std::cout<<"bg_p3   param   "<<bg_p3->getVal()<<" "<<bg_p3->getError()<<std::endl;
    std::cout<<"bg_p4   param   "<<bg_p4->getVal()<<" "<<bg_p4->getError()<<std::endl;
    std::cout<<"bg_p5   param   "<<bg_p5->getVal()<<" "<<bg_p5->getError()<<std::endl;
    std::cout<<"bg_p6   param   "<<bg_p6->getVal()<<" "<<bg_p6->getError()<<std::endl;
    
    std::cout<<" COUNTING = "<<h_mX_SR_fakeData->GetSumOfWeights()<<std::endl;
    std::cout<<" COUNTING = "<<h_mX_SR_fakeData->Integral(plot_lo,456)<<std::endl;
    std::cout<<" COUNTING = "<<data_obs.sum(kFALSE) << " " << data_obs.sum(kTRUE) << " " << data_obs.numEntries()<<std::endl;
    std::cout<<" x " <<  " " << plot_lo << " " << plot_hi <<std::endl;
    x->Print();
    r_bg_sum_gauss->Print(); 
    r_bg_novo->Print(); 
    r_bg_novo1->Print(); 
    r_bg_landau_pol->Print(); 
    r_bg_exp->Print();
    r_gaus_bern->Print();
    

}





