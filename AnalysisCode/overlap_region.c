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

void overlap_region(){
    gROOT->SetStyle("Plain");
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    writeExtraText = true;
    extraText  = "Preliminary";
    lumi_13TeV  = "35.9 fb^{-1}";
    
    TFile *f_data_SB=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SB=(TH1F*)f_data_SB->Get("h_mX_SB_kinFit");
    h_mX_SB->Rebin(3);
    h_mX_SB->Scale(1./h_mX_SB->Integral());

    TFile *f_data_SB_AntiTag=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total_caterina.root");
    TH1F *h_mX_SB_AntiTag=(TH1F*)f_data_SB_AntiTag->Get("h_mX_SB_kinFit");
    h_mX_SB_AntiTag->Rebin(3);
    h_mX_SB_AntiTag->Scale(1./h_mX_SB_AntiTag->Integral());

    TFile *f_data_SB_90=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_90/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SB_90=(TH1F*)f_data_SB_90->Get("h_mX_SB_kinFit");
    h_mX_SB_90->Rebin(3);
    h_mX_SB_90->Scale(1./h_mX_SB_90->Integral());

    TFile *f_data_SB_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SB_150=(TH1F*)f_data_SB_150->Get("h_mX_SB_kinFit");
    h_mX_SB_150->Rebin(3);
    h_mX_SB_150->Scale(1./h_mX_SB_150->Integral());


TFile *f_data_SR=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SR=(TH1F*)f_data_SR->Get("h_mX_SR_kinFit");
    h_mX_SR->Rebin(3);
    h_mX_SR->Scale(1./h_mX_SR->Integral());

    TFile *f_data_SR_AntiTag=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total_caterina.root");
    TH1F *h_mX_SR_AntiTag=(TH1F*)f_data_SR_AntiTag->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag->Rebin(3);
    h_mX_SR_AntiTag->Scale(1./h_mX_SR_AntiTag->Integral());

    TFile *f_data_SR_90=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_90/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SR_90=(TH1F*)f_data_SR_90->Get("h_mX_SR_kinFit");
    h_mX_SR_90->Rebin(3);
    h_mX_SR_90->Scale(1./h_mX_SR_90->Integral());

    TFile *f_data_SR_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SR_150=(TH1F*)f_data_SR_150->Get("h_mX_SR_kinFit");
    h_mX_SR_150->Rebin(3);
    h_mX_SR_150->Scale(1./h_mX_SR_150->Integral());

    
    RooRealVar *x = new RooRealVar("x", "m_{X} (GeV)", 252, 800);
    RooDataHist pred_SB("pred_SB", "Data", RooArgList(*x), h_mX_SB);
    RooDataHist pred_SR("pred_SR", "Data", RooArgList(*x), h_mX_SR);
    RooDataHist pred_SB_AntiTag("pred_SB_AntiTag", "Data", RooArgList(*x), h_mX_SB_AntiTag);
    RooDataHist pred_SR_AntiTag("pred_SR_AntiTag", "Data", RooArgList(*x), h_mX_SR_AntiTag);
    RooDataHist pred_SB_90("pred_SB_90", "Data", RooArgList(*x), h_mX_SB_90);
    RooDataHist pred_SR_90("pred_SR_90", "Data", RooArgList(*x), h_mX_SR_90);
    RooDataHist pred_SB_150("pred_SB_150", "Data", RooArgList(*x), h_mX_SB_150);
    RooDataHist pred_SR_150("pred_SR_150", "Data", RooArgList(*x), h_mX_SR_150);
    

    RooPlot *frame=x->frame();
    pred_SB.plotOn(frame, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    pred_SR.plotOn(frame, RooFit::LineColor(kAzure+10), RooFit::MarkerColor(kAzure+10));
    pred_SB_AntiTag.plotOn(frame, RooFit::LineColor(kOrange), RooFit::MarkerColor(kOrange));
    pred_SR_AntiTag.plotOn(frame, RooFit::LineColor(kBlue), RooFit::MarkerColor(kBlue));
    pred_SB_90.plotOn(frame, RooFit::LineColor(kGreen), RooFit::MarkerColor(kGreen));
    pred_SR_90.plotOn(frame, RooFit::LineColor(kRed), RooFit::MarkerColor(kRed));
    pred_SB_150.plotOn(frame, RooFit::LineColor(kMagenta), RooFit::MarkerColor(kMagenta));
    pred_SR_150.plotOn(frame, RooFit::LineColor(kViolet-3), RooFit::MarkerColor(kViolet-3));
    TCanvas *c_overlap=new TCanvas("c_overlap", "c_overlap", 800, 800);
    frame->Draw("same");
    
    TLegend *leg = new TLegend(0.5,0.6,0.8,0.85,NULL,"brNDC");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(2);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    h_mX_SB->SetMarkerColor(kBlack);
    h_mX_SR->SetMarkerColor(kAzure+10);
    h_mX_SB_AntiTag->SetMarkerColor(kOrange);
    h_mX_SR_AntiTag->SetMarkerColor(kBlue);
    h_mX_SB_90->SetMarkerColor(kGreen);
    h_mX_SR_90->SetMarkerColor(kRed);
    h_mX_SB_150->SetMarkerColor(kMagenta);
    h_mX_SR_150->SetMarkerColor(kViolet-3);
    h_mX_SB->SetMarkerStyle(20);
    h_mX_SR->SetMarkerStyle(20);
    h_mX_SB_AntiTag->SetMarkerStyle(20);
    h_mX_SR_AntiTag->SetMarkerStyle(20);
    h_mX_SB_90->SetMarkerStyle(20);
    h_mX_SR_90->SetMarkerStyle(20);
    h_mX_SB_150->SetMarkerStyle(20);
    h_mX_SR_150->SetMarkerStyle(20);
    leg->AddEntry(h_mX_SB, "Data in SB", "ep");
    leg->AddEntry(h_mX_SR, "Data in SR", "ep");
    leg->AddEntry(h_mX_SB_AntiTag, "Data in SB_AntiTag", "ep");
    leg->AddEntry(h_mX_SR_AntiTag, "Data in SR_AntiTag", "ep");
    leg->AddEntry(h_mX_SB_90, "Data in SB_90", "ep");
    leg->AddEntry(h_mX_SR_90, "Data in SR_90", "ep");
    leg->AddEntry(h_mX_SB_150, "Data in SB_150", "ep");
    leg->AddEntry(h_mX_SR_150, "Data in SR_150", "ep");
    leg->Draw("same");











    TFile *f_data_SR_AntiTag_caterina=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total_caterina.root");
    TH1F *h_mX_SR_AntiTag_caterina=(TH1F*)f_data_SR_AntiTag_caterina->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_caterina->Rebin(3);
    h_mX_SR_AntiTag_caterina->Scale(1./h_mX_SR_AntiTag_caterina->Integral());

    TFile *f_data_SR_AntiTag_1=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SR_AntiTag_1=(TH1F*)f_data_SR_AntiTag_1->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_1->Rebin(3);
    h_mX_SR_AntiTag_1->Scale(1./h_mX_SR_AntiTag_1->Integral());

    TFile *f_data_SR_AntiTag_l3=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total_l3.root");
    TH1F *h_mX_SR_AntiTag_l3=(TH1F*)f_data_SR_AntiTag_l3->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_l3->Rebin(3);
    h_mX_SR_AntiTag_l3->Scale(1./h_mX_SR_AntiTag_l3->Integral());

    TFile *f_data_SR_AntiTag_l4=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total_l4.root");
    TH1F *h_mX_SR_AntiTag_l4=(TH1F*)f_data_SR_AntiTag_l4->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_l4->Rebin(3);
    h_mX_SR_AntiTag_l4->Scale(1./h_mX_SR_AntiTag_l4->Integral());

    RooDataHist pred_SR_AntiTag_caterina("pred_SR_caterina", "Data", RooArgList(*x), h_mX_SR_AntiTag_caterina);
    RooDataHist pred_SR_AntiTag_1("pred_SR", "Data", RooArgList(*x), h_mX_SR_AntiTag_1);
    RooDataHist pred_SR_AntiTag_l3("pred_SR_l3", "Data", RooArgList(*x), h_mX_SR_AntiTag_l3);
    RooDataHist pred_SR_AntiTag_l4("pred_SR_l4", "Data", RooArgList(*x), h_mX_SR_AntiTag_l4);

    RooPlot *frame_1=x->frame();
    pred_SR_AntiTag_caterina.plotOn(frame_1, RooFit::LineColor(kOrange), RooFit::MarkerColor(kOrange));
    pred_SR_AntiTag_1.plotOn(frame_1, RooFit::LineColor(kAzure), RooFit::MarkerColor(kAzure));
    pred_SR_AntiTag_l3.plotOn(frame_1, RooFit::LineColor(kViolet-3), RooFit::MarkerColor(kViolet-3));
    pred_SR_AntiTag_l4.plotOn(frame_1, RooFit::LineColor(kRed), RooFit::MarkerColor(kRed));

    TCanvas *c_overlap_1=new TCanvas("c_overlap_1", "c_overlap_1", 800, 800);
    frame_1->Draw("same");

    TLegend *leg_1 = new TLegend(0.5,0.6,0.8,0.85,NULL,"brNDC");
    leg_1->SetBorderSize(0);
    leg_1->SetTextSize(0.035);
    leg_1->SetLineColor(1);
    leg_1->SetLineStyle(1);
    leg_1->SetLineWidth(2);
    leg_1->SetFillColor(0);
    leg_1->SetFillStyle(0);
    h_mX_SR_AntiTag_caterina->SetMarkerColor(kOrange);
    h_mX_SR_AntiTag_1->SetMarkerColor(kAzure);
    h_mX_SR_AntiTag_l3->SetMarkerColor(kViolet-3);
    h_mX_SR_AntiTag_l4->SetMarkerColor(kRed);
    h_mX_SR_AntiTag_caterina->SetMarkerStyle(20);
    h_mX_SR_AntiTag_1->SetMarkerStyle(20);
    h_mX_SR_AntiTag_l3->SetMarkerStyle(20);
    h_mX_SR_AntiTag_l4->SetMarkerStyle(20);
    leg_1->AddEntry(h_mX_SR_AntiTag_caterina, "Data in SR caterina", "ep");
    leg_1->AddEntry(h_mX_SR_AntiTag_1, "Data in SR 1", "ep");
    leg_1->AddEntry(h_mX_SR_AntiTag_l3, "Data in SR l3", "ep");
    leg_1->AddEntry(h_mX_SR_AntiTag_l4, "Data in SR l4", "ep");
    leg_1->Draw("same");



    TFile *f_data_SR_AntiTag_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag_150/Histograms_LMR_chi2_tree_total_leading.root");
    TH1F *h_mX_SR_AntiTag_150=(TH1F*)f_data_SR_AntiTag_150->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_150->Rebin(4);
    //h_mX_SR_AntiTag_150->Scale(1./h_mX_SR_AntiTag_150->Integral());

    TFile *f_data_SR_AntiTag_2=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_mX_SR_AntiTag_2=(TH1F*)f_data_SR_AntiTag_2->Get("h_mX_SR_kinFit");
    h_mX_SR_AntiTag_2->Rebin(4);
    //h_mX_SR_AntiTag_2->Scale(1./h_mX_SR_AntiTag_2->Integral());
    //h_mX_SR_AntiTag_150->Divide(h_mX_SR_AntiTag_2);
    h_mX_SR_AntiTag_2->Divide(h_mX_SR_AntiTag_150);
    new TCanvas;
    //h_mX_SR_AntiTag_150->Draw("same");
    h_mX_SR_AntiTag_2->Draw("same");

}

