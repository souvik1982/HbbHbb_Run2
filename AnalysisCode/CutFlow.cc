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

bool data_sets=false;

bool signaleff=true;
bool cumeff=true;

struct Samples
{
  std::vector<TH1F *> v_Cuts;
  std::vector<TH1F *> v_CountWithPU;
} signals, data;

void pushBackHistograms(Samples &sample, TFile *file, bool MC=true)
{
  if (MC==true)
  {
    sample.v_CountWithPU.push_back((TH1F*)file->Get("CountWithPU"));
  }
  sample.v_Cuts.push_back((TH1F*)file->Get("h_Cuts"));
}

void signalEff()
{
  int massPts[15]={270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  
  std::cout<<" === Signal Efficiencies === "<<std::endl;
  std::cout<<" mX | Trigger | VType | nJets > 3 | HH Candidate | MMMM | SR "<<std::endl;
  for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
  {
    double triggerEff=(signals.v_Cuts.at(i)->GetBinContent(4))/(signals.v_CountWithPU.at(i)->GetBinContent(1));
    double vtypeEff=(signals.v_Cuts.at(i)->GetBinContent(6))/(signals.v_Cuts.at(i)->GetBinContent(4));
    double nCJetsEff=(signals.v_Cuts.at(i)->GetBinContent(8))/(signals.v_Cuts.at(i)->GetBinContent(6));
    double hhCandEff=(signals.v_Cuts.at(i)->GetBinContent(10))/(signals.v_Cuts.at(i)->GetBinContent(8));
    double btagEff=(signals.v_Cuts.at(i)->GetBinContent(14))/(signals.v_Cuts.at(i)->GetBinContent(10));
    double SREff=(signals.v_Cuts.at(i)->GetBinContent(16))/(signals.v_Cuts.at(i)->GetBinContent(14));
    
    std::cout<<massPts[i]<<" | "<<triggerEff<<" | "<<vtypeEff<<" | "<<nCJetsEff<<" | "<<hhCandEff<<" | "<<btagEff<<" | "<<SREff<<std::endl;
  }
  std::cout<<" === === "<<std::endl;
}

void cumEff()
{
  int massPts[15]={270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  
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

void CutFlow()
{
  int massPts[15]={270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  
  TFile *glugluToX270=new TFile("Histograms_RadionToHH_4b_M-270_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX300=new TFile("Histograms_RadionToHH_4b_M-300_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX350=new TFile("Histograms_RadionToHH_4b_M-350_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX400=new TFile("Histograms_RadionToHH_4b_M-400_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX450=new TFile("Histograms_RadionToHH_4b_M-450_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX500=new TFile("Histograms_RadionToHH_4b_M-500_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX550=new TFile("Histograms_RadionToHH_4b_M-550_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX600=new TFile("Histograms_RadionToHH_4b_M-600_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX650=new TFile("Histograms_RadionToHH_4b_M-650_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX700=new TFile("Histograms_RadionToHH_4b_M-700_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX800=new TFile("Histograms_RadionToHH_4b_M-800_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX900=new TFile("Histograms_RadionToHH_4b_M-900_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX1000=new TFile("Histograms_RadionToHH_4b_M-1000_TuneZ2star_8TeV_FULLSIM.root");
  TFile *glugluToX1100=new TFile("Histograms_RadionToHH_4b_M-1100_TuneZ2star_8TeV_FULLSIM.root");
  
  pushBackHistograms(signals, glugluToX270);
  pushBackHistograms(signals, glugluToX300);
  pushBackHistograms(signals, glugluToX350);
  pushBackHistograms(signals, glugluToX400);
  pushBackHistograms(signals, glugluToX450);
  pushBackHistograms(signals, glugluToX500);
  pushBackHistograms(signals, glugluToX550);
  pushBackHistograms(signals, glugluToX600);
  pushBackHistograms(signals, glugluToX650);
  pushBackHistograms(signals, glugluToX700);
  pushBackHistograms(signals, glugluToX800);
  pushBackHistograms(signals, glugluToX900);
  pushBackHistograms(signals, glugluToX1000);
  pushBackHistograms(signals, glugluToX1100);
  
  TH1F *h_Init=new TH1F("h_Init", "h_Init", 88, 320, 1200);
  std::vector<TH1F *> h_Cut;
  
  // TH1F *h_Events2=(TH1F*)h_Init->Clone("h_Events2");
  TH1F *h_Events4=(TH1F*)h_Init->Clone("h_Events4");
  TH1F *h_Events6=(TH1F*)h_Init->Clone("h_Events6");
  TH1F *h_Events8=(TH1F*)h_Init->Clone("h_Events8");
  TH1F *h_Events10=(TH1F*)h_Init->Clone("h_Events10");
  TH1F *h_Events12=(TH1F*)h_Init->Clone("h_Events12");
  TH1F *h_Events14=(TH1F*)h_Init->Clone("h_Events14");
  TH1F *h_Events16=(TH1F*)h_Init->Clone("h_Events16");
  for (unsigned int i=0; i<signals.v_Cuts.size(); ++i)
  {
    h_Init->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_CountWithPU.at(i)->GetBinContent(1));
    // std::cout<<"signals.v_CountWithPU.at(i)->GetBinContent(1) = "<<.signals.v_CountWithPU.at(i)->GetBinContent(1)<<std::endl;
    // h_Events2->SetBinContent(i, signals.v_Cuts.at(i)->GetBinContent(2));
    h_Events4->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(4));
    h_Events6->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(6));
    h_Events8->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(8));
    h_Events10->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(10));
    h_Events12->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(12));
    h_Events14->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(14));
    h_Events16->SetBinContent(h_Init->FindBin(massPts[i]), signals.v_Cuts.at(i)->GetBinContent(16));
    
    // std::cout<<"m_X (GeV) = "<<massPts[i]<<", Efficiency = "<<signals.v_Cuts.at(i)->GetBinContent(16)/signals.v_CountWithPU.at(i)->GetBinContent(1)<<std::endl;
  }
  
  // TGraphAsymmErrors *g_Ae_2=new TGraphAsymmErrors(h_Events2, h_Init); g_Ae_2->SetTitle("Step 2 ntuplization efficiency");
  TGraphAsymmErrors *g_Ae_4=new TGraphAsymmErrors(h_Events4, h_Init); g_Ae_4->SetTitle("Trigger Efficiency"); g_Ae_4->SetLineColor(kViolet);
  TGraphAsymmErrors *g_Ae_6=new TGraphAsymmErrors(h_Events6, h_Init); g_Ae_6->SetTitle("Vtype efficiency"); g_Ae_6->SetLineColor(kOrange);
  TGraphAsymmErrors *g_Ae_8=new TGraphAsymmErrors(h_Events8, h_Init); g_Ae_8->SetTitle("4 bjets efficiency"); g_Ae_8->SetLineColor(kMagenta);
  TGraphAsymmErrors *g_Ae_10=new TGraphAsymmErrors(h_Events10, h_Init); g_Ae_10->SetTitle("HH Candidate efficiency"); g_Ae_10->SetLineColor(kGreen);
  TGraphAsymmErrors *g_Ae_12=new TGraphAsymmErrors(h_Events10, h_Init); g_Ae_12->SetTitle("H pT > 200 GeV"); g_Ae_12->SetLineColor(kCyan);
  TGraphAsymmErrors *g_Ae_14=new TGraphAsymmErrors(h_Events14, h_Init); g_Ae_14->SetTitle("btagging efficiency"); g_Ae_14->SetLineColor(kBlue);
  TGraphAsymmErrors *g_Ae_16=new TGraphAsymmErrors(h_Events16, h_Init); g_Ae_16->SetTitle("SR efficiency"); g_Ae_16->SetLineColor(kRed);
  
  // ATLAS curves
  double masses_ATLAS[8]={500, 600, 700, 800, 900, 1000, 1100};
  double btag_ATLAS[8]={0.078, 0.105, 0.118, 0.12, 0.121, 0.118, 0.1};
  double dijet_ATLAS[8]={0.015, 0.065, 0.095, 0.105, 0.11, 0.105, 0.095};
  double SR_ATLAS[8]={0.01, 0.035, 0.05, 0.055, 0.06, 0.06, 0.055};
  
  TGraph *g_ATLAS_btag=new TGraph(7, masses_ATLAS, btag_ATLAS); g_ATLAS_btag->SetLineWidth(2);
  TGraph *g_ATLAS_dijet=new TGraph(7, masses_ATLAS, dijet_ATLAS); g_ATLAS_dijet->SetLineWidth(2);
  TGraph *g_ATLAS_SR=new TGraph(7, masses_ATLAS, SR_ATLAS); g_ATLAS_SR->SetLineWidth(2);
  
  TCanvas *c_Ae=new TCanvas("c_Ae", "c_Ae", 1000, 700);
  g_Ae_8->SetMaximum(0.14); g_Ae_8->SetMinimum(0);
  // g_Ae_2->Draw("AL*");
  // g_Ae_4->Draw("AL*");
  // g_Ae_6->Draw("L* same");
  g_Ae_8->Draw("AL*");
  g_Ae_12->Draw("L* same");
  g_Ae_10->Draw("L* same");
  g_Ae_14->Draw("L* same");
  g_Ae_16->Draw("L* same");
  g_ATLAS_btag->Draw("L* same");
  g_ATLAS_dijet->Draw("L* same");
  g_ATLAS_SR->Draw("L* same");
  // c_Ae->SetLogy();
  TLegend *leg=new TLegend(0.7, 0.9, 1., 1.);
  leg->SetFillStyle(1); leg->SetFillColor(kWhite);
  leg->AddEntry(g_Ae_4, "Trigger");
  leg->AddEntry(g_Ae_6, "Vtype");
  leg->AddEntry(g_Ae_8, "bJets > 3");
  leg->AddEntry(g_Ae_10, "HH candidate");
  leg->AddEntry(g_Ae_12, "H p_{T} > 200 GeV");
  leg->AddEntry(g_Ae_14, "b-tagging");
  leg->AddEntry(g_Ae_16, "Signal Region");
  leg->Draw();
  c_Ae->Update();
  c_Ae->SaveAs("c_Ae.png");
  c_Ae->SaveAs("c_Ae.root");
  
  if (signaleff) signalEff();
  if (cumeff) cumEff();
  
  if (data_sets)
  {
    TFile *data_8TeV=new TFile("Histograms_BJetPlusX_Run2012BCD_Skim.root");
    pushBackHistograms(data, data_8TeV, false);
    /*
    int x[7], y[7];
    x[0]=1; y[0]=data.v_Cuts.at(0)->GetBinContent(2);
    x[1]=1; y[1]=data.v_Cuts.at(0)->GetBinContent(4);
    x[2]=1; y[2]=data.v_Cuts.at(0)->GetBinContent(6);
    x[3]=1; y[3]=data.v_Cuts.at(0)->GetBinContent(8);
    x[4]=1; y[4]=data.v_Cuts.at(0)->GetBinContent(10);
    x[5]=1; y[5]=data.v_Cuts.at(0)->GetBinContent(14);
    x[6]=1; y[6]=data.v_Cuts.at(0)->GetBinContent(16);
    
    TGraph *g_data=new TGraph(7, x, y);
    TCanvas *c_data=new TCanvas("c_data", "c_data", 1000, 700);
    TPad *p_2=new TPad("p_2", "p_2", 0.8, 0, 1, 1);
    TPad *p_1=new TPad("p_1", "p_1", 0, 0, 0.8, 1);
    p_1->Draw();
    p_2->Draw();
    p_1->cd();
    g_Ae_8->Draw("AL*");
    g_Ae_10->Draw("L* same");
    g_Ae_14->Draw("L* same");
    g_Ae_16->Draw("L* same");
    p_2->cd();
    // p_2->DrawFrame(0, 100, 1, g_data->SetMaximum(10000000));
    g_data->SetMinimum(100); g_data->GetXaxis()->SetRangeUser(0, 1.1);
    g_data->Draw("A*");
    p_2->SetLogy();
    p_1->cd();
    */
    
    TCanvas *c_data=new TCanvas("c_data", "c_data", 700, 700);
    data.v_Cuts.at(0)->SetTitle("Cut flow in Data");
    data.v_Cuts.at(0)->Draw();
    c_data->SetLogy();
    c_data->SaveAs("c_data.png");
    c_data->SaveAs("c_data.root");
    
  }
}
