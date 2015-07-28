/*---------------------------------------------/
Analysis Code for X->HH->bbbb searches in CMS
Authors: Souvik Das (Univ. of Florida), 
         Caterina Vernieri (Fermilab)
/---------------------------------------------*/

#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <iostream>

// Hardcoded configuration parameters
double jet_pT_cut=40.;
double jet_eta_cut=2.5;
/////////////////////////////////////

typedef std::map<double, int> JetList;

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
  bool isData;
  double trigger_HLT_HH4bDouble, trigger_HLT_HH4bQuad;
  double vType;
  double puWeight;
  int nJets;
  double jet_btagCSV[100], jet_btagCMVA[100];
  double jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100];
  
  // Retrieve variables
  tree->SetBranchAddress("evt", &evt);
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("evt", 1);
  tree->SetBranchAddress("run", &run);                                tree->SetBranchStatus("run", 1);  
  tree->SetBranchAddress("isData", &isData);                          tree->SetBranchStatus("isData", 1);
  tree->SetBranchAddress("HLT_HH4bDouble", &trigger_HLT_HH4bDouble);  tree->SetBranchStatus("HLT_HH4bDouble", 1);
  tree->SetBranchAddress("HLT_HH4bQuad", &trigger_HLT_HH4bQuad);      tree->SetBranchStatus("HLT_HH4bQuad", 1);
  tree->SetBranchAddress("Vtype", &(vType));                          tree->SetBranchStatus("Vtype", 1); 
  tree->SetBranchAddress("puWeight", &(puWeight));                    tree->SetBranchStatus("puWeight", 1); 
  tree->SetBranchAddress("nJet", &(nJets));                           tree->SetBranchStatus("nJet", 1); 
  tree->SetBranchAddress("Jet_btagCSV", &(jet_btagCSV));              tree->SetBranchStatus("Jet_btagCSV", 1); 
  tree->SetBranchAddress("Jet_btagCMVA", &(jet_btagCMVA));            tree->SetBranchStatus("Jet_btagCMVA", 1); 
  tree->SetBranchAddress("Jet_pt", &(jet_pT));                        tree->SetBranchStatus("Jet_pt", 1); 
  tree->SetBranchAddress("Jet_eta", &(jet_eta));                      tree->SetBranchStatus("Jet_eta", 1); 
  tree->SetBranchAddress("Jet_phi", &(jet_phi));                      tree->SetBranchStatus("Jet_phi", 1); 
  tree->SetBranchAddress("Jet_mass", &(jet_mass));                    tree->SetBranchStatus("Jet_mass", 1);
  
  TH1F *h_nJets=new TH1F("h_nJets", "h_nJets; # Cleaned PAT Jets; n", 10, 0., 10.);
  
  TH1F *h_pTOrder_JetpT_1=new TH1F("h_pTOrder_JetpT_1", "; pT Ordered Jet pT 1 (GeV); Events", 50, 0., 800.);
  TH1F *h_pTOrder_JetpT_2=new TH1F("h_pTOrder_JetpT_2", "; pT Ordered Jet pT 2 (GeV); Events", 50, 0., 500.);
  TH1F *h_pTOrder_JetpT_3=new TH1F("h_pTOrder_JetpT_3", "; pT Ordered Jet pT 3 (GeV); Events", 50, 0., 350.);
  TH1F *h_pTOrder_JetpT_4=new TH1F("h_pTOrder_JetpT_4", "; pT Ordered Jet pT 4 (GeV); Events", 50, 0., 250.);
  TH1F *h_pTOrder_JetCSV_1=new TH1F("h_pTOrder_JetCSV_1", "; pT Ordered Jet CSV 1 (GeV); Events", 50, 0., 1.);
  TH1F *h_pTOrder_JetCSV_2=new TH1F("h_pTOrder_JetCSV_2", "; pT Ordered Jet CSV 2 (GeV); Events", 50, 0., 1.);
  TH1F *h_pTOrder_JetCSV_3=new TH1F("h_pTOrder_JetCSV_3", "; pT Ordered Jet CSV 3 (GeV); Events", 50, 0., 1.);
  TH1F *h_pTOrder_JetCSV_4=new TH1F("h_pTOrder_JetCSV_4", "; pT Ordered Jet CSV 4 (GeV); Events", 50, 0., 1.);
  
  TH1F *h_Cuts=new TH1F("h_Cuts", "Cut flow", 16, 0, 16);
  TAxis *a_Cuts=h_Cuts->GetXaxis();
  a_Cuts->SetBinLabel(2, "Initial");
  a_Cuts->SetBinLabel(4, "Trigger");
  a_Cuts->SetBinLabel(6, "Vtype");
  a_Cuts->SetBinLabel(8, "nCJets>=4");
  a_Cuts->SetBinLabel(10, "HH Cand");
  a_Cuts->SetBinLabel(12, "SR");
  
  // Output tree in new file
  std::string outfilename="PreSelected_"+sample+".root";
  TFile *outfile=new TFile(outfilename.c_str(), "recreate");
  TTree *outtree=tree->CloneTree(0);
  std::vector<unsigned int> jetIndex_pTOrder;
  std::vector<unsigned int> jetIndex_CSVOrder;
  std::vector<unsigned int> jetIndex_CMVAOrder;
  outtree->Branch("jetIndex_pTOrder", &jetIndex_pTOrder);
  outtree->Branch("jetIndex_CSVOrder", &jetIndex_CSVOrder);
  outtree->Branch("jetIndex_CMVAOrder", &jetIndex_CMVAOrder);
  
  // Loop over events
  int nEvents=tree->GetEntries();
  double nCut0=0, nCut1=0, nCut2=0, nCut3=0, nCut4=0, nCut5=0;
  for (int i=0; i<nEvents; ++i)
  {
    ++nCut0;
    tree->GetEvent(i);
    
    if (trigger_HLT_HH4bDouble==1 || trigger_HLT_HH4bQuad==1)
    {
      ++nCut1;
      
      if (vType==-1)
      {
        ++nCut2;
        
        // Order the jets by pT, CSV, and CMVA
        JetList jetList_pTOrder;
        JetList jetList_CSVOrder;
        JetList jetList_CMVAOrder;
        int nCJets=0;
        double ht=0;
        for (unsigned int j=0; j<(unsigned int)nJets; ++j)
        {
          if (jet_pT[j]>jet_pT_cut && fabs(jet_eta[j])<jet_eta_cut) 
          {
            ++nCJets;
            jetList_pTOrder[jet_pT[j]]=j;
            jetList_CSVOrder[jet_btagCSV[j]]=j;
            jetList_CMVAOrder[jet_btagCMVA[j]]=j;
          }
        }
        h_nJets->Fill(nCJets);
        
        // Fill jet pT order histograms
        JetList::reverse_iterator iJet=jetList_pTOrder.rbegin();
        if (iJet!=jetList_pTOrder.rend())
        {
          h_pTOrder_JetpT_1->Fill(iJet->first, puWeight);
          h_pTOrder_JetCSV_1->Fill(jet_btagCSV[iJet->second]);
          ++iJet; 
          if (iJet!=jetList_pTOrder.rend())
          {
            h_pTOrder_JetpT_2->Fill(iJet->first, puWeight);
            h_pTOrder_JetCSV_2->Fill(jet_btagCSV[iJet->second]);
            ++iJet; 
            if (iJet!=jetList_pTOrder.rend()) 
            {
              h_pTOrder_JetpT_3->Fill(iJet->first, puWeight);
              h_pTOrder_JetCSV_2->Fill(jet_btagCSV[iJet->second]);
              ++iJet; 
              if (iJet!=jetList_pTOrder.rend()) 
              {
                h_pTOrder_JetpT_4->Fill(iJet->first, puWeight);
                h_pTOrder_JetCSV_4->Fill(jet_btagCSV[iJet->second]);
              }
            }
          }
        }
        
        if (nCJets>=4)
        {
          ++nCut3;
          
          for (JetList::reverse_iterator iJet=jetList_pTOrder.rbegin(); iJet!=jetList_pTOrder.rend(); ++iJet)
          {
            jetIndex_pTOrder.push_back(iJet->second);
          }
          
          for (JetList::reverse_iterator iJet=jetList_CSVOrder.rbegin(); iJet!=jetList_CSVOrder.rend(); ++iJet)
          {
            jetIndex_CSVOrder.push_back(iJet->second);
          }
          
          for (JetList::reverse_iterator iJet=jetList_CMVAOrder.rbegin(); iJet!=jetList_CMVAOrder.rend(); ++iJet)
          {
            jetIndex_CMVAOrder.push_back(iJet->second);
          }
          
          // Write out tree
          outtree->Fill();
          
        } // nCJets>=4
        
        jetIndex_pTOrder.clear();
        jetIndex_CSVOrder.clear();
        jetIndex_CMVAOrder.clear();
        
      } // vType==-1
    } // Trigger
    
    if (i%(nEvents/10)==0) std::cout<<int(i*100./nEvents)+1<<"% of "<<nEvents<<" events have been processed."<<std::endl;
    
  } // Event loop
  
  h_Cuts->Fill(1, nCut0); // Initial
  h_Cuts->Fill(3, nCut1); // Trigger
  h_Cuts->Fill(5, nCut2); // Vtype
  h_Cuts->Fill(7, nCut3); // nCJets>=4
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
  h_nJets->Write();
  h_pTOrder_JetpT_1->Write();
  h_pTOrder_JetpT_2->Write();
  h_pTOrder_JetpT_3->Write();
  h_pTOrder_JetpT_4->Write();
  h_pTOrder_JetCSV_1->Write();
  h_pTOrder_JetCSV_2->Write();
  h_pTOrder_JetCSV_3->Write();
  h_pTOrder_JetCSV_4->Write();
  h_Cuts->Write();
  tFile->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  
  std::cout<<"=== Cut Efficiencies === "<<std::endl;
  if (isData==false) std::cout<<"Initial number of events = "<<nInitial<<std::endl;
  std::cout<<"Number of events at the end of step 2 = "<<nCut0<<std::endl;
  std::cout<<"Number of events after trigger = "<<nCut1<<std::endl;
  std::cout<<"Number of events after Vtype==-1 = "<<nCut2<<std::endl;
  std::cout<<"Number of events after nCJets>=4 = "<<nCut3<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.4)  = "<<nCut4<<std::endl;
  std::cout<<"Number of events after finding X = "<<nCut5<<", eff. = "<<nCut5/nInitial<<std::endl;
  std::cout<<"========================"<<std::endl;
  
}
            
      
  
  
  
  
