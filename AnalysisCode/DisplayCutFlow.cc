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
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
bool data_sets=false;

bool signaleff=true;
bool cumeff=true;

struct Samples
{
	std::vector<TH1F *> v_Cuts;
	std::vector<TH1F *> v_CountWithPU;
} signals, data;

void pushBackHistograms(Samples &sample, TFile *file, TFile * old, bool MC=true)
{
	if (MC==true)
	{
		sample.v_CountWithPU.push_back((TH1F*)old->Get("Count"));
	}
	sample.v_Cuts.push_back((TH1F*)file->Get("h_Cuts"));
}

void signalEff(int npoint)
{
	int massPtsStd[7]={260, 270, 300, 400, 600, 800, 1000};
	int massPts[npoint];


	for(int i=0; i<npoint; i++) massPts[i]=massPtsStd[i];  
	std::cout<<" === Signal Efficiencies === "<<std::endl;
	std::cout<<" mX | Trigger | VType | nJets > 3 | HH Candidate | LLLL | SR "<<std::endl;
	for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
	{
		double triggerEff=(signals.v_Cuts.at(i)->GetBinContent(3))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double vtypeEff=(signals.v_Cuts.at(i)->GetBinContent(6))/(signals.v_Cuts.at(i)->GetBinContent(4));
		double nCJetsEff=(signals.v_Cuts.at(i)->GetBinContent(7))/(signals.v_Cuts.at(i)->GetBinContent(6));
		double hhCandEff=(signals.v_Cuts.at(i)->GetBinContent(9))/(signals.v_Cuts.at(i)->GetBinContent(8));
		double btagEff=(signals.v_Cuts.at(i)->GetBinContent(14))/(signals.v_Cuts.at(i)->GetBinContent(10));
		double SREff=(signals.v_Cuts.at(i)->GetBinContent(11))/(signals.v_Cuts.at(i)->GetBinContent(14));

		std::cout<<massPts[i]<<" | "<<triggerEff<<" | "<<vtypeEff<<" | "<<nCJetsEff<<" | "<<hhCandEff<<" | "<<btagEff<<" | "<<SREff<<std::endl;
	}
	std::cout<<" === === "<<std::endl;
}

void cumEff(int npoint)
{
	int massPtsStd[7]={260, 270, 300, 400, 600, 800, 1000};

	int massPts[npoint];
	for(int i=0; i<npoint; i++) massPts[i]=massPtsStd[i];

	std::cout<<" === Signal Efficiencies === "<<std::endl;
	std::cout<<" mX | Trigger | VType | nJets > 3 | HH Candidate | LLLL | SR "<<std::endl;
	for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
	{
		double triggerEff=(signals.v_Cuts.at(i)->GetBinContent(4))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double vtypeEff=(signals.v_Cuts.at(i)->GetBinContent(6))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double nCJetsEff=(signals.v_Cuts.at(i)->GetBinContent(8))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double hhCandEff=(signals.v_Cuts.at(i)->GetBinContent(10))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double btagEff=(signals.v_Cuts.at(i)->GetBinContent(14))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
		double SREff=(signals.v_Cuts.at(i)->GetBinContent(16))/(signals.v_CountWithPU.at(i)->GetBinContent(1));

		std::cout<<massPts[i]<<" | "<<triggerEff<<" | "<<vtypeEff<<" | "<<nCJetsEff<<" | "<<hhCandEff<<" | "<<btagEff<<" | "<<SREff<<std::endl;
	}
	std::cout<<" === === "<<std::endl;
}

