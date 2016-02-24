#include"fittedFunctions.h"
//#include"fittedFunctions.h.GoodOld"

void Doubleplots_fit_test_singleBtag(){
    gStyle->SetOptStat(0);
//    gROOT->SetBatch();

    TCanvas* c1 = new TCanvas("c1","c1");
    c1->SetGridx();
    c1->SetGridy();

//    TFile *_file0 = TFile::Open("SingleElectronVBF.root");
    TFile *_file0 = TFile::Open("../SingleElectronVBF.root");
    TTree* tree = (TTree*) _file0->Get("tree");

    //////////////////////////////////////////////////
    // plots for the single b-tag trigger, starting from (HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30)
    //////////////////////////////////////////////////

    tree->Draw("Jet_pt[3]  >> h(25,0,200)"," DoubleTriggerWeight(Jet_pt[0], Jet_pt[1], Jet_pt[2], Jet_pt[3], min(CSV[2],1-1.e-7))*(HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","");
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("Jet_pt[3]"," 1.0001*(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV0p67_v && (HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same");

    c1->SaveAs("check_full_pt4_single.png");
    c1->SaveAs("check_full_pt4_single.C");

    tree->Draw("CSV[2]  >> h(25,0,1)"," DoubleTriggerWeight(Jet_pt[0], Jet_pt[1], Jet_pt[2], Jet_pt[3], min(CSV[2],1-1.e-7))*(HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","");
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("CSV[2]"," 1.0001*(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV0p67_v && (HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same");

    c1->SaveAs("check_full_CSV3_single.png");
    c1->SaveAs("check_full_CSV3_single.C");

    tree->Draw("Jet_eta[0]  >> h(25,-4,+4)"," DoubleTriggerWeight(Jet_pt[0], Jet_pt[1], Jet_pt[2], Jet_pt[3], min(CSV[2],1-1.e-7))*(HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","");
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("Jet_eta[0]"," 1.0001*(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV0p67_v && (HLT_BIT_HLT_Ele23_WPLoose_Gsf_v && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same");

    c1->SaveAs("check_full_eta0_single.png");
    c1->SaveAs("check_full_eta0_single.C");


}
