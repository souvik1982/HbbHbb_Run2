#include "fittedFunctions_RunC.h"
//#include"fittedFunctions.h.GoodOld"
#include "../TDRStyle.h"
#include "test.h"

TString runName = "RunC";
//-log(1-CSV3+1.e-7

double TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return QuaJet_L1->Eval(sumpt)*QuaJet_CaloPt4->Eval(pt4)*QuaJet_CSV3->Eval(CSV3)*QuaJet_PFPt4->Eval(pt4);
}

double TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return QuaJet_L1Up->Eval(sumpt)*QuaJet_CaloPt4Up->Eval(pt4)*QuaJet_CSV3Up->Eval(CSV3)*QuaJet_PFPt4Up->Eval(pt4);
}

double TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return QuaJet_L1Down->Eval(sumpt)*QuaJet_CaloPt4Down->Eval(pt4)*QuaJet_CSV3Down->Eval(CSV3)*QuaJet_PFPt4Down->Eval(pt4);
}

void Quadplots_fit_test_singleBtag(){
    gStyle->SetOptStat(0);
    //    gROOT->SetBatch();
    setTDRStyle();

    TCanvas* c1 = new TCanvas("c1","c1",800,800);
    TPad * mainPad = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    mainPad->SetBottomMargin(0.05); // Upper and lower plot are joined
    // mainPad->SetGridx();         // Vertical grid

    mainPad->SetLeftMargin(0.13);
    mainPad->Draw();             // Draw the upper pad: pad1
    // mainPad->cd();               // pad1 becomes the current pad

    TPad * ratioPad = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
    ratioPad->SetTopMargin(0.03);
    ratioPad->SetBottomMargin(0.3);
    //    ratioPad->SetGridx(); // vertical grid

    ratioPad->SetLeftMargin(0.13);
    ratioPad->Draw();
   // c1->SetGridx();
   // c1->SetGridy();

    //    TFile *_file0 = TFile::Open("SingleElectronVBF.root");
    //  TFile *_file0 = TFile::Open("ZvvHighPt_V20_SingleMuon.root");
    TString fileName = "root://cmseos.fnal.gov//store/user/lpchbb/HeppyNtuples/V23/SingleMuon" + runName + ".root";
   // TString fileName = "../PreselectedWithoutRegression/Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root";
    TFile *_file0 = TFile::Open(fileName);
    TTree* tree = (TTree*) _file0->Get("tree");
    TString outName; 
    TH1* h,*h1,*hR, *hU,*hD;

  /*  c1->SetLogy();
    gPad->RedrawAxis();
  //  mainPad->cd();   
  //  tree->Draw("run  >> h(200,275600,276500)","HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v","");
    tree->Draw("run  >> h(200,275600,276500)","","");
    tree->Draw("run  >> h1(200,275600,276500)","HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4","same");
    tree->Draw("run  >> h2(200,275600,276500)","!HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4","same");

    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kRed);h->GetYaxis()->SetRangeUser(1e3,10e6);
    h = (TProfile*) gDirectory->Get("h2");h->SetLineColor(kBlack);//h->SetMaximum(2.0*h->GetMaximum());

    outName = "check_full_" + runName;
    h->GetXaxis()->SetTitle("Run Number");
    c1->SaveAs( outName+"trigger.pdf");
*/

    Long64_t maxEv = tree->GetEntries(); 

    //////////////////////////////////////////////////
    // plots for the single b-tag trigger, starting from (HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30)
    //////////////////////////////////////////////////
    gPad->RedrawAxis();
    mainPad->cd();   
    tree->Draw("Jet_pt[3]  >> h(25,0,200)"," TurnOnQuad(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","",maxEv);
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("Jet_pt[3] >> h1(25,0,1)"," 1.0001*(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v && (HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same",maxEv);
    h1 = (TProfile*) gDirectory->Get("h1");
    tree->Draw("Jet_pt[3]  >> h2(25,0,200)"," TurnOnQuadUp(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);
    tree->Draw("Jet_pt[3]  >> h3(25,0,200)"," TurnOnQuadDown(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);

    hU=(TProfile*) gDirectory->Get("h2");
    hU->SetLineStyle(2);
    hU->SetLineColor(kBlack);
    hD=(TProfile*) gDirectory->Get("h3");
    hD->SetLineStyle(2);
    hD->SetLineColor(kBlack);

    h1->SetLineColor( kRed );
    h1->GetYaxis()->SetLabelSize(20);
    h1->GetYaxis()->SetTitleSize(20); 
    h1->GetXaxis()->SetLabelSize(20);


    hR = (TH1*) h->Clone("hR");
    hR->Divide(h1);
    hRU = (TH1*) hU->Clone("hRU");
    hRU->Divide(h1);
    hRD = (TH1*) hD->Clone("hRD");
    hRD->Divide(h1);

    ratioPad->cd();
    hR->Draw("");
    hRU->Draw("Lhistsame");
    hRD->Draw("Lhistsame");


    hR->GetXaxis()->SetLabelFont(43);
    hR->GetXaxis()->SetLabelSize(20);
    hR->GetYaxis()->SetLabelFont(43);
    hR->GetYaxis()->SetLabelSize(20);
    hR ->GetXaxis()->SetTitleSize(25);
    hR->GetYaxis()->SetTitleSize(25);

    hR ->GetYaxis()->SetTitleOffset(1.5);
    hR->GetYaxis()->SetTitleFont(43);

    hR->GetXaxis()->SetTitleOffset(3);
    hR->GetXaxis()->SetTitleFont(43);
    hR->GetYaxis()->SetNdivisions(50205);
    hR->GetYaxis()->SetRangeUser(0.5,1.5);
    hR->GetYaxis()->SetTitle("Ratio");
    hR->GetXaxis()->SetTitle("p_{T}^{3}");
    TLine* horiz_line = new TLine(0,1,200,1);
    horiz_line->DrawLine(0,1,200,1);

    // hR->GetXaxis()->SetTitleSize(18);  
    gPad->RedrawAxis();

    outName = "check_full_" + runName;
    c1->SaveAs( outName+"_pt4_single.pdf");
    //  c1->SaveAs("check_full_pt4_single.C");

    // return;
    //
    mainPad->cd();
    tree->Draw("MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)))  >> h(25,0,1)"," TurnOnQuad(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","",maxEv);
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))) >> h1(25,0,1)"," 1.0001*(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v && (HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same",maxEv);
    h1 = (TProfile*) gDirectory->Get("h1");
    tree->Draw("MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)))  >> h2(25,0,200)"," TurnOnQuadUp(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);
    tree->Draw("MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)))  >> h3(25,0,200)"," TurnOnQuadDown(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);

    hU=(TProfile*) gDirectory->Get("h2");
    hU->SetLineStyle(2);
    hU->SetLineColor(kBlack);
    hD=(TProfile*) gDirectory->Get("h3");
    hD->SetLineStyle(2);
    hD->SetLineColor(kBlack);



    h1->SetLineColor( kRed );
    h1->GetYaxis()->SetLabelSize(20);
    h1->GetYaxis()->SetTitleSize(20); 
    h1->GetXaxis()->SetLabelSize(20);



    hR = (TH1*) h->Clone("hR");
    hR->Divide(h1);
    hRU = (TH1*) hU->Clone("hRU");
    hRU->Divide(h1);
    hRD = (TH1*) hD->Clone("hRD");
    hRD->Divide(h1);

    ratioPad->cd();
    hR->Draw("");
    hRU->Draw("Lhistsame");
    hRD->Draw("Lhistsame");

    hR->GetXaxis()->SetLabelFont(43);
    hR->GetXaxis()->SetLabelSize(20);
    hR->GetYaxis()->SetLabelFont(43);
    hR->GetYaxis()->SetLabelSize(20);
    hR ->GetXaxis()->SetTitleSize(25);
    hR->GetYaxis()->SetTitleSize(25);

    hR ->GetYaxis()->SetTitleOffset(1.5);
    hR->GetYaxis()->SetTitleFont(43);

    hR->GetXaxis()->SetTitleOffset(3);
    hR->GetXaxis()->SetTitleFont(43);
    hR->GetYaxis()->SetNdivisions(50205);
    hR->GetYaxis()->SetRangeUser(0.5,1.5);
    hR->GetYaxis()->SetTitle("Ratio");
    hR->GetXaxis()->SetTitle("CSV^{3}");
    horiz_line->DrawLine(0,1,1,1);
    gPad->RedrawAxis();
    c1->SaveAs( outName+"_CSV3_single.pdf");
    //  c1->SaveAs("check_full_CSV3_single.C");

    mainPad->cd();
    tree->Draw("Jet_eta[0]  >> h(25,-4,+4)"," TurnOnQuad(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","",maxEv);
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("Jet_eta[0] >> h1(25,0,1)"," 1.0001*(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v && (HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same",maxEv);
    h1 = (TProfile*) gDirectory->Get("h1");

    tree->Draw("Jet_eta[0] >> h2(25,0,200)"," TurnOnQuadUp(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);
    tree->Draw("Jet_eta[0] >> h3(25,0,200)"," TurnOnQuadDown(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);

    hU=(TProfile*) gDirectory->Get("h2");
    hU->SetLineStyle(2);
    hU->SetLineColor(kBlack);
    hD=(TProfile*) gDirectory->Get("h3");
    hD->SetLineStyle(2);
    hD->SetLineColor(kBlack);



    h1->SetLineColor( kRed );
    h1->GetYaxis()->SetLabelSize(20);
    h1->GetYaxis()->SetTitleSize(20); 
    h1->GetXaxis()->SetLabelSize(20);


    hR = (TH1*) h->Clone("hR");
    hR->Divide(h1);
    hRU = (TH1*) hU->Clone("hRU");
    hRU->Divide(h1);
    hRD = (TH1*) hD->Clone("hRD");
    hRD->Divide(h1);

    ratioPad->cd();
    hR->Draw("");
    hRU->Draw("Lhistsame");
    hRD->Draw("Lhistsame");


    hR->GetXaxis()->SetLabelFont(43);
    hR->GetXaxis()->SetLabelSize(20);
    hR->GetYaxis()->SetLabelFont(43);
    hR->GetYaxis()->SetLabelSize(20);
    hR ->GetXaxis()->SetTitleSize(25);
    hR->GetYaxis()->SetTitleSize(25);

    hR ->GetYaxis()->SetTitleOffset(1.5);
    hR->GetYaxis()->SetTitleFont(43);

    hR->GetXaxis()->SetTitleOffset(3);
    hR->GetXaxis()->SetTitleFont(43);
    hR->GetYaxis()->SetNdivisions(50205);

    hR->GetYaxis()->SetTitle("Ratio");
    hR->GetXaxis()->SetTitle("#eta^1");
    horiz_line->DrawLine(-4,1,4,1);
    hR->GetYaxis()->SetRangeUser(0.5,1.5);

    gPad->RedrawAxis();
    c1->SaveAs( outName+"_eta1_single.pdf");
    //c1->SaveAs("check_full_eta0_single.C");
    //*/


    mainPad->cd();
    tree->Draw("Jet_pt[1]  >> h(25,0,200)"," TurnOnQuad(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","",maxEv);
    h = (TProfile*) gDirectory->Get("h");h->SetLineColor(kBlack);h->SetMaximum(2.0*h->GetMaximum());
    tree->Draw("Jet_pt[1] >> h1(25,0,1)"," 1.0001*(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v && (HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4))","same",maxEv);
    h1 = (TProfile*) gDirectory->Get("h1");
    tree->Draw("Jet_pt[1]  >> h2(25,0,200)"," TurnOnQuadUp(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);
    tree->Draw("Jet_pt[1]  >> h3(25,0,200)"," TurnOnQuadDown(Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3], Sum$(Pt4(Jet_pt,Jet_eta,1,Iteration$,Length$)), Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)), min(MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV)&&Jet_btagCSV!=MaxIf$(Jet_btagCSV,Jet_btagCSV!=Max$(Jet_btagCSV))),1-1.e-7))*(HLT_BIT_HLT_IsoMu24_v && Jet_puId>=4 && Alt$(Jet_pt[3],0)>30 && abs(Jet_eta[0])<2.4 && abs(Jet_eta[1])<2.4 && abs(Jet_eta[2])<2.4 && abs(Jet_eta[3])<2.4)","Lhistsame",maxEv);

    hU=(TProfile*) gDirectory->Get("h2");
    hU->SetLineStyle(2);
    hU->SetLineColor(kBlack);
    hD=(TProfile*) gDirectory->Get("h3");
    hD->SetLineStyle(2);
    hD->SetLineColor(kBlack);


    h1->SetLineColor( kRed );
    h1->GetYaxis()->SetLabelSize(20);
    h1->GetYaxis()->SetTitleSize(20); 
    h1->GetXaxis()->SetLabelSize(20);

    hR = (TH1*) h->Clone("hR");
    hR->Divide(h1);
    hRU = (TH1*) hU->Clone("hRU");
    hRU->Divide(h1);
    hRD = (TH1*) hD->Clone("hRD");
    hRD->Divide(h1);

    ratioPad->cd();
    hR->Draw("");
    hRU->Draw("Lhistsame");
    hRD->Draw("Lhistsame");

    hR->GetXaxis()->SetLabelFont(43);
    hR->GetXaxis()->SetLabelSize(20);
    hR->GetYaxis()->SetLabelFont(43);
    hR->GetYaxis()->SetLabelSize(20);
    hR ->GetXaxis()->SetTitleSize(25);
    hR->GetYaxis()->SetTitleSize(25);

    hR ->GetYaxis()->SetTitleOffset(1.5);
    hR->GetYaxis()->SetTitleFont(43);

    hR->GetXaxis()->SetTitleOffset(3);
    hR->GetXaxis()->SetTitleFont(43);
    hR->GetYaxis()->SetNdivisions(50205);

    hR->GetYaxis()->SetTitle("Ratio");
    hR->GetXaxis()->SetTitle("p_{T}^{2}");
    horiz_line->DrawLine(0,1,200,1);
    hR->GetYaxis()->SetRangeUser(0.5,1.5);

    gPad->RedrawAxis();
    c1->SaveAs( outName+"_pt2_single.pdf");

}
