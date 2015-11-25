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
  int massPtsStd[10]={260, 270, 300, 400, 500, 600, 650, 700, 800, 900};
  int massPts[npoint];
  

  for(int i=0; i<npoint; i++) massPts[i]=massPtsStd[i];  
  std::cout<<" === Signal Efficiencies === "<<std::endl;
  std::cout<<" mX | Trigger | VType | nJets > 3 | HH Candidate | MMMM | SR "<<std::endl;
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
  int massPtsStd[10]={260, 270, 300, 400, 500, 600, 650, 700, 800, 900};

  int massPts[npoint];
  for(int i=0; i<npoint; i++) massPts[i]=massPtsStd[i];
 
  std::cout<<" === Signal Efficiencies === "<<std::endl;
  std::cout<<" mX | Trigger | VType | nJets > 3 | HH Candidate | MMMM | SR "<<std::endl;
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
 

//////LMA
 
  //int n=10;
  //int massPts[15]={270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  int massL[6]={260, 270, 300, 400, 500, 600};//, 550, 600, 650, 700, 800, 900, 1000, 1100};
  TFile *glugluToX260=new TFile("../LMR/Histograms_Graviton260GeV.root");
  TFile *glugluToX270=new TFile("../LMR/Histograms_Graviton270GeV.root");//DiJetPt_RadionToHH_4b_M-270GeV
  TFile *glugluToX300=new TFile("../LMR/Histograms_Graviton300GeV.root");//DiJetPt_RadionToHH_4b_M-270GeV
  TFile *glugluToX400=new TFile("../LMR/Histograms_Graviton400GeV.root");//DiJetPt_RadionToHH_4b_M-270GeV
  TFile *glugluToX500=new TFile("../LMR/Histograms_Graviton500GeV.root");//DiJetPt_RadionToHH_4b_M-270GeV
  TFile *glugluToX600=new TFile("../LMR/Histograms_Graviton600GeV.root"); 
  /*TFile *old550=new TFile("/gpfs/ddn/cms/user/cvernier/H4b_step2/CMSSW_5_3_3_patch2/src/VHbbAnalysis/VHbbDataFormats/bin/DiJetPt_RadionToHH_4b_M-550GeV.root");
  TFile *glugluToX550=new TFile("../LMR/Histograms_Graviton550GeV.root");//DiJetPt_RadionToHH_4b_M-270GeV
*/

  pushBackHistograms(signals, glugluToX260, glugluToX260);
  pushBackHistograms(signals, glugluToX270, glugluToX270);
  pushBackHistograms(signals, glugluToX300, glugluToX300 );
  pushBackHistograms(signals, glugluToX400, glugluToX400);
  pushBackHistograms(signals, glugluToX500, glugluToX500);
 
  pushBackHistograms(signals, glugluToX600, glugluToX600);

  std::vector<TH1F *> h_Cut;
  TH1F *h_Init=new TH1F("h_Init", "h_Init", 74, 260, 1000);
  
  TH1F *h_Events3=(TH1F*)h_Init->Clone("h_Events3");
  TH1F *h_Events8=(TH1F*)h_Init->Clone("h_Events8");
  TH1F *h_Events10=(TH1F*)h_Init->Clone("h_Events10");
  TH1F *h_Events16=(TH1F*)h_Init->Clone("h_Events16");
  for (unsigned int i=0; i<6; ++i)
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
  g_Ae_3->SetMinimum(0.001);
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

 TLegend *leg = new TLegend(0.55625,0.6321654,0.8765625,0.8603839,NULL,"brNDC");
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
  signals.v_Cuts.clear();
  signals.v_CountWithPU.clear();
