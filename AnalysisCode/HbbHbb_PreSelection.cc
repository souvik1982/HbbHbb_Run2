/*----------------------------------------------------------------/
Analysis Code for X->HH->bbbb searches in CMS
Authors: Souvik Das (Univ. of Florida) & Caterina Vernieri (FNAL)
/----------------------------------------------------------------*/

#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <iostream>
#include "TLorentzVector.h"

double pi=3.14159265358979;

// Hardcoded configuration parameters
double jet_pT_cut=40.;
double jet_pT_ttbar_cut=20.;
double jet_eta_cut=2.5;
double jet_btag_cut=0.6;
/////////////////////////////////////

typedef std::map<double, int> JetList;

void fillHistogramsFromJetList(JetList jetList, std::vector<TH1F*> histograms, double eventWeight)
{
  int nHistograms=histograms.size();
  int i_histogram=0;
  for (JetList::reverse_iterator iJet=jetList.rbegin(); (iJet!=jetList.rend() && i_histogram<nHistograms); ++iJet, ++i_histogram)
  {
    histograms.at(i_histogram)->Fill(iJet->first, eventWeight);
  }
}

void fillIndexVectorFromJetList(JetList jetList, std::vector<unsigned int> *indexVector)
{
  for (JetList::reverse_iterator iJet=jetList.rbegin(); iJet!=jetList.rend(); ++iJet)
  {
    indexVector->push_back(iJet->second);
  }
}

