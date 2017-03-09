/*----------------------------------------------------------------/
Analysis Code for X->HH->bbbb searches in CMS
Authors: Souvik Das (Univ. of Florida) & Caterina Vernieri (FNAL)
/----------------------------------------------------------------*/

#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <iostream>
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/DrawFunctions.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/Trigger/Double76.h"
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/Trigger/Quad76.h" // to be updated
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/BTagCalibrationStandalone.cpp"

#include <TSystem.h>
#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

double pi=3.14159265358979;

// Hardcoded configuration parameters
double jet_pT_cut=30.;
double jet_eta_cut=2.4;
double jet_btag_cut_L=0.2219; double jet_btag_cut_M=0.6324; double jet_btag_cut_T=0.8958; //Pb+Pbb DeepCSVM
//double jet_btag_cut=0.4432;// CMVAM https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
double jet_btag_cut_min = jet_btag_cut_M;
double jet_btag_cut_max = jet_btag_cut_T;
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

void HbbHbb_PreSelection_malara_2000_2L2M(std::string source_dir, std::string dest_dir, std::string sample,
                         std::string sigmaJECUnc_string="JEC", 
                         std::string sigmaJERUnc_string="JER", 
                         std::string sigmaTrigUnc_string="Trig",
                         std::string sigmabTagUnc_string="bTag",
                         std::string regressionFile="")
{
std::string inputfilename=source_dir+"/"+sample+".root";                           
   
    TChain *tree_test=new TChain("tree");
    tree_test->Add(inputfilename.c_str());
    int test=tree_test->GetEntries();
   
    TChain *tree=new TChain("tree");                                                   
    tree->Add(inputfilename.c_str());                                                  
    std::cout<<"Opened input file "<<inputfilename<<std::endl;                         
    if (test<=0) tree->Scan();
    if (regressionFile=="") std::cout<<"b jet regression not done. jet_regressed_pT = jet_pT"<<std::endl;
    else std::cout<<"b jet regression done with "<<regressionFile<<" decisions file."<<std::endl;

  
  // Book variables
  //

  BTagCalibration calib("DeepCSV","/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/deepCSV_BH_Moriond17.csv");
  BTagCalibrationReader csv_calib_l_L(BTagEntry::OP_MEDIUM,"central",{"up", "down"});
  BTagCalibrationReader csv_calib_c_L(BTagEntry::OP_MEDIUM,"central",{"up", "down"});
  BTagCalibrationReader csv_calib_b_L(BTagEntry::OP_MEDIUM,"central",{"up", "down"});
  
  BTagCalibrationReader csv_calib_l_H(BTagEntry::OP_TIGHT,"central",{"up", "down"});
  BTagCalibrationReader csv_calib_c_H(BTagEntry::OP_TIGHT,"central",{"up", "down"});
  BTagCalibrationReader csv_calib_b_H(BTagEntry::OP_MEDIUM,"central",{"up", "down"});
    
  csv_calib_l_L.load(calib,                // calibration instance
	    BTagEntry::FLAV_UDSG,    // btag flavour
	    "incl");               // measurement type
  csv_calib_c_L.load(calib,
            BTagEntry::FLAV_C,
            "mujets");
    csv_calib_b_L.load(calib,
                       BTagEntry::FLAV_B,
                       "mujets");
    
    csv_calib_l_H.load(calib,                // calibration instance
                       BTagEntry::FLAV_UDSG,    // btag flavour
                       "incl");               // measurement type
    csv_calib_c_H.load(calib,
                       BTagEntry::FLAV_C,
                       "mujets");
    csv_calib_b_H.load(calib,
                       BTagEntry::FLAV_B,
                       "mujets");



  int run;
  int evt;
  int isData, nTrueInt, json;
  float trigger_HLT_HH4bLowLumi;
  int trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v; 
  int trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v;
  float vType;
  float puWeight, genWeight;
  int nJets;
  float jet_btagCSV[100], jet_btagCMVA[100], jet_btagCMVAMSF[100], jet_btagCMVAMSFUp[100], jet_btagCMVAMSFDown[100],jet_btagDeepCSVb[100], jet_btagDeepCSVbb[100];
  float jet_pT[100], jet_eta[100], jet_phi[100], jet_mass[100], jet_rawpT[100];
  int jet_flavor[100];
  float jet_corrJERUp[100], jet_corrJERDown[100], jet_corrJECUp[100], jet_corrJECDown[100] , jet_corrJER[100], jet_corrJEC[100];
  int nGenHiggsBoson;	
  float genHiggsBoson_pT[100], genHiggsBoson_eta[100], genHiggsBoson_phi[100], genHiggsBoson_mass[100];
  float eventWeight;
  int nGenBQuarkFromH;
  float genBQuarkFromH_pT[100], genBQuarkFromH_eta[100], genBQuarkFromH_phi[100], genBQuarkFromH_mass[100];
  float jet_MCpT[100], jet_MCeta[100], jet_MCphi[100], jet_MCmass[100];
  float met_pT, met_phi;

  int isMC;
  std::size_t findGrav = sample.find("Grav");std::size_t findRad = sample.find("Radion"); 
  if ( findGrav !=std::string::npos || findRad !=std::string::npos ) isMC = 1; //add TT and ZZ
  else isMC = 0;
  float btagWeightsCMVAV2;	


  
  float jet_corr[100], 
        nPVs,
        jet_mt[100], 
        jet_leadTrackPt[100], 
        jet_leptonPtRel[100], 
        jet_leptonPt[100], 
        jet_leptonDeltaR[100],
        jet_neHEF[100],
	jet_chHEF[100],
        jet_neEmEF[100], 
        jet_chMult[100], 
        jet_vtxPt[100], 
        jet_vtxMass[100], 
        jet_vtx3dL[100], 
        jet_vtxNtrk[100], 
        jet_vtx3deL[100];
        
  float this_Jet_pt,
        this_Jet_corr, 
        this_rho, 
        this_Jet_eta, 
        this_Jet_mt, 
        this_Jet_leadTrackPt, 
        this_Jet_leptonPtRel, 
        this_Jet_leptonPt, 
        this_Jet_leptonDeltaR, 
        this_Jet_neHEF,
        this_Jet_neEmEF, 
        this_Jet_chMult, 
        this_Jet_vtxPt, 
        this_Jet_vtxMass, 
        this_Jet_vtx3dL, 
        this_Jet_vtxNtrk, 
        this_Jet_vtx3deL;
  
  TMVA::Reader *reader=new TMVA::Reader("!Color:!Silent");
	
  if (regressionFile!="")
  {

    // b jet regression variables
    reader->AddVariable("Jet_pt",            &this_Jet_pt);
    //reader->AddVariable("Jet_corr",          &this_Jet_corr);
    reader->AddVariable("nPVs",               &this_rho);
    reader->AddVariable("Jet_eta",           &this_Jet_eta); 
    reader->AddVariable("Jet_mt",            &this_Jet_mt); 
    reader->AddVariable("Jet_leadTrackPt",   &this_Jet_leadTrackPt); 
    reader->AddVariable("Jet_leptonPtRel",   &this_Jet_leptonPtRel); 
    reader->AddVariable("Jet_leptonPt",      &this_Jet_leptonPt); 
    reader->AddVariable("Jet_leptonDeltaR",  &this_Jet_leptonDeltaR);
    reader->AddVariable("Jet_neHEF",         &this_Jet_neHEF);
    reader->AddVariable("Jet_neEmEF",        &this_Jet_neEmEF); 
    //reader->AddVariable("Jet_chMult",        &this_Jet_chMult);
    reader->AddVariable("Jet_vtxPt",         &this_Jet_vtxPt); 
    reader->AddVariable("Jet_vtxMass",       &this_Jet_vtxMass);
    reader->AddVariable("Jet_vtx3dL",        &this_Jet_vtx3dL); 
    reader->AddVariable("Jet_vtxNtrk",       &this_Jet_vtxNtrk);
    reader->AddVariable("Jet_vtx3deL",       &this_Jet_vtx3deL);
    reader->BookMVA("BDTG method", regressionFile);

  }

  
  // Retrieve variables
  tree->SetBranchAddress("evt", &evt);
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("evt", 1);
  tree->SetBranchAddress("run", &run);                                      tree->SetBranchStatus("run", 1);  
  if(isMC==1){ tree->SetBranchAddress("nTrueInt",&nTrueInt);				                      tree->SetBranchStatus("nTrueInt",1);  } 
  tree->SetBranchAddress("isData", &isData);                                tree->SetBranchStatus("isData", 1);
  tree->SetBranchAddress("json",&json); tree->SetBranchStatus("json",1);
  



  // Different name for MC and data
  if(isMC==1){ tree->SetBranchAddress("HLT_HH4bLowLumi", &trigger_HLT_HH4bLowLumi);      tree->SetBranchStatus("HLT_HH4bLowLumi", 1); }
  else {  tree->SetBranchAddress("HLT_HH4bLowLumi", &trigger_HLT_HH4bLowLumi);      tree->SetBranchStatus("HLT_HH4bLowLumi", 1); }
  if(isMC==1){ tree->SetBranchAddress("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v",&trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v); tree->SetBranchStatus("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v",1); }
  else { tree->SetBranchAddress("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v",&trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v); tree->SetBranchStatus("HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v",1); }

  if(isMC==1){ tree->SetBranchAddress("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v",&trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v);  tree->SetBranchStatus("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v",1); }
  else { tree->SetBranchAddress("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v",&trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v); tree->SetBranchStatus("HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v",1); }

  tree->SetBranchAddress("Vtype", &(vType));                                tree->SetBranchStatus("Vtype", 1); 
  if(isMC==1){ tree->SetBranchAddress("puWeight", &(puWeight));                          tree->SetBranchStatus("puWeight", 1); }
  if(isMC==1){  tree->SetBranchAddress("genWeight", &(genWeight));                        tree->SetBranchStatus("genWeight", 1); }
  tree->SetBranchAddress("nJet", &(nJets));                                 tree->SetBranchStatus("nJet", 1); 
  tree->SetBranchAddress("Jet_btagCSV", &(jet_btagCSV));                    tree->SetBranchStatus("Jet_btagCSV", 1); 
  tree->SetBranchAddress("Jet_btagCMVAV2", &(jet_btagCMVA));                tree->SetBranchStatus("Jet_btagCMVAV2", 1);
  if(isMC==1){ tree->SetBranchAddress("Jet_btagCMVAV2M_SF_up", &(jet_btagCMVAMSFUp));     tree->SetBranchStatus("Jet_btagCMVAV2M_SF_up", 1);
  tree->SetBranchAddress("Jet_btagCMVAV2M_SF_down", &(jet_btagCMVAMSFDown)); tree->SetBranchStatus("Jet_btagCMVAV2M_SF_down", 1);
  tree->SetBranchAddress("Jet_btagCMVAV2M_SF", &(jet_btagCMVAMSF));          tree->SetBranchStatus("Jet_btagCMVAV2M_SF", 1); }	
  tree->SetBranchAddress("Jet_btagDeepCSVb", &(jet_btagDeepCSVb)); tree->SetBranchStatus("Jet_btagDeepCSVb",1);
  tree->SetBranchAddress("Jet_btagDeepCSVbb", &(jet_btagDeepCSVbb)); tree->SetBranchStatus("Jet_btagDeepCSVbb",1);
  tree->SetBranchAddress("Jet_pt", &(jet_pT));                              tree->SetBranchStatus("Jet_pt", 1);
  tree->SetBranchAddress("Jet_rawPt", &(jet_rawpT));                        tree->SetBranchStatus("Jet_rawPt", 1);
  tree->SetBranchAddress("Jet_eta", &(jet_eta));                            tree->SetBranchStatus("Jet_eta", 1); 
  tree->SetBranchAddress("Jet_phi", &(jet_phi));                            tree->SetBranchStatus("Jet_phi", 1); 
  tree->SetBranchAddress("Jet_mass", &(jet_mass));                          tree->SetBranchStatus("Jet_mass", 1);
  if(isMC==1){ tree->SetBranchAddress("Jet_mcPt", &(jet_MCpT));                          tree->SetBranchStatus("Jet_mcPt", 1);
  tree->SetBranchAddress("Jet_mcEta", &(jet_MCeta));                        tree->SetBranchStatus("Jet_mcEta", 1);
  tree->SetBranchAddress("Jet_mcPhi", &(jet_MCphi));                        tree->SetBranchStatus("Jet_mcPhi", 1);
  tree->SetBranchAddress("Jet_mcM", &(jet_MCmass));                         tree->SetBranchStatus("Jet_mcM", 1); 
  tree->SetBranchAddress("nGenHiggsBoson", &(nGenHiggsBoson));              tree->SetBranchStatus("nGenHiggsBoson",1);
  tree->SetBranchAddress("GenHiggsBoson_pt", &(genHiggsBoson_pT));          tree->SetBranchStatus("GenHiggsBoson_pt",1);
  tree->SetBranchAddress("GenHiggsBoson_eta", &(genHiggsBoson_eta));        tree->SetBranchStatus("GenHiggsBoson_eta",1);
  tree->SetBranchAddress("GenHiggsBoson_phi", &(genHiggsBoson_phi));        tree->SetBranchStatus("GenHiggsBoson_phi",1);
  tree->SetBranchAddress("GenHiggsBoson_mass", &(genHiggsBoson_mass));      tree->SetBranchStatus("GenHiggsBoson_mass",1);
  tree->SetBranchAddress("nGenBQuarkFromH", &(nGenBQuarkFromH));            tree->SetBranchStatus("nGenBQuarkFromH",1);
  tree->SetBranchAddress("GenBQuarkFromH_pt", &(genBQuarkFromH_pT));        tree->SetBranchStatus("GenBQuarkFromH_pt", 1);
  tree->SetBranchAddress("GenBQuarkFromH_eta", &(genBQuarkFromH_eta));      tree->SetBranchStatus("GenBQuarkFromH_eta", 1);
  tree->SetBranchAddress("GenBQuarkFromH_phi", &(genBQuarkFromH_phi));      tree->SetBranchStatus("GenBQuarkFromH_phi", 1);
  tree->SetBranchAddress("GenBQuarkFromH_mass", &(genBQuarkFromH_mass));    tree->SetBranchStatus("GenBQuarkFromH_mass", 1); }
  tree->SetBranchAddress("met_pt", &(met_pT));                              tree->SetBranchStatus("met_pt", 1);
  tree->SetBranchAddress("met_phi", &(met_phi));                            tree->SetBranchStatus("met_phi", 1);
  tree->SetBranchAddress("Jet_corr", &(jet_corrJEC));
  tree->SetBranchAddress("Jet_corr_JECUp", &(jet_corrJECUp));
  tree->SetBranchAddress("Jet_corr_JECDown", &(jet_corrJECDown));
 if(isMC==1){  tree->SetBranchAddress("Jet_corr_JER", &(jet_corrJER));
  tree->SetBranchAddress("Jet_corr_JERUp", &(jet_corrJERUp));
  tree->SetBranchAddress("Jet_corr_JERDown", &(jet_corrJERDown));
  tree->SetBranchAddress("Jet_mcFlavour", &(jet_flavor)); tree->SetBranchStatus("Jet_mcFlavour", 1); 
    }
    
  if(isMC==1){ tree->SetBranchAddress("btagWeightCMVAV2", &(btagWeightsCMVAV2));}



  if (regressionFile!="")
  {

    tree->SetBranchAddress("Jet_corr", &(jet_corr));                     
    tree->SetBranchAddress("nPVs", &(nPVs));                               
    tree->SetBranchAddress("Jet_leadTrackPt", &(jet_leadTrackPt));        
    tree->SetBranchAddress("Jet_leptonPtRel", &(jet_leptonPtRel));       
    tree->SetBranchAddress("Jet_leptonPt", &(jet_leptonPt));             
    tree->SetBranchAddress("Jet_leptonDeltaR", &(jet_leptonDeltaR));     
    tree->SetBranchAddress("Jet_neHEF", &(jet_neHEF));                   
    tree->SetBranchAddress("Jet_chHEF", &(jet_chHEF));
    tree->SetBranchAddress("Jet_neEmEF", &(jet_neEmEF));                 
    tree->SetBranchAddress("Jet_chMult", &(jet_chMult));                 
    tree->SetBranchAddress("Jet_vtxPt", &(jet_vtxPt));                   
    tree->SetBranchAddress("Jet_vtxMass", &(jet_vtxMass));               
    tree->SetBranchAddress("Jet_vtx3DVal", &(jet_vtx3dL));               
    tree->SetBranchAddress("Jet_vtx3DSig", &(jet_vtx3deL));              
    tree->SetBranchAddress("Jet_vtxNtracks", &(jet_vtxNtrk));
  }           


  TH1F *h_nCbJets=new TH1F("h_nCbJets", "; #Jets with |#eta|<2.5, p_{T} > 30 GeV, CMVA > CMVAM; Events", 10, 0., 10.);
  
  TH1F *h_pTOrder_JetpT_1=new TH1F("h_pTOrder_JetpT_1", "; Jet p_{T} 1 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 800.);
  TH1F *h_pTOrder_JetpT_2=new TH1F("h_pTOrder_JetpT_2", "; Jet p_{T} 2 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 500.);
  TH1F *h_pTOrder_JetpT_3=new TH1F("h_pTOrder_JetpT_3", "; Jet p_{T} 3 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 350.);
  TH1F *h_pTOrder_JetpT_4=new TH1F("h_pTOrder_JetpT_4", "; Jet p_{T} 4 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
  TH1F *h_pTOrder_JetpT_5=new TH1F("h_pTOrder_JetpT_5", "; Jet p_{T} 5 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
 
  TH1F *h_pTreg_JetpT_1=new TH1F("h_pTreg_JetpT_1", "; Jet p_{T} 1 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 800.);
  TH1F *h_pTreg_JetpT_2=new TH1F("h_pTreg_JetpT_2", "; Jet p_{T} 2 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 500.);
  TH1F *h_pTreg_JetpT_3=new TH1F("h_pTreg_JetpT_3", "; Jet p_{T} 3 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 350.);
  TH1F *h_pTreg_JetpT_4=new TH1F("h_pTreg_JetpT_4", "; Jet p_{T} 4 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
  TH1F *h_pTreg_JetpT_5=new TH1F("h_pTreg_JetpT_5", "; Jet p_{T} 5 for jets with |#eta|<2.5 (GeV); Events", 50, 0., 250.);
  TH1F *h_CSVOrder_JetCSV_1=new TH1F("h_CSVOrder_JetCSV_1", "; Jet CSV 1 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CSVOrder_JetCSV_2=new TH1F("h_CSVOrder_JetCSV_2", "; Jet CSV 2 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CSVOrder_JetCSV_3=new TH1F("h_CSVOrder_JetCSV_3", "; Jet CSV 3 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CSVOrder_JetCSV_4=new TH1F("h_CSVOrder_JetCSV_4", "; Jet CSV 4 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CMVAOrder_JetCMVA_1=new TH1F("h_CMVAOrder_JetCMVA_1", "; Jet CMVA 1 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CMVAOrder_JetCMVA_2=new TH1F("h_CMVAOrder_JetCMVA_2", "; Jet CMVA 2 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CMVAOrder_JetCMVA_3=new TH1F("h_CMVAOrder_JetCMVA_3", "; Jet CMVA 3 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  TH1F *h_CMVAOrder_JetCMVA_4=new TH1F("h_CMVAOrder_JetCMVA_4", "; Jet CMVA 4 for jets with |#eta|<2.5, p_{T} > 30 GeV; Events", 50, -1., 1.);
  
  TH1F *hSF =new TH1F("hSF"," ", 100, 0., 2.);
  TH1F *hWeight =new TH1F("hWeight"," ", 100, 0., 2.);

  TH1F *hWeightH =new TH1F("hWeightH","Weight High", 100, 0., 5.);
  TH1F *hWeightL =new TH1F("hWeightL","Weight Low", 100, 0., 5.);
  TH1F *h_pt_spike=new TH1F("h_pt_spike", "pt in spike; Jet p_{T} 1 for jets with |#eta|<2.5 (GeV); Events", 100, 0., 800.);

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
 std::string outfilename=dest_dir+"/"+"PreSelected_"+sample+".root";


  TFile *outfile=new TFile(outfilename.c_str(), "recreate");
  TTree *outtree=tree->CloneTree(0);

  float jet_regressed_pT[100];
  std::vector<unsigned int> jetIndex_CentralpT40btag_pTOrder;
  std::vector<unsigned int> jetIndex_CentralpT40btag_CSVOrder;
  std::vector<unsigned int> jetIndex_CentralpT40btag_CMVAOrder;
  std::vector<unsigned int> jetIndex_CentralpT40_CSVOrder;	
  std::vector<unsigned int> jetIndex_Central_pTOrder;
  outtree->Branch("Jet_regressed_pt", &jet_regressed_pT, "Jet_regressed_pt[nJet]/F");
  outtree->Branch("jetIndex_CentralpT40btag_pTOrder", &jetIndex_CentralpT40btag_pTOrder);
  outtree->Branch("jetIndex_CentralpT40btag_CSVOrder", &jetIndex_CentralpT40btag_CSVOrder);
  outtree->Branch("jetIndex_CentralpT40btag_CMVAOrder", &jetIndex_CentralpT40btag_CMVAOrder);
  outtree->Branch("jetIndex_Central_pTOrder", &jetIndex_Central_pTOrder);
  outtree->Branch("jetIndex_CentralpT40_CSVOrder", &jetIndex_CentralpT40_CSVOrder);
  outtree->Branch("eventWeight", &eventWeight);
 
  // Loop over events 
  int nEvents=tree->GetEntries();

  std::cout<<nEvents<<std::endl;
  double nCut0=0, nCut1=0, nCut2=0, nCut3=0, nCut4=0, nCut5=0;
  double nTrig1=0, nTrig12=0, nTrig2=0;
  for (int i=0; i<nEvents; ++i)
  {
    ++nCut0;
    tree->GetEvent(i);
   
    eventWeight=1;	 
    if (isData==1 && json <1) continue;
    if (isData!=1) eventWeight=puWeight;//weight2( nTrueInt )*genWeight/fabs(genWeight);

    
    if (isData!=1)
    {
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
    }
    
    h_MET->Fill(met_pT, eventWeight);
    h_MET_phi->Fill(met_phi, eventWeight);
    if (trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v==1 && trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v!=1) nTrig1+=1;
    if (trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v==1 && trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v==1) nTrig12+=1;
    if (trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v!=1 && trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v==1) nTrig2+=1;

    
	
   //  std::cout<<"trigger_HLT_HH4bLowLumi = "<<trigger_HLT_HH4bLowLumi<<std::endl;
   //  std::cout<<"trigger_HLT_HH4bLowLumi = "<<trigger_HLT_HH4bLowLumi<<std::endl;
    float max1 =-1 ;
    float max2=-1;
    float max3=-1;	
    float max4=-1;	
    for (int i=0; i<8;i++)
    {
	    if(max1 < jet_btagCSV[i]) { max4=max3;max3=max2; max2=max1; max1=jet_btagCSV[i];}
	    else if (max2  < jet_btagCSV[i]){max4=max3;max3=max2; max2 = jet_btagCSV[i];}
	    else if (max3  < jet_btagCSV[i]) {max4=max3;max3 = jet_btagCSV[i];}
	    else if (max4  < jet_btagCSV[i]) max4 = jet_btagCSV[i];
    }
    
    /*std::cout<<max1<<"   "<<max2<<"  "<<max3<<std::endl;
    std::cout<<"pt order "<<std::endl;	
    std::cout<<jet_btagCSV[0]<<"   "<<jet_btagCSV[1]<<"   "<<jet_btagCSV[2]<<std::endl;
    
    float CSV3 = TMath::Min(max3, (float) 0.9999999999);	
    float quad ;
    float Double ; 
    if(sigmaTrigUnc_string == "Trigm1") {
		quad =  TurnOnQuadDown(jet_pT[0], jet_pT[1], jet_pT[2], jet_pT[3], CSV3);
		Double = TurnOnDoubleDown(jet_pT[0], jet_pT[1], jet_pT[2], jet_pT[3], CSV3);

		}
    else if (sigmaTrigUnc_string == "Trigp1") {
	    quad =  TurnOnDoubleUp(jet_pT[0], jet_pT[1], jet_pT[2], jet_pT[3], CSV3);
      	    Double = TurnOnQuadUp(jet_pT[0], jet_pT[1], jet_pT[2], jet_pT[3], CSV3);
    }
    */		
    if (trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v==1 || trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v==1)
    {
      //if(sigmaTrigUnc_string == "Trigm1" || sigmaTrigUnc_string == "Trigp1") eventWeight = eventWeight*(Double+quad-Double*quad); //P(A||B) = P(A)+P(B)-P(A&B) = P(A)+P(B)-P(A)*(B));
      nCut1+=eventWeight;
      
      if (vType==-1 || vType ==4)
      {
        nCut2+=eventWeight;
        
        // Order the jets by pT, CSV, and CMVA
        JetList jetList_Central_pTOrder;
        JetList jetList_Central_pTreg;
        JetList jetList_CentralpT40_CSVOrder;
        JetList jetList_CentralpT40btag_pTOrder;
        JetList jetList_CentralpT40btag_CSVOrder;
        JetList jetList_CentralpT40btag_CMVAOrder;
        int nCbJets=0;
        int nHJets=0;
        for (unsigned int j=0; j<(unsigned int)nJets; ++j)
        {
          if (sigmaJECUnc_string=="JECp1") jet_pT[j] = jet_rawpT[j]*jet_corrJECUp[j]*jet_corrJER[j];
          if (sigmaJECUnc_string=="JECm1") jet_pT[j] = jet_rawpT[j]*jet_corrJECDown[j]*jet_corrJER[j];
          if (sigmaJERUnc_string=="JERp1") jet_pT[j] = jet_rawpT[j]*jet_corrJEC[j]*jet_corrJERUp[j];
          if (sigmaJERUnc_string=="JERm1") jet_pT[j] = jet_rawpT[j]*jet_corrJEC[j]*jet_corrJERDown[j];
	      
          if (fabs(jet_eta[j])<jet_eta_cut) 
          {
            jetList_Central_pTOrder[jet_pT[j]]=j;
            if (jet_pT[j]>jet_pT_cut)
            {
		
        //      if (jet_btagCSV[j]>-1)
              {  
                //jetList_CentralpT40_CSVOrder[jet_btagCMVA[j]]=j;
                jetList_CentralpT40_CSVOrder[jet_btagDeepCSVb[j]+jet_btagDeepCSVbb[j]]=j;
                //if (jet_btagCMVA[j]>jet_btag_cut)
                if (jet_btagDeepCSVb[j]+jet_btagDeepCSVbb[j]>jet_btag_cut_min)
                {
                  ++nCbJets;
                  if( nCbJets<= 4 && isData!=1)
                  {
	
		       double jet_scalefactor=1;
		
                          if (jet_btagDeepCSVb[j]+jet_btagDeepCSVbb[j]>jet_btag_cut_max)
                          {
                              nHJets++;
                              if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_H.eval_auto_bounds("central", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                              else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_H.eval_auto_bounds("central", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                              else jet_scalefactor    = csv_calib_l_H.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                              
                              if (sigmabTagUnc_string=="bTagp1") {
                                  
                                  if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_H.eval_auto_bounds("up", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                                  else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_H.eval_auto_bounds("up", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                                  else jet_scalefactor    = csv_calib_l_H.eval_auto_bounds("up", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                                  
                                  
                              }
                              
                              if (sigmabTagUnc_string=="bTagm1") {
                                  
                                  if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_H.eval_auto_bounds("down", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                                  else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_H.eval_auto_bounds("down", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                                  else jet_scalefactor    = csv_calib_l_H.eval_auto_bounds("down", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                                  
                                  
                              }
                          } else
                          {
                              if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_L.eval_auto_bounds("central", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                              else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_L.eval_auto_bounds("central", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                              else jet_scalefactor    = csv_calib_l_L.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                              
                              if (sigmabTagUnc_string=="bTagp1") {
                                  
                                  if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_L.eval_auto_bounds("up", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                                  else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_L.eval_auto_bounds("up", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                                  else jet_scalefactor    = csv_calib_l_L.eval_auto_bounds("up", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                                  
                                  
                              }
                              
                              if (sigmabTagUnc_string=="bTagm1") {
                                  
                                  if (TMath::Abs(jet_flavor[j])==5 ) jet_scalefactor    = csv_calib_b_L.eval_auto_bounds("down", BTagEntry::FLAV_B, jet_eta[j], jet_pT[j]);
                                  else if (TMath::Abs(jet_flavor[j])==4 ) jet_scalefactor    = csv_calib_c_L.eval_auto_bounds("down", BTagEntry::FLAV_C, jet_eta[j], jet_pT[j]);
                                  else jet_scalefactor    = csv_calib_l_L.eval_auto_bounds("down", BTagEntry::FLAV_UDSG, jet_eta[j], jet_pT[j]);
                                  
                                  
                              }
                          }
                          eventWeight=eventWeight*jet_scalefactor;
			
		
                      //if (sigmabTagUnc_string=="bTagp1") eventWeight=eventWeight*(jet_btagCMVAMSFUp[j]);
                      //if (sigmabTagUnc_string=="bTagm1") eventWeight=eventWeight*(jet_btagCMVAMSFDown[j]);
                      //if (sigmabTagUnc_string!="bTagm1" && sigmabTagUnc_string!="bTagp1" ) eventWeight=eventWeight*jet_btagCMVAMSF[j];
                      //
                  }  
                  jetList_CentralpT40btag_pTOrder[jet_pT[j]]=j;
                  if (jet_btagCSV[j]>0) jetList_CentralpT40btag_CSVOrder[jet_btagCSV[j]]=j;
                  //jetList_CentralpT40btag_CMVAOrder[jet_btagCMVA[j]]=j;
                  jetList_CentralpT40btag_CMVAOrder[jet_btagDeepCSVb[j]+jet_btagDeepCSVbb[j]]=j;
                }
              }
            }
          }
        }
	//std::cout<<eventWeight << "<--- from SF from shape corr --->"<<btagWeightsCMVAV2<<std::endl;
	if(nCbJets>3 && nHJets>=2) {
	hSF->Fill(eventWeight);
        if(isMC==1){  hWeight->Fill(btagWeightsCMVAV2); }
	}
        h_nCbJets->Fill(nCbJets, eventWeight);
        
        // Fill jet pT order histograms
        std::vector<TH1F*> v_pTOrder_JetpT = {h_pTOrder_JetpT_1, h_pTOrder_JetpT_2, h_pTOrder_JetpT_3, h_pTOrder_JetpT_4, h_pTOrder_JetpT_5};
        std::vector<TH1F*> v_pTreg_JetpT = {h_pTreg_JetpT_1, h_pTreg_JetpT_2, h_pTreg_JetpT_3, h_pTreg_JetpT_4, h_pTreg_JetpT_5};
        std::vector<TH1F*> v_CSVOrder_JetCSV = {h_CSVOrder_JetCSV_1, h_CSVOrder_JetCSV_2, h_CSVOrder_JetCSV_3, h_CSVOrder_JetCSV_4};
        std::vector<TH1F*> v_CMVAOrder_JetCMVA = {h_CMVAOrder_JetCMVA_1, h_CMVAOrder_JetCMVA_2, h_CMVAOrder_JetCMVA_3, h_CMVAOrder_JetCMVA_4};
        fillHistogramsFromJetList(jetList_Central_pTOrder, v_pTOrder_JetpT, eventWeight);
        fillHistogramsFromJetList(jetList_CentralpT40_CSVOrder, v_CSVOrder_JetCSV, eventWeight);
        fillHistogramsFromJetList(jetList_CentralpT40_CSVOrder, v_CMVAOrder_JetCMVA, eventWeight);

        
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
        
        if (nCbJets>=3 && nHJets>=2)
        {
          fillIndexVectorFromJetList(jetList_CentralpT40btag_pTOrder, &jetIndex_CentralpT40btag_pTOrder);
          fillIndexVectorFromJetList(jetList_CentralpT40btag_CSVOrder, &jetIndex_CentralpT40btag_CSVOrder);
          fillIndexVectorFromJetList(jetList_CentralpT40btag_CMVAOrder, &jetIndex_CentralpT40btag_CMVAOrder);
          fillIndexVectorFromJetList(jetList_Central_pTOrder, &jetIndex_Central_pTOrder);
		
          fillIndexVectorFromJetList(jetList_CentralpT40_CSVOrder, &jetIndex_CentralpT40_CSVOrder);
          
          // Perform b-jet regression here
          // std::cout<<" === new event with at least 3 central b-tagged pT > 40 jets === "<<std::endl;
          // std::cout<<"evt = "<<evt<<std::endl;
          for (unsigned int j=0; j<(unsigned int)nJets; ++j) jet_regressed_pT[j]=jet_pT[j];
          if (regressionFile!="")
          {
            for (unsigned int j=0; j<jetIndex_CentralpT40btag_CMVAOrder.size(); ++j)
            {
              int jetIndex = jetIndex_CentralpT40btag_CMVAOrder.at(j);
              this_Jet_pt = jet_pT[jetIndex];
              
             // if (isData!=1) this_Jet_corr = jet_corr[jetIndex];
             // else this_Jet_corr = jet_pT[jetIndex]/jet_rawpT[jetIndex];
              
              this_rho = nPVs;
              this_Jet_eta = jet_eta[jetIndex];
              
              TLorentzVector jet;
              jet.SetPtEtaPhiM(this_Jet_pt, this_Jet_eta, jet_phi[jetIndex], jet_mass[jetIndex]);
              this_Jet_mt = jet.Mt();
              
              this_Jet_leadTrackPt = jet_leadTrackPt[jetIndex];
              this_Jet_leptonPtRel = jet_leptonPtRel[jetIndex];
              this_Jet_leptonPt = jet_leptonPt[jetIndex];
              this_Jet_leptonDeltaR = jet_leptonDeltaR[jetIndex];
              this_Jet_neHEF = jet_neHEF[jetIndex];//+jet_chHEF[jetIndex];
              this_Jet_neEmEF = jet_neEmEF[jetIndex];
              this_Jet_chMult = jet_chMult[jetIndex];
              this_Jet_vtxPt = jet_vtxPt[jetIndex];
              this_Jet_vtxMass = jet_vtxMass[jetIndex];
              this_Jet_vtx3dL = jet_vtx3dL[jetIndex];
              this_Jet_vtxNtrk = jet_vtxNtrk[jetIndex];
              this_Jet_vtx3deL = jet_vtx3deL[jetIndex];
              double regressedJetpT=(reader->EvaluateRegression("BDTG method"))[0];
              
             // if( jet_pT[jetIndex]>400 ) jet_regressed_pT[jetIndex] = jet_pT[jetIndex];
              jet_regressed_pT[jetIndex]=regressedJetpT;// * jet_pT[jetIndex];
              if(jet_pT[jetIndex]<400) hWeightL->Fill( regressedJetpT/jet_pT[jetIndex] );
              if(jet_pT[jetIndex]>500) hWeightH->Fill( regressedJetpT/jet_pT[jetIndex] );  
              if(regressedJetpT>450 && regressedJetpT<500) h_pt_spike->Fill( jet_pT[jetIndex] );            

              //std::cout<<"Jet pT = "<<this_Jet_pt<<", corr = "<<this_Jet_corr<<", regressed pT = "<<regressedJetpT<<std::endl;
            }

          }

          for (unsigned int j=0; j<jetIndex_CentralpT40btag_CMVAOrder.size(); ++j)
          {
              int jetIndex = jetIndex_CentralpT40btag_CMVAOrder.at(j);
              jetList_Central_pTreg[jet_regressed_pT[jetIndex]]=jetIndex;
          }
          fillHistogramsFromJetList(jetList_Central_pTreg, v_pTreg_JetpT, eventWeight);
          //
          // std::cout<<"Writing out the regressed jet pT "<<std::endl;
          // for (unsigned int j=0; j<(unsigned int)nJets; ++j) std::cout<<"jet_regressed_pT["<<j<<"]="<<jet_regressed_pT[j]=jet_pT[j]<<std::endl;

          // Write out tree
          outtree->Fill();
          
        } // nCbJets>=3
        
        if (nCbJets>=4 && nHJets>=2) nCut3+=eventWeight;
        
        
        jetIndex_CentralpT40btag_pTOrder.clear();
        jetIndex_CentralpT40btag_CSVOrder.clear();
        jetIndex_CentralpT40btag_CMVAOrder.clear();
        jetIndex_Central_pTOrder.clear();
        jetIndex_CentralpT40_CSVOrder.clear();
        
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
                  
  std::string histfilename=dest_dir+"/"+"Histograms_PreSelected_"+sample+".root";
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_Count->Write();
  h_nCbJets->Write();
  h_pTOrder_JetpT_1->Write();
  h_pTOrder_JetpT_2->Write();
  h_pTOrder_JetpT_3->Write();
  h_pTOrder_JetpT_4->Write();
  h_pTOrder_JetpT_5->Write();
  h_pTreg_JetpT_1->Write();
  h_pTreg_JetpT_2->Write();
  h_pTreg_JetpT_3->Write();
  h_pTreg_JetpT_4->Write();
  h_pTreg_JetpT_5->Write();
  h_CSVOrder_JetCSV_1->Write();
  h_CSVOrder_JetCSV_2->Write();
  h_CSVOrder_JetCSV_3->Write();
  h_CSVOrder_JetCSV_4->Write();
  h_CMVAOrder_JetCMVA_1->Write();
  h_CMVAOrder_JetCMVA_2->Write();
  h_CMVAOrder_JetCMVA_3->Write();
  h_CMVAOrder_JetCMVA_4->Write();
  hSF->Write();
  if(isMC==1){ hWeight->Write(); }
  hWeightH->Write(); hWeightL->Write(); h_pt_spike->Write(); 

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
  std::cout<<"Number of events after trigger = "<<nCut1<< "   "<<(double) nCut1/nInitial<<std::endl;
  std::cout<<"Number of events after Vtype==-1 = "<<nCut2<<std::endl;
  std::cout<<"Number of events after nCbJets>=4 = "<<nCut3<<std::endl;
  std::cout<<"Number of events after finding HH candidate (btag && pT>40 GeV && |eta|<2.4)  = "<<nCut4<<std::endl;
  std::cout<<"Number of events after finding X = "<<nCut5<<", eff. = "<<nCut5/nInitial<<std::endl;
  std::cout<<"========================"<<std::endl;
  
  std::cout<<"=== Trigger Report === "<<std::endl;
  std::cout<<"trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v = "<<nTrig1/(nTrig1+nTrig12+nTrig2)*100.<<"%"<<std::endl;
  std::cout<<"trigger_HLT_BIT_HLT_DoubleJet90_Double30_TripleBTagCSV_p087_v && trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v = "<<nTrig12/(nTrig1+nTrig12+nTrig2)*100.<<"%"<<std::endl;
  std::cout<<"trigger_HLT_BIT_HLT_QuadJet45_TripleBTagCSV_p087_v = "<<nTrig2/(nTrig1+nTrig12+nTrig2)*100.<<"%"<<std::endl;
  
  delete h_Count;
  delete h_nCbJets;
  delete h_pTOrder_JetpT_1;
  delete h_pTOrder_JetpT_2;
  delete h_pTOrder_JetpT_3;
  delete h_pTOrder_JetpT_4;
  delete h_pTOrder_JetpT_5;
  delete h_pTreg_JetpT_1;
  delete h_pTreg_JetpT_2;
  delete h_pTreg_JetpT_3;
  delete h_pTreg_JetpT_4;
  delete h_pTreg_JetpT_5;
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
            
      
  
  
  
  
