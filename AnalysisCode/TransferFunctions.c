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
#include "CMS_lumi.h"
#include <iostream>


Double_t pol0(Double_t *x, Double_t *par){
	return  par[0];
}


void TransferFunctions(){
    gROOT->SetStyle("Plain");
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    gStyle->SetOptFit(11111111);
    //gStyle->SetOptStat("SneMRou");
    
    int rebin = 3;

    TFile *f_SR_AntiTag_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SR_AntiTag_150=(TH1F*)f_SR_AntiTag_150->Get("h_mX_SR_kinFit");
    h_SR_AntiTag_150->Rebin(rebin);



    TFile *f_SR_AntiTag=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SR_AntiTag=(TH1F*)f_SR_AntiTag->Get("h_mX_SR_kinFit");
    h_SR_AntiTag->Rebin(rebin);

    TFile *f_SR_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SR_150=(TH1F*)f_SR_150->Get("h_mX_SR_kinFit");
    h_SR_150->Rebin(rebin);

    TFile *f_SB_AntiTag_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SB_AntiTag_150=(TH1F*)f_SB_AntiTag_150->Get("h_mX_SB_kinFit");
    h_SB_AntiTag_150->Rebin(rebin);

    TFile *f_SB_AntiTag=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SB_AntiTag=(TH1F*)f_SB_AntiTag->Get("h_mX_SB_kinFit");
    h_SB_AntiTag->Rebin(rebin);

    TFile *f_SB_150=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_150/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SB_150=(TH1F*)f_SB_150->Get("h_mX_SB_kinFit");
    h_SB_150->Rebin(rebin);

    TFile *f_SB=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SB=(TH1F*)f_SB->Get("h_mX_SB_kinFit");
    h_SB->Rebin(rebin);


    h_SR_AntiTag_150->Scale(1./h_SR_AntiTag_150->Integral());
    h_SR_AntiTag->Scale(1./h_SR_AntiTag->Integral());
    h_SB_AntiTag->Scale(1./h_SB_AntiTag->Integral());
    h_SR_150->Scale(1./h_SR_150->Integral());
    h_SB_AntiTag_150->Scale(1./h_SB_AntiTag_150->Integral());
    h_SB_AntiTag->Scale(1./h_SB_AntiTag->Integral());
    h_SB_150->Scale(1./h_SB_150->Integral());
    h_SB->Scale(1./h_SB->Integral());

new TCanvas; h_SR_AntiTag->Draw();

 const int nbins = h_SR_AntiTag->GetNbinsX();
    int bin_min = h_SR_AntiTag->FindBin(252);
    int bin_max = h_SR_AntiTag->FindBin(900);
    std::vector<double> v_SR_AntiTag;


    for (int i = bin_min; i<= bin_max; i++) {
        v_SR_AntiTag.push_back(h_SR_AntiTag->GetBinContent(i));
        cout<< i << " " << h_SR_AntiTag->GetBinContent(i)/h_SR_AntiTag->Integral()<< " " <<  v_SR_AntiTag[i-bin_min]<< endl; 
    }


    TH1F *h_SB_AntiTag_test_1=(TH1F*)h_SB_AntiTag_150->Clone("h_mX_SB_kinFit");
    TH1F *h_SB_AntiTag_test_2=(TH1F*)h_SB_AntiTag_150->Clone("h_mX_SB_kinFit");
    h_SB_AntiTag_test_1->SetLineColor(kRed);
    h_SB_AntiTag_test_2->SetLineColor(kRed);

    TH1F *h_SR_150_test_1=(TH1F*)h_SR_AntiTag_150->Clone("h_mX_SR_kinFit");
    TH1F *h_SR_150_test_2=(TH1F*)h_SR_AntiTag_150->Clone("h_mX_SR_kinFit");
    h_SR_150_test_1->SetLineColor(kRed);
    h_SR_150_test_2->SetLineColor(kRed);

    h_SB_AntiTag_test_1->Divide(h_SB_150);
    h_SB_AntiTag_test_1->Multiply(h_SB);
    h_SB_AntiTag_test_2->Divide(h_SR_AntiTag_150);
    h_SB_AntiTag_test_2->Multiply(h_SR_AntiTag);

    h_SR_150_test_1->Divide(h_SB_150);
    h_SR_150_test_1->Multiply(h_SB_AntiTag_150);
    h_SR_150_test_2->Multiply(h_SB_150);
    h_SR_150_test_2->Divide(h_SB_AntiTag_150);


    TH1F *h_SB_test_1=(TH1F*)h_SB_AntiTag->Clone("h_mX_SR_kinFit");
    h_SB_test_1->SetLineColor(kRed);

    h_SB_test_1->Divide(h_SB_AntiTag_150);
    h_SB_test_1->Multiply(h_SB_150);

    TH1F *h_SR_test_1=(TH1F*)h_SR_150->Clone("h_mX_SR_kinFit");
    h_SR_test_1->SetLineColor(kRed);

    //h_SR_test_1->Divide(h_SR_AntiTag_150);
    //h_SR_test_1->Multiply(h_SR_AntiTag);

    //TH1F *h_SR_test_1=(TH1F*)h_SR_150->Clone("h_mX_SR_kinFit");
    //h_SR_test_1->SetLineColor(kRed);

    //h_SR_test_1->Divide(h_SB_150);
    //h_SR_test_1->Multiply(h_SB);

    TCanvas *c_D1=new TCanvas("c_D1", "c_D1", 800, 800);
    h_SB_AntiTag_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SB_AntiTag_test_1->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_D1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_D1->SetBorderSize(0);
    leg_D1->SetTextSize(0.02);
    leg_D1->SetLineColor(1);
    leg_D1->SetLineStyle(1);
    leg_D1->SetLineWidth(2);
    leg_D1->SetFillColor(0);
    leg_D1->SetFillStyle(0);
    h_SB_AntiTag_test_1->SetMarkerColor(kRed);
    h_SB_AntiTag->SetMarkerColor(kAzure+10);
    leg_D1->AddEntry(h_SB_AntiTag_test_1, "h_SB_AntiTag_test_1", "l");
    leg_D1->AddEntry(h_SB_AntiTag, "h_SB_AntiTag", "l");
    leg_D1->Draw("same");

    TCanvas *c_D2=new TCanvas("c_D2", "c_D2", 800, 800);
    h_SB_AntiTag_test_2->GetXaxis()->SetRangeUser(240, 700);
    h_SB_AntiTag_test_2->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_D2 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_D2->SetBorderSize(0);
    leg_D2->SetTextSize(0.02);
    leg_D2->SetLineColor(1);
    leg_D2->SetLineStyle(1);
    leg_D2->SetLineWidth(2);
    leg_D2->SetFillColor(0);
    leg_D2->SetFillStyle(0);
    h_SB_AntiTag_test_2->SetMarkerColor(kRed);
    h_SB_AntiTag->SetMarkerColor(kAzure+10);
    leg_D2->AddEntry(h_SB_AntiTag_test_2, "h_SB_AntiTag_test_2", "l");
    leg_D2->AddEntry(h_SB_AntiTag, "h_SB_AntiTag", "l");
    leg_D2->Draw("same");

    TCanvas *c_E1=new TCanvas("c_E1", "c_E1", 800, 800);
    h_SR_150_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SR_150_test_1->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_E1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_E1->SetBorderSize(0);
    leg_E1->SetTextSize(0.02);
    leg_E1->SetLineColor(1);
    leg_E1->SetLineStyle(1);
    leg_E1->SetLineWidth(2);
    leg_E1->SetFillColor(0);
    leg_E1->SetFillStyle(0);
    h_SR_150_test_1->SetMarkerColor(kRed);
    h_SR_150->SetMarkerColor(kAzure+10);
    leg_E1->AddEntry(h_SR_150_test_1, "h_SR_150_test_1", "l");
    leg_E1->AddEntry(h_SR_150, "h_SR_150", "l");
    leg_E1->Draw("same");

    TCanvas *c_E2=new TCanvas("c_E2", "c_E2", 800, 800);
    h_SR_150_test_2->GetXaxis()->SetRangeUser(240, 700);
    h_SR_150_test_2->Draw("same");
    h_SR_150->Draw("same");
    TLegend *leg_E2 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_E2->SetBorderSize(0);
    leg_E2->SetTextSize(0.02);
    leg_E2->SetLineColor(1);
    leg_E2->SetLineStyle(1);
    leg_E2->SetLineWidth(2);
    leg_E2->SetFillColor(0);
    leg_E2->SetFillStyle(0);
    h_SR_150_test_2->SetMarkerColor(kRed);
    h_SR_150->SetMarkerColor(kAzure+10);
    leg_E2->AddEntry(h_SR_150_test_2, "h_SR_150_test_2", "l");
    leg_E2->AddEntry(h_SR_150, "h_SR_150", "l");
    leg_E2->Draw("same");

    TCanvas *c_B1=new TCanvas("c_B1", "c_B1", 800, 800);
    h_SB_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SB->GetXaxis()->SetRangeUser(240, 700);
    h_SB->Draw("same");
    h_SB_test_1->Draw("same");
    TLegend *leg_B1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_B1->SetBorderSize(0);
    leg_B1->SetTextSize(0.02);
    leg_B1->SetLineColor(1);
    leg_B1->SetLineStyle(1);
    leg_B1->SetLineWidth(2);
    leg_B1->SetFillColor(0);
    leg_B1->SetFillStyle(0);
    h_SB_test_1->SetMarkerColor(kRed);
    h_SB->SetMarkerColor(kAzure+10);
    leg_B1->AddEntry(h_SB_test_1, "h_SB_test_1", "l");
    leg_B1->AddEntry(h_SB, "h_SR", "l");
    leg_B1->Draw("same");



    TFile *f_SR=new TFile("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root");
    TH1F *h_SR=(TH1F*)f_SR->Get("h_mX_SR_kinFit");
    h_SR->Rebin(rebin);
    h_SR->Scale(1./h_SR->Integral());

    TCanvas *c_A1=new TCanvas("c_A1", "c_A1", 800, 800);
    h_SR_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SR_test_1->Draw("same");
    h_SR->Draw("same");
    TLegend *leg_A1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_A1->SetBorderSize(0);
    leg_A1->SetTextSize(0.02);
    leg_A1->SetLineColor(1);
    leg_A1->SetLineStyle(1);
    leg_A1->SetLineWidth(2);
    leg_A1->SetFillColor(0);
    leg_A1->SetFillStyle(0);
    h_SR_test_1->SetMarkerColor(kRed);
    h_SR_test_1->SetMarkerColor(kAzure+10);
    leg_A1->AddEntry(h_SR_test_1, "h_SR_test_1", "l");
    leg_A1->AddEntry(h_SR_test_1, "h_SR", "l");
    leg_A1->Draw("same");



new TCanvas;
    TH1F *h_SR_150_diff=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_diff->Add(h_SR_150,-1);
    h_SR_150_diff->SetLineColor(kBlack);
    h_SR_150_diff->Draw("same");

new TCanvas;
    TH1F *h_SR_150_ratio=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_ratio->Divide(h_SR_150);
    h_SR_150_ratio->SetLineColor(kBlack);
    h_SR_150_ratio->Draw("same");


TF1 *fit_pol = new TF1("fit_pol", pol0, 0., 2000., 1);
	fit_pol->SetParameter(0, 1.);
	
	h_SR_150_ratio->Fit(fit_pol,"","",0.,700.);

new TCanvas;
    TH1F *h_SB_AntiTag_ratio=(TH1F*)h_SB_AntiTag_test_1->Clone("h_mX_SB_kinFit");
    h_SB_AntiTag_ratio->Divide(h_SB_AntiTag);
    h_SB_AntiTag_ratio->SetLineColor(kBlack);
    h_SB_AntiTag_ratio->Draw("same");


TF1 *fit_pol1 = new TF1("fit_pol", pol0, 0., 2000., 1);
        fit_pol1->SetParameter(0, 1.);

        h_SB_AntiTag_ratio->Fit(fit_pol1,"","",0.,700.);

new TCanvas;
    TH1F *h_SB_ratio=(TH1F*)h_SB_test_1->Clone("h_mX_SB_kinFit");
    h_SB_ratio->Divide(h_SB);
    h_SB_ratio->SetLineColor(kBlack);
    h_SB_ratio->Draw("same");


TF1 *fit_pol2 = new TF1("fit_pol", pol0, 0., 2000., 1);
        fit_pol2->SetParameter(0, 1.);

        h_SB_ratio->Fit(fit_pol2,"","",0.,700.);


}

