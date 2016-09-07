#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <iostream>
#include <vector>
#include "PDFs/BtagCalibrationStandalone.cc"
#include "HbbHbb_Component_SignalPurity.cc"
#include "HbbHbb_Component_KinFit.cc"

double jet_pT_cut1=30.;

double mean_H1_mass_=125;// 120 125;
double sigma_H1_mass_=20; //20
double mean_H2_mass_=125;//125;
double sigma_H2_mass_=20;

float mass_mean( int mass )
{
    if( mass == 400 ) return 380;
    else if( mass == 450 ) return 425;
    else if( mass == 500 ) return 476;
    else if( mass == 550 ) return 524;
    else if( mass == 600 ) return 573;
    else if( mass == 650 ) return 623;
    else if( mass == 700 ) return 674;
    else if( mass == 750 ) return 720;
    else if( mass == 800 ) return 772;
    else if( mass == 900 ) return 871;
    else return mass; 
}

float mass_mean_reg( int mass )
{
    if( mass == 400 ) return 388;
    else if( mass == 450 ) return 434;
    else if( mass == 500 ) return 482;
    else if( mass == 550 ) return 540;
    else if( mass == 600 ) return 589;
    else if( mass == 650 ) return 638;
    else if( mass == 700 ) return 689;
    else if( mass == 750 ) return 737;
    else if( mass == 800 ) return 787;
    else if( mass == 900 ) return 886;

    else return mass; 
}
float mass_sigma( int mass )
{
    if( mass == 400 ) return 21;
    else if( mass == 450 ) return 25;
    else if( mass == 500 ) return 28;
    else if( mass == 550 ) return 30;
    else if( mass == 600 ) return 32;
    else if( mass == 650 ) return 34;
    else if( mass == 700 ) return 35;
    else if( mass == 750 ) return 39;
    else if( mass == 800 ) return 39;
    else if( mass == 900 ) return 42;
    else return 30; 
}

float mass_sigma_reg( int mass )
{
    if( mass == 400 ) return 23;
    else if( mass == 450 ) return 24;
    else if( mass == 500 ) return 28;
    else if( mass == 550 ) return 29;
    else if( mass == 600 ) return 31;
    else if( mass == 650 ) return 33;
    else if( mass == 700 ) return 35;
    else if( mass == 750 ) return 38;
    else if( mass == 800 ) return 40;
    else if( mass == 900 ) return 45;
    else return 30; 
}


TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double M)
{
  TLorentzVector jet_p4;
  jet_p4.SetPtEtaPhiM(pT, eta, phi, M);
  return jet_p4;
}

