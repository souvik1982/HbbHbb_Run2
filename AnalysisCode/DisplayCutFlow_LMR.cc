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

int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
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
        int massPtsStd[9]={260, 270, 300, 350, 400, 450,  500, 550, 650};
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
	int massPtsStd[9]={260, 270, 300, 350, 400, 450,  500, 550, 650};
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

void DisplayCutFlow_LMR()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0);
  writeExtraText = true;       // if extra text
  extraText  = "Simulation" ; //Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "2.3 fb^{-1}";  // default is "5.1 fb^{-1}"


	//int n=10;
	int massL[9]={260, 270, 300, 350, 400, 450,  500, 550, 650};// 800, 1000, 1200};
//	int massL[5]={260, 270, 300, 400, 600}; //, 700, 800, 900, 1000, 1100};
  TFile *glugluToX260=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root");
  TFile *glugluToX270=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root");
  TFile *glugluToX300=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root");
 TFile *glugluToX350=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root");
  TFile *glugluToX400=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root");
  TFile *glugluToX450=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"); 
  TFile *glugluToX500=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root");
  TFile *glugluToX550=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root");
//  TFile *glugluToX600=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root");
  TFile *glugluToX650=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root");
 // TFile *glugluToX700=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph.root");
//TFile *glugluToX800=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root");
//TFile *glugluToX900=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root");
//TFile *glugluToX1000=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1000_narrow_13TeV-madgraph.root");
//TFile *glugluToX1200=new TFile("Histograms_GluGluToBulkGravitonToHHTo4B_M-1200_narrow_13TeV-madgraph.root");

  pushBackHistograms(signals, glugluToX260, glugluToX260);
  pushBackHistograms(signals, glugluToX270, glugluToX270);
  pushBackHistograms(signals, glugluToX300, glugluToX300 );
  pushBackHistograms(signals, glugluToX350, glugluToX350 );
  pushBackHistograms(signals, glugluToX400, glugluToX400);
  pushBackHistograms(signals, glugluToX450, glugluToX450);
  pushBackHistograms(signals, glugluToX500, glugluToX500);
  pushBackHistograms(signals, glugluToX550, glugluToX550);
 // pushBackHistograms(signals, glugluToX600, glugluToX600);
  pushBackHistograms(signals, glugluToX650, glugluToX650);
 // pushBackHistograms(signals, glugluToX700, glugluToX700);
//pushBackHistograms(signals, glugluToX800, glugluToX800);
//pushBackHistograms(signals, glugluToX900, glugluToX900);
//pushBackHistograms(signals, glugluToX1000, glugluToX1000);
//pushBackHistograms(signals, glugluToX1200, glugluToX1200);

  std::vector<TH1F *> h_Cut;
  TH1F *h_Init=new TH1F("h_Init", "h_Init", 154, 260, 1800);

  TH1F *h_Events3=(TH1F*)h_Init->Clone("h_Events3");
  TH1F *h_Events8=(TH1F*)h_Init->Clone("h_Events8");
  TH1F *h_Events10=(TH1F*)h_Init->Clone("h_Events10");
  TH1F *h_Events16=(TH1F*)h_Init->Clone("h_Events16");
//  for (unsigned int i=2; i<=8; ++i)
   for (unsigned int i=0; i<9; ++i)
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
  TGraphAsymmErrors *g_Ae_3=new TGraphAsymmErrors(h_Events3, h_Init); g_Ae_3->SetTitle("Trigger efficiency"); g_Ae_3->SetLineColor(kPink+2); g_Ae_3->SetMarkerColor(kPink+2); g_Ae_3->SetMarkerStyle(20); g_Ae_3->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_8=new TGraphAsymmErrors(h_Events8, h_Init); g_Ae_8->SetTitle("4 bjets efficiency"); g_Ae_8->SetLineColor(kBlue+2); g_Ae_8->SetMarkerColor(kBlue+2); g_Ae_8->SetMarkerStyle(20); g_Ae_8->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_10=new TGraphAsymmErrors(h_Events10, h_Init); g_Ae_10->SetTitle("HH Candidate efficiency"); g_Ae_10->SetLineColor(kGreen+2); g_Ae_10->SetMarkerColor(kGreen+2); g_Ae_10->SetMarkerStyle(20); g_Ae_10->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_16=new TGraphAsymmErrors(h_Events16, h_Init); g_Ae_16->SetTitle("SR efficiency"); g_Ae_16->SetLineColor(kRed+2);  g_Ae_16->SetMarkerColor(kRed+2); g_Ae_16->SetMarkerStyle(20); g_Ae_16->SetLineWidth(2);

  TCanvas *c_Ae=new TCanvas("c_Ae", "c_Ae", 700, 700);
  c_Ae->SetTickx(1);
  c_Ae->SetTicky(1);
  c_Ae->SetLogy();

  c_Ae->SetFrameFillStyle(4000);
  c_Ae->SetFrameFillColor(0000);
  g_Ae_3->SetMaximum(10.);
  g_Ae_3->SetMinimum(0.001);
  //g_Ae_3->SetMaximum(0.7); g_Ae_3->SetMinimum(0);
  g_Ae_3->SetTitle("");
  g_Ae_3->GetXaxis()->SetTitle("m_{X} (GeV)");
  g_Ae_3->GetYaxis()->SetTitle("efficiency (%)");
  g_Ae_3->GetYaxis()->SetTitleOffset(1.1);
  g_Ae_3->GetYaxis()->SetTitleFont(42); 	
  g_Ae_3->GetYaxis()->SetLabelFont(42); 
  g_Ae_3->GetXaxis()->SetTitleFont(42);   
  g_Ae_3->GetXaxis()->SetLabelFont(42);	
  g_Ae_3->GetYaxis()->SetLabelSize(0.03);
  g_Ae_3->GetXaxis()->SetLabelSize(0.03);
  g_Ae_3->Draw("ALP");
  g_Ae_8->Draw("LP same");
  g_Ae_10->Draw("LP same");
  g_Ae_16->Draw("LP same");
  std::cout<<" LMA "<<std::endl;

  TLegend *leg = new TLegend(0.60,0.15,0.90,0.40,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);	
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
 
  CMS_lumi( c_Ae, iPeriod, iPos );
  
  c_Ae->Update();

  // g_Ae_2->Draw("AL*");

  c_Ae->SaveAs("c_Ae.png");
  c_Ae->SaveAs("c_Ae.root");


}
