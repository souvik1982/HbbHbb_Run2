#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TSystem.h>
#include <TLorentzVector.h>
#include <iostream>
#include <vector>

double pi=3.14159265358979;
double H_mass=125.;

TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double M)
{
  TLorentzVector jet_p4;
  jet_p4.SetPtEtaPhiM(pT, eta, phi, M);
  return jet_p4;
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

void HbbHbb_MMRSelection(std::string sample)
{
  std::string inputfilename="../PreSelected_"+sample+".root";
  TChain *tree=new TChain("tree");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;
  
  // Book variables
  double eventWeight;
  int nJets;
  double jet_btagCSV[100], jet_btagCMVA[100];
  double jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
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
  
  // Book histograms
  TH1F *h_H1_mass=new TH1F("h_H1_mass", "H1 mass; mass (GeV)", 50, 50., 200.);
  TH1F *h_H1_pT=new TH1F("h_H1_pT", "H1 p_{T}; p_{T} (GeV/c)", 50, 0., 800.);
  TH1F *h_H2_mass=new TH1F("h_H2_mass", "H2 mass; mass (GeV)", 50, 50., 200.);
  TH1F *h_H2_pT=new TH1F("h_H2_pT", "H2 p_{T}; p_{T} (GeV/c)", 50, 0., 800.);
  TH1F *h_mX_SR=new TH1F("h_mX_SR", "h_mX_SR", 200, 0., 2000.); h_mX_SR->Sumw2();
  
  // Get the h_Cuts histogram
  std::string histfilename="Histograms_"+sample+".root";
  gSystem->Exec(("cp ../"+histfilename+" "+histfilename).c_str());
  TFile *tFile1=new TFile(("../"+histfilename).c_str(), "READ");
  TH1F h_Cuts=*((TH1F*)((TH1F*)tFile1->Get("h_Cuts"))->Clone("h_Cuts"));
  tFile1->Close();
  
  // Event loop
  double nCut4=0, nCut5=0;
  for (int i=0; i<tree->GetEntries(); ++i)
  {
    tree->GetEvent(i);
    
    bool foundHH=false;
    double m_diff_old=50.;
    int H1jet1_i, H1jet2_i;
    int H2jet1_i, H2jet2_i;
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
          jet2_p4=fillTLorentzVector(jet_pT[k_jetIndex], jet_eta[k_jetIndex], jet_phi[k], jet_mass[k_jetIndex]);
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
                  
      // Randomization or ordering of which Higgs is which
      if (int((jet1_p4+jet2_p4).Pt()*100.) % 2 == 1) {swap(H1jet1_i, H2jet1_i); swap(H1jet2_i, H2jet2_i);} // swap if H pT is odd in second decimal place
      
      jet1_p4=fillTLorentzVector(jet_pT[H1jet1_i], jet_eta[H1jet1_i], jet_phi[H1jet1_i], jet_mass[H1jet1_i]);
      jet2_p4=fillTLorentzVector(jet_pT[H1jet2_i], jet_eta[H1jet2_i], jet_phi[H1jet2_i], jet_mass[H1jet2_i]); 
      jet3_p4=fillTLorentzVector(jet_pT[H2jet1_i], jet_eta[H2jet1_i], jet_phi[H2jet1_i], jet_mass[H2jet1_i]); 
      jet4_p4=fillTLorentzVector(jet_pT[H2jet2_i], jet_eta[H2jet2_i], jet_phi[H2jet2_i], jet_mass[H2jet2_i]);
      
      TLorentzVector H1_p4=jet1_p4+jet2_p4;
      TLorentzVector H2_p4=jet3_p4+jet4_p4;
      TLorentzVector X_p4=H1_p4+H2_p4;
      
      h_H1_mass->Fill(H1_p4.M(), eventWeight);
      h_H1_pT->Fill(H1_p4.Pt(), eventWeight);
      h_H2_mass->Fill(H2_p4.M(), eventWeight);
      h_H2_pT->Fill(H2_p4.Pt(), eventWeight);
            
      int region=withinRegion(H1_p4.M(), H2_p4.M(), 17.5, 35., H_mass, H_mass);
      
      if (region==0) // SR
      {
        nCut5+=eventWeight;
        
        h_mX_SR->Fill(X_p4.M(), eventWeight);
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
  h_mX_SR->Write();
  h_Cuts.Write();
  
  tFile2->Write();
  tFile2->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  
  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.5)  = "<<nCut4<<std::endl;
  std::cout<<"Number of events in SR = "<<nCut5<<std::endl;
  std::cout<<"========================"<<std::endl;
  
}