//////HMA
//

  int massH[6]={400, 500, 600, 700, 800, 900};

  //TFile *MglugluToX270=new TFile("../MMR/Histograms_Graviton270GeV.root");//DiJetPt_RadionToHH_4b_M-270_TuneZ2star_8TeV-Madgraph_Mpythia6
  //TFile *MglugluToX300=new TFile("../MMR/Histograms_Graviton300GeV.root");
  TFile *MglugluToX400=new TFile("../MMR/Histograms_Graviton400GeV.root");
  TFile *MglugluToX500=new TFile("../MMR/Histograms_Graviton500GeV.root");
  TFile *MglugluToX600=new TFile("../MMR/Histograms_Graviton600GeV.root");
  TFile *MglugluToX650=new TFile("../MMR/Histograms_Graviton650GeV.root");
  TFile *MglugluToX700=new TFile("../MMR/Histograms_Graviton700GeV.root");
  TFile *MglugluToX800=new TFile("../MMR/Histograms_Graviton800GeV.root");
  TFile *MglugluToX900=new TFile("../MMR/Histograms_Graviton900GeV.root");

  //pushBackHistograms(signals, MglugluToX270, MglugluToX270);
  //pushBackHistograms(signals, MglugluToX300, MglugluToX300 );
  pushBackHistograms(signals, MglugluToX400, MglugluToX400);
  pushBackHistograms(signals, MglugluToX500, MglugluToX500);
  pushBackHistograms(signals, MglugluToX600, MglugluToX600);
  //pushBackHistograms(signals, MglugluToX650, MglugluToX650);
  pushBackHistograms(signals, MglugluToX700, MglugluToX700);
  pushBackHistograms(signals, MglugluToX800, MglugluToX800);
  pushBackHistograms(signals, MglugluToX900, MglugluToX900);
  TH1F *h_MInit=new TH1F("h_MInit", "h_MInit", 88, 320, 1200);
    TH1F *h_MEvents3=(TH1F*)h_MInit->Clone("h_MEvents3");
  TH1F *h_MEvents8=(TH1F*)h_MInit->Clone("h_MEvents8");
  TH1F *h_MEvents10=(TH1F*)h_MInit->Clone("h_MEvents10");
  TH1F *h_MEvents16=(TH1F*)h_MInit->Clone("h_MEvents16");
  for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
  {
    h_MInit->SetBinContent(h_MInit->FindBin(massH[i]), signals.v_CountWithPU.at(i)->GetBinContent(1));

std::cout<<massH[i]<<"   "<<signals.v_Cuts.at(i)->GetBinContent(4)<< "   "<<signals.v_Cuts.at(i)->GetBinContent(8)<<"   "<< signals.v_Cuts.at(i)->GetBinContent(10)<< "  "<< signals.v_Cuts.at(i)->GetBinContent(12)<<std::endl;
    h_MEvents3->SetBinContent(h_MInit->FindBin(massH[i]), signals.v_Cuts.at(i)->GetBinContent(4)); 
    h_MEvents8->SetBinContent(h_MInit->FindBin(massH[i]), signals.v_Cuts.at(i)->GetBinContent(8));
    h_MEvents10->SetBinContent(h_MInit->FindBin(massH[i]), signals.v_Cuts.at(i)->GetBinContent(10));
    h_MEvents16->SetBinContent(h_MInit->FindBin(massH[i]), signals.v_Cuts.at(i)->GetBinContent(12));
  }
   TGraphAsymmErrors *g_Ae_M3=new TGraphAsymmErrors(h_MEvents3, h_MInit); g_Ae_M3->SetTitle("Trigger efficiency"); g_Ae_M3->SetLineColor(kPink+2); g_Ae_M3->SetMarkerColor(kPink+2); g_Ae_M3->SetMarkerStyle(22); g_Ae_M3->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_M8=new TGraphAsymmErrors(h_MEvents8, h_MInit); g_Ae_M8->SetTitle("4 bjets efficiency"); g_Ae_M8->SetLineColor(kBlue+2); g_Ae_M8->SetMarkerColor(kBlue+2); g_Ae_M8->SetMarkerStyle(22); g_Ae_M8->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_M10=new TGraphAsymmErrors(h_MEvents10, h_MInit); g_Ae_M10->SetTitle("HH Candidate efficiency"); g_Ae_M10->SetLineColor(kGreen+2); g_Ae_M10->SetMarkerColor(kGreen+2); g_Ae_M10->SetMarkerStyle(23); g_Ae_M10->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_M16=new TGraphAsymmErrors(h_MEvents16, h_MInit); g_Ae_M16->SetTitle("SR efficiency"); g_Ae_M16->SetLineColor(kRed+2);  g_Ae_M16->SetMarkerColor(kRed+2); g_Ae_M16->SetMarkerStyle(33); g_Ae_M16->SetLineWidth(2);
c_Ae->cd();

