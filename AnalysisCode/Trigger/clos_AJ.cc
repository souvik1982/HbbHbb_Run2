#include "fittedFunctions_.h"
#include "fittedFunctions2_.h"
#include "fittedFunctions3_.h"
//#include"fittedFunctions.h.GoodOld"
#include "../TDRStyle.h"
#include "test.h"

TString runName = "";
TString fitName = "_v0C_NC";

double TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = DoubleJet_CaloPt4l->Eval(pt4);
    else calopt4 = DoubleJet_CaloPt4h->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = DoubleJet_L1l->Eval(sumpt);
    else L1=DoubleJet_L1h->Eval(sumpt);
	return L1*calopt4*DoubleJet_CaloPt2->Eval(pt2)*DoubleJet_CSV3->Eval(CSV3)*DoubleJet_PFPt4->Eval(pt4)*DoubleJet_PFPt2->Eval(pt2);
}

double TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = DoubleJet_CaloPt4lUp->Eval(pt4);
    else calopt4 = DoubleJet_CaloPt4hUp->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = DoubleJet_L1lUp->Eval(sumpt);
    else L1=DoubleJet_L1hUp->Eval(sumpt);
	return L1*calopt4*DoubleJet_CaloPt2Up->Eval(pt2)*DoubleJet_CSV3Up->Eval(CSV3)*DoubleJet_PFPt4Up->Eval(pt4)*DoubleJet_PFPt2Up->Eval(pt2);
};

double TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = DoubleJet_CaloPt4lDown->Eval(pt4);
    else calopt4 = DoubleJet_CaloPt4hDown->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = DoubleJet_L1lDown->Eval(sumpt);
    else L1=DoubleJet_L1hDown->Eval(sumpt);
	return L1*calopt4*DoubleJet_CaloPt2Down->Eval(pt2)*DoubleJet_CSV3Down->Eval(CSV3)*DoubleJet_PFPt4Down->Eval(pt4)*DoubleJet_PFPt2Down->Eval(pt2);
}

double TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QuaJet_CaloPt4l->Eval(pt4);
    else calopt4 = QuaJet_CaloPt4h->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QuaJet_L1l->Eval(sumpt);
    else L1=QuaJet_L1h->Eval(sumpt);
	return L1*calopt4*QuaJet_CSV3->Eval(CSV3)*QuaJet_PFPt4->Eval(pt4);
}

double TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QuaJet_CaloPt4lUp->Eval(pt4);
    else calopt4 = QuaJet_CaloPt4hUp->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QuaJet_L1lUp->Eval(sumpt);
    else L1=QuaJet_L1hUp->Eval(sumpt);
	return L1*calopt4*QuaJet_CSV3Up->Eval(CSV3)*QuaJet_PFPt4Up->Eval(pt4);
}

double TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QuaJet_CaloPt4lDown->Eval(pt4);
    else calopt4 = QuaJet_CaloPt4hDown->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QuaJet_L1lDown->Eval(sumpt);
    else L1=QuaJet_L1hDown->Eval(sumpt);
	return L1*calopt4*QuaJet_CSV3Down->Eval(CSV3)*QuaJet_PFPt4Down->Eval(pt4);
}

double QaD_TurnOnDouble(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4l->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4h->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1l->Eval(sumpt);
    else L1=QaD_DoubleJet_L1h->Eval(sumpt);
	return L1*calopt4*QaD_DoubleJet_CaloPt2->Eval(pt2)*QaD_DoubleJet_CSV3->Eval(CSV3)*QaD_DoubleJet_PFPt4->Eval(pt4)*QaD_DoubleJet_PFPt2->Eval(pt2);
}

double QaD_TurnOnDoubleUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4lUp->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4hUp->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1lUp->Eval(sumpt);
    else L1=QaD_DoubleJet_L1hUp->Eval(sumpt);
	return L1*calopt4*QaD_DoubleJet_CaloPt2Up->Eval(pt2)*QaD_DoubleJet_CSV3Up->Eval(CSV3)*QaD_DoubleJet_PFPt4Up->Eval(pt4)*QaD_DoubleJet_PFPt2Up->Eval(pt2);
};

double QaD_TurnOnDoubleDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<45) calopt4 = QaD_DoubleJet_CaloPt4lDown->Eval(pt4);
    else calopt4 = QaD_DoubleJet_CaloPt4hDown->Eval(pt4);
    float L1;
    if(sumpt<120) L1 = QaD_DoubleJet_L1lDown->Eval(sumpt);
    else L1=QaD_DoubleJet_L1hDown->Eval(sumpt);
	return L1*calopt4*QaD_DoubleJet_CaloPt2Down->Eval(pt2)*QaD_DoubleJet_CSV3Down->Eval(CSV3)*QaD_DoubleJet_PFPt4Down->Eval(pt4)*QaD_DoubleJet_PFPt2Down->Eval(pt2);
}

