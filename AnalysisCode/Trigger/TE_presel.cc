TString runName = "RunB";

void TE_presel()
{

    TString fileName = "root://cmseos.fnal.gov//store/user/lpchbb/HeppyNtuples/V23/SingleMuon" + runName + ".root";
  //  TFile *_file0 = TFile::Open(fileName);
    TChain *tree=new TChain("tree");
    tree->Add(fileName);
  // TChain* tree = (TChain*) _file0->Get("tree");

    int HLT_BIT_HLT_IsoMu24_v, Vtype;
    int nJet, Jet_puId[100], HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v, ntrgObjects_hltQuadCentralJet45, ntrgObjects_hltBTagCaloCSVp087Triple, ntrgObjects_hltQuadPFCentralJetLooseID45,ntrgObjects_hltQuadCentralJet30, ntrgObjects_hltDoubleCentralJet90, ntrgObjects_hltQuadPFCentralJetLooseID30, ntrgObjects_hltDoublePFCentralJetLooseID90, HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v;
    Float_t  jet_pt[100], Jet_eta[100], Jet_btagCSV[100], vLeptons_pt[100], Jet_btagCMVAV2[100];
    tree->SetBranchStatus("*",0);
    tree->SetBranchAddress("Jet_pt", &(jet_pt)); tree->SetBranchStatus("Jet_pt", 1);
    tree->SetBranchAddress("Jet_eta", &(Jet_eta)); tree->SetBranchStatus("Jet_eta", 1);
    tree->SetBranchAddress("Jet_btagCSV", &(Jet_btagCSV)); tree->SetBranchStatus("Jet_btagCSV", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_IsoMu24_v", &(HLT_BIT_HLT_IsoMu24_v)); tree->SetBranchStatus("HLT_BIT_HLT_IsoMu24_v", 1);
    tree->SetBranchAddress("Jet_puId", &(Jet_puId)); tree->SetBranchStatus("Jet_puId", 1);
  tree->SetBranchAddress("ntrgObjects_hltQuadCentralJet30", &(ntrgObjects_hltQuadCentralJet30)); tree->SetBranchStatus("ntrgObjects_hltQuadCentralJet30", 1);
  tree->SetBranchAddress("ntrgObjects_hltDoubleCentralJet90", &(ntrgObjects_hltDoubleCentralJet90)); tree->SetBranchStatus("ntrgObjects_hltDoubleCentralJet90", 1);
  tree->SetBranchAddress("ntrgObjects_hltQuadPFCentralJetLooseID30", &(ntrgObjects_hltQuadPFCentralJetLooseID30)); tree->SetBranchStatus("ntrgObjects_hltQuadPFCentralJetLooseID30", 1);
  tree->SetBranchAddress("ntrgObjects_hltDoublePFCentralJetLooseID90", &(ntrgObjects_hltDoublePFCentralJetLooseID90)); tree->SetBranchStatus("ntrgObjects_hltDoublePFCentralJetLooseID90", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v", &(HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v)); tree->SetBranchStatus("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v", 1);
  tree->SetBranchAddress("nJet", &(nJet)); tree->SetBranchStatus("nJet", 1);
  tree->SetBranchAddress("ntrgObjects_hltQuadCentralJet45", &(ntrgObjects_hltQuadCentralJet45)); tree->SetBranchStatus("ntrgObjects_hltQuadCentralJet45", 1);
  tree->SetBranchAddress("ntrgObjects_hltBTagCaloCSVp087Triple", &(ntrgObjects_hltBTagCaloCSVp087Triple)); tree->SetBranchStatus("ntrgObjects_hltBTagCaloCSVp087Triple", 1);
  tree->SetBranchAddress("ntrgObjects_hltQuadPFCentralJetLooseID45", &(ntrgObjects_hltQuadPFCentralJetLooseID45)); tree->SetBranchStatus("ntrgObjects_hltQuadPFCentralJetLooseID45", 1);
    tree->SetBranchAddress("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", &(HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v)); tree->SetBranchStatus("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v", 1);
    tree->SetBranchAddress("vLeptons_pt", &(vLeptons_pt)); tree->SetBranchStatus("vLeptons_pt", 1);
   tree->SetBranchAddress("Vtype", &(Vtype)); tree->SetBranchStatus("Vtype", 1);
  tree->SetBranchAddress("Jet_btagCMVAV2", &(Jet_btagCMVAV2)); tree->SetBranchStatus("Jet_btagCMVAV2", 1);

  Float_t  jet_pt_[100], Jet_eta_[100], Jet_btagCSV_[100], Jet_btagCMVAV2_[100];
  int  Jet_puId_[100];
  TFile *outfile=new TFile("SingleMuonSkimmed"+runName+".root", "recreate");  
  TTree *outtree=tree->CloneTree(0);
  Float_t CSVsorted[100],  CMVAVsorted[100];
  // outtree->SetBranchAddress("CSVsorted", &(CSVsorted)); tree->SetBranchStatus("CSVsorted", 1);
    outtree->Branch("CMVAVsorted",&CMVAVsorted,"CMVAVsorted[nJet]/F");
    outtree->Branch("CSVsorted",&CSVsorted,"CSVsorted[nJet]/F");
    outtree->SetBranchAddress("Jet_pt", &(jet_pt_)); tree->SetBranchStatus("Jet_pt", 1);
    outtree->SetBranchAddress("Jet_eta", &(Jet_eta_)); tree->SetBranchStatus("Jet_eta", 1);
    outtree->SetBranchAddress("Jet_btagCSV", &(Jet_btagCSV_)); tree->SetBranchStatus("Jet_btagCSV", 1);

    outtree->SetBranchAddress("Jet_puId", &(Jet_puId_)); tree->SetBranchStatus("Jet_puId", 1);  
    outtree->SetBranchAddress("Jet_btagCMVAV2", &(Jet_btagCMVAV2_)); tree->SetBranchStatus("Jet_btagCMVAV2", 1);

 /* outtree->Branch("Jet_pt",&Jet_pt,"Jet_pt/F");
  outtree->Branch("Jet_eta",&Jet_eta,"Jet_eta/F");
  outtree->Branch("Jet_btagCSV",&Jet_btagCSV,"Jet_btagCSV/F");
  outtree->Branch("HLT_BIT_HLT_IsoMu24_v",&HLT_BIT_HLT_IsoMu24_v,"HLT_BIT_HLT_IsoMu24_v/i");
  outtree->Branch("Jet_puId",&Jet_puId,"Jet_puId/i");
  outtree->Branch("ntrgObjects_hltQuadCentralJet30",&ntrgObjects_hltQuadCentralJet30,"ntrgObjects_hltQuadCentralJet30/i");
  outtree->Branch("ntrgObjects_hltDoubleCentralJet90",&ntrgObjects_hltDoubleCentralJet90,"ntrgObjects_hltDoubleCentralJet90/i");
  outtree->Branch("ntrgObjects_hltQuadPFCentralJetLooseID30",&ntrgObjects_hltQuadPFCentralJetLooseID30,"ntrgObjects_hltQuadPFCentralJetLooseID30/i");
  outtree->Branch("ntrgObjects_hltDoublePFCentralJetLooseID90",&ntrgObjects_hltDoublePFCentralJetLooseID90,"ntrgObjects_hltDoublePFCentralJetLooseID90/i");
  outtree->Branch("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v",&HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v,"HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v/i");
  outtree->Branch("nJet",&nJet,"nJet/i");
  outtree->Branch("ntrgObjects_hltQuadCentralJet45",&ntrgObjects_hltQuadCentralJet45,"ntrgObjects_hltQuadCentralJet45/i");
  outtree->Branch("ntrgObjects_hltBTagCaloCSVp087Triple",&ntrgObjects_hltBTagCaloCSVp087Triple,"ntrgObjects_hltBTagCaloCSVp087Triple/i");
  outtree->Branch("ntrgObjects_hltQuadPFCentralJetLooseID45",&ntrgObjects_hltQuadPFCentralJetLooseID45,"ntrgObjects_hltQuadPFCentralJetLooseID45/i");*/

  Long64_t nEvents = tree->GetEntries(); 
  int shout = nEvents/10;
  for (Int_t i=0; i<nEvents; ++i)
  {
        if( i >= shout ){ std::cout << "Event " << i << "/" << nEvents << std::endl; shout=shout+nEvents/10; }

      tree->GetEvent(i);
      if( ! ( HLT_BIT_HLT_IsoMu24_v ) ) continue;
      Int_t counter = 0;
      Int_t GoodJets[100];
      for( Int_t j=0; j<nJet; ++j ) if( abs(Jet_eta[j])<2.6 && Jet_puId[j]>=4 ){ GoodJets[counter]=j; counter++;  }
     if( counter < 4 ) continue; // at least 4 good jets
      //CSVsorted[0] = Jet_btagCSV[GoodJets[0]]; CSVsorted[1] = Jet_btagCSV[GoodJets[1]]; CSVsorted[2] = Jet_btagCSV[GoodJets[2]]; CSVsorted[3] = Jet_btagCSV[GoodJets[3]];
        //float CSVsorted[4] = { Jet_btagCSV[GoodJets[0]], Jet_btagCSV[GoodJets[1]], Jet_btagCSV[GoodJets[2]], Jet_btagCSV[GoodJets[3]] };
        //std::cout << "here" << std::endl;

        for( Int_t j=0; j<counter; ++j )
        {
            jet_pt_[j]=jet_pt[GoodJets[j]];
            Jet_eta_[j]=Jet_eta[GoodJets[j]];
            Jet_btagCSV_[j]=Jet_btagCSV[GoodJets[j]];
            Jet_btagCMVAV2_[j]=Jet_btagCMVAV2[GoodJets[j]];
            CSVsorted[j]=Jet_btagCSV[GoodJets[j]];
            CMVAVsorted[j]=Jet_btagCMVAV2[GoodJets[j]];            
            Jet_puId_[j]=Jet_puId[GoodJets[j]];
            //if( j<4 ){ std::cout  << " " << CSVsorted[j] << std::endl; }
        }
        
        std::sort( CSVsorted, CSVsorted+counter, std::greater<Float_t>() );
        std::sort( CMVAVsorted, CMVAVsorted+counter, std::greater<Float_t>() );
        nJet=counter;
      /*  HLT_BIT_HLT_IsoMu24_v_ = HLT_BIT_HLT_IsoMu24_v;
        ntrgObjects_hltQuadCentralJet30_  = ntrgObjects_hltQuadCentralJet30;
        ntrgObjects_hltDoubleCentralJet90_ =ntrgObjects_hltDoubleCentralJet90;
        ntrgObjects_hltQuadPFCentralJetLooseID30_ = ntrgObjects_hltQuadPFCentralJetLooseID30;
        ntrgObjects_hltDoublePFCentralJetLooseID90_ = ntrgObjects_hltDoublePFCentralJetLooseID90;
        HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v_ = HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v;
        ntrgObjects_hltQuadCentralJet45_ = ntrgObjects_hltQuadCentralJet45;
        ntrgObjects_hltBTagCaloCSVp087Triple_ = ntrgObjects_hltBTagCaloCSVp087Triple;
        ntrgObjects_hltQuadPFCentralJetLooseID45_ = ntrgObjects_hltQuadPFCentralJetLooseID45;*/
        outtree->Fill();
       // if (i%1000 == 1) outtree->AutoSave("SaveSelf");
        
   
    }
  outtree->Write("tree");
  outfile->Close();
}