void DisplayCutFlow()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0);


	//int n=10;
	//int massPts[15]={270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
	int massL[9]={260, 270, 300, 400, 600, 800, 1000, 1200, 1600};//, 550, 600, 650, 700, 800, 900, 1000, 1100};
  TFile *glugluToX260=new TFile("Histograms_Graviton260GeV.root");
  TFile *glugluToX270=new TFile("Histograms_Graviton270GeV.root");
  TFile *glugluToX300=new TFile("Histograms_Graviton300GeV.root");
  TFile *glugluToX400=new TFile("Histograms_Graviton400GeV.root");
  TFile *glugluToX600=new TFile("Histograms_Graviton600GeV.root"); 
  TFile *glugluToX800=new TFile("Histograms_Graviton800GeV.root");
  TFile *glugluToX1000=new TFile("Histograms_Graviton1000GeV.root");
  TFile *glugluToX1200=new TFile("Histograms_Graviton1200GeV.root");
  TFile *glugluToX1600=new TFile("Histograms_Graviton1600GeV.root");

  pushBackHistograms(signals, glugluToX260, glugluToX260);
  pushBackHistograms(signals, glugluToX270, glugluToX270);
  pushBackHistograms(signals, glugluToX300, glugluToX300 );
  pushBackHistograms(signals, glugluToX400, glugluToX400);
  pushBackHistograms(signals, glugluToX600, glugluToX600);
  pushBackHistograms(signals, glugluToX800, glugluToX800);
  pushBackHistograms(signals, glugluToX1000, glugluToX1000);
  pushBackHistograms(signals, glugluToX1200, glugluToX1200);
  pushBackHistograms(signals, glugluToX1600, glugluToX1600);

  std::vector<TH1F *> h_Cut;
  TH1F *h_Init=new TH1F("h_Init", "h_Init", 154, 260, 1800);

  TH1F *h_Events3=(TH1F*)h_Init->Clone("h_Events3");
  TH1F *h_Events8=(TH1F*)h_Init->Clone("h_Events8");
  TH1F *h_Events10=(TH1F*)h_Init->Clone("h_Events10");
  TH1F *h_Events16=(TH1F*)h_Init->Clone("h_Events16");
  for (unsigned int i=2; i<=8; ++i)
  // for (unsigned int i=0; i<=5; ++i)
  {
	  h_Init->SetBinContent(h_Init->FindBin(massL[i]), signals.v_CountWithPU.at(i)->GetBinContent(1));
	  // std::cout<<"signals.v_CountWithPU.at(i)->GetBinContent(1) = "<<.signals.v_CountWithPU.at(i)->GetBinContent(1)<<std::endl;
	  // h_Events2->SetBinContent(i, signals.v_Cuts.at(i)->GetBinContent(2));
	  //
	  std::cout<<massL[i]<<"   "<<signals.v_Cuts.at(i)->GetBinContent(4)<< "   "<<signals.v_Cuts.at(i)->GetBinContent(8)<<"   "<< signals.v_Cuts.at(i)->GetBinContent(10)<< "  "<< signals.v_Cuts.at(i)->GetBinContent(12)<<std::endl;
	  h_Events3->SetBinContent(h_Init->FindBin(massL[i]), signals.v_Cuts.at(i)->GetBinContent(4));
	  h_Events8->SetBinContent(h_Init->FindBin(massL[i]), signals.v_Cuts.at(i)->GetBinContent(8));
	  h_Events10->SetBinContent(h_Init->FindBin(massL[i]), signals.v_Cuts.at(i)->GetBinContent(10));
	  h_Events16->SetBinContent(h_Init->FindBin(massL[i]), signals.v_Cuts.at(i)->GetBinContent(12));

	  // std::cout<<"m_X (GeV) = "<<massPts[i]<<", Efficiency = "<<signals.v_Cuts.at(i)->GetBinContent(16)/signals.v_CountWithPU.at(i)->GetBinContent(1)<<std::endl;
  }
  TGraphAsymmErrors *g_Ae_3=new TGraphAsymmErrors(h_Events3, h_Init); g_Ae_3->SetTitle("Trigger efficiency"); g_Ae_3->SetLineColor(kPink+2); g_Ae_3->SetMarkerColor(kPink+2); g_Ae_3->SetMarkerStyle(22); g_Ae_3->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_8=new TGraphAsymmErrors(h_Events8, h_Init); g_Ae_8->SetTitle("4 bjets efficiency"); g_Ae_8->SetLineColor(kBlue+2); g_Ae_8->SetMarkerColor(kBlue+2); g_Ae_8->SetMarkerStyle(22); g_Ae_8->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_10=new TGraphAsymmErrors(h_Events10, h_Init); g_Ae_10->SetTitle("HH Candidate efficiency"); g_Ae_10->SetLineColor(kGreen+2); g_Ae_10->SetMarkerColor(kGreen+2); g_Ae_10->SetMarkerStyle(23); g_Ae_10->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_16=new TGraphAsymmErrors(h_Events16, h_Init); g_Ae_16->SetTitle("SR efficiency"); g_Ae_16->SetLineColor(kRed+2);  g_Ae_16->SetMarkerColor(kRed+2); g_Ae_16->SetMarkerStyle(33); g_Ae_16->SetLineWidth(2);

  TCanvas *c_Ae=new TCanvas("c_Ae", "c_Ae", 1000, 700);
  c_Ae->SetTickx(1);
  c_Ae->SetTicky(1);
  c_Ae->SetLogy();

  c_Ae->SetFrameFillStyle(4000);
  c_Ae->SetFrameFillColor(0000);
  g_Ae_3->SetMaximum(1.);
  g_Ae_3->SetMinimum(0.0001);
  //g_Ae_3->SetMaximum(0.7); g_Ae_3->SetMinimum(0);
  g_Ae_3->SetTitle("");
  g_Ae_3->GetXaxis()->SetTitle("m_{X} [GeV]");
  g_Ae_3->GetYaxis()->SetTitle("A #times #epsilon");
  g_Ae_3->GetYaxis()->SetTitleOffset(1.1);
  g_Ae_3->GetYaxis()->SetLabelSize(0.03);
  g_Ae_3->GetXaxis()->SetLabelSize(0.03);
  g_Ae_3->Draw("ALP");
  g_Ae_8->Draw("LP same");
  g_Ae_10->Draw("LP same");
  g_Ae_16->Draw("LP same");
  std::cout<<" LMA "<<std::endl;

  TLegend *leg = new TLegend(0.55,0.25,0.90,0.50,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(g_Ae_3, "Trigger");
  leg->AddEntry(g_Ae_8, "4 b-tagged jets", "lp");
  leg->AddEntry(g_Ae_10, "HH candidate", "lp");
  leg->AddEntry(g_Ae_16, "Signal Region", "lp");
  leg->Draw("same");

  c_Ae->SaveAs("step1.png");
  
  TLatex * tPrel = new TLatex();
  tPrel->SetNDC();
  tPrel->SetTextColor(kBlack);
  tPrel->SetTextSize(0.04027386);
  tPrel->DrawLatex(0.09821429,0.9194523,"CMS Simulation; #sqrt{s} =  13 TeV");
  c_Ae->Update();

  // g_Ae_2->Draw("AL*");

  c_Ae->SaveAs("c_Ae.png");
  c_Ae->SaveAs("c_Ae.root");


}
