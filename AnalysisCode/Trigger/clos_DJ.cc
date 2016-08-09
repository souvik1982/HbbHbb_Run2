#include "fittedFunctions2_RunD.h"
//#include"fittedFunctions.h.GoodOld"
#include "../TDRStyle.h"
#include "test.h"

TString runName = "RunD";

double TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return DoubleJet_L1->Eval(sumpt)*DoubleJet_CaloPt4->Eval(pt4)*DoubleJet_CaloPt2->Eval(pt2)*DoubleJet_CSV3->Eval(CSV3)*DoubleJet_PFPt4->Eval(pt4)*DoubleJet_PFPt2->Eval(pt2);
}

double TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return DoubleJet_L1Up->Eval(sumpt)*DoubleJet_CaloPt4Up->Eval(pt4)*DoubleJet_CaloPt2Up->Eval(pt2)*DoubleJet_CSV3Up->Eval(CSV3)*DoubleJet_PFPt4Up->Eval(pt4)*DoubleJet_PFPt2Up->Eval(pt2);
}

double TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return DoubleJet_L1Down->Eval(sumpt)*DoubleJet_CaloPt4Down->Eval(pt4)*DoubleJet_CaloPt2Down->Eval(pt2)*DoubleJet_CSV3Down->Eval(CSV3)*DoubleJet_PFPt4Down->Eval(pt4)*DoubleJet_PFPt2Down->Eval(pt2);
}


void SetHistos( TH1* histos[4], TString name, int nbin, float binMin, float binMax );
void FillHistos( TH1 * histos[4], float variable, float sumpt, float pt2, float pt4, float CSV3, int pass_trigger );
void PlotHistos( TH1* histos[4], TString name );