void HbbHbb_MMRSelection_chi2(std::string type, std::string sample, int signal_mass = 300, bool reg = false  )
{

  std::string inputfilename="../PreSelected_"+sample+".root";
  TChain *tree=new TChain("tree");
  tree->Add(inputfilename.c_str());
  //std::cout<<"Opened input file "<<inputfilename<<std::endl;
  
  int evt;
  float eventWeight;
  int nJets, nGenBQuarkFromH;
  float jet_btagCSV[100], jet_btagCMVA[100];
  float jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
  float genBQuarkFromH_pT[100],genBQuarkFromH_eta[100],genBQuarkFromH_phi[100],genBQuarkFromH_mass[100];
  float jet_regressed_pT[100], jet_flavor[100];
  std::vector<unsigned int> *jetIndex_CentralpT40btag_CMVAOrder=0;
  
  tree->SetBranchAddress("evt", &evt);
  tree->SetBranchAddress("eventWeight", &(eventWeight));                
  tree->SetBranchAddress("nJet", &(nJets));                       
  tree->SetBranchAddress("Jet_btagCSV", &(jet_btagCSV));          
  tree->SetBranchAddress("Jet_btagCMVAV2", &(jet_btagCMVA));        
  tree->SetBranchAddress("Jet_pt", &(jet_pT));                    
  tree->SetBranchAddress("Jet_eta", &(jet_eta));                  
  tree->SetBranchAddress("Jet_phi", &(jet_phi));                  
  tree->SetBranchAddress("Jet_mass", &(jet_mass));
  tree->SetBranchAddress("Jet_regressed_pt", &(jet_regressed_pT));
  tree->SetBranchAddress("jetIndex_CentralpT40btag_CMVAOrder", &(jetIndex_CentralpT40btag_CMVAOrder));
  if(type!="Data"){
  tree->SetBranchAddress("nGenBQuarkFromH", &(nGenBQuarkFromH));         
  tree->SetBranchAddress("GenBQuarkFromH_pt", &(genBQuarkFromH_pT));     
  tree->SetBranchAddress("GenBQuarkFromH_eta", &(genBQuarkFromH_eta));   
  tree->SetBranchAddress("GenBQuarkFromH_phi", &(genBQuarkFromH_phi));   
  tree->SetBranchAddress("GenBQuarkFromH_mass", &(genBQuarkFromH_mass));
  tree->SetBranchAddress("Jet_mcFlavour", &(jet_flavor));
   }

  TH1F * hJet_pt_H = new TH1F("hJet_pt_H","; jet pt (GeV)", 600, 0., 1200.);
	
  TH1F *h_H1_mass = new TH1F("h_H1_mass", "; m_{H1} (GeV)", 300, 0., 300.);
  TH1F *h_H1_pT = new TH1F("h_H1_pT", "; H1 p_{T} (GeV/c)", 800, 0., 800.);
  TH1F *h_H2_mass = new TH1F("h_H2_mass", "; m_{H2} (GeV)", 300, 0., 300.);
  TH1F *h_H2_pT = new TH1F("h_H2_pT", "; H2 p_{T} (GeV/c)", 800, 0., 800.);
  TH1F *h_HH_balance = new TH1F("h_HH_balance", "; (#vec{p}_{H1} + #vec{p}_{H2} - #vec{p}_{X}^{gen})_{T} GeV", 200, 0, 200.);
  TH2F *h_mH1_mH2_asym = new TH2F("h_mH1_mH2_asym", "; m_{H1} (GeV); m_{H2} (GeV)", 300, 0., 300., 300, 0., 300.);
  
  TH1F *h_H1_mass_biasCorrected = new TH1F("h_H1_mass_biasCorrected", "; Bias Corrected m_{H1} (GeV)", 300, 0., 300.);
  TH1F *h_H1_pT_biasCorrected = new TH1F("h_H1_pT_biasCorrected", "; H1 p_{T} (GeV/c)", 800, 0., 800.);
  TH1F *h_H2_mass_biasCorrected = new TH1F("h_H2_mass_biasCorrected", "; Bias Corrected m_{H2} (GeV)", 300, 0., 300.);
  TH1F *h_H2_pT_biasCorrected = new TH1F("h_H2_pT_biasCorrected", "; H2 p_{T} (GeV/c)", 800, 0., 800.);
  TH1F *h_HH_balance_biasCorrected = new TH1F("h_HH_balance_biasCorrected", "; (#vec{p}_{H1} + #vec{p}_{H2} - #vec{p}_{X}^{gen})_{T} GeV", 200, 0, 200.);
  TH2F *h_mH1_mH2_asym_biasCorrected = new TH2F("h_mH1_mH2_asym_biasCorrected", "; m_{H1} (GeV); m_{H2} (GeV)", 300, 0., 300., 300, 0., 300.);
  
  TH1F *h_GenX_pT = new TH1F("h_GenX_pT", "; (#vec{p}_{H1} + #vec{p}_{H2})_{T} GeV", 200, 0., 800.);
  TH1F *h_kinFitchi2=new TH1F("h_kinFitchi2", "; Event 4 jet kinematic #chi^2", 200, 0., 10.);
  TH1F *h_chi=new TH1F("h_chi", "; HH #chi", 100, 0, 100);
  TH1F *h_chi_biasCorrected=new TH1F("h_chi_biasCorrected", "; HH #chi", 100, 0, 100);
  
  TH1F *h_mX_SR         = new TH1F("h_mX_SR", "; m_{X} (GeV)", 3000, 0., 3000.);          h_mX_SR->Sumw2();
  TH1F *h_mX_SR_purity0 = new TH1F("h_mX_SR_purity0", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity0->Sumw2();
  TH1F *h_mX_SR_purity1 = new TH1F("h_mX_SR_purity1", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity1->Sumw2();
  TH1F *h_mX_SR_purity2 = new TH1F("h_mX_SR_purity2", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity2->Sumw2();
  TH1F *h_mX_SR_purity3 = new TH1F("h_mX_SR_purity3", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity3->Sumw2();
  TH1F *h_mX_SR_purity4 = new TH1F("h_mX_SR_purity4", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity4->Sumw2();
  TH1F *h_mX_SR_purity5 = new TH1F("h_mX_SR_purity5", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_purity5->Sumw2();
  TH1F *h_mX_SR_biasCorrected = new TH1F("h_mX_SR_biasCorrected", "; m_{X} (GeV)", 3000, 0., 3000.); h_mX_SR_biasCorrected->Sumw2();
  
  TH1F *h_mX_SR_kinFit         = new TH1F("h_mX_SR_kinFit", "; m_{X} (GeV)", 3000, 0., 3000.);          h_mX_SR_kinFit->Sumw2();
  TH1F *h_mX_SR_kinFit_purity0 = new TH1F("h_mX_SR_kinFit_purity0", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity0->Sumw2();
  TH1F *h_mX_SR_kinFit_purity1 = new TH1F("h_mX_SR_kinFit_purity1", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity1->Sumw2();
  TH1F *h_mX_SR_kinFit_purity2 = new TH1F("h_mX_SR_kinFit_purity2", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity2->Sumw2();
  TH1F *h_mX_SR_kinFit_purity3 = new TH1F("h_mX_SR_kinFit_purity3", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity3->Sumw2();
  TH1F *h_mX_SR_kinFit_purity4 = new TH1F("h_mX_SR_kinFit_purity4", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity4->Sumw2();
  TH1F *h_mX_SR_kinFit_purity5 = new TH1F("h_mX_SR_kinFit_purity5", "; m_{X} (GeV)", 3000, 0., 3000.);  h_mX_SR_kinFit_purity5->Sumw2();
  TH1F *h_HH_balance_kinFit = new TH1F("h_HH_balance_kinFit", "; (#vec{p}_{H1} + #vec{p}_{H2} - #vec{p}_{X}^{gen})_{T} GeV", 200, 0, 200.);
  
  TH1F *h_mX_SB               = new TH1F("h_mX_SB", "; m_{X} (GeV)", 3000, 0., 3000.);                 h_mX_SB->Sumw2();
  TH1F *h_mX_SB_biasCorrected = new TH1F("h_mX_SB_biasCorrected", "; m_{X} (GeV)", 3000, 0., 3000.);   h_mX_SB_biasCorrected->Sumw2();
  TH1F *h_mX_SB_kinFit        = new TH1F("h_mX_SB_kinFit", "; m_{X} (GeV)", 3000, 0., 3000.);          h_mX_SB_kinFit->Sumw2();
  
  std::string histfilename="Histograms_"+sample+".root";
  gSystem->Exec(("cp ../"+histfilename+" "+histfilename).c_str());
  TFile *tFile1=new TFile((histfilename).c_str(), "READ");
  TH1F h_Cuts=*((TH1F*)((TH1F*)tFile1->Get("h_Cuts"))->Clone("h_Cuts"));
  tFile1->Close();

  float SR_tot=0, SB_tot=0;
  int masses[]={400,450,500,550,600,650,700,750,800,900};
  std::map<int,float> SB_m, SR_m;
  for( auto m : masses ){ SR_m[m]=0; SB_m[m]=0; }
  double nCut4=0, nCut5=0, nCutGen=0;
  for (int i=0; i<tree->GetEntries(); ++i)
  {
    tree->GetEvent(i);
    
    bool foundHH=false;
    double chi2_old=200.;
    int H1jet1_i=-1, H1jet2_i=-1;
    int H2jet1_i=-1, H2jet2_i=-1;
    for (unsigned int j=0; j<jetIndex_CentralpT40btag_CMVAOrder->size(); ++j)
    {
      unsigned int j_jetIndex=jetIndex_CentralpT40btag_CMVAOrder->at(j);
      TLorentzVector jet1_p4, jet2_p4, jet3_p4, jet4_p4;
      jet1_p4=fillTLorentzVector(jet_regressed_pT[j_jetIndex], jet_eta[j_jetIndex], jet_phi[j_jetIndex], jet_mass[j_jetIndex]);
      if (jet1_p4.Pt()>jet_pT_cut1)
      {
        for (unsigned int k=0; k<jetIndex_CentralpT40btag_CMVAOrder->size(); ++k)
        {
          unsigned int k_jetIndex=jetIndex_CentralpT40btag_CMVAOrder->at(k);
          jet2_p4=fillTLorentzVector(jet_regressed_pT[k_jetIndex], jet_eta[k_jetIndex], jet_phi[k_jetIndex], jet_mass[k_jetIndex]);
          if (k_jetIndex!=j_jetIndex && jet2_p4.Pt()>jet_pT_cut1)
          {
            for (unsigned int l=0; l<jetIndex_CentralpT40btag_CMVAOrder->size(); ++l)
            {
              unsigned int l_jetIndex=jetIndex_CentralpT40btag_CMVAOrder->at(l);
              jet3_p4=fillTLorentzVector(jet_regressed_pT[l_jetIndex], jet_eta[l_jetIndex], jet_phi[l_jetIndex], jet_mass[l_jetIndex]);
              if (l_jetIndex!=k_jetIndex && l_jetIndex!=j_jetIndex && jet3_p4.Pt()>jet_pT_cut1)
              {
                for (unsigned int m=0; m<jetIndex_CentralpT40btag_CMVAOrder->size(); ++m)
                {
                  unsigned int m_jetIndex=jetIndex_CentralpT40btag_CMVAOrder->at(m);
                  jet4_p4=fillTLorentzVector(jet_regressed_pT[m_jetIndex], jet_eta[m_jetIndex], jet_phi[m_jetIndex], jet_mass[m_jetIndex]);
                  if (m_jetIndex!=l_jetIndex && m_jetIndex!=k_jetIndex && m_jetIndex!=j_jetIndex && jet4_p4.Pt()>jet_pT_cut1)
                  {
                    // swap if H pT is odd in second decimal place
                    if (int((jet1_p4+jet2_p4).Pt()*100.) % 2 == 1)
                    {
                      swap(j_jetIndex, l_jetIndex); 
                      swap(k_jetIndex, m_jetIndex);
                      swap(jet1_p4, jet3_p4);
                      swap(jet2_p4, jet4_p4);
                    }
                    
                    double deltaR1=jet1_p4.DeltaR(jet2_p4);
                    double deltaR2=jet3_p4.DeltaR(jet4_p4);
                    
                    TLorentzVector diJet1_p4=jet1_p4+jet2_p4;
                    TLorentzVector diJet2_p4=jet3_p4+jet4_p4;
                    
                    double mH1=diJet1_p4.M();
                    double mH2=diJet2_p4.M();
                    
                    double chi2=pow((mH1-mean_H1_mass_)/sigma_H1_mass_, 2)+pow((mH2-mean_H2_mass_)/sigma_H2_mass_, 2);
                  
                    if (chi2<chi2_old && deltaR1<1.5 && deltaR2<1.5)
                    {
                      H1jet1_i=j_jetIndex;
                      H1jet2_i=k_jetIndex;
                      H2jet1_i=l_jetIndex;
                      H2jet2_i=m_jetIndex;
                      chi2_old=chi2;
                      foundHH=true;
                    }
                  } // Conditions on 4th jet
                } // Loop over 4th jet
              } // Conditions on 3rd jet
            } // Loop over 3rd jet
          } // Conditions on 2nd jet
        } // Loop over 2nd jet
      } // Condition of 1st jet
    } // Loop over 1st jet

    if (foundHH)
    {
      nCut4+=eventWeight;

      double chi=pow(chi2_old, 0.5);
      h_chi->Fill(chi, eventWeight);
      
	    hJet_pt_H->Fill(jet_pT[H1jet1_i]);
      hJet_pt_H->Fill(jet_pT[H1jet2_i]);
      hJet_pt_H->Fill(jet_pT[H2jet1_i]);
      hJet_pt_H->Fill(jet_pT[H2jet2_i]);

      TLorentzVector jet1_p4=fillTLorentzVector(jet_regressed_pT[H1jet1_i], jet_eta[H1jet1_i], jet_phi[H1jet1_i], jet_mass[H1jet1_i]);
	    TLorentzVector jet2_p4=fillTLorentzVector(jet_regressed_pT[H1jet2_i], jet_eta[H1jet2_i], jet_phi[H1jet2_i], jet_mass[H1jet2_i]);    
	    TLorentzVector jet3_p4=fillTLorentzVector(jet_regressed_pT[H2jet1_i], jet_eta[H2jet1_i], jet_phi[H2jet1_i], jet_mass[H2jet1_i]);    
	    TLorentzVector jet4_p4=fillTLorentzVector(jet_regressed_pT[H2jet2_i], jet_eta[H2jet2_i], jet_phi[H2jet2_i], jet_mass[H2jet2_i]);
      
      TLorentzVector jet1_p4_unregressed=fillTLorentzVector(jet_pT[H1jet1_i], jet_eta[H1jet1_i], jet_phi[H1jet1_i], jet_mass[H1jet1_i]);
      TLorentzVector jet2_p4_unregressed=fillTLorentzVector(jet_pT[H1jet2_i], jet_eta[H1jet2_i], jet_phi[H1jet2_i], jet_mass[H1jet2_i]); 
      TLorentzVector jet3_p4_unregressed=fillTLorentzVector(jet_pT[H2jet1_i], jet_eta[H2jet1_i], jet_phi[H2jet1_i], jet_mass[H2jet1_i]); 
      TLorentzVector jet4_p4_unregressed=fillTLorentzVector(jet_pT[H2jet2_i], jet_eta[H2jet2_i], jet_phi[H2jet2_i], jet_mass[H2jet2_i]);
      
      TLorentzVector H1_p4=jet1_p4+jet2_p4;
      TLorentzVector H2_p4=jet3_p4+jet4_p4;
      TLorentzVector X_p4=H1_p4+H2_p4;
      double pTH1=H1_p4.Pt();
      double pTH2=H2_p4.Pt();
      double mH1=H1_p4.M();
      double mH2=H2_p4.M();
      
      h_H1_mass->Fill(mH1, eventWeight);
      h_H1_pT->Fill(pTH1, eventWeight);
      h_H2_mass->Fill(mH2, eventWeight);
      h_H2_pT->Fill(pTH2, eventWeight);
      h_mH1_mH2_asym->Fill(mH1, mH2, eventWeight);
      
      TLorentzVector jet1_p4_biasCorrected=biasEt_signal(jet1_p4_unregressed);
      TLorentzVector jet2_p4_biasCorrected=biasEt_signal(jet2_p4_unregressed);
      TLorentzVector jet3_p4_biasCorrected=biasEt_signal(jet3_p4_unregressed);
      TLorentzVector jet4_p4_biasCorrected=biasEt_signal(jet4_p4_unregressed);
      
      TLorentzVector H1_p4_biasCorrected=jet1_p4_biasCorrected+jet2_p4_biasCorrected;
      TLorentzVector H2_p4_biasCorrected=jet3_p4_biasCorrected+jet4_p4_biasCorrected;
      TLorentzVector X_p4_biasCorrected=H1_p4_biasCorrected+H2_p4_biasCorrected;
      double pTH1_biasCorrected=H1_p4_biasCorrected.Pt();
      double pTH2_biasCorrected=H2_p4_biasCorrected.Pt();
      double mH1_biasCorrected=H1_p4_biasCorrected.M();
      double mH2_biasCorrected=H2_p4_biasCorrected.M();
      h_H1_mass_biasCorrected->Fill(mH1_biasCorrected, eventWeight);
      h_H1_pT_biasCorrected->Fill(pTH1_biasCorrected, eventWeight);
      h_H2_mass_biasCorrected->Fill(mH2_biasCorrected, eventWeight);
      h_H2_pT_biasCorrected->Fill(pTH2_biasCorrected, eventWeight);
      h_mH1_mH2_asym_biasCorrected->Fill(mH1_biasCorrected, mH2_biasCorrected, eventWeight);
      
      TLorentzVector b1_p4;
      TLorentzVector b2_p4;
      TLorentzVector b3_p4;
      TLorentzVector b4_p4;
      int purity=-3;
      if (type=="Signal")
      {
        if (nGenBQuarkFromH==4)
        {
          b1_p4=fillTLorentzVector(genBQuarkFromH_pT[0], genBQuarkFromH_eta[0], genBQuarkFromH_phi[0], genBQuarkFromH_mass[0]);
          b2_p4=fillTLorentzVector(genBQuarkFromH_pT[1], genBQuarkFromH_eta[1], genBQuarkFromH_phi[1], genBQuarkFromH_mass[1]);
          b3_p4=fillTLorentzVector(genBQuarkFromH_pT[2], genBQuarkFromH_eta[2], genBQuarkFromH_phi[2], genBQuarkFromH_mass[2]);
          b4_p4=fillTLorentzVector(genBQuarkFromH_pT[3], genBQuarkFromH_eta[3], genBQuarkFromH_phi[3], genBQuarkFromH_mass[3]);
          TLorentzVector j[4]={jet1_p4, jet2_p4, jet3_p4, jet4_p4};
          TLorentzVector b[4]={b1_p4,   b2_p4,   b3_p4,   b4_p4};
          int jMatchedbindex[4]={-1, -1, -1, -1};
          purity=purityTest(j, b, jMatchedbindex);
        }
        else
        {
          std::cout<<"ERROR: This is a signal sample without 4 gen b from H."<<std::endl;
        }
      }
      
      double oppSign=(mH1-mean_H1_mass_)*(mH2-mean_H2_mass_);
      if (chi<=1)                                                                        // Signal Region
      {
        nCut5+=eventWeight;
         SR_tot++;
        for( auto m : masses )
        {
            if( !reg  && X_p4.M() > mass_mean(m)-mass_sigma(m)*3 &&  X_p4.M() < mass_mean(m)+mass_sigma(m)*3 ) SR_m[m]++;
            else if( reg  && X_p4.M() > mass_mean_reg(m)-mass_sigma_reg(m)*3 &&  X_p4.M() < mass_mean_reg(m)+mass_sigma_reg(m)*3 ) SR_m[m]++;
        }
        

        double kinFitchi2=constrainHH_signalMeasurement(&jet1_p4, &jet2_p4, &jet3_p4, &jet4_p4);
        h_kinFitchi2->Fill(kinFitchi2, eventWeight);
        TLorentzVector X_p4_kinFit=(jet1_p4+jet2_p4+jet3_p4+jet4_p4);
        
        h_mX_SR->Fill(X_p4.M(), eventWeight);
        h_mX_SR_biasCorrected->Fill(X_p4_biasCorrected.M(), eventWeight);
        h_mX_SR_kinFit->Fill(X_p4_kinFit.M(), eventWeight);
        if (purity==-1)
        {
          h_mX_SR_purity5->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity5->Fill(X_p4_kinFit.M(), eventWeight);
        }
        else if (purity==0)
        {
          h_mX_SR_purity0->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity0->Fill(X_p4_kinFit.M(), eventWeight);
        }
        else if (purity==1)
        {
          h_mX_SR_purity1->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity1->Fill(X_p4_kinFit.M(), eventWeight);
        }
        else if (purity==2)
        {
          h_mX_SR_purity2->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity2->Fill(X_p4_kinFit.M(), eventWeight);
        }
        else if (purity==3)
        {
          h_mX_SR_purity3->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity3->Fill(X_p4_kinFit.M(), eventWeight);
        }
        else if (purity==4)
        {
          h_mX_SR_purity4->Fill(X_p4.M(), eventWeight);
          h_mX_SR_kinFit_purity4->Fill(X_p4_kinFit.M(), eventWeight);
        }
        
        if (type=="Signal" && nGenBQuarkFromH==4)
        {
          TLorentzVector gen_X_p4 = b1_p4 + b2_p4 + b3_p4 + b4_p4;
          h_HH_balance->Fill((X_p4 - gen_X_p4).Pt(), eventWeight);
          h_HH_balance_biasCorrected->Fill((X_p4_biasCorrected - gen_X_p4).Pt(), eventWeight);
          h_HH_balance_kinFit->Fill((X_p4_kinFit - gen_X_p4).Pt(), eventWeight);
        } 
      }
      else if (1<chi && chi<2 && oppSign<0)                                   // Sideband Region
      {

        SB_tot++;        
        for( auto m : masses )
        {
            if( !reg  && X_p4.M() > mass_mean(m)-mass_sigma(m)*3 &&  X_p4.M() < mass_mean(m)+mass_sigma(m)*3 ) SB_m[m]++;
            else if( reg  && X_p4.M() > mass_mean_reg(m)-mass_sigma_reg(m)*3 &&  X_p4.M() < mass_mean_reg(m)+mass_sigma_reg(m)*3 ) SB_m[m]++;
        }
        double kinFitchi2=constrainHH_signalMeasurement(&jet1_p4, &jet2_p4, &jet3_p4, &jet4_p4);
        TLorentzVector X_p4_kinFit=(jet1_p4+jet2_p4+jet3_p4+jet4_p4);
        
        h_mX_SB->Fill(X_p4.M(), eventWeight);
        h_mX_SB_biasCorrected->Fill(X_p4_biasCorrected.M(), eventWeight);
        h_mX_SB_kinFit->Fill(X_p4_kinFit.M(), eventWeight);
      }
      
    }
  } // Event loop

  if(type!="Data") std::cout << signal_mass <<  "   " << SR_m[signal_mass] << std::endl;
  else for( auto m : masses ) std::cout << m << "   " << SB_m[m]*SR_tot/SB_tot << std::endl;
 
 
  h_Cuts.Fill(9, nCut4); // HH Candidates
  h_Cuts.Fill(11, nCut5); // SR

  TFile *tFile2=new TFile(histfilename.c_str(), "UPDATE");
  tFile2->Delete("h_Cuts;1");
  h_H1_mass->Write();
  h_H1_pT->Write();
  h_H2_mass->Write();
  h_H2_pT->Write();
  h_HH_balance->Write();
  h_mH1_mH2_asym->Write();
  h_H1_mass_biasCorrected->Write();
  h_H1_pT_biasCorrected->Write();
  h_H2_mass_biasCorrected->Write();
  h_H2_pT_biasCorrected->Write();
  h_HH_balance_biasCorrected->Write();
  h_mH1_mH2_asym_biasCorrected->Write();
  h_GenX_pT->Write();
  h_kinFitchi2->Write();
  h_chi->Write();
  h_chi_biasCorrected->Write();
   if(type!="Data"){h_mX_SR->Write();
  h_mX_SR_biasCorrected->Write();
  h_mX_SR_purity5->Write();
  h_mX_SR_purity0->Write();
  h_mX_SR_purity1->Write();
  h_mX_SR_purity2->Write();
  h_mX_SR_purity3->Write();
  h_mX_SR_purity4->Write();
  h_mX_SR_kinFit->Write();}
  h_HH_balance_kinFit->Write();        
   if(type!="Data"){h_mX_SR_kinFit_purity0->Write();
  h_mX_SR_kinFit_purity1->Write();
  h_mX_SR_kinFit_purity2->Write();
  h_mX_SR_kinFit_purity3->Write();
  h_mX_SR_kinFit_purity4->Write();
  h_mX_SR_kinFit_purity5->Write(); }
  h_mX_SB->Write();
  h_mX_SB_biasCorrected->Write();
  h_mX_SB_kinFit->Write();
  hJet_pt_H->Write(); 
  h_Cuts.Write();

  tFile2->Write();
  tFile2->Close();
  /*std::cout<<"Wrote output file "<<histfilename<<std::endl;

  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.5)  = "<<nCut4<<std::endl;
  std::cout<<"Number of events in SR = "<<nCut5<<std::endl;
  std::cout<<"========================"<<std::endl;*/
  
  delete h_H1_mass;
  delete h_H1_pT;
  delete h_H2_mass;
  delete h_H2_pT;
  delete h_HH_balance;
  delete h_mH1_mH2_asym;
  delete h_H1_mass_biasCorrected;
  delete h_H1_pT_biasCorrected;
  delete h_H2_mass_biasCorrected;
  delete h_H2_pT_biasCorrected;
  delete h_HH_balance_biasCorrected;
  delete h_mH1_mH2_asym_biasCorrected;
  delete h_GenX_pT;
  delete h_kinFitchi2;
  delete h_chi;
  delete h_chi_biasCorrected;
  delete h_mX_SR;
  delete h_mX_SR_biasCorrected;
  delete h_mX_SR_purity5;
  delete h_mX_SR_purity0;
  delete h_mX_SR_purity1;
  delete h_mX_SR_purity2;
  delete h_mX_SR_purity3;
  delete h_mX_SR_purity4;
  delete h_mX_SR_kinFit;
  delete h_HH_balance_kinFit;
  delete h_mX_SR_kinFit_purity0;
  delete h_mX_SR_kinFit_purity1;
  delete h_mX_SR_kinFit_purity2;
  delete h_mX_SR_kinFit_purity3;
  delete h_mX_SR_kinFit_purity4;
  delete h_mX_SR_kinFit_purity5;
  delete h_mX_SB;
  delete h_mX_SB_biasCorrected;
  delete h_mX_SB_kinFit;
  delete hJet_pt_H;
}