double QaD_TurnOnQuad(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QaD_QuaJet_CaloPt4l->Eval(pt4);
    else calopt4 = QaD_QuaJet_CaloPt4h->Eval(pt4);
    float L1;
    if(sumpt<210) L1 = QaD_QuaJet_L1l->Eval(sumpt);
    else L1=QaD_QuaJet_L1h->Eval(sumpt);
	return L1*calopt4*QaD_QuaJet_CSV3->Eval(CSV3)*QaD_QuaJet_PFPt4->Eval(pt4);
}

double QaD_TurnOnQuadUp(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QaD_QuaJet_CaloPt4lUp->Eval(pt4);
    else calopt4 = QaD_QuaJet_CaloPt4hUp->Eval(pt4);
    float L1;
    if(sumpt<210) L1 = QaD_QuaJet_L1lUp->Eval(sumpt);
    else L1=QaD_QuaJet_L1hUp->Eval(sumpt);
	return L1*calopt4*QaD_QuaJet_CSV3Up->Eval(CSV3)*QaD_QuaJet_PFPt4Up->Eval(pt4);
}

double QaD_TurnOnQuadDown(float sumpt, float pt2, float pt4, float CSV3) {
	if(isnan(CSV3)) CSV3=0;
        CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
    float calopt4;
    if(pt4<60) calopt4 = QaD_QuaJet_CaloPt4lDown->Eval(pt4);
    else calopt4 = QaD_QuaJet_CaloPt4hDown->Eval(pt4);
    float L1;
    if(sumpt<210) L1 = QaD_QuaJet_L1lDown->Eval(sumpt);
    else L1=QaD_QuaJet_L1hDown->Eval(sumpt);
	return L1*calopt4*QaD_QuaJet_CSV3Down->Eval(CSV3)*QaD_QuaJet_PFPt4Down->Eval(pt4);
}


void SetHistos( TH1* histos[4], TString name, int nbin, float binMin, float binMax );
void FillHistos( TH1 * histos[4], float variable, float sumpt, float pt2, float pt4, float CSV3, int pass_trigger1, int pass_trigger2 );
void PlotHistos( TH1* histos[4], TString name, TString XAxis, TString Title  );
void myText(  Double_t x, Double_t y, int lStyle,const char *text, float tsize, float lSize=0.05 );