void HbbHbb_PreSelection(std::string dir, std::string sample, 
                              std::string sigmaJECUnc_string="JEC", 
                              std::string sigmaJERUnc_string="JER")
{
  
  std::string inputfilename=dir+"/"+sample+".root";
  TChain *tree=new TChain("tree");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;
  
  double sigmaJECUnc; // -1, 0, +1
  double sigmaJERUnc; // -1, 0, +1
  if (sigmaJECUnc_string=="JEC") sigmaJECUnc=0;
  else if (sigmaJECUnc_string=="JECp1") sigmaJECUnc=1;
  else if (sigmaJECUnc_string=="JECm1") sigmaJECUnc=-1;
  
  if (sigmaJERUnc_string=="JER") sigmaJERUnc=0;
  else if (sigmaJERUnc_string=="JERp1") sigmaJERUnc=1;
  else if (sigmaJERUnc_string=="JERm1") sigmaJERUnc=-1;
  
  // Book variables
  int run;
  int evt;
  int isData;
  float trigger_HLT_HH4bLowLumi;
  float vType;
  float puWeight, genWeight;
  int nJets;
  float jet_btagCSV[100], jet_btagCMVA[100];
  float jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
  int nGenHiggsBoson;	
  float genHiggsBoson_pT[100], genHiggsBoson_eta[100], genHiggsBoson_phi[100], genHiggsBoson_mass[100];
  float eventWeight;
  int nGenBQuarkFromH;
  float genBQuarkFromH_pT[100], genBQuarkFromH_eta[100], genBQuarkFromH_phi[100], genBQuarkFromH_mass[100];
  float jet_MCpT[100], jet_MCeta[100], jet_MCphi[100], jet_MCmass[100];
  float met_pT, met_phi;
  
  // Retrieve variables
  tree->SetBranchAddress("evt", &evt);
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("evt", 1);
  tree->SetBranchAddress("run", &run);                                   tree->SetBranchStatus("run", 1);  
  tree->SetBranchAddress("isData", &isData);                             tree->SetBranchStatus("isData", 1);
  tree->SetBranchAddress("HLT_HH4bLowLumi", &trigger_HLT_HH4bLowLumi);   tree->SetBranchStatus("HLT_HH4bLowLumi", 1);
  tree->SetBranchAddress("Vtype", &(vType));                             tree->SetBranchStatus("Vtype", 1); 
  tree->SetBranchAddress("puWeight", &(puWeight));                       tree->SetBranchStatus("puWeight", 1); 
  tree->SetBranchAddress("genWeight", &(genWeight));                     tree->SetBranchStatus("genWeight", 1);
  tree->SetBranchAddress("nJet", &(nJets));                              tree->SetBranchStatus("nJet", 1); 
  tree->SetBranchAddress("Jet_btagCSV", &(jet_btagCSV));                 tree->SetBranchStatus("Jet_btagCSV", 1); 
  tree->SetBranchAddress("Jet_btagCMVA", &(jet_btagCMVA));               tree->SetBranchStatus("Jet_btagCMVA", 1);
  tree->SetBranchAddress("Jet_pt", &(jet_pT));                           tree->SetBranchStatus("Jet_pt", 1); 
  tree->SetBranchAddress("Jet_eta", &(jet_eta));                         tree->SetBranchStatus("Jet_eta", 1); 
  tree->SetBranchAddress("Jet_phi", &(jet_phi));                         tree->SetBranchStatus("Jet_phi", 1); 
  tree->SetBranchAddress("Jet_mass", &(jet_mass));                       tree->SetBranchStatus("Jet_mass", 1);
  tree->SetBranchAddress("Jet_mcPt", &(jet_MCpT));                       tree->SetBranchStatus("Jet_mcPt", 1);
  tree->SetBranchAddress("Jet_mcEta", &(jet_MCeta));                     tree->SetBranchStatus("Jet_mcEta", 1);
  tree->SetBranchAddress("Jet_mcPhi", &(jet_MCphi));                     tree->SetBranchStatus("Jet_mcPhi", 1);
  tree->SetBranchAddress("Jet_mcM", &(jet_MCmass));                      tree->SetBranchStatus("Jet_mcM", 1);
  tree->SetBranchAddress("nGenHiggsBoson", &(nGenHiggsBoson));           tree->SetBranchStatus("nGenHiggsBoson",1);
  tree->SetBranchAddress("GenHiggsBoson_pt", &(genHiggsBoson_pT));       tree->SetBranchStatus("GenHiggsBoson_pt",1);
  tree->SetBranchAddress("GenHiggsBoson_eta", &(genHiggsBoson_eta));     tree->SetBranchStatus("GenHiggsBoson_eta",1);
  tree->SetBranchAddress("GenHiggsBoson_phi", &(genHiggsBoson_phi));     tree->SetBranchStatus("GenHiggsBoson_phi",1);
  tree->SetBranchAddress("GenHiggsBoson_mass", &(genHiggsBoson_mass));   tree->SetBranchStatus("GenHiggsBoson_mass",1);
  tree->SetBranchAddress("nGenBQuarkFromH", &(nGenBQuarkFromH));         tree->SetBranchStatus("nGenBQuarkFromH",1);
  tree->SetBranchAddress("GenBQuarkFromH_pt", &(genBQuarkFromH_pT));     tree->SetBranchStatus("GenBQuarkFromH_pt", 1);
  tree->SetBranchAddress("GenBQuarkFromH_eta", &(genBQuarkFromH_eta));   tree->SetBranchStatus("GenBQuarkFromH_eta", 1);
  tree->SetBranchAddress("GenBQuarkFromH_phi", &(genBQuarkFromH_phi));   tree->SetBranchStatus("GenBQuarkFromH_phi", 1);
  tree->SetBranchAddress("GenBQuarkFromH_mass", &(genBQuarkFromH_mass)); tree->SetBranchStatus("GenBQuarkFromH_mass", 1);
  tree->SetBranchAddress("met_pt", &(met_pT));                           tree->SetBranchStatus("met_pt", 1);
  tree->SetBranchAddress("met_phi", &(met_phi));                         tree->SetBranchStatus("met_phi", 1);
  
  TH1F *h_nCbJets=new TH1F("h_nCbJets", "; # Cleaned PAT Jets with |#eta|<2.5, p_{T} > 40 GeV, CSV > 0.6; Events", 10, 0., 10.);
  
  TH1F *h_pTOrder_JetpT_1=new TH1F("h_pTOrder_JetpT_1", "; Jet pT 1 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 800.);
  TH1F *h_pTOrder_JetpT_2=new TH1F("h_pTOrder_JetpT_2", "; Jet pT 2 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 500.);
  TH1F *h_pTOrder_JetpT_3=new TH1F("h_pTOrder_JetpT_3", "; Jet pT 3 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 350.);
  TH1F *h_pTOrder_JetpT_4=new TH1F("h_pTOrder_JetpT_4", "; Jet pT 4 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
  TH1F *h_pTOrder_JetpT_5=new TH1F("h_pTOrder_JetpT_5", "; Jet pT 5 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
  TH1F *h_CSVOrder_JetCSV_1=new TH1F("h_CSVOrder_JetCSV_1", "; Jet CSV 1 for jets with |#eta|<2.5, p_{T} > 40 GeV; Events", 50, 0., 1.);
  TH1F *h_CSVOrder_JetCSV_2=new TH1F("h_CSVOrder_JetCSV_2", "; Jet CSV 2 for jets with |#eta|<2.5, p_{T} > 40 GeV; Events", 50, 0., 1.);
  TH1F *h_CSVOrder_JetCSV_3=new TH1F("h_CSVOrder_JetCSV_3", "; Jet CSV 3 for jets with |#eta|<2.5, p_{T} > 40 GeV; Events", 50, 0., 1.);
  TH1F *h_CSVOrder_JetCSV_4=new TH1F("h_CSVOrder_JetCSV_4", "; Jet CSV 4 for jets with |#eta|<2.5, p_{T} > 40 GeV; Events", 50, 0., 1.);
  
  TH1F *h_GenX_mass=new TH1F("h_GenX_mass", "; m_{X}^{GEN} (GeV); Events", 1800, 200, 2000);
  TH1F *h_dR_genHbb=new TH1F("h_dR_genHbb", "; #Delta R(b#bar{b}}; Events", 1000, 0., 5.);
  
  TH1F *h_MET=new TH1F("h_MET", "; MET (GeV); Events", 50, 0., 500.);
  TH1F *h_MET_phi=new TH1F("h_MET_phi", "; #phi_{MET} (GeV)", 50, -pi, pi);
  
  TH1F *h_Cuts=new TH1F("h_Cuts", "Cut flow", 16, 0, 16);
  TAxis *a_Cuts=h_Cuts->GetXaxis();
  a_Cuts->SetBinLabel(2, "Initial");
  a_Cuts->SetBinLabel(4, "Trigger");
  a_Cuts->SetBinLabel(6, "Vtype");
  a_Cuts->SetBinLabel(8, "nCbJets>=4");
  a_Cuts->SetBinLabel(10, "HH Cand");
  a_Cuts->SetBinLabel(12, "SR");
  
  // Output tree in new file
  std::string outfilename="PreSelected_"+sample+".root";
  TFile *outfile=new TFile(outfilename.c_str(), "recreate");
  TTree *outtree=tree->CloneTree(0);
  std::vector<unsigned int> jetIndex_CentralpT40btag_pTOrder;
  std::vector<unsigned int> jetIndex_CentralpT40btag_CSVOrder;
  std::vector<unsigned int> jetIndex_CentralpT40btag_CMVAOrder;
  std::vector<unsigned int> jetIndex_Central_pTOrder;
  outtree->Branch("jetIndex_CentralpT40btag_pTOrder", &jetIndex_CentralpT40btag_pTOrder);
  outtree->Branch("jetIndex_CentralpT40btag_CSVOrder", &jetIndex_CentralpT40btag_CSVOrder);
  outtree->Branch("jetIndex_CentralpT40btag_CMVAOrder", &jetIndex_CentralpT40btag_CMVAOrder);
  outtree->Branch("jetIndex_Central_pTOrder", &jetIndex_Central_pTOrder);
  outtree->Branch("eventWeight", &eventWeight);
  
  // Loop over events
  int nEvents=tree->GetEntries();
  double nCut0=0, nCut1=0, nCut2=0, nCut3=0, nCut4=0, nCut5=0;
  for (int i=0; i<nEvents; ++i)
  {
    ++nCut0;
    tree->GetEvent(i);
    
    if (isData==1) eventWeight=1;
    else eventWeight=puWeight*genWeight/fabs(genWeight);
    
    if (nGenHiggsBoson==2)
    {
      TLorentzVector gen_H1,gen_H2;
      gen_H1.SetPtEtaPhiM(genHiggsBoson_pT[0], genHiggsBoson_eta[0], genHiggsBoson_phi[0], genHiggsBoson_mass[0]);
      gen_H2.SetPtEtaPhiM(genHiggsBoson_pT[1], genHiggsBoson_eta[1], genHiggsBoson_phi[1], genHiggsBoson_mass[1]);
      h_GenX_mass->Fill((gen_H1+gen_H2).M(), eventWeight);
    }
    
    if (nGenBQuarkFromH==4)
    {
      TLorentzVector gen_H1_b, gen_H1_bbar;
      gen_H1_b.SetPtEtaPhiM(genBQuarkFromH_pT[0], genBQuarkFromH_eta[0], genBQuarkFromH_phi[0], genBQuarkFromH_mass[0]);
      gen_H1_bbar.SetPtEtaPhiM(genBQuarkFromH_pT[1], genBQuarkFromH_eta[1], genBQuarkFromH_phi[1], genBQuarkFromH_mass[1]);
      h_dR_genHbb->Fill(gen_H1_b.DeltaR(gen_H1_bbar), eventWeight);
    }
    
    h_MET->Fill(met_pT, eventWeight);
    h_MET_phi->Fill(met_phi, eventWeight);	
    
    // std::cout<<"trigger_HLT_HH4bLowLumi = "<<trigger_HLT_HH4bLowLumi<<std::endl;
    // std::cout<<"trigger_HLT_HH4bLowLumi = "<<trigger_HLT_HH4bLowLumi<<std::endl;
    if (trigger_HLT_HH4bLowLumi==1)
    {
      nCut1+=eventWeight;
      
      if (vType==-1)
      {
        nCut2+=eventWeight;
        
        // Order the jets by pT, CSV, and CMVA
        JetList jetList_Central_pTOrder;
        JetList jetList_CentralpT40_CSVOrder;
        JetList jetList_CentralpT40btag_pTOrder;
        JetList jetList_CentralpT40btag_CSVOrder;
        JetList jetList_CentralpT40btag_CMVAOrder;
        int nCbJets=0;
        double ht=0;
        for (unsigned int j=0; j<(unsigned int)nJets; ++j)
        {
          if (fabs(jet_eta[j])<jet_eta_cut) 
          {
            jetList_Central_pTOrder[jet_pT[j]]=j;
            if (jet_pT[j]>jet_pT_cut)
            {
              if (jet_btagCSV[j]>0) jetList_CentralpT40_CSVOrder[jet_btagCSV[j]]=j;
              {
                if (jet_btagCSV[j]>jet_btag_cut)
                {
                  ++nCbJets;
                  jetList_CentralpT40btag_pTOrder[jet_pT[j]]=j;
                  if (jet_btagCSV[j]>0) jetList_CentralpT40btag_CSVOrder[jet_btagCSV[j]]=j;
                  if (jet_btagCMVA[j]>0) jetList_CentralpT40btag_CMVAOrder[jet_btagCMVA[j]]=j;
                }
              }
            }
          }
        }
        h_nCbJets->Fill(nCbJets);
        
        // Fill jet pT order histograms
        std::vector<TH1F*> v_pTOrder_JetpT = {h_pTOrder_JetpT_1, h_pTOrder_JetpT_2, h_pTOrder_JetpT_3, h_pTOrder_JetpT_4, h_pTOrder_JetpT_5};
        std::vector<TH1F*> v_CSVOrder_JetCSV = {h_CSVOrder_JetCSV_1, h_CSVOrder_JetCSV_2, h_CSVOrder_JetCSV_3, h_CSVOrder_JetCSV_4};
        fillHistogramsFromJetList(jetList_Central_pTOrder, v_pTOrder_JetpT, puWeight);
        fillHistogramsFromJetList(jetList_CentralpT40_CSVOrder, v_CSVOrder_JetCSV, puWeight);
        
        // A non-symmetric CSV cut
        /*if (jetList_CentralpT40_CSVOrder.size()>=4)
        {
          if (jet_btagCSV[1highestCSVjet]>0.9)
          {
            if (jet_btagCSV[2highestCSVjet]>0.8)
            {
              if (jet_btagCSV[3highestCSVjet]>0.8)
              {
                // keep event
              }
            }
          }
        }*/
        
        if (nCbJets>=3)
        {
          nCut3+=eventWeight;
          
          fillIndexVectorFromJetList(jetList_CentralpT40btag_pTOrder, &jetIndex_CentralpT40btag_pTOrder);
          fillIndexVectorFromJetList(jetList_CentralpT40btag_CSVOrder, &jetIndex_CentralpT40btag_CSVOrder);
          fillIndexVectorFromJetList(jetList_CentralpT40btag_CMVAOrder, &jetIndex_CentralpT40btag_CMVAOrder);
          fillIndexVectorFromJetList(jetList_Central_pTOrder, &jetIndex_Central_pTOrder);
          
          // Write out tree
          outtree->Fill();
          
        } // nCbJets>=4
        
        jetIndex_CentralpT40btag_pTOrder.clear();
        jetIndex_CentralpT40btag_CSVOrder.clear();
        jetIndex_CentralpT40btag_CMVAOrder.clear();
        jetIndex_Central_pTOrder.clear();
        
      } // vType==-1
    } // Trigger
    
    if (i%(nEvents/10)==0) std::cout<<int(i*100./nEvents)+1<<"% of "<<nEvents<<" events have been processed."<<std::endl;
    
  } // Event loop
  
  h_Cuts->Fill(1, nCut0); // Initial
  h_Cuts->Fill(3, nCut1); // Trigger
  h_Cuts->Fill(5, nCut2); // Vtype
  h_Cuts->Fill(7, nCut3); // nCbJets>=4
  h_Cuts->Fill(9, nCut4); // HH Candidates
  h_Cuts->Fill(11, nCut5); // SR
  
  outtree->Write();
  outfile->Close();
  std::cout<<"Wrote output file "<<outfilename<<std::endl;
  
  TFile *file=new TFile(inputfilename.c_str());
  TH1F *h_Count=(TH1F*)file->Get("Count");
  double nInitial=h_Count->GetBinContent(1);
                  
  std::string histfilename="Histograms_"+sample+".root";
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_Count->Write();
  h_nCbJets->Write();
  h_pTOrder_JetpT_1->Write();
  h_pTOrder_JetpT_2->Write();
  h_pTOrder_JetpT_3->Write();
  h_pTOrder_JetpT_4->Write();
  h_pTOrder_JetpT_5->Write();
  h_CSVOrder_JetCSV_1->Write();
  h_CSVOrder_JetCSV_2->Write();
  h_CSVOrder_JetCSV_3->Write();
  h_CSVOrder_JetCSV_4->Write();
  h_GenX_mass->Write();
  h_dR_genHbb->Write();
  h_MET->Write();
  h_MET_phi->Write();
  h_Cuts->Write();
  tFile->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  
  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  if (isData==0) std::cout<<"Initial number of events = "<<nInitial<<std::endl;
  std::cout<<"Number of events at the end of step 2 = "<<nCut0<<std::endl;
  std::cout<<"Number of events after trigger = "<<nCut1<<std::endl;
  std::cout<<"Number of events after Vtype==-1 = "<<nCut2<<std::endl;
  std::cout<<"Number of events after nCbJets>=4 = "<<nCut3<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.4)  = "<<nCut4<<std::endl;
  std::cout<<"Number of events after finding X = "<<nCut5<<", eff. = "<<nCut5/nInitial<<std::endl;
  std::cout<<"========================"<<std::endl;
  
  delete h_Count;
  delete h_nCbJets;
  delete h_pTOrder_JetpT_1;
  delete h_pTOrder_JetpT_2;
  delete h_pTOrder_JetpT_3;
  delete h_pTOrder_JetpT_4;
  delete h_pTOrder_JetpT_5;
  delete h_CSVOrder_JetCSV_1;
  delete h_CSVOrder_JetCSV_2;
  delete h_CSVOrder_JetCSV_3;
  delete h_CSVOrder_JetCSV_4;
  delete h_GenX_mass;
  delete h_dR_genHbb;
  delete h_MET;
  delete h_MET_phi;
  delete h_Cuts;
  
}
            
      
  
  
  
  
