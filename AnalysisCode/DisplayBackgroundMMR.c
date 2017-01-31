#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TArrow.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <THStack.h>
#include <TLatex.h>
#include <iostream>



std::string itoa(int i)
{
  char res[10];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}


void DisplayBackgroundMMR(){



 gROOT->SetStyle("Plain");
 gStyle->SetOptStat(0000);
 //gStyle->SetErrorX(0) 
 gStyle->SetPadGridX(0);
 gStyle->SetPadGridY(0);
 TCanvas * c = new TCanvas("c", "c", 700,700);
 c->SetTickx(1);
 c->SetTicky(1);

 c->SetFrameFillStyle(4000);
 c->SetFrameFillColor(0);
 c->cd();

   gStyle->SetPadGridX(0);
   gStyle->SetPadGridY(0);
   gROOT->SetStyle("Plain");


  double totalLuminosity=22040; // /pb
  
  double xsec_ttbar=831.76;
  double xsec_qcd[8]={27850000,1717000,351300,31630.,6802.,1206.,120.4,25.24};
  double xsec_st =35.6;
  double xsec_zz =6.842;

  TFile *ttbar=new TFile("Histograms_TT.root"); 	
  TFile *singletop=new TFile("Histograms_ST.root");
  TFile *zz=new TFile("Histograms_ZZ.root");	
  /*std::vector<TFile*> qcd;
  qcd.push_back(new TFile ("Histograms_QCD_HT100to200_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT200to300_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT300to500_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT500to700_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT700to1000_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT1000to1500_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT1500to2000_Skim.root"));
  qcd.push_back(new TFile("Histograms_QCD_HT2000toInf_Skim.root"));



  double init_ttbar=((TH1F*)ttbar->Get("Count"))->GetBinContent(1);
  double init_qcd[8];

  double scale_qcd[8];
  double scale_ttbar=totalLuminosity*xsec_ttbar/init_ttbar;

  for(int l=0; l<8;l++){
	  init_qcd[l]=((TH1F*)qcd.at(l)->Get("Count"))->GetBinContent(1);
	  scale_qcd[l]=totalLuminosity*xsec_qcd[l]/init_qcd[l];

  }	


*/


  double init_ttbar=((TH1F*)ttbar->Get("Count"))->GetBinContent(1);
  double scale_ttbar=totalLuminosity*xsec_ttbar/init_ttbar;
	
  double init_st=((TH1F*)singletop->Get("Count"))->GetBinContent(1);
  double scale_st=totalLuminosity*xsec_st/init_st;

  double init_zz=((TH1F*)zz->Get("Count"))->GetBinContent(1);
  double scale_zz=totalLuminosity*xsec_zz/init_zz;

  TH1F * h_bkg = new TH1F("h_bkg","h_bkg",  50, 0., 3000.);
  THStack hs("hs","test stacked histograms");
  hs.SetTitle("");
  //c->cd();
  TH1F* h_mX_SB_kinFit=(TH1F*)ttbar->Get("h_mX_SB_kinFit");	
  std::cout<<" here "<<h_mX_SB_kinFit->GetEntries();
  h_mX_SB_kinFit->Scale(scale_ttbar);
  h_mX_SB_kinFit->Rebin(40);	
  h_bkg->Add(h_mX_SB_kinFit);
  h_mX_SB_kinFit->SetLineColor(kBlue+1);
  h_mX_SB_kinFit->SetFillColor(kBlue+1);
	
  TH1F* h_mX_SB_kinFit_zz=(TH1F*)zz->Get("h_mX_SB_kinFit");
  TH1F* h_mX_SB_kinFit_st=(TH1F*)singletop->Get("h_mX_SB_kinFit");
  
  h_mX_SB_kinFit_st->Scale(scale_st);
  h_mX_SB_kinFit_st->Rebin(40);
  h_bkg->Add(h_mX_SB_kinFit_st);
  h_mX_SB_kinFit_st->SetLineColor(kGreen+1);
  h_mX_SB_kinFit_st->SetFillColor(kGreen+1); 

  h_mX_SB_kinFit_zz->Scale(scale_zz);
  h_mX_SB_kinFit_zz->Rebin(40);
  h_bkg->Add(h_mX_SB_kinFit_zz);
  h_mX_SB_kinFit_zz->SetLineColor(kRed+1);
  h_mX_SB_kinFit_zz->SetFillColor(kRed+1);

  TLegend *leg = new TLegend(0.55625,0.7321654,0.8765625,0.87103839,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);	
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);



  double integral =0 ;
  integral = integral + h_mX_SB_kinFit->Integral(0,100);
  std::cout<< "integral tt " << integral<<std::endl;
  std::cout<< "integral zz " << h_mX_SB_kinFit_zz->Integral(0,100)<<std::endl;
  std::cout<< "integral st " << h_mX_SB_kinFit_st->Integral(0,100)<<std::endl;

  leg->AddEntry(h_mX_SB_kinFit, "t#bar{t} ", "f");
  leg->AddEntry(h_mX_SB_kinFit_st, "single top ", "f");
  leg->AddEntry(h_mX_SB_kinFit_zz, "ZZ ", "f");

  h_mX_SB_kinFit->Draw("");
  hs.Add(h_mX_SB_kinFit,"hist");
  hs.Add(h_mX_SB_kinFit_st,"hist");
  hs.Add(h_mX_SB_kinFit_zz,"hist");
