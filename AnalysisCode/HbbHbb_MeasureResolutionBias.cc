#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <TRandom3.h>
#include <iostream>
#include <vector>

#include "HbbHbb_Component_SignalPurity.cc"
#include "HbbHbb_Component_KinFit.cc"

double pi=3.14159265358979;
double H_mass=125.;

TRandom3 *r3=new TRandom3();

TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double M)
{
  TLorentzVector jet_p4;
  jet_p4.SetPtEtaPhiM(pT, eta, phi, M);
  return jet_p4;
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

Double_t asymmetricGaussian(Double_t *x, Double_t *par)
{
  double ret;
  if (x[0]<par[0])
  {
    ret=exp(-0.5*pow((x[0]-par[0])/par[1], 2));
  }
  else
  {
    ret=exp(-0.5*pow((x[0]-par[0])/par[2], 2));
  }
  return ret;
} 

TLorentzVector asymmetricGaussianSmear(TLorentzVector a, double sigma1=5, double sigma2=5)
{
  double pT=a.Pt();
  double eta=a.Eta();
  double phi=a.Phi();
  double mass=a.M();
  
  TF1 *f_asymGauss=new TF1("f_xgauss", asymmetricGaussian, -sigma1*3, sigma2*3, 3);
  f_asymGauss->SetParameter(0, 0);
  f_asymGauss->SetParameter(1, sigma1);
  f_asymGauss->SetParameter(2, sigma2);

  double newpT=pT+f_asymGauss->GetRandom();
  
  TLorentzVector b=fillTLorentzVector(newpT, eta, phi, mass);
  return b;
}
  

void HbbHbb_MeasureResolutionBias(std::string sample)
{

  std::cout<<" This program measures the jet energy resolutions and bias for b jets in a X -> HH -> bbbb signal sample."<<std::endl;
  std::cout<<" Do not give it anything other than a signal sample. "<<std::endl;
  std::cout<<" - Souvik Das 2015 -"<<std::endl;
  
  std::string inputfilename="../PreSelected_"+sample+".root";
  TChain *tree=new TChain("tree");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;
  
  // Book variables
  float eventWeight;
  int nJets, nGenBQuarkFromH;
  float jet_btagCSV[100], jet_btagCMVA[100];
  float jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
  float jet_MCpT[100], jet_MCeta[100], jet_MCphi[100], jet_MCmass[100];
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
  tree->SetBranchAddress("Jet_mcPt", &(jet_MCpT));  
  tree->SetBranchAddress("Jet_mcEta", &(jet_MCeta));
  tree->SetBranchAddress("Jet_mcPhi", &(jet_MCphi));
  tree->SetBranchAddress("Jet_mcM", &(jet_MCmass));
  tree->SetBranchAddress("jetIndex_pTOrder", &(jetIndex_pTOrder));
  tree->SetBranchAddress("nGenBQuarkFromH", &(nGenBQuarkFromH));         
  tree->SetBranchAddress("GenBQuarkFromH_pt", &(genBQuarkFromH_pT));     
  tree->SetBranchAddress("GenBQuarkFromH_eta", &(genBQuarkFromH_eta));   
  tree->SetBranchAddress("GenBQuarkFromH_phi", &(genBQuarkFromH_phi));   
  tree->SetBranchAddress("GenBQuarkFromH_mass", &(genBQuarkFromH_mass));

  // Book histograms
  TH2F *h_jet_pT_res_vs_pT = new TH2F("h_jet_pT_res_vs_pT", "; p_{T}^{reco} (GeV); b Jet p_{T}^{reco} - p_{T}^{part} (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_jet_pT_res_vs_pT_eta_0_1p4 = new TH2F("h_jet_pT_res_vs_pT_eta_0_1p4", "; p_{T}^{reco} (GeV); b Jet p_{T}^{reco} - p_{T}^{part} (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_jet_pT_res_vs_pT_eta_1p4_2p5 = new TH2F("h_jet_pT_res_vs_pT_eta_1p4_2p5", "; p_{T}^{reco} (GeV); Jet p_{T}^{reco} - p_{T}^{part} (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_jet_pT_res_vs_eta = new TH2F("h_jet_pT_res_vs_eta", "; #eta; b Jet p_{T}^{reco} - p_{T}^{part}", 100, 0., 2.5, 100, -200., 200.);
  TH2F *h_jet_eta_res_vs_pT = new TH2F("h_jet_eta_res_vs_pT", "; p_{T}; b Jet #eta^{reco} - #eta^{part}", 100, 0., 1000., 100, -2.5, 2.5);                    
  TH2F *h_jet_eta_res_vs_eta = new TH2F("h_jet_eta_res_vs_eta", "; #eta; b Jet #eta^{reco} - #eta^{part}", 100, 0., 2.5, 100, -2.5, 2.5);
  TH2F *h_jet_phi_res_vs_pT = new TH2F("h_jet_phi_res_vs_pT", "; p_{T}; b Jet #phi^{reco} - #phi^{part}", 100, 0., 1000., 100, -3.14, 3.14);
  TH2F *h_jet_phi_res_vs_eta = new TH2F("h_jet_phi_res_vs_eta", "; #eta; b Jet #phi^{reco} - #phi^{part}", 100, 0., 2.5, 100, -3.14, 3.14);
  
  TH3F *h_jet_pTres_vs_etares_vs_pT=new TH3F("h_jet_pTres_vs_etares_vs_pT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{part}) (GeV); Jet (#eta^{reco} - #eta^{part})", 100, 0., 1000., 100, -200., 200., 100, -2.5, 2.5);
  TH3F *h_jet_pTres_vs_phires_vs_pT=new TH3F("h_jet_pTres_vs_phires_vs_pT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{part}) (GeV); Jet (#phi^{reco} - #phi^{part})", 100, 0., 1000., 100, -200., 200., 100, -3.14, 3.14);
  
  TH2F *h_recopT_minus_partpT_vs_recopT = new TH2F("h_recopT_minus_partpT_vs_recopT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{part}) (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_recopT_minus_genpT_vs_recopT = new TH2F("h_recopT_minus_genpT_vs_recopT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{reco} - p_{T}^{gen}) (GeV)", 100, 0., 1000., 100, -200., 200.);
  TH2F *h_genpT_minus_partpT_vs_recopT = new TH2F("h_genpT_minus_partpT_vs_recopT", "; p_{T}^{reco} (GeV); Jet (p_{T}^{gen} - p_{T}^{part}) (GeV)", 100, 0., 1000., 100, -200., 200.);
  
  TH1F *h_mX_genForKinFitCheck = new TH1F("h_mX_genForKinFitCheck", "; m_{X} (GeV)", 2000, 0., 2000.);  h_mX_genForKinFitCheck->Sumw2();
  
  // Event loop
  double nCut4=0, nCutGen=0;
  for (int i=0; i<tree->GetEntries(); ++i)
  {
    tree->GetEvent(i);
    
    bool foundHH=false;
    double m_diff_old=50.;
    int H1jet1_i=-1, H1jet2_i=-1;
    int H2jet1_i=-1, H2jet2_i=-1;
    
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
      
      TLorentzVector jet1_MC_p4=fillTLorentzVector(jet_MCpT[H1jet1_i], jet_MCeta[H1jet1_i], jet_MCphi[H1jet1_i], jet_MCmass[H1jet1_i]);
      TLorentzVector jet2_MC_p4=fillTLorentzVector(jet_MCpT[H1jet2_i], jet_MCeta[H1jet2_i], jet_MCphi[H1jet2_i], jet_MCmass[H1jet2_i]);    
      TLorentzVector jet3_MC_p4=fillTLorentzVector(jet_MCpT[H2jet1_i], jet_MCeta[H2jet1_i], jet_MCphi[H2jet1_i], jet_MCmass[H2jet1_i]);    
      TLorentzVector jet4_MC_p4=fillTLorentzVector(jet_MCpT[H2jet2_i], jet_MCeta[H2jet2_i], jet_MCphi[H2jet2_i], jet_MCmass[H2jet2_i]);
      
      // Check purity of jet selection here
      int purity=-3;
      double mX_genForKinFitCheck=0;
      if (nGenBQuarkFromH==4)
      {
        TLorentzVector b1_p4=fillTLorentzVector(genBQuarkFromH_pT[0], genBQuarkFromH_eta[0], genBQuarkFromH_phi[0], genBQuarkFromH_mass[0]);
        TLorentzVector b2_p4=fillTLorentzVector(genBQuarkFromH_pT[1], genBQuarkFromH_eta[1], genBQuarkFromH_phi[1], genBQuarkFromH_mass[1]);
        TLorentzVector b3_p4=fillTLorentzVector(genBQuarkFromH_pT[2], genBQuarkFromH_eta[2], genBQuarkFromH_phi[2], genBQuarkFromH_mass[2]);
        TLorentzVector b4_p4=fillTLorentzVector(genBQuarkFromH_pT[3], genBQuarkFromH_eta[3], genBQuarkFromH_phi[3], genBQuarkFromH_mass[3]);
        TLorentzVector j[4]={jet1_p4, jet2_p4, jet3_p4, jet4_p4};
        TLorentzVector j_MC[4]={jet1_MC_p4, jet2_MC_p4, jet3_MC_p4, jet4_MC_p4};
        TLorentzVector b[4]={b1_p4,   b2_p4,   b3_p4,   b4_p4};
        int jMatchedbindex[4]={-1, -1, -1, -1};
        purity=purityTest(j, b, jMatchedbindex);
        if (purity==4)
        {
          nCutGen+=eventWeight;
          for (unsigned int ijet=0; ijet<4; ++ijet)
          {
            double res_pT=j[ijet].Pt() - b[jMatchedbindex[ijet]].Pt();
            double res_eta=j[ijet].Eta() - b[jMatchedbindex[ijet]].Eta();
            double res_phi=j[ijet].Phi() - b[jMatchedbindex[ijet]].Phi();
            
            h_jet_pT_res_vs_pT->Fill(j[ijet].Pt(), res_pT, eventWeight);
            h_jet_pT_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_pT, eventWeight);
            
            h_jet_eta_res_vs_pT->Fill(j[ijet].Pt(), res_eta, eventWeight);
            h_jet_eta_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_eta, eventWeight);
            
            h_jet_phi_res_vs_pT->Fill(j[ijet].Pt(), res_phi, eventWeight);
            h_jet_phi_res_vs_eta->Fill(fabs(j[ijet].Eta()), res_phi, eventWeight);
            
            h_jet_pTres_vs_etares_vs_pT->Fill(j[ijet].Pt(), res_pT, res_eta, eventWeight);
            h_jet_pTres_vs_phires_vs_pT->Fill(j[ijet].Pt(), res_pT, res_phi, eventWeight);
            
            h_recopT_minus_partpT_vs_recopT->Fill(j[ijet].Pt(), j[ijet].Pt() - b[jMatchedbindex[ijet]].Pt(), eventWeight);
            if (j_MC[ijet].Pt()>0) h_recopT_minus_genpT_vs_recopT->Fill(j[ijet].Pt(), j[ijet].Pt() - j_MC[ijet].Pt(), eventWeight);
            if (j_MC[ijet].Pt()>0) h_genpT_minus_partpT_vs_recopT->Fill(j[ijet].Pt(), j_MC[ijet].Pt() - b[jMatchedbindex[ijet]].Pt(), eventWeight);
            
            // In eta bins
            if (fabs(j[ijet].Eta())<1.4)
            {
              h_jet_pT_res_vs_pT_eta_0_1p4->Fill(j[ijet].Pt(), res_pT, eventWeight);
            }
            else if (fabs(j[ijet].Eta())<2.5)
            {
              h_jet_pT_res_vs_pT_eta_1p4_2p5->Fill(j[ijet].Pt(), res_pT, eventWeight);
            }
          }
        }
        
        // Smear the generated 4 vector
        TLorentzVector b1_smeared_p4=asymmetricGaussianSmear(b1_p4, 5, 25);
        TLorentzVector b2_smeared_p4=asymmetricGaussianSmear(b2_p4, 5, 25);
        TLorentzVector b3_smeared_p4=asymmetricGaussianSmear(b3_p4, 5, 25);
        TLorentzVector b4_smeared_p4=asymmetricGaussianSmear(b4_p4, 5, 25);
        double chi2=constrainHH(&b1_smeared_p4, &b2_smeared_p4, &b3_smeared_p4, &b4_smeared_p4);
        mX_genForKinFitCheck=(b1_smeared_p4+b2_smeared_p4+b3_smeared_p4+b4_smeared_p4).M();
        
        h_mX_genForKinFitCheck->Fill(mX_genForKinFitCheck, eventWeight);
      }
      else
      {
        std::cout<<"ERROR: This is not a X -> HH -> bbbb signal sample."<<std::endl;
      }
    }
  } // Event loop

  // Write histograms to file
  std::string histfilename="ResolutionHistograms_"+sample+".root";
  TFile *tFile2=new TFile(histfilename.c_str(), "RECREATE");
  h_jet_pT_res_vs_pT->Write();
  h_jet_pT_res_vs_eta->Write();
  h_jet_eta_res_vs_eta->Write();
  h_jet_eta_res_vs_pT->Write();
  h_jet_phi_res_vs_eta->Write();
  h_jet_phi_res_vs_pT->Write();
  h_jet_pTres_vs_etares_vs_pT->Write();
  h_jet_pTres_vs_phires_vs_pT->Write();
  h_jet_pT_res_vs_pT_eta_0_1p4->Write();
  h_jet_pT_res_vs_pT_eta_1p4_2p5->Write();
  h_recopT_minus_partpT_vs_recopT->Write();
  h_recopT_minus_genpT_vs_recopT->Write();
  h_genpT_minus_partpT_vs_recopT->Write();
  h_mX_genForKinFitCheck->Write();
  tFile2->Write();
  tFile2->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;

  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.5)  = "<<nCut4<<std::endl;
  std::cout<<"Number of matched events "<<nCutGen<<std::endl;
  std::cout<<"========================"<<std::endl;
  
  // Delete all histograms
  delete h_jet_pT_res_vs_pT;
  delete h_jet_pT_res_vs_eta;
  delete h_jet_eta_res_vs_eta;
  delete h_jet_eta_res_vs_pT;
  delete h_jet_phi_res_vs_eta;
  delete h_jet_phi_res_vs_pT;
  delete h_jet_pTres_vs_etares_vs_pT;
  delete h_jet_pTres_vs_phires_vs_pT;
  delete h_jet_pT_res_vs_pT_eta_0_1p4;
  delete h_jet_pT_res_vs_pT_eta_1p4_2p5;
  delete h_recopT_minus_partpT_vs_recopT;
  delete h_recopT_minus_genpT_vs_recopT;
  delete h_genpT_minus_partpT_vs_recopT;
  delete h_mX_genForKinFitCheck;
}
