#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <TRandom3.h>
#include <iostream>
#include <vector>

#include "KinFitInterface.cc"

double pi=3.14159265358979;
double H_mass=125.;

TRandom3 *r3=new TRandom3();

// gSystem->Load("libPhysicsToolsKinFitter.so");

TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double M)
{
  TLorentzVector jet_p4;
  jet_p4.SetPtEtaPhiM(pT, eta, phi, M);
  return jet_p4;
}

int purityTest(TLorentzVector j[4], TLorentzVector b[4], int jMatchedbindex[4])
{
  int purity=-2; // reflects how many jets are matched. 
  // If -1, that means multiple b were matched most closely to the same j
  
  int nMatches=0;
  for (unsigned int i_j=0; i_j<4; ++i_j)
  {
    double mindR=0.4;
    for (unsigned int i_b=0; i_b<4; ++i_b)
    {
      double dR=j[i_j].DeltaR(b[i_b]);
      if (dR<mindR)
      {
        mindR=dR;
        jMatchedbindex[i_j]=i_b;
      } 
    }
    if (jMatchedbindex[i_j]!=-1) // Match has happened
    {
      for (unsigned int i_i_j=0; i_i_j<i_j; ++i_i_j)
      {
        if (jMatchedbindex[i_j]==jMatchedbindex[i_i_j]) return -1;
      }
      ++nMatches;
    }
  }
  
  return nMatches;
} 

int withinRegion(double mH1, double mH2, double r1=15., double r2=30., double mH1_c=H_mass, double mH2_c=H_mass)
{
  double r=pow(pow(mH1-mH1_c, 2)+pow(mH2-mH2_c, 2), 0.5);
  double angle=atan2(mH2-mH2_c, mH1-mH1_c);
  // std::cout<<"(mH1, mH2) = ("<<mH1<<", "<<mH2<<") lies in region ";
  int ret=-1;
  if (r<r1) ret=0;
  else if (r>r1 && r<r2)
  {
    if (angle>=0 && angle<pi/2.) ret=1;
    else if (angle>=pi/2. && angle<pi) ret=4;
    else if (angle<0 && angle>=-pi/2.) ret=2;
    else if (angle<pi/2.&& angle>=-pi) ret=3;
    else std::cout<<"This is within annulus but not within any CR!"<<std::endl;
  }
  else ret=5;
  // std::cout<<ret<<std::endl;
  return ret;
}

TLorentzVector gaussianSmear(TLorentzVector a, double smear=5)
{
  double pT=a.Pt();
  double eta=a.Eta();
  double phi=a.Phi();
  double mass=a.M();

  double newpT=pT+r3->Gaus(0, smear);

  TLorentzVector b=fillTLorentzVector(newpT, eta, phi, mass);
  return b;
}