/*  double integralQCD =0;
  for(int m=0; m<8;m++){
	  TH1F* h_mX_SB_kinFitQ=(TH1F*)qcd.at(m)->Get("h_mX_SB_kinFit");
	  h_mX_SB_kinFitQ->Scale(scale_qcd[m]);
	  h_mX_SB_kinFitQ->Rebin(40);
	  h_bkg->Add(h_mX_SB_kinFitQ);
	  h_mX_SB_kinFitQ->Draw("same");
	  h_mX_SB_kinFitQ->SetLineColor(kRed+1);
	  h_mX_SB_kinFitQ->SetFillColor(kRed+1);
//	  if(m==0) leg->AddEntry(h_mX_SB_kinFitQ, "QCD", "f");
//	  hs.Add(h_mX_SB_kinFitQ,"hist");
	  integralQCD = integralQCD + h_mX_SB_kinFitQ->Integral(0, 200);

  }
  std::cout<< "integral QCD " << integralQCD<<std::endl;
 */ h_mX_SB_kinFit->GetYaxis()->SetRangeUser(0., hs.GetMaximum()*5.);
  //h_mX_SB_kinFit->Scale(b/a);
  h_mX_SB_kinFit->SetTitle("");
  h_mX_SB_kinFit->SetLineColor(kBlue+2);
  h_mX_SB_kinFit->GetXaxis()->SetTitle("m_{X} (GeV)");
  std::cout<<h_mX_SB_kinFit->GetBinWidth(1)<<std::endl;
  //char * title="Events / 20 GeV";// / ("+itoa(h_mX_SB_kinFit->GetBinWidth(1))+" GeV)";
  h_mX_SB_kinFit->GetYaxis()->SetTitle(("Events / "+itoa(h_mX_SB_kinFit->GetBinWidth(1))+" (GeV)").c_str());
  h_mX_SB_kinFit->GetYaxis()->SetTitleSize(0.033);
  h_mX_SB_kinFit->GetYaxis()->SetTitleOffset(1.35);
  h_mX_SB_kinFit->GetYaxis()->SetLabelSize(0.03);
  h_mX_SB_kinFit->GetXaxis()->SetLabelSize(0.03);

  //h_mX_SB_kinFit->Draw("");
  h_mX_SB_kinFit->GetXaxis()->SetRangeUser(300.,1400.);
  //h_mX_SB_kinFit->SetMarkerStyle(20);
  //h_mX_SB_kinFit->SetMarkerColor(kBlack);
  //h_mX_SB_kinFit->SetLineColor(kBlack);
  //h_mX_SB_kinFit->Draw("same");
  //hs.GetXaxis()->SetRangeUser(220.,1200.);
  //hs->Rebin(2);
  hs.Draw("");
  
  //hs.GetXaxis()->SetRangeUser(220.,1200.);
  h_mX_SB_kinFit->Draw("");
  hs.Draw("same");


	

  std::cout<<" adding data "<<std::endl;

  TFile * fData = new TFile("Histogram_BTagCSV.root");
  TH1F* h_mX_SB_kinFitD=(TH1F*)fData->Get("h_mX_SB_kinFit");	
  h_mX_SB_kinFitD->Rebin(40);	
  h_mX_SB_kinFitD->SetMarkerStyle(20);
  h_mX_SB_kinFitD->SetMarkerColor(kBlack);
  h_mX_SB_kinFitD->SetLineColor(kBlack);
  h_mX_SB_kinFitD->Draw("same");
  //h_mX_SB_kinFit->Draw("same");
  hs.Draw("same");

	
  std::cout<<" data integral is : "<<h_mX_SB_kinFitD->Integral(0, 100)<<std::endl;

  leg->AddEntry(h_mX_SB_kinFitD, "Data in SB, MMR_{#chi} ", "lp");
	
	
	
   		

  TLatex * tPrel = new TLatex();
  tPrel->SetNDC();
  tPrel->SetTextColor(kBlack);
  tPrel->SetTextSize(0.04027386);
  tPrel->SetTextFont(42);	
  tPrel->DrawLatex(0.09821429,0.9194523,"CMS Preliminary          (13 TeV)  22.0 fb^{-1}");



  leg->Draw();
  //h_ttbar->Rebin(2);



  c->Print("stackMMR.root");
  c->Print("stackMMR.pdf");
  //h_mX_SB_kinFit->Rebin(4);

  //sprintf(name,"SB: t#bar{t} contribution =%d",integral/data);
  //pave->AddText(name);
  //pave->Draw();


}