g_Ae_M3->SetMinimum(0.001);
//  g_Ae_M3->SetMaximum(0.7); g_Ae_M3->SetMinimum(0);
  g_Ae_M3->SetTitle("");
  g_Ae_M3->GetXaxis()->SetTitle("m_{X} [GeV]");
  g_Ae_M3->GetYaxis()->SetTitle("A #times #epsilon");
  g_Ae_M3->GetYaxis()->SetTitleOffset(1.1);
  g_Ae_M3->GetYaxis()->SetLabelSize(0.03);
  g_Ae_M3->GetXaxis()->SetLabelSize(0.03);
  g_Ae_M3->Draw("ALP");

  g_Ae_M8->Draw("LP same");
  g_Ae_M10->Draw("LP same");
  g_Ae_M16->Draw("LP same");

  signals.v_Cuts.clear();
  signals.v_CountWithPU.clear();

std::cout<<"  MML "<<std::endl;

////HMA
//
/* 
  int massU[5]={700, 800, 900, 1000, 1100};

  TFile * HglugluToX700=new TFile("HMA/Histograms_RadionToHH_4b_M-700GeV.root");
  TFile *HglugluToX800=new TFile("HMA/Histograms_RadionToHH_4b_M-800GeV.root");
  TFile *HglugluToX900=new TFile("HMA/Histograms_RadionToHH_4b_M-900GeV.root");
  TFile *HglugluToX1000=new TFile("HMA/Histograms_RadionToHH_4b_M-1000GeV.root");
  TFile *HglugluToX1100=new TFile("HMA/Histograms_RadionToHH_4b_M-1100GeV.root");

  pushBackHistograms(signals, HglugluToX700, HglugluToX700);
  pushBackHistograms(signals, HglugluToX800, HglugluToX800);
  pushBackHistograms(signals, HglugluToX900, HglugluToX900);
  pushBackHistograms(signals, HglugluToX1000, HglugluToX1000);
  pushBackHistograms(signals, HglugluToX1100, HglugluToX1100);

  TH1F *h_HInit=new TH1F("h_HInit", "h_HInit", 88, 320, 1200);

  TH1F *h_HEvents8=(TH1F*)h_HInit->Clone("h_HEvents8");
  TH1F *h_HEvents10=(TH1F*)h_HInit->Clone("h_HEvents10");
  TH1F *h_HEvents16=(TH1F*)h_HInit->Clone("h_HEvents16");
  for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
  {
    h_HInit->SetBinContent(h_HInit->FindBin(massU[i]), signals.v_CountWithPU.at(i)->GetBinContent(1));
    h_HEvents8->SetBinContent(h_HInit->FindBin(massU[i]), signals.v_Cuts.at(i)->GetBinContent(8));
    h_HEvents10->SetBinContent(h_HInit->FindBin(massU[i]), signals.v_Cuts.at(i)->GetBinContent(10));
    h_HEvents16->SetBinContent(h_HInit->FindBin(massU[i]), signals.v_Cuts.at(i)->GetBinContent(16));
  }

  TGraphAsymmErrors *g_Ae_H8=new TGraphAsymmErrors(h_HEvents8, h_HInit); g_Ae_H8->SetTitle("4 bjets efficiency"); g_Ae_H8->SetLineColor(kBlue+2); g_Ae_H8->SetMarkerColor(kBlue+2); g_Ae_H8->SetMarkerStyle(22); g_Ae_H8->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_H10=new TGraphAsymmErrors(h_HEvents10, h_HInit); g_Ae_H10->SetTitle("HH Candidate efficiency"); g_Ae_H10->SetLineColor(kGreen+2); g_Ae_H10->SetMarkerColor(kGreen+2); g_Ae_H10->SetMarkerStyle(23); g_Ae_H10->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_H16=new TGraphAsymmErrors(h_HEvents16, h_HInit); g_Ae_H16->SetTitle("SR efficiency"); g_Ae_H16->SetLineColor(kRed+2);  g_Ae_H16->SetMarkerColor(kRed+2); g_Ae_H16->SetMarkerStyle(33); g_Ae_H16->SetLineWidth(2);

  g_Ae_H8->Draw(" LP same");
  g_Ae_H10->Draw("LP same");
  g_Ae_H16->Draw("LP same");

*/
/*   TLegend *leg = new TLegend(0.55625,0.6321654,0.8765625,0.8603839,NULL,"brNDC");
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
  */leg->Draw("same");

  c_Ae->Update();
  




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