void clos_AJ()
{
  gStyle->SetOptStat(0);
    //    gROOT->SetBatch();
    setTDRStyle();


    //TString fileName = "root://cmseos.fnal.gov//store/user/lpchbb/HeppyNtuples/V23/SingleMuon" + runName + ".root";
   TString fileName = "SingleMuonSkimmed" + runName + ".root";

    TFile *_file0 = TFile::Open(fileName);
    TTree* tree = (TTree*) _file0->Get("tree");
    TH1*hPt4[4]; SetHistos(hPt4,"hPt4",50,0,200);
    TH1*hCSV[4]; SetHistos(hCSV,"hCSV",50,0,1);
    TH1*hEta[4]; SetHistos(hEta,"hEta",80,-4,4);
    TH1*hPt2[4]; SetHistos(hPt2,"hPt2",50,0,200);
    TH1*hPt3[4]; SetHistos(hPt3,"hPt3",50,0,200);
    TH1*hPt5[4]; SetHistos(hPt5,"hPt5",50,0,200);

    int nJet, Jet_puId[100], HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_IsoMu24_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v;
    float  Jet_pt[100], Jet_eta[100], Jet_btagCSV[100], Vtype, CSVsorted[100], Jet_btagCMVAV2[100];
    tree->SetBranchAddress("Jet_pt", &(Jet_pt)); tree->SetBranchStatus("Jet_pt", 1);
    tree->SetBranchAddress("Jet_eta", &(Jet_eta)); tree->SetBranchStatus("Jet_eta", 1);
    tree->SetBranchAddress("Jet_btagCSV", &(Jet_btagCSV)); tree->SetBranchStatus("Jet_btagCSV", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_IsoMu24_v", &(HLT_BIT_HLT_IsoMu24_v)); tree->SetBranchStatus("HLT_BIT_HLT_IsoMu24_v", 1);
    tree->SetBranchAddress("Jet_puId", &(Jet_puId)); tree->SetBranchStatus("Jet_puId", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", &(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v)); tree->SetBranchStatus("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v", &(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v)); tree->SetBranchStatus("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v", 1);
  tree->SetBranchAddress("nJet", &(nJet)); tree->SetBranchStatus("nJet", 1);
   tree->SetBranchAddress("CSVsorted", &(CSVsorted)); tree->SetBranchStatus("CSVsorted", 1);
  tree->SetBranchAddress("Vtype", &(Vtype)); tree->SetBranchStatus("Vtype", 1); 
   tree->SetBranchAddress("Jet_btagCMVAV2", &(Jet_btagCMVAV2)); tree->SetBranchStatus("Jet_btagCMVAV2", 1);

    Long64_t nEvents = tree->GetEntries(); 
    int shout = nEvents/10;
    for (int i=0; i<nEvents; ++i)
    {
        tree->GetEvent(i);         
        if( i >= shout ){ std::cout << "Event " << i << "/" << nEvents << ", shout: " << shout << std::endl; shout=shout+nEvents/10; }
        if( ! ( HLT_BIT_HLT_IsoMu24_v  && Vtype == 2  ) ) continue;
        int GoodJets[100]; int counter = 0;
       float CSV[100], CMVAV[100];
    //    std::sort( Jet_pt, Jet_pt + nJet, std::greater<float>());
        for( int j=0; j<nJet; ++j ) if( fabs(Jet_eta[j])<2.6 && (Jet_puId[j]>=4)){ GoodJets[counter]=j; CSV[counter]=Jet_btagCSV[j]; CMVAV[counter]=Jet_btagCMVAV2[j]; counter++; }
        if( counter < 4 ) continue; // at least 4 good jets
        float pt4 = Jet_pt[GoodJets[3]];    
        if( pt4 < 30) continue;
        float pt2 = Jet_pt[GoodJets[1]]; float pt3 = Jet_pt[GoodJets[2]]; float pt5 = Jet_pt[GoodJets[4]];
        float eta1 = Jet_eta[GoodJets[0]];
        float sumpt = Jet_pt[GoodJets[1]]+Jet_pt[GoodJets[2]]+Jet_pt[GoodJets[3]];
       // float CSV[4] = { Jet_btagCSV[GoodJets[0]], Jet_btagCSV[GoodJets[1]], Jet_btagCSV[GoodJets[2]], Jet_btagCSV[GoodJets[3]] };
        std::sort( CSV, CSV+counter, std::greater<float>() );
        std::sort( CMVAV, CMVAV+counter, std::greater<float>() );
        float CSV3 = CSV[2];
       // if( CSV[3] < 0.8 ) continue;
           if( CSV[2] < 0.6 ) continue;
    //    if( CMVAV[3] < 0.185 ) continue;
        FillHistos( hPt4, pt4, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v );
        FillHistos( hCSV, CSV3, sumpt, pt2, pt4, CSV3,HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v  );
        FillHistos( hEta, eta1, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v );
        FillHistos( hPt2, pt2, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v );
        FillHistos( hPt3, pt3, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v );
        FillHistos( hPt5, pt5, sumpt, pt2, pt4, CSV3, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v, HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v );
    }

    TString title =  "QuadJet||DoubleJet Trigger Closure";
    PlotHistos( hPt4, "pt4", "p_{T}^{4}", title);
    PlotHistos( hCSV, "CSV", "CSV^{3}", title);
    PlotHistos( hEta, "eta1", "#eta^{1}", title);    
    PlotHistos( hPt2, "pt2", "p_{T}^{2}",title);
    PlotHistos( hPt3, "pt3", "p_{T}^{3}",title);
    PlotHistos( hPt5, "pt5", "p_{T}^{5}",title);
}

void PlotHistos( TH1* histos[4], TString name, TString XAxis, TString Title  )
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
    TLegend *leg  = new TLegend(0.5,0.8,0.8,0.9);
    histos[0]->SetTitle(Title);
    histos[0]->Draw(""); histos[1]->Draw("histsame"); histos[2]->Draw("Lhistsame"); histos[3]->Draw("Lhistsame");
    histos[0]->SetLineColor( kRed );
    histos[0]->GetYaxis()->SetLabelSize(20);
    histos[0]->GetYaxis()->SetTitleSize(22); 
    histos[0]->GetXaxis()->SetLabelSize(20);
    histos[0]->GetXaxis()->SetTitleSize(22); 
    histos[0]->GetXaxis()->SetLabelSize(20);
    histos[0]->GetXaxis()->SetLabelFont(43);
    histos[0]->GetYaxis()->SetLabelFont(43); leg->AddEntry( histos[0], "Triggered","LE" );
    histos[1]->SetLineColor(kBlack);histos[0]->SetMaximum(2.0*histos[0]->GetMaximum()); leg->AddEntry( histos[1], "Weighted","LE" );
    histos[2]->SetLineStyle(2); histos[2]->SetLineColor(kBlack);
    histos[3]->SetLineStyle(3); histos[3]->SetLineColor(kBlack);
    leg->Draw();
    myText( 0.2, 0.8, 0.05,"#bf{CMS} #it{Internal}",0.04);

    TH1* hR = (TH1*) histos[1]->Clone("hR"+name);
    hR->Divide(histos[0]);
    TH1* hRU = (TH1*) histos[2]->Clone("hRU"+name);
    hRU->Divide(histos[0]);
    TH1* hRD = (TH1*) histos[3]->Clone("hRD"+name);
    hRD->Divide(histos[0]);

    ratioPad.cd();
    hR->SetTitle("");
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
    hR->GetXaxis()->SetTitle(XAxis);
    TLine* horiz_line = new TLine(0,1,200,1);
    horiz_line->DrawLine(hR->GetBinCenter(1),1,hR->GetBinCenter(hR->GetNbinsX()),1);
    

    // hR->GetXaxis()->SetTitleSize(18);  
    gPad->RedrawAxis();


    TString outName = "check_full_AJ_" + runName;
    c.SaveAs( outName+"_"+name+fitName+".pdf");
}
        
void FillHistos( TH1 * histos[4], float variable, float sumpt, float pt2, float pt4, float CSV3, int pass_trigger1, int pass_trigger2 )
{
    float weight = 0, weightUp = 0, weightDown = 0; 
/*    if( pass_trigger1==1 ){ weight += TurnOnDouble( sumpt, pt2, pt4, CSV3 ); weightUp += TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 ); weightDown += TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 ); }
    if( pass_trigger2==1 ){ weight += TurnOnQuad( sumpt, pt2, pt4, CSV3 ); weightUp += TurnOnQuadUp( sumpt, pt2, pt4, CSV3 ); weightDown += TurnOnQuadDown( sumpt, pt2, pt4, CSV3 ); }
    if( pass_trigger1==1 &&pass_trigger2==1 ){ weight-=TurnOnDouble( sumpt, pt2, pt4, CSV3 )*TurnOnQuad( sumpt, pt2, pt4, CSV3 ); weightUp-=TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 )*TurnOnQuadUp( sumpt, pt2, pt4, CSV3 ); weightDown-=TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 )*TurnOnQuadDown( sumpt, pt2, pt4, CSV3 ); }
//*/
    weight += TurnOnDouble( sumpt, pt2, pt4, CSV3 ); weightUp += TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 ); weightDown += TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 );
    weight += TurnOnQuad( sumpt, pt2, pt4, CSV3 ); weightUp += TurnOnQuadUp( sumpt, pt2, pt4, CSV3 ); weightDown += TurnOnQuadDown( sumpt, pt2, pt4, CSV3 );
   // weight-=QaD_TurnOnDouble( sumpt, pt2, pt4, CSV3 )*QaD_TurnOnQuad( sumpt, pt2, pt4, CSV3 ); weightUp-=QaD_TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 )*QaD_TurnOnQuadUp( sumpt, pt2, pt4, CSV3 ); weightDown-=QaD_TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 )*QaD_TurnOnQuadDown( sumpt, pt2, pt4, CSV3 );//*/
     weight-=TurnOnDouble( sumpt, pt2, pt4, CSV3 )*TurnOnQuad( sumpt, pt2, pt4, CSV3 ); weightUp-=TurnOnDoubleUp( sumpt, pt2, pt4, CSV3 )*TurnOnQuadUp( sumpt, pt2, pt4, CSV3 ); weightDown-=TurnOnDoubleDown( sumpt, pt2, pt4, CSV3 )*TurnOnQuadDown( sumpt, pt2, pt4, CSV3 );//*/
    
   
 if( pass_trigger1==1 || pass_trigger2==1 ){ histos[0]->Fill( variable, 1. ); } 
    histos[1]->Fill( variable, weight  ); 
    histos[2]->Fill( variable, weightUp ); 
    histos[3]->Fill( variable, weightDown );//*/    

   /* if( pass_trigger1==1 || pass_trigger2==1 ){ histos[0]->Fill( variable, 1./weight ); } 
    histos[1]->Fill( variable, 1. ); 
    histos[2]->Fill( variable, weightUp/weight ); 
    histos[3]->Fill( variable, weightDown/weight ); //*/
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

void myText(  Double_t x, Double_t y, int lStyle,const char *text, float tsize, float lSize ) {

//  Double_t tsize=0.06;

  TLatex l; l.SetTextAlign(12);
  l.SetTextSize(tsize);
  l.SetNDC();
  if(std::string(text).size()) l.DrawLatex(x,y,text);

  Double_t y1=y-0.25*tsize;
  Double_t y2=y+0.25*tsize;
  Double_t x2=x-0.3*tsize;
  Double_t x1=x2-lSize;

  bool debug=0;
  if(debug) printf("x1= %f x2= %f y1= %f y2= %f \n",x1,x2,y1,y2);

}