void clos_DJ()
{
  gStyle->SetOptStat(0);
    //    gROOT->SetBatch();
    setTDRStyle();


    TString fileName = "root://cmseos.fnal.gov//store/user/lpchbb/HeppyNtuples/V23/SingleMuon" + runName + ".root";
    TFile *_file0 = TFile::Open(fileName);
    TTree* tree = (TTree*) _file0->Get("tree");
    TH1*hPt4[4]; SetHistos(hPt4,"hPt4",50,0,200);
    TH1*hCSV[4]; SetHistos(hCSV,"hCSV",50,0,1);
    TH1*hEta[4]; SetHistos(hEta,"hEta",80,-4,4);
    TH1*hPt2[4]; SetHistos(hPt2,"hPt2",50,0,200);

    int nJet, Jet_puId[100], HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_IsoMu24_v;
    float  Jet_pt[100], Jet_eta[100], Jet_btagCSV[100];
    tree->SetBranchAddress("Jet_pt", &(Jet_pt)); tree->SetBranchStatus("Jet_pt", 1);
    tree->SetBranchAddress("Jet_eta", &(Jet_eta)); tree->SetBranchStatus("Jet_eta", 1);
    tree->SetBranchAddress("Jet_btagCSV", &(Jet_btagCSV)); tree->SetBranchStatus("Jet_btagCSV", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_IsoMu24_v", &(HLT_BIT_HLT_IsoMu24_v)); tree->SetBranchStatus("HLT_BIT_HLT_IsoMu24_v", 1);
    tree->SetBranchAddress("Jet_puId", &(Jet_puId)); tree->SetBranchStatus("Jet_puId", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", &(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v)); tree->SetBranchStatus("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", 1);
  tree->SetBranchAddress("nJet", &(nJet)); tree->SetBranchStatus("nJet", 1);
 
    Long64_t nEvents = tree->GetEntries(); 
    int shout = nEvents/10;
    for (int i=0; i<nEvents; ++i)
    {
        tree->GetEvent(i);         
        if( i >= shout ){ std::cout << "Event " << i << "/" << nEvents << ", shout: " << shout << std::endl; shout=shout+nEvents/10; }
        if( ! ( HLT_BIT_HLT_IsoMu24_v  ) ) continue;
        int GoodJets[100]; int counter = 0;
    //    std::sort( Jet_pt, Jet_pt + nJet, std::greater<float>());
        for( int j=0; j<nJet; ++j ) if( fabs(Jet_eta[j])<2.4 && (Jet_puId[j]>=4)){ GoodJets[counter]=j; counter++; }
        if( counter < 4 ) continue; // at least 4 good jets
        float pt4 = Jet_pt[GoodJets[3]];
        if( pt4 < 30 ) continue;
        float pt2 = Jet_pt[GoodJets[1]];
        float eta1 = Jet_eta[GoodJets[0]];
        float sumpt = Jet_pt[0]+Jet_pt[1]+Jet_pt[2]+Jet_pt[3];
        float CSV[4] = { Jet_btagCSV[GoodJets[0]], Jet_btagCSV[GoodJets[1]], Jet_btagCSV[GoodJets[2]], Jet_btagCSV[GoodJets[3]] };
        std::sort( CSV, CSV+4, std::greater<float>() );
        float CSV3 = CSV[2];
        FillHistos( hPt4, pt4, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v );
        FillHistos( hCSV, CSV3, sumpt, pt2, pt4, CSV3,HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v  );
        FillHistos( hEta, eta1, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v );
        FillHistos( hPt2, pt2, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v );
    }

    PlotHistos( hPt4, "pt4");
    PlotHistos( hCSV, "CSV");
    PlotHistos( hEta, "eta1");    
    PlotHistos( hPt2, "pt2");
}

void PlotHistos( TH1* histos[4], TString name )
{
    TCanvas c("c"+name,"c"+name,800,800);
    c.cd();
    TPad  mainPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    mainPad.SetBottomMargin(0.05); // Upper and lower plot are joined
    mainPad.SetLeftMargin(0.13);
    mainPad.Draw();             // Draw the upper pad: pad1
    TPad ratioPad("pad2", "pad2", 0, 0, 1, 0.3);
    ratioPad.SetTopMargin(0.03);
    ratioPad.SetBottomMargin(0.3);
    ratioPad.SetLeftMargin(0.13);
    ratioPad.Draw();

    mainPad.cd();
    histos[0]->Draw(""); histos[1]->Draw("histsame"); histos[2]->Draw("Lhistsame"); histos[3]->Draw("Lhistsame");
    histos[0]->SetLineColor( kRed );
    histos[0]->GetYaxis()->SetLabelSize(20);
    histos[0]->GetYaxis()->SetTitleSize(22); 
    histos[0]->GetXaxis()->SetLabelSize(20);
    histos[0]->GetXaxis()->SetTitleSize(22); 
    histos[0]->GetXaxis()->SetLabelSize(20);
    histos[0]->GetXaxis()->SetLabelFont(43);
    histos[0]->GetYaxis()->SetLabelFont(43);
    histos[1]->SetLineColor(kBlack);histos[1]->SetMaximum(2.0*histos[1]->GetMaximum());
    histos[2]->SetLineStyle(2); histos[2]->SetLineColor(kBlack);
    histos[3]->SetLineStyle(3); histos[3]->SetLineColor(kBlack);

    TH1* hR = (TH1*) histos[1]->Clone("hR"+name);
    hR->Divide(histos[0]);
    TH1* hRU = (TH1*) histos[2]->Clone("hRU"+name);
    hRU->Divide(histos[0]);
    TH1* hRD = (TH1*) histos[3]->Clone("hRD"+name);
    hRD->Divide(histos[0]);

    ratioPad.cd();
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
    horiz_line->DrawLine(hR->GetBinCenter(1),1,hR->GetBinCenter(hR->GetNbinsX()),1);

    // hR->GetXaxis()->SetTitleSize(18);  
    gPad->RedrawAxis();

    TString outName = "check_full_DJ_" + runName;
    c.SaveAs( outName+"_"+name+".pdf");
}
        
void FillHistos( TH1 * histos[4], float variable, float sumpt, float pt2, float pt4, float CSV3, int pass_trigger )
{
    if( pass_trigger ){ histos[0]->Fill( variable, 1 ); } 
    histos[1]->Fill( variable, TurnOnDouble( sumpt, pt2, pt4, CSV3 ) ); 
    histos[2]->Fill( variable, TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 ) ); 
    histos[3]->Fill( variable, TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 ) ); 
}
   
void SetHistos( TH1* histos[4], TString name, int nbin, float binMin, float binMax )
{   
    histos[0] = new TH1F( name + "T", name + "T", nbin, binMin, binMax );
    histos[0]->Sumw2();
    histos[1] = new TH1F( name + "E", name + "E", nbin, binMin, binMax );
    histos[1]->Sumw2();
    histos[2] = new TH1F( name + "EU", name + "EU", nbin, binMin, binMax );
    histos[2]->Sumw2();
    histos[3] = new TH1F( name + "ED", name + "ED", nbin, binMin, binMax );
    histos[3]->Sumw2();
}
