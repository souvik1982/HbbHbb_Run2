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

void BackgroundPrediction_AntiTag_Split_malara(int range_lo_1, int range_hi_1, double rebin,
                                                 int range_lo_2, int range_hi_2,
                                                 double crystalball_mean_lo, double crystalball_mean_hi,
                                                 double crystalball_width_lo, double crystalball_width_hi,
                                                 double crystalball_exp_lo, double crystalball_exp_hi,
                                                 double crystalball_switch_lo, double crystalball_switch_hi,
                                                 std::string hist="h_mX_SB_kinFit",
                                                 std::string log="lin",
                                                 std::string filename="Histograms_BTagall.root",
                                                 std::string dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/fit")
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
    TFile *f_scale=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_tmp=(TH1F*)f_scale->Get("h_mX_SR_kinFit");
    double nEventsSR= h_tmp->Integral();
    
    RooRealVar *x = new RooRealVar("x", "m_{X} (GeV)", 252, 455);
    RooDataHist pred("pred", "Data", RooArgList(*x), h_mX_SR);
    
   
    //int range_lo_1 = 252;
    //int range_hi_1 = 324;
    //int range_lo_2 = 285;
    //int range_hi_2 = 550;
    char value[1000];
    
    RooRealVar *x_1 = new RooRealVar("x", "m_{X} (GeV)", range_lo_1, range_hi_1);
    RooRealVar *x_2 = new RooRealVar("x", "m_{X} (GeV)", range_lo_2, range_hi_2);
    RooDataHist pred_1("pred_1", "Data", RooArgList(*x_1), h_mX_SR);
    RooDataHist pred_2("pred_2", "Data", RooArgList(*x_2), h_mX_SR);
    
    string type;

    RooRealVar par_crystal_0("par_crystal_0", "par_crystal_0", crystalball_switch_lo, crystalball_switch_hi);
    RooRealVar par_crystal_1("par_crystal_1", "par_crystal_1", crystalball_exp_lo, crystalball_exp_hi);
    RooRealVar par_crystal_2("par_crystal_2", "par_crystal_2", crystalball_mean_lo, crystalball_mean_hi);
    RooRealVar par_crystal_3("par_crystal_3", "par_crystal_3", crystalball_width_lo, crystalball_width_hi);
    RevCrystalBall f_crystal("f_crystal","f_crystal", *x_1, par_crystal_0, par_crystal_1, par_crystal_2, par_crystal_3);
    RooFitResult *r_crystal=f_crystal.fitTo(pred_1, RooFit::Range(range_lo_1, range_hi_1), RooFit::Save());
    
    RooPlot *frame_crystal=x_1->frame();
    pred_1.plotOn(frame_crystal, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_crystal.plotOn(frame_crystal, RooFit::VisualizeError(*r_crystal, 0.5), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_crystal.plotOn(frame_crystal, RooFit::LineColor(kBlue+1));
    double fitChi2_crystal=frame_crystal->chiSquare();
    RooAbsReal* chi2_crystal = f_crystal.createChi2(pred_1);
    double pvalue_crystal=TMath::Prob(chi2_crystal->getVal(),int((range_hi_1-range_lo_1)/rebin)-3);
    
    TCanvas *c_crystal=new TCanvas("c_crystal", "c_crystal", 800, 800);
    frame_crystal->Draw();
    
    TPaveText *pave_crystal = new TPaveText(0.6,0.7,0.9,0.9,"NDC");
    pave_crystal->SetBorderSize(0);
    pave_crystal->SetTextSize(0.03);
    pave_crystal->SetLineColor(1);
    pave_crystal->SetLineStyle(1);
    pave_crystal->SetLineWidth(2);
    pave_crystal->SetFillColor(0);
    pave_crystal->SetFillStyle(0);
    pave_crystal->AddText("RevCrystal");
    sprintf(value,"par_crystal_0 = %2.3f +- %2.3f",par_crystal_0.getVal(),par_crystal_0.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_1 = %2.3f +- %2.3f",par_crystal_1.getVal(),par_crystal_1.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_2 = %2.3f +- %2.3f",par_crystal_2.getVal(),par_crystal_2.getError());
    pave_crystal->AddText(value);
    sprintf(value,"par_crystal_3 = %2.3f +- %2.3f",par_crystal_3.getVal(),par_crystal_3.getError());
    sprintf(value,"range [%d,%d]",range_lo_1,range_hi_1);
    pave_crystal->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_crystal);
    pave_crystal->AddText(value);
    pave_crystal->Draw();
    type= "SB_crystal_"+to_string(range_lo_1)+"_"+to_string(range_hi_1);
    c_crystal->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());
    
    RooRealVar par_gaus_exp_0("par_gaus_exp_0", "par_gaus_exp_0", 260, 300);
    RooRealVar par_gaus_exp_1("par_gaus_exp_1", "par_gaus_exp_1", 9, 40);
    RooRealVar par_gaus_exp_2("par_gaus_exp_2", "par_gaus_exp_2", 0.05, 3.1);
    GaussExp f_gaus_exp("f_gaus_exp", "Background Prediction PDF", *x_1, par_gaus_exp_0, par_gaus_exp_1, par_gaus_exp_2);
    RooFitResult *r_gaus_exp=f_gaus_exp.fitTo(pred_1, RooFit::Range(range_lo_1, range_hi_1), RooFit::Save());
    
    RooPlot *frame_gaus_exp=x_1->frame();
    pred_1.plotOn(frame_gaus_exp, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_gaus_exp.plotOn(frame_gaus_exp, RooFit::VisualizeError(*r_gaus_exp, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_gaus_exp.plotOn(frame_gaus_exp, RooFit::LineColor(kBlue+1));
    double fitChi2_gaus_exp=frame_gaus_exp->chiSquare();
    RooAbsReal* chi2_gaus_exp = f_gaus_exp.createChi2(pred_1);
    double pvalue_gaus_exp=TMath::Prob(chi2_gaus_exp->getVal(),int((range_hi_1-range_lo_1)/rebin)-3);
    TCanvas *c_gaus_exp=new TCanvas("c_gaus_exp", "c_gaus_exp", 800, 800);
    frame_gaus_exp->Draw();
    
    TPaveText *pave_gaus_exp = new TPaveText(0.6,0.7,0.9,0.9,"NDC");
    pave_gaus_exp->SetBorderSize(0);
    pave_gaus_exp->SetTextSize(0.03);
    pave_gaus_exp->SetLineColor(1);
    pave_gaus_exp->SetLineStyle(1);
    pave_gaus_exp->SetLineWidth(2);
    pave_gaus_exp->SetFillColor(0);
    pave_gaus_exp->SetFillStyle(0);
    pave_gaus_exp->AddText("Gaus_Exp");
    sprintf(value,"par_gaus_exp_0= %2.3f +- %2.3f",par_gaus_exp_0.getVal(),par_gaus_exp_0.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"par_gaus_exp_1= %2.3f +- %2.3f",par_gaus_exp_1.getVal(),par_gaus_exp_1.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"par_gaus_exp_2= %2.3f +- %2.3f",par_gaus_exp_2.getVal(),par_gaus_exp_2.getError());
    pave_gaus_exp->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_gaus_exp);
    pave_gaus_exp->AddText(value);
    pave_gaus_exp->Draw();
    type= "SB_gaus_exp_"+to_string(range_lo_1)+"_"+to_string(range_hi_1);
    c_gaus_exp->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());
    
    
    
    //RooRealVar par_novo_0("par_novo_0", "par_novo_0", 275, 10, 285);
    //RooRealVar par_novo_1("par_novo_1", "par_novo_1", 10, 10, 100);
    //RooRealVar par_novo_2("par_novo_2", "par_novo_2", -1e+01, -100, 1);
    RooRealVar par_novo_0("par_novo_0", "par_novo_0", 250, 301);
    RooRealVar par_novo_1("par_novo_1", "par_novo_1", 0, 54);
    RooRealVar par_novo_2("par_novo_2", "par_novo_2", -100, 100);
    RooNovosibirsk f_novo("f_novo", "Background Prediction PDF", *x_2, par_novo_0, par_novo_1, par_novo_2);
    RooFitResult *r_novo=f_novo.fitTo(pred_2, RooFit::Range(range_lo_2, range_hi_2), RooFit::Save());
    
    RooPlot *frame_novo=x_2->frame();
    pred_2.plotOn(frame_novo, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_novo.plotOn(frame_novo, RooFit::VisualizeError(*r_novo, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_novo.plotOn(frame_novo, RooFit::LineColor(kBlue+1));
    double fitChi2_Novo=frame_novo->chiSquare();
    RooAbsReal* chi2_novo = f_novo.createChi2(pred_2);
    double pvalue_novo=TMath::Prob(chi2_novo->getVal(),int((range_hi_2-range_lo_2)/rebin)-3);
    
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
    sprintf(value,"par_novo_0= %2.3f +- %2.3f",par_novo_0.getVal(),par_novo_0.getError());
    pave_novo->AddText(value);
    sprintf(value,"par_novo_1= %2.3f +- %2.3f",par_novo_1.getVal(),par_novo_1.getError());
    pave_novo->AddText(value);
    sprintf(value,"par_novo_2= %2.3f +- %2.3f",par_novo_2.getVal(),par_novo_2.getError());
    pave_novo->AddText(value);
    sprintf(value,"range [%d,%d]",range_lo_2,range_hi_2);
    pave_novo->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_Novo);
    pave_novo->AddText(value);
    pave_novo->Draw();
    type= "SB_novo_"+to_string(range_lo_2)+"_"+to_string(range_hi_2);
    c_novo->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());
    
    
    RooRealVar par_crystal_1_0("par_crystal_1_0", "par_crystal_1_0", crystalball_switch_lo, crystalball_switch_hi);
    RooRealVar par_crystal_1_1("par_crystal_1_1", "par_crystal_1_1", crystalball_exp_lo, crystalball_exp_hi);
    RooRealVar par_crystal_1_2("par_crystal_1_2", "par_crystal_1_2", crystalball_mean_lo, crystalball_mean_hi);
    RooRealVar par_crystal_1_3("par_crystal_1_3", "par_crystal_1_3", crystalball_width_lo, crystalball_width_hi);
    RevCrystalBall f_crystal_1("f_crystal_1","f_crystal_1", *x_2, par_crystal_1_0, par_crystal_1_1, par_crystal_1_2, par_crystal_1_3);
    RooFitResult *r_crystal_1=f_crystal_1.fitTo(pred_2, RooFit::Range(range_lo_2, range_hi_2), RooFit::Save());
    
    RooPlot *frame_crystal_1=x_2->frame();
    pred_2.plotOn(frame_crystal_1, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_crystal_1.plotOn(frame_crystal_1, RooFit::VisualizeError(*r_crystal_1, 0.5), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_crystal_1.plotOn(frame_crystal_1, RooFit::LineColor(kBlue+1));
    double fitChi2_crystal_1=frame_crystal_1->chiSquare();
    RooAbsReal* chi2_crystal_1 = f_crystal_1.createChi2(pred_2);
    double pvalue_crystal_1=TMath::Prob(chi2_crystal_1->getVal(),int((range_hi_2-range_lo_2)/rebin)-3);
    
    TCanvas *c_crystal_1=new TCanvas("c_crystal_1", "c_crystal_1", 800, 800);
    frame_crystal_1->Draw();
    
    TPaveText *pave_crystal_1 = new TPaveText(0.90,0.7,0.67,0.9,"NDC");
    pave_crystal_1->SetBorderSize(0);
    pave_crystal_1->SetTextSize(0.03);
    pave_crystal_1->SetLineColor(1);
    pave_crystal_1->SetLineStyle(1);
    pave_crystal_1->SetLineWidth(2);
    pave_crystal_1->SetFillColor(0);
    pave_crystal_1->SetFillStyle(0);
    pave_crystal_1->AddText("Revcrystal_1");
    sprintf(value,"par_crystal_1_0= %2.3f +- %2.3f",par_crystal_1_0.getVal(),par_crystal_1_0.getError());
    pave_crystal_1->AddText(value);
    sprintf(value,"par_crystal_1_1= %2.3f +- %2.3f",par_crystal_1_1.getVal(),par_crystal_1_1.getError());
    pave_crystal_1->AddText(value);
    sprintf(value,"par_crystal_1_2= %2.3f +- %2.3f",par_crystal_1_2.getVal(),par_crystal_1_2.getError());
    pave_crystal_1->AddText(value);
    sprintf(value,"par_crystal_1_3= %2.3f +- %2.3f",par_crystal_1_3.getVal(),par_crystal_1_3.getError());
    pave_crystal_1->AddText(value);
    sprintf(value,"range [%d,%d]",range_lo_2,range_hi_2);
    pave_crystal_1->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_crystal_1);
    pave_crystal_1->AddText(value);
    pave_crystal_1->Draw();
    type= "SB_crystal_1_"+to_string(range_lo_2)+"_"+to_string(range_hi_2);
    c_crystal_1->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());
    


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


    RooGaussStepBernstein f_gaus_bern("f_gaus_bern","f_gaus_bern",*x_2, par_gaus_bern_0, par_gaus_bern_1, par_gaus_bern_2, RooArgList(*par_gaus_bern_3, *par_gaus_bern_4, *par_gaus_bern_5, *par_gaus_bern_6));
    RooFitResult *r_gaus_bern=f_gaus_bern.fitTo(pred_2, RooFit::Range(range_lo_2, range_hi_2), RooFit::Save());

    RooPlot *frame_gaus_bern=x_2->frame();
    pred_2.plotOn(frame_gaus_bern, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_gaus_bern.plotOn(frame_gaus_bern, RooFit::VisualizeError(*r_gaus_bern, 0.5), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    f_gaus_bern.plotOn(frame_gaus_bern, RooFit::LineColor(kBlue+1));
    double fitChi2_gaus_bern=frame_gaus_bern->chiSquare();
    RooAbsReal* chi2_gaus_bern = f_gaus_bern.createChi2(pred_2);
    double pvalue_gaus_bern=TMath::Prob(chi2_gaus_bern->getVal(),int((range_hi_2-range_lo_2)/rebin)-3);

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
    pave_gaus_bern->AddText("Revgaus_bern");
    sprintf(value,"par_gaus_bern_0= %2.3f +- %2.3f",par_gaus_bern_0.getVal(),par_gaus_bern_0.getError());
    pave_gaus_bern->AddText(value);
    sprintf(value,"par_gaus_bern_1= %2.3f +- %2.3f",par_gaus_bern_1.getVal(),par_gaus_bern_1.getError());
    pave_gaus_bern->AddText(value);
    sprintf(value,"par_gaus_bern_2= %2.3f +- %2.3f",par_gaus_bern_2.getVal(),par_gaus_bern_2.getError());
    pave_gaus_bern->AddText(value);
    sprintf(value,"par_gaus_bern_3= %2.3f +- %2.3f",par_gaus_bern_3->getVal(),par_gaus_bern_3->getError());
    pave_gaus_bern->AddText(value);
    sprintf(value,"range [%d,%d]",range_lo_2,range_hi_2);
    pave_gaus_bern->AddText(value);
    sprintf(value,"chi^2 %2.1f",fitChi2_gaus_bern);
    pave_gaus_bern->AddText(value);
    pave_gaus_bern->Draw();
    type= "SB_gaus_bern_"+to_string(range_lo_2)+"_"+to_string(range_hi_2);
    c_gaus_bern->SaveAs((dest_dir+"/"+"BackgroundFit_"+type+".png").c_str());
 
    
    
    TH1* hh_pdf = f_gaus_exp.createHistogram("hh", *x_1, RooFit::Binning(1000,range_hi_1, range_hi_1)) ;
    TH1* hh_pdf_11 = f_crystal.createHistogram("hh1", *x_1, RooFit::Binning(1000,range_hi_1, range_hi_1)) ;
    TH1* hh_pdf_2 = f_gaus_exp.createHistogram("difference_1", *x_1, RooFit::Binning(1000,range_hi_1, range_hi_1)) ;
    TH1* hh_pdf_4 = f_gaus_exp.createHistogram("sum", *x_1, RooFit::Binning(1000,range_hi_1, range_hi_1)) ;
    TH1* hh_pdf_5 = f_gaus_exp.createHistogram("ratio", *x_1, RooFit::Binning(1000,range_hi_1, range_hi_1)) ;
    hh_pdf_5->SetLineColor(kRed);
    hh_pdf_2->Add(hh_pdf_11,-1);
    hh_pdf_4->Add(hh_pdf_11,1);
    hh_pdf_4->Scale(0.5);
    hh_pdf_5->Add(hh_pdf,-1);
    hh_pdf_5->Add(hh_pdf_2,1);
    hh_pdf_5->Divide(hh_pdf_4);
    //hh_pdf_5->Scale(100);
    new TCanvas; hh_pdf_5->Draw();
 
    
    
    TH1* hh_pdf_1 = f_novo.createHistogram("hh_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    //TH1* hh_pdf_1_1 = f_crystal_1.createHistogram("hh1_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    TH1* hh_pdf_1_1 = f_gaus_bern.createHistogram("hh1_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    TH1* hh_pdf_2_1 = f_novo.createHistogram("difference_1_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    TH1* hh_pdf_4_1 = f_novo.createHistogram("sum_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    TH1* hh_pdf_5_1 = f_novo.createHistogram("ratio_1", *x_2, RooFit::Binning(1000,range_hi_2, range_hi_2)) ;
    hh_pdf_5_1->SetLineColor(kRed);
    hh_pdf_2_1->Add(hh_pdf_1_1,-1);
    hh_pdf_4_1->Add(hh_pdf_1_1,1);
    hh_pdf_4_1->Scale(0.5);
    hh_pdf_5_1->Add(hh_pdf_1,-1);
    hh_pdf_5_1->Add(hh_pdf_2_1,1);
    hh_pdf_5_1->Divide(hh_pdf_4_1);
    //hh_pdf_5_1->Scale(100);
    new TCanvas; hh_pdf_5_1->Draw();
    
    
    
    
    
    
    double xPad = 0.3;
    TCanvas *c_gaus_exp_1=new TCanvas("c_gaus_exp_1", "c_gaus_exp_1", 700*(1.-xPad), 700);
    c_gaus_exp_1->SetFillStyle(4000);
    c_gaus_exp_1->SetFrameFillColor(0);
    
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
    
    
    RooPlot *frame_gaus_exp_1=x_1->frame();
    pred_1.plotOn(frame_gaus_exp_1, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_gaus_exp.plotOn(frame_gaus_exp_1, RooFit::VisualizeError(*r_gaus_exp, 1), RooFit::FillColor(kBlack), RooFit::FillStyle(3004));
    f_crystal.plotOn(frame_gaus_exp_1, RooFit::VisualizeError(*r_crystal, 1), RooFit::FillColor(kRed+1), RooFit::FillStyle(3001));
    f_gaus_exp.plotOn(frame_gaus_exp_1, RooFit::LineColor(kBlack), RooFit::LineWidth(6));
    f_crystal.plotOn(frame_gaus_exp_1, RooFit::LineColor(kRed), RooFit::LineWidth(4), RooFit::LineStyle(kDashed) );
    
    
    if (log=="log") frame_gaus_exp_1->GetYaxis()->SetRangeUser(1e-4, h_mX_SR->GetMaximum()*5.);
    else frame_gaus_exp_1->GetYaxis()->SetRangeUser(0, h_mX_SR->GetMaximum()*1.2);
    frame_gaus_exp_1->GetXaxis()->SetLabelOffset(0.03);
    frame_gaus_exp_1->GetYaxis()->SetLabelFont(42);
    frame_gaus_exp_1->GetYaxis()->SetTitleFont(42);
    frame_gaus_exp_1->GetYaxis()->SetTitleOffset(1.25);
    frame_gaus_exp_1->Draw("same");
    frame_gaus_exp_1->SetTitle(("; m_{X} (GeV); Events / "+itoa(h_mX_SR->GetBinWidth(1))+" GeV").c_str());
    if (log=="log") p_1->SetLogy();
    
    TPaveText *pave = new TPaveText(0.68,0.6,0.8,0.7,"NDC");
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
        sprintf(name,"SB_gaus_exp #chi^{2}/n = %.2f",fitChi2_gaus_exp);
        sprintf(name1,"p-value_gaus_exp = %.2f",pvalue_gaus_exp);
    }
    else sprintf(name,"SR_gaus_exp #chi^{2}/n = %.2f",fitChi2_gaus_exp);
    pave->AddText(name);
    pave->AddText(name1);
    if (hist.substr(0,7)=="h_mX_SB") {
        sprintf(name,"SB_crystal #chi^{2}/n = %.2f",fitChi2_crystal);
        sprintf(name1,"p-value_crystal = %.2f",pvalue_crystal);
    }
    else sprintf(name,"SR_crystal #chi^{2}/n = %.2f",fitChi2_crystal);
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
    leg->AddEntry(temp, "GaussExp fit", "l");
    TH1F * temp1 = new TH1F("temp1", "temp1", 100, 0,1); temp1->SetLineWidth(2);
    temp1->SetLineColor(kRed);
    leg->AddEntry(temp1, "CrystalBall fit", "l");
    leg->Draw();
    
    CMS_lumi( p_1, iPeriod, iPos );
    
    p_2->cd();
    RooHist *hpull, *hpull1;
    hpull = frame_gaus_exp->pullHist();
    hpull->SetLineWidth(2);
    hpull1 = frame_crystal->pullHist();
    hpull1->SetMarkerColor(kRed);
    hpull1->SetLineStyle(kDashed);
    hpull1->SetMarkerSize(0.6);
    hpull1->SetLineColor(kRed);
    RooPlot* frameP = x_1->frame() ;
    
    frameP->SetTitle("; m_{X} (GeV); Pull_gaus_exp");
    frameP->addPlotable(hpull,"P");
    frameP->addPlotable(hpull1,"P same");
    frameP->GetYaxis()->SetTitleSize(0.07);
    frameP->GetYaxis()->SetTitleOffset(0.5);
    frameP->GetXaxis()->SetTitleSize(0.09);
    frameP->GetXaxis()->SetTitleOffset(1.0);
    frameP->GetXaxis()->SetLabelSize(0.07);
    frameP->GetYaxis()->SetLabelSize(0.06);
    frameP->Draw();
    
    
    TLine *line=new TLine(range_lo_1, 0, range_hi_1, 0);
    line->SetLineWidth(2);
    line->Draw();
    
    string tag;
    if (hist.substr(0,7)=="h_mX_SB") tag="SB";
    else tag="SR";
    c_gaus_exp_1->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.png").c_str());
    c_gaus_exp_1->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.pdf").c_str());
 
    
    
    
    
    
    
    
    
    
    

    TCanvas *c_novo_1=new TCanvas("c_novo_1", "c_novo_1", 700*(1.-xPad), 700);
    c_novo_1->SetFillStyle(4000);
    c_novo_1->SetFrameFillColor(0);
    
    TPad *p_3=new TPad("p_3", "p_3", 0, xPad, 1, 1);
    p_3->SetFillStyle(4000);
    p_3->SetFrameFillColor(0);
    p_3->SetBottomMargin(0.02);
    
    TPad* p_4 = new TPad("p_4", "p_4",0,0,1,xPad);
    p_4->SetBottomMargin((1.-xPad)/xPad*0.13);
    p_4->SetTopMargin(0.03);
    p_4->SetFillColor(0);
    p_4->SetBorderMode(0);
    p_4->SetBorderSize(2);
    p_4->SetFrameBorderMode(0);
    p_4->SetFrameBorderMode(0);
    
    p_3->Draw();
    p_4->Draw();
    p_3->cd();
    
    
    RooPlot *frame_novo_1=x_2->frame();
    pred_2.plotOn(frame_novo_1, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    f_novo.plotOn(frame_novo_1, RooFit::VisualizeError(*r_novo, 1), RooFit::FillColor(kBlack), RooFit::FillStyle(3001));
    f_crystal_1.plotOn(frame_novo_1, RooFit::VisualizeError(*r_crystal_1, 1), RooFit::FillColor(kRed+1), RooFit::FillStyle(3004));
    f_novo.plotOn(frame_novo_1, RooFit::LineColor(kBlack), RooFit::LineWidth(6));
    f_crystal_1.plotOn(frame_novo_1, RooFit::LineColor(kRed), RooFit::LineWidth(4), RooFit::LineStyle(kDashed) );
    
    
    if (log=="log") frame_novo_1->GetYaxis()->SetRangeUser(1e-4, h_mX_SR->GetMaximum()*5);
    else frame_novo_1->GetYaxis()->SetRangeUser(0, h_mX_SR->GetMaximum()*1.4);
    frame_novo_1->GetXaxis()->SetLabelOffset(0.03);
    frame_novo_1->GetYaxis()->SetLabelFont(42);
    frame_novo_1->GetYaxis()->SetTitleFont(42);
    frame_novo_1->GetYaxis()->SetTitleOffset(1.25);
    frame_novo_1->Draw("same");
    frame_novo_1->SetTitle(("; m_{X} (GeV); Events / "+itoa(h_mX_SR->GetBinWidth(1))+" GeV").c_str());
    if (log=="log") p_3->SetLogy();
    
    TPaveText *pave_1 = new TPaveText(0.68,0.6,0.8,0.7,"NDC");
    pave_1->SetBorderSize(0);
    pave_1->SetTextSize(0.03);
    pave_1->SetLineColor(1);
    pave_1->SetLineStyle(1);
    pave_1->SetLineWidth(2);
    pave_1->SetFillColor(0);
    pave_1->SetFillStyle(0);
    char name_1[1000];
    char name_11[1000];
    if (hist.substr(0,7)=="h_mX_SB") {
        sprintf(name_1,"SB_novo #chi^{2}/n = %.2f",fitChi2_Novo);
        sprintf(name_11,"p-value_novo = %.2f",pvalue_novo);
    }
    else sprintf(name_1,"SR_novo #chi^{2}/n = %.2f",fitChi2_Novo);
    pave_1->AddText(name_1);
    pave_1->AddText(name_11);
    if (hist.substr(0,7)=="h_mX_SB") {
        sprintf(name_1,"SB_crystal #chi^{2}/n = %.2f",fitChi2_crystal_1);
        sprintf(name_11,"p-value_crystal = %.2f",pvalue_crystal_1);
    }
    else sprintf(name_1,"SR_crystal #chi^{2}/n = %.2f",fitChi2_crystal_1);
    pave_1->AddText(name_1);
    pave_1->AddText(name_11);
    pave_1->Draw();
    
    TLatex * tPrel_1 = new TLatex();
    tPrel_1->SetNDC();
    tPrel_1->SetTextColor(kBlack);
    tPrel_1->SetTextSize(0.04);
    
    TLegend *leg_1 = new TLegend(0.85625,0.721654,0.6165625,0.8903839,NULL,"brNDC");
    leg_1->SetBorderSize(0);
    leg_1->SetTextSize(0.035);
    leg_1->SetLineColor(1);
    leg_1->SetLineStyle(1);
    leg_1->SetLineWidth(2);
    leg_1->SetFillColor(0);
    leg_1->SetFillStyle(0);
    h_mX_SR->SetMarkerStyle(20);
    if (hist.substr(0,7)=="h_mX_SB"){
        h_mX_SR->SetLineColor(kBlack);
        h_mX_SR->SetMarkerColor(kBlack);
        leg_1->AddEntry(h_mX_SR, "Data in SB", "ep");
        
    }
    else leg_1->AddEntry(h_mX_SR, "Data in SR", "ep");
    TH1F* temp_1 = new TH1F("temp_1", "temp_1", 100, 0,1); temp_1->SetLineWidth(2);  temp_1->SetLineColor(kBlack);
    leg_1->AddEntry(temp_1, "Novorsibisk fit", "l");
    TH1F* temp_11 = new TH1F("temp_11", "temp_11", 100, 0,1); temp_11->SetLineWidth(2);
    temp_11->SetLineColor(kRed);
    leg_1->AddEntry(temp_11, "CrystalBall fit", "l");
    leg_1->Draw();
    
    CMS_lumi( p_3, iPeriod, iPos );
    
    p_4->cd();
    RooHist *hpull_1, *hpull_11;
    hpull_1 = frame_novo->pullHist();
    hpull_1->SetLineWidth(2);
    hpull_11 = frame_crystal_1->pullHist();
    hpull_11->SetLineStyle(kDashed);
    hpull_11->SetLineColor(kRed);
    hpull_11->SetMarkerSize(0.6);
    hpull_11->SetMarkerColor(kRed);
    RooPlot* frameP_1 = x_2->frame() ;
    
    frameP_1->SetTitle("; m_{X} (GeV); Pull_Novo");
    frameP_1->addPlotable(hpull_1,"P");
    frameP_1->addPlotable(hpull_11,"P same");
    frameP_1->GetYaxis()->SetTitleSize(0.07);
    frameP_1->GetYaxis()->SetTitleOffset(0.5);
    frameP_1->GetXaxis()->SetTitleSize(0.09);
    frameP_1->GetXaxis()->SetTitleOffset(1.0);
    frameP_1->GetXaxis()->SetLabelSize(0.07);
    frameP_1->GetYaxis()->SetLabelSize(0.06);
    frameP_1->Draw();
    
    
    TLine *line_1=new TLine(range_lo_2, 0, range_hi_2, 0);
    line_1->SetLineWidth(2);
    line_1->Draw();
    
    c_novo_1->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.png").c_str());
    c_novo_1->SaveAs((dest_dir+"/"+"BackgroundFit_"+tag+"_Split.pdf").c_str());
    
    
    
    
    
    
    
    
    
    TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
    h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
    RooDataHist data_obs("data_obs", "Data", RooArgList(*x), h_mX_SR_fakeData);
    
    RooDataHist data_obs_crystal(Form("data_obs_crystal_%d_%d",range_lo_1, range_hi_1), "Data", RooArgList(*x_1), h_mX_SR_fakeData);
    RooDataHist data_obs_gaus_exp(Form("data_obs_gaus_exp_%d_%d",range_lo_1, range_hi_1), "Data", RooArgList(*x_1), h_mX_SR_fakeData);
    RooDataHist data_obs_novo(Form("data_obs_novo_%d_%d",range_lo_2, range_hi_2), "Data", RooArgList(*x_2), h_mX_SR_fakeData);
    RooDataHist data_obs_crystal_1(Form("data_obs_crystal_1_%d_%d",range_lo_2, range_hi_2), "Data", RooArgList(*x_2), h_mX_SR_fakeData);
    RooDataHist data_obs_gaus_bern(Form("data_obs_gaus_bern_%d_%d",range_lo_2, range_hi_2), "Data", RooArgList(*x_2), h_mX_SR_fakeData);
    
    
    RooWorkspace *w_background_crystal=new RooWorkspace("HbbHbb");
    w_background_crystal->import(data_obs_crystal);
    w_background_crystal->import(f_crystal);
    w_background_crystal->SaveAs((dest_dir+"/"+Form("w_background_crystal_%d_%d.root",range_lo_1,range_hi_1)).c_str());
    
    RooWorkspace *w_background_gaus_exp=new RooWorkspace("HbbHbb");
    w_background_gaus_exp->import(data_obs_gaus_exp);
    w_background_gaus_exp->import(f_gaus_exp);
    w_background_gaus_exp->SaveAs((dest_dir+"/"+Form("w_background_gaus_exp_%d_%d.root",range_lo_1,range_hi_1)).c_str());
    
    
    RooWorkspace *w_background_novo=new RooWorkspace("HbbHbb");
    w_background_novo->import(data_obs_novo);
    w_background_novo->import(f_novo);
    w_background_novo->SaveAs((dest_dir+"/"+Form("w_background_novo_%d_%d.root",range_lo_2,range_hi_2)).c_str());
    
    RooWorkspace *w_background_crystal_1=new RooWorkspace("HbbHbb");
    w_background_crystal_1->import(data_obs_crystal_1);
    w_background_crystal_1->import(f_crystal_1);
    w_background_crystal_1->SaveAs((dest_dir+"/"+Form("w_background_crystal_1_%d_%d.root",range_lo_2,range_hi_2)).c_str());

    RooWorkspace *w_background_gaus_bern=new RooWorkspace("HbbHbb");
    w_background_gaus_bern->import(data_obs_gaus_bern);
    w_background_gaus_bern->import(f_gaus_bern);
    w_background_gaus_bern->SaveAs((dest_dir+"/"+Form("w_background_gaus_bern_%d_%d.root",range_lo_2,range_hi_2)).c_str());
    
    
    
    std::cout<<" === RooFit data fit result to be entered in datacard === "<<std::endl;
    
    std::cout<<Form(" Background number of crystal_%d_%d = ", range_lo_1, range_hi_1)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo_1),h_mX_SR_fakeData->FindBin(range_hi_1))<<std::endl;
    std::cout<<Form(" Background number of gaus_exp_%d_%d = ", range_lo_1, range_hi_1)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo_1),h_mX_SR_fakeData->FindBin(range_hi_1))<<std::endl;
    std::cout<<Form(" Background number of novo_%d_%d = ", range_lo_2, range_hi_2)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo_2),h_mX_SR_fakeData->FindBin(range_hi_2))<<std::endl;
    std::cout<<Form(" Background number of crystal_1_%d_%d = ", range_lo_2, range_hi_2)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo_2),h_mX_SR_fakeData->FindBin(range_hi_2))<<std::endl;
    std::cout<<Form(" Background number of gaus_bern_%d_%d = ", range_lo_2, range_hi_2)<<h_mX_SR_fakeData->Integral(h_mX_SR_fakeData->FindBin(range_lo_2),h_mX_SR_fakeData->FindBin(range_hi_2))<<std::endl;
    
    
    std::cout<<"par_crystal_0   param   "<<par_crystal_0.getVal()<<" "<<par_crystal_0.getError()<<std::endl;
    std::cout<<"par_crystal_1   param   "<<par_crystal_1.getVal()<<" "<<par_crystal_1.getError()<<std::endl;
    std::cout<<"par_crystal_2   param   "<<par_crystal_2.getVal()<<" "<<par_crystal_2.getError()<<std::endl;
    std::cout<<"par_crystal_3   param   "<<par_crystal_3.getVal()<<" "<<par_crystal_3.getError()<<std::endl;
    
    
    
    std::cout<<"par_crystal_1_0   param   "<<par_crystal_1_0.getVal()<<" "<<par_crystal_1_0.getError()<<std::endl;
    std::cout<<"par_crystal_1_1   param   "<<par_crystal_1_1.getVal()<<" "<<par_crystal_1_1.getError()<<std::endl;
    std::cout<<"par_crystal_1_2   param   "<<par_crystal_1_2.getVal()<<" "<<par_crystal_1_2.getError()<<std::endl;
    std::cout<<"par_crystal_1_3   param   "<<par_crystal_1_3.getVal()<<" "<<par_crystal_1_3.getError()<<std::endl;
    
    std::cout<<"par_gaus_exp_0   param   "<<par_gaus_exp_0.getVal()<<" "<<par_gaus_exp_0.getError()<<std::endl;
    std::cout<<"par_gaus_exp_1   param   "<<par_gaus_exp_1.getVal()<<" "<<par_gaus_exp_1.getError()<<std::endl;
    std::cout<<"par_gaus_exp_2   param   "<<par_gaus_exp_2.getVal()<<" "<<par_gaus_exp_2.getError()<<std::endl;
    
    std::cout<<"par_novo_0   param   "<<par_novo_0.getVal()<<" "<<par_novo_0.getError()<<std::endl;
    std::cout<<"par_novo_1   param   "<<par_novo_1.getVal()<<" "<<par_novo_1.getError()<<std::endl;
    std::cout<<"par_novo_2   param   "<<par_novo_2.getVal()<<" "<<par_novo_2.getError()<<std::endl;


    
    
    
}