void HbbHbb_MMRSelection_CheckKinFit(std::string type, std::string sample)
{
  gSystem->Load("libPhysicsToolsKinFitter.so");
  
  std::string inputfilename="../PreSelected_"+sample+".root";
  TChain *tree=new TChain("tree");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;
  
  // Book variables
  float eventWeight;
  int nJets, nGenBQuarkFromH;
  float jet_btagCSV[100], jet_btagCMVA[100];
  float jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
  float genBQuarkFromH_pT[100],genBQuarkFromH_eta[100],genBQuarkFromH_phi[100],genBQuarkFromH_mass[100];
  std::vector<unsigned int> *jetIndex_pTOrder=0;
  
  // Retrieve variables
  tree->SetBranchAddress("eventWeight", &(eventWeight));                
  tree->SetBranchAddress("nJet", &(nJets));                       
  tree->SetBranchAddress("Jet_btagCSV", &(jet_btagCSV));          
  tree->SetBranchAddress("Jet_btagCMVA", &(jet_btagCMVA));        
  tree->SetBranchAddress("Jet_pt", &(jet_pT));                    
  tree->SetBranchAddress("Jet_eta", &(jet_eta));                  
  tree->SetBranchAddress("Jet_phi", &(jet_phi));                  
  tree->SetBranchAddress("Jet_mass", &(jet_mass));                
  tree->SetBranchAddress("jetIndex_pTOrder", &(jetIndex_pTOrder));
  tree->SetBranchAddress("nGenBQuarkFromH", &(nGenBQuarkFromH));         
  tree->SetBranchAddress("GenBQuarkFromH_pt", &(genBQuarkFromH_pT));     
  tree->SetBranchAddress("GenBQuarkFromH_eta", &(genBQuarkFromH_eta));   
  tree->SetBranchAddress("GenBQuarkFromH_phi", &(genBQuarkFromH_phi));   
  tree->SetBranchAddress("GenBQuarkFromH_mass", &(genBQuarkFromH_mass));

  // Book histograms
  TH1F *h_H1_mass=new TH1F("h_H1_mass", "H1 mass; mass (GeV)", 50, 50., 200.);
  TH1F *h_H1_pT=new TH1F("h_H1_pT", "H1 p_{T}; p_{T} (GeV/c)", 50, 0., 800.);
  TH1F *h_H2_mass=new TH1F("h_H2_mass", "H2 mass; mass (GeV)", 50, 50., 200.);
  TH1F *h_H2_pT=new TH1F("h_H2_pT", "H2 p_{T}; p_{T} (GeV/c)", 50, 0., 800.);
  TH2F *h_mH1_mH2_asym1 = new TH2F("h_mH1_mH2_asym1", "; m_{H1} (GeV); m_{H2} (GeV)", 50, 50., 200., 50, 50., 200.);
  TH2F *h_mH1_mH2_sym   = new TH2F("h_mH1_mH2_sym",   "; m_{H1} (GeV); m_{H2} (GeV)", 50, 50., 200., 50, 50., 200.); 
  
  TH1F *h_mX_SR         = new TH1F("h_mX_SR", "; m_{X} (GeV)", 2000, 0., 2000.);          h_mX_SR->Sumw2();
  TH1F *h_mX_SR_purity0 = new TH1F("h_mX_SR_purity0", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity0->Sumw2();
  TH1F *h_mX_SR_purity1 = new TH1F("h_mX_SR_purity1", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity1->Sumw2();
  TH1F *h_mX_SR_purity2 = new TH1F("h_mX_SR_purity2", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity2->Sumw2();
  TH1F *h_mX_SR_purity3 = new TH1F("h_mX_SR_purity3", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity3->Sumw2();
  TH1F *h_mX_SR_purity4 = new TH1F("h_mX_SR_purity4", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity4->Sumw2();
  TH1F *h_mX_SR_purity5 = new TH1F("h_mX_SR_purity5", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_purity5->Sumw2();
  
  TH1F *h_X2_SR_kinFit         = new TH1F("h_X2_SR_kinFit", "; #chi^{2}", 100, 0, 10.);                 h_X2_SR_kinFit->Sumw2();
  TH1F *h_mX_SR_kinFit         = new TH1F("h_mX_SR_kinFit", "; m_{X} (GeV)", 2000, 0., 2000.);          h_mX_SR_kinFit->Sumw2();
  TH1F *h_mX_SR_kinFit_purity0 = new TH1F("h_mX_SR_kinFit_purity0", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity0->Sumw2();
  TH1F *h_mX_SR_kinFit_purity1 = new TH1F("h_mX_SR_kinFit_purity1", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity1->Sumw2();
  TH1F *h_mX_SR_kinFit_purity2 = new TH1F("h_mX_SR_kinFit_purity2", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity2->Sumw2();
  TH1F *h_mX_SR_kinFit_purity3 = new TH1F("h_mX_SR_kinFit_purity3", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity3->Sumw2();
  TH1F *h_mX_SR_kinFit_purity4 = new TH1F("h_mX_SR_kinFit_purity4", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity4->Sumw2();
  TH1F *h_mX_SR_kinFit_purity5 = new TH1F("h_mX_SR_kinFit_purity5", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_SR_kinFit_purity5->Sumw2();

  TH1F *h_mX_genForKinFitCheck = new TH1F("h_mX_genForKinFitCheck", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_genForKinFitCheck->Sumw2();
  
  TH1F *h_jet_pT_res = new TH1F("h_jet_pT_res", "; Jet (p_{T}^{reco} - p_{T}^{MC}) / p_{T}^{MC}", 1000, -2., 2.);                                     h_jet_pT_res->Sumw2();
  TH2F *h_jet_pT_res_vs_pT = new TH2F("h_jet_pT_res_vs_pT", "; p_{T}; Jet (p_{T}^{reco} - p_{T}^{MC}) / p_{T}^{MC}", 100, 0., 1000., 100, -2., 2.);
  TH2F *h_jet_pT_res_vs_eta = new TH2F("h_jet_pT_res_vs_eta", "; #eta; Jet p_{T}^{reco} - p_{T}^{MC}", 100, 0., 2.5, 100, -200., 200.);
  TH2F *h_jet_pT_vs_eta = new TH2F("h_jet_pT_vs_eta", "; #eta; Jet p_{T}^{reco}", 100, 0., 2.5, 100, 0., 1000.);
  TH1F *h_jet_eta_res = new TH1F("h_jet_eta_res", "; Jet #eta^{reco} - #eta^{MC}", 1000, -1.0, 1.0);                                                    h_jet_eta_res->Sumw2();
  TH2F *h_jet_eta_res_vs_eta = new TH2F("h_jet_eta_res_vs_eta", "; #eta; Jet #eta^{reco} - #eta^{MC}", 100, 0., 2.5, 100, -2.5, 2.5);
  TH2F *h_jet_eta_res_vs_pT = new TH2F("h_jet_eta_res_vs_pT", "; p_{T}; Jet #eta^{reco} - #eta^{MC}", 100, 0., 1000., 100, -2.5, 2.5);                    
  TH2F *h_jet_phi_res_vs_eta = new TH2F("h_jet_phi_res_vs_eta", "; #eta; Jet #phi^{reco} - #phi^{MC}", 100, 0., 2.5, 100, -3.14, 3.14);
  TH2F *h_jet_phi_res_vs_pT = new TH2F("h_jet_phi_res_vs_pT", "; p_{T}; Jet #phi^{reco} - #phi^{MC}", 100, 0., 1000., 100, -3.14, 3.14);
  
  TH1F *h_H1_mass_kinFit=new TH1F("h_H1_mass_kinFit", "; H mass after KinFit (GeV)", 50, 50., 200.);
  TH1F *h_H1_pT_kinFit=new TH1F("h_H1_pT_kinFit", "; H p_{T} after KinFit (GeV/c)", 50, 0., 800.);
  TH1F *h_H2_mass_kinFit=new TH1F("h_H2_mass_kinFit", "; H mass after KinFit (GeV)", 50, 50., 200.);
  TH1F *h_H2_pT_kinFit=new TH1F("h_H2_pT_kinFit", "; H p_{T} after KinFit (GeV/c)", 50, 0., 800.);
  
  // New histograms
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4 = new TH2F("h_jet_pT_res_vs_pT_eta_0_1p4", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{MC}) (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5 = new TH2F("h_jet_pT_res_vs_pT_eta_1p4_2p5", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{MC}) (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH3F *h_jet_pTres_vs_etares_vs_pT=new TH3F("h_jet_pTres_vs_etares_vs_pT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{MC}) (GeV); Jet (#eta^{reco} - #eta^{gen})", 100, 0., 1000., 100, -200., 200., 100, -2.5, 2.5);
  TH3F *h_jet_pTres_vs_phires_vs_pT=new TH3F("h_jet_pTres_vs_phires_vs_pT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{MC}) (GeV); Jet (#phi^{reco} - #phi^{gen})", 100, 0., 1000., 100, -200., 200., 100, -3.14, 3.14);
  
  // Check histogram
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4_Corrected = new TH2F("h_jet_pT_res_vs_pT_eta_0_1p4_Corrected", "h_jet_pT_res_vs_pT_eta_0_1p4_Corrected", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected = new TH2F("h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected", "h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected", 100, 0., 1000., 100, -200., 200.);
  
  // What happens at the kinFit?
  TH1F *h_jet_pT_diff=new TH1F("h_jet_pT_diff", "h_jet_pT_diff", 100, -100, 100);
  TH1F *h_H_dR=new TH1F("h_H_dR", "h_H_dR", 100, -2.5, 2.5);
  TH1F *h_H1_mass_biasCorrected=new TH1F("h_H1_mass_biasCorrected", "h_H1_mass_biasCorrected", 50, 50, 200);
  
  // Get the h_Cuts histogram
  std::string histfilename="Histograms_"+sample+".root";
  gSystem->Exec(("cp ../"+histfilename+" "+histfilename).c_str());
  TFile *tFile1=new TFile(("../"+histfilename).c_str(), "READ");
  TH1F h_Cuts=*((TH1F*)((TH1F*)tFile1->Get("h_Cuts"))->Clone("h_Cuts"));
  tFile1->Close();
  
  // Event loop
  double nCut4=0, nCut5=0, nCutGen=0;
  for (int i=0; i<tree->GetEntries(); ++i)
  {
    tree->GetEvent(i);
    
    bool foundHH=false;
    double m_diff_old=50.;
    int H1jet1_i=-1, H1jet2_i=-1;
    int H2jet1_i=-1, H2jet2_i=-1;
    
    // std::cout<<"jetIndex_pTOrder->size() = "<<jetIndex_pTOrder->size()<<std::endl;
  
    for (unsigned int j=0; j<jetIndex_pTOrder->size(); ++j)
    {
      unsigned int j_jetIndex=jetIndex_pTOrder->at(j);
      TLorentzVector jet1_p4, jet2_p4, jet3_p4, jet4_p4;
      jet1_p4=fillTLorentzVector(jet_pT[j_jetIndex], jet_eta[j_jetIndex], jet_phi[j_jetIndex], jet_mass[j_jetIndex]);
      for (unsigned int k=0; k<jetIndex_pTOrder->size(); ++k)
      {
        if (k!=j)
        {
          unsigned int k_jetIndex=jetIndex_pTOrder->at(k);
          jet2_p4=fillTLorentzVector(jet_pT[k_jetIndex], jet_eta[k_jetIndex], jet_phi[k_jetIndex], jet_mass[k_jetIndex]);
          for (unsigned int l=0; l<jetIndex_pTOrder->size(); ++l)
          {
            if (l!=j && l!=k)
            {
              unsigned int l_jetIndex=jetIndex_pTOrder->at(l);
              jet3_p4=fillTLorentzVector(jet_pT[l_jetIndex], jet_eta[l_jetIndex], jet_phi[l_jetIndex], jet_mass[l_jetIndex]);
              for (unsigned int m=0; m<jetIndex_pTOrder->size(); ++m)
              {
                if (m!=j && m!=k && m!=l)
                {
                  unsigned int m_jetIndex=jetIndex_pTOrder->at(m);
                  jet4_p4=fillTLorentzVector(jet_pT[m_jetIndex], jet_eta[m_jetIndex], jet_phi[m_jetIndex], jet_mass[m_jetIndex]);
                   
                  TLorentzVector diJet1_p4=jet1_p4+jet2_p4;
                  TLorentzVector diJet2_p4=jet3_p4+jet4_p4;
                  
                  double deltaR1=jet1_p4.DeltaR(jet2_p4);
                  double deltaR2=jet3_p4.DeltaR(jet4_p4);
                  
                  double m_diff=fabs(diJet1_p4.M()-diJet2_p4.M());
                  if (m_diff<m_diff_old && deltaR1<1.5 && deltaR2<1.5)
                  {
                    H1jet1_i=j_jetIndex;
                    H1jet2_i=k_jetIndex;
                    H2jet1_i=l_jetIndex;
                    H2jet2_i=m_jetIndex;
                    m_diff_old=m_diff;
                    foundHH=true;
                  }
                } // Conditions on 4th jet
              } // Loop over 4th jet
            } // Conditions on 3rd jet
          } // Loop over 3rd jet
        } // Conditions on 2nd jet
      } // Loop over 2nd jet
    } // Loop over 1st jet

    if (foundHH)
    {
      nCut4+=eventWeight;
      
      TLorentzVector jet1_p4=fillTLorentzVector(jet_pT[H1jet1_i], jet_eta[H1jet1_i], jet_phi[H1jet1_i], jet_mass[H1jet1_i]);
      TLorentzVector jet2_p4=fillTLorentzVector(jet_pT[H1jet2_i], jet_eta[H1jet2_i], jet_phi[H1jet2_i], jet_mass[H1jet2_i]);    
      TLorentzVector jet3_p4=fillTLorentzVector(jet_pT[H2jet1_i], jet_eta[H2jet1_i], jet_phi[H2jet1_i], jet_mass[H2jet1_i]);    
      TLorentzVector jet4_p4=fillTLorentzVector(jet_pT[H2jet2_i], jet_eta[H2jet2_i], jet_phi[H2jet2_i], jet_mass[H2jet2_i]);
      
      // Fill mH1 vs mH2 asym before randomization
      double pTH1=(jet1_p4+jet2_p4).Pt();
      double pTH2=(jet3_p4+jet4_p4).Pt();
      double mH1=(jet1_p4+jet2_p4).M();
      double mH2=(jet3_p4+jet4_p4).M();
      h_mH1_mH2_asym1->Fill((pTH1>pTH2)?mH1:mH2, (pTH1>pTH2)?mH2:mH1, eventWeight);

      // Randomization or ordering of which Higgs is which
      if (int((jet1_p4+jet2_p4).Pt()*100.) % 2 == 1) {swap(H1jet1_i, H2jet1_i); swap(H1jet2_i, H2jet2_i);} // swap if H pT is odd in second decimal place

      jet1_p4=fillTLorentzVector(jet_pT[H1jet1_i], jet_eta[H1jet1_i], jet_phi[H1jet1_i], jet_mass[H1jet1_i]);
      jet2_p4=fillTLorentzVector(jet_pT[H1jet2_i], jet_eta[H1jet2_i], jet_phi[H1jet2_i], jet_mass[H1jet2_i]); 
      jet3_p4=fillTLorentzVector(jet_pT[H2jet1_i], jet_eta[H2jet1_i], jet_phi[H2jet1_i], jet_mass[H2jet1_i]); 
      jet4_p4=fillTLorentzVector(jet_pT[H2jet2_i], jet_eta[H2jet2_i], jet_phi[H2jet2_i], jet_mass[H2jet2_i]);
      
      // Check purity of jet selection here
      int purity=-3;
      double mX_genForKinFitCheck=0;
      if (type=="Signal")
      {
        if (nGenBQuarkFromH==4)
        {
          TLorentzVector b1_p4=fillTLorentzVector(genBQuarkFromH_pT[0], genBQuarkFromH_eta[0], genBQuarkFromH_phi[0], genBQuarkFromH_mass[0]);
          TLorentzVector b2_p4=fillTLorentzVector(genBQuarkFromH_pT[1], genBQuarkFromH_eta[1], genBQuarkFromH_phi[1], genBQuarkFromH_mass[1]);
          TLorentzVector b3_p4=fillTLorentzVector(genBQuarkFromH_pT[2], genBQuarkFromH_eta[2], genBQuarkFromH_phi[2], genBQuarkFromH_mass[2]);
          TLorentzVector b4_p4=fillTLorentzVector(genBQuarkFromH_pT[3], genBQuarkFromH_eta[3], genBQuarkFromH_phi[3], genBQuarkFromH_mass[3]);
          TLorentzVector j[4]={jet1_p4, jet2_p4, jet3_p4, jet4_p4};
          TLorentzVector b[4]={b1_p4,   b2_p4,   b3_p4,   b4_p4};
          int jMatchedbindex[4]={-1, -1, -1, -1};
          purity=purityTest(j, b, jMatchedbindex);
          if (purity==4)
          {
            for (unsigned int ijet=0; ijet<4; ++ijet)
            {
              double res_pT=j[ijet].Pt() - b[jMatchedbindex[ijet]].Pt();
              h_jet_pT_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_pT, eventWeight);
              double res_eta=j[ijet].Eta() - b[jMatchedbindex[ijet]].Eta();
              h_jet_eta_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_eta, eventWeight);
              h_jet_eta_res_vs_pT->Fill(j[ijet].Pt(), res_eta, eventWeight);
              double res_phi=j[ijet].Phi() - b[jMatchedbindex[ijet]].Phi();
              h_jet_phi_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_phi, eventWeight);
              h_jet_phi_res_vs_pT->Fill(j[ijet].Pt(), res_phi, eventWeight);
              
              h_jet_pTres_vs_etares_vs_pT->Fill(j[ijet].Pt(), res_pT, res_eta, eventWeight);
              h_jet_pTres_vs_phires_vs_pT->Fill(j[ijet].Pt(), res_pT, res_phi, eventWeight);
              
              // New histograms
              if (fabs(j[ijet].Eta())<1.4)
              {
                h_jet_pT_res_vs_pT_eta_0_1p4->Fill(j[ijet].Pt(), res_pT, eventWeight);
                
                // Now make a clone of this jet, correct for its bias and fill the same histogram
                // TLorentzVector correctedJet(j[ijet]);
                // biasEt_signal(&correctedJet);
                // h_jet_pT_res_vs_pT_eta_0_1p4_Corrected->Fill(correctedJet.Pt(), correctedJet.Pt() - b[jMatchedbindex[ijet]].Pt(), eventWeight);
              }
              else if (fabs(j[ijet].Eta())<2.5)
              {
                h_jet_pT_res_vs_pT_eta_1p4_2p5->Fill(j[ijet].Pt(), res_pT, eventWeight);
                
                // Now make a clone of this jet, correct for its bias and fill the same histogram
                // TLorentzVector correctedJet(j[ijet]);
                // biasEt_signal(&correctedJet);
                // h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->Fill(correctedJet.Pt(), correctedJet.Pt() - b[jMatchedbindex[ijet]].Pt(), eventWeight);
              }
              
            }
              
          }

          // Smear the generated 4 vector
          TLorentzVector b1_smeared_p4=gaussianSmear(b1_p4);
          TLorentzVector b2_smeared_p4=gaussianSmear(b2_p4);
          TLorentzVector b3_smeared_p4=gaussianSmear(b3_p4);
          TLorentzVector b4_smeared_p4=gaussianSmear(b4_p4);
          double chi2=constrainHH(&b1_smeared_p4, &b2_smeared_p4, &b3_smeared_p4, &b4_smeared_p4);
          mX_genForKinFitCheck=(b1_smeared_p4+b2_smeared_p4+b3_smeared_p4+b4_smeared_p4).M();

        }
        else
        {
          std::cout<<"ERROR: This is a signal sample without 4 gen b from H."<<std::endl;
        }
      }

      TLorentzVector H1_p4=jet1_p4+jet2_p4;
      TLorentzVector H2_p4=jet3_p4+jet4_p4;
      TLorentzVector X_p4=H1_p4+H2_p4;

      h_H1_mass->Fill(H1_p4.M(), eventWeight);
      h_H1_pT->Fill(H1_p4.Pt(), eventWeight);
      h_H2_mass->Fill(H2_p4.M(), eventWeight);
      h_H2_pT->Fill(H2_p4.Pt(), eventWeight);
      h_mH1_mH2_sym->Fill(H1_p4.M(), H2_p4.M(), eventWeight);
      
      // Before and after... kinFitter effect plots
      double jet1_pT=jet1_p4.Pt();
      double jet2_pT=jet2_p4.Pt();
      double jet3_pT=jet3_p4.Pt();
      double jet4_pT=jet4_p4.Pt();
      double deltaR_12=jet1_p4.DeltaR(jet2_p4);
      
      TLorentzVector jet1_pT_corrected(jet1_p4);
      TLorentzVector jet2_pT_corrected(jet2_p4);
      TLorentzVector jet3_pT_corrected(jet3_p4);
      TLorentzVector jet4_pT_corrected(jet4_p4);
      biasEt_signal(&jet1_pT_corrected);
      biasEt_signal(&jet2_pT_corrected);
      biasEt_signal(&jet3_pT_corrected);
      biasEt_signal(&jet4_pT_corrected);
      h_H1_mass_biasCorrected->Fill((jet1_pT_corrected+jet2_pT_corrected).M(), eventWeight);

      int region=withinRegion(H1_p4.M(), H2_p4.M(), 17.5, 35., H_mass, H_mass);
      if (region==0) // SR
      {
        nCut5+=eventWeight;
        
        h_mX_SR->Fill(X_p4.M(), eventWeight);
        if (purity==-1) h_mX_SR_purity5->Fill(X_p4.M(), eventWeight);
        if (purity== 0) h_mX_SR_purity0->Fill(X_p4.M(), eventWeight);
        if (purity== 1) h_mX_SR_purity1->Fill(X_p4.M(), eventWeight);
        if (purity== 2) h_mX_SR_purity2->Fill(X_p4.M(), eventWeight);
        if (purity== 3) h_mX_SR_purity3->Fill(X_p4.M(), eventWeight);
        if (purity== 4) h_mX_SR_purity4->Fill(X_p4.M(), eventWeight);
        
        // Do the kinematic constraint
        double chi2=constrainHH_signalMeasurement(&jet1_p4, &jet2_p4, &jet3_p4, &jet4_p4);
        TLorentzVector H1_p4=jet1_p4+jet2_p4;
        TLorentzVector H2_p4=jet3_p4+jet4_p4;
        TLorentzVector X_p4=H1_p4+H2_p4;
        h_X2_SR_kinFit->Fill(chi2, eventWeight);
        h_H1_mass_kinFit->Fill(H1_p4.M(), eventWeight);
        h_H1_pT_kinFit->Fill(H1_p4.Pt(), eventWeight);
        h_H2_mass_kinFit->Fill(H2_p4.M(), eventWeight);
        h_H2_pT_kinFit->Fill(H2_p4.Pt(), eventWeight);
        h_mX_SR_kinFit->Fill(X_p4.M(), eventWeight);
        if (purity==-1) h_mX_SR_kinFit_purity5->Fill(X_p4.M(), eventWeight);
        if (purity== 0) h_mX_SR_kinFit_purity0->Fill(X_p4.M(), eventWeight);
        if (purity== 1) h_mX_SR_kinFit_purity1->Fill(X_p4.M(), eventWeight);
        if (purity== 2) h_mX_SR_kinFit_purity2->Fill(X_p4.M(), eventWeight);
        if (purity== 3) h_mX_SR_kinFit_purity3->Fill(X_p4.M(), eventWeight);
        if (purity== 4) h_mX_SR_kinFit_purity4->Fill(X_p4.M(), eventWeight);
        
        h_jet_pT_diff->Fill(jet1_p4.Pt()-jet1_pT, eventWeight);
        h_jet_pT_diff->Fill(jet2_p4.Pt()-jet2_pT, eventWeight);
        h_jet_pT_diff->Fill(jet3_p4.Pt()-jet3_pT, eventWeight);
        h_jet_pT_diff->Fill(jet4_p4.Pt()-jet4_pT, eventWeight);
        h_H_dR->Fill(jet1_p4.DeltaR(jet2_p4)-deltaR_12, eventWeight);
        
        if (type=="Signal" && nGenBQuarkFromH==4) h_mX_genForKinFitCheck->Fill(mX_genForKinFitCheck, eventWeight);
      }

    }

  } // Event loop

  h_Cuts.Fill(9, nCut4); // HH Candidates
  h_Cuts.Fill(11, nCut5); // SR

  TFile *tFile2=new TFile(histfilename.c_str(), "UPDATE");
  tFile2->Delete("h_Cuts;1");
  h_H1_mass->Write();
  h_H1_pT->Write();
  h_H2_mass->Write();
  h_H2_pT->Write();
  h_mH1_mH2_asym1->Write();
  h_mH1_mH2_sym->Write();
  h_mX_SR->Write();
  h_mX_SR_purity5->Write();
  h_mX_SR_purity0->Write();
  h_mX_SR_purity1->Write();
  h_mX_SR_purity2->Write();
  h_mX_SR_purity3->Write();
  h_mX_SR_purity4->Write();
  h_X2_SR_kinFit->Write();      
  h_H1_mass_kinFit->Write();
  h_H1_pT_kinFit->Write();
  h_H2_mass_kinFit->Write();
  h_H2_pT_kinFit->Write();
  h_mX_SR_kinFit->Write();
  h_mX_SR_kinFit_purity0->Write();
  h_mX_SR_kinFit_purity1->Write();
  h_mX_SR_kinFit_purity2->Write();
  h_mX_SR_kinFit_purity3->Write();
  h_mX_SR_kinFit_purity4->Write();
  h_mX_SR_kinFit_purity5->Write();
  h_jet_pT_res->Write();
  h_jet_pT_res_vs_pT->Write();
  h_jet_pT_res_vs_eta->Write();
  h_jet_pT_vs_eta->Write();
  h_jet_eta_res->Write();
  h_jet_eta_res_vs_eta->Write();
  h_jet_eta_res_vs_pT->Write();
  h_jet_phi_res_vs_eta->Write();
  h_jet_phi_res_vs_pT->Write();
  h_jet_pTres_vs_etares_vs_pT->Write();
  h_jet_pTres_vs_phires_vs_pT->Write();
  h_jet_pT_res_vs_pT_eta_0_1p4->Write();
  h_jet_pT_res_vs_pT_eta_1p4_2p5->Write();
  h_jet_pT_res_vs_pT_eta_0_1p4_Corrected->Write();
  h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected->Write();
  h_mX_genForKinFitCheck->Write();
  h_H1_mass_biasCorrected->Write();
  h_jet_pT_diff->Write();
  h_H_dR->Write();
  h_Cuts.Write();

  tFile2->Write();
  tFile2->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;

  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.5)  = "<<nCut4<<std::endl;
  std::cout<<"Number of matched events "<<nCutGen<<std::endl;
  std::cout<<"Number of events in SR = "<<nCut5<<std::endl;
  std::cout<<"========================"<<std::endl;
  
  delete h_H1_mass;
  delete h_H1_pT;
  delete h_H2_mass;
  delete h_H2_pT;
  delete h_mH1_mH2_asym1;
  delete h_mH1_mH2_sym;
  delete h_mX_SR;
  delete h_mX_SR_purity5;
  delete h_mX_SR_purity0;
  delete h_mX_SR_purity1;
  delete h_mX_SR_purity2;
  delete h_mX_SR_purity3;
  delete h_mX_SR_purity4;
  delete h_X2_SR_kinFit; 
  delete h_H1_mass_kinFit;
  delete h_H1_pT_kinFit;
  delete h_H2_mass_kinFit;
  delete h_H2_pT_kinFit;
  delete h_mX_SR_kinFit;
  delete h_mX_SR_kinFit_purity0;
  delete h_mX_SR_kinFit_purity1;
  delete h_mX_SR_kinFit_purity2;
  delete h_mX_SR_kinFit_purity3;
  delete h_mX_SR_kinFit_purity4;
  delete h_mX_SR_kinFit_purity5;
  delete h_mX_genForKinFitCheck;
  delete h_H1_mass_biasCorrected;
  
  delete h_jet_pT_res;
  delete h_jet_pT_res_vs_pT;
  delete h_jet_pT_res_vs_eta;
  delete h_jet_pT_vs_eta;
  delete h_jet_eta_res;
  delete h_jet_eta_res_vs_eta;
  delete h_jet_eta_res_vs_pT;
  delete h_jet_phi_res_vs_eta;
  delete h_jet_phi_res_vs_pT;
  delete h_jet_pTres_vs_etares_vs_pT;
  delete h_jet_pTres_vs_phires_vs_pT;
  delete h_jet_pT_res_vs_pT_eta_0_1p4;
  delete h_jet_pT_res_vs_pT_eta_1p4_2p5;
  delete h_jet_pT_res_vs_pT_eta_0_1p4_Corrected;
  delete h_jet_pT_res_vs_pT_eta_1p4_2p5_Corrected;
  
  delete h_jet_pT_diff;
  delete h_H_dR;
}
