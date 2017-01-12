#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"

void Vskim(std::string infile)
{
  TFile *file=new TFile((infile+".root").c_str());
  TH1F *h_Count=(TH1F*)file->Get("Count");
  TH1F *h_CountWeighted=(TH1F*)file->Get("CountWeighted");
  TH1F *h_CountPosWeight=(TH1F*)file->Get("CountPosWeight");
  TH1F *h_CountNegWeight=(TH1F*)file->Get("CountNegWeight");
  TTree *tree=(TTree*)file->Get("tree");
  
  std::string cut="(Vtype == -1 || Vype==4) && HLT_HH4bAll == 1";
  std::cout<<"Copying new tree with "<<cut<<"... ";
  TFile *outfile=new TFile((infile+"_Skim.root").c_str(), "recreate");
  outfile->cd();
  TTree *tree_new=(TTree*)tree->CopyTree(cut.c_str());
  std::cout<<"done."<<std::endl;
  
  tree_new->Write();
  h_Count->Write();
  h_CountWeighted->Write();
  h_CountPosWeight->Write();
  h_CountNegWeight->Write();
  outfile->Close();
  
  return;
}
  
