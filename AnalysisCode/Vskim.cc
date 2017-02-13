#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include <TSystem.h>
#include <fstream>



void Vskim(std::string source_dir, std::string dest_dir, std::string infile, int from, int to)
{
    std::string Dest_dir=gSystem->ExpandPathName("$dest_dir");
    std::string Source_dir=gSystem->ExpandPathName("$source_dir");
    std::string old_file_test=Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+".root";
    if(!gSystem->AccessPathName((old_file_test).c_str(),kFileExists)){ //Returns true if not found
        gSystem->Exec(("mv "+Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+".root"+" "+Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+"_OLD.root").c_str());
        std::cout<<"\033[1;31m mv "+Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+".root"+" "+Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+"_OLD.root"+"\033[0m"<< endl;
    }
    bool flag = false;
    for (int i = from; i<=to; i++) {
        std::string InputFileName=Source_dir+"/"+infile+to_string(i)+".root";
        if(!gSystem->AccessPathName((InputFileName).c_str(),kFileExists)){
            TFile *file=new TFile((InputFileName).c_str());
            TH1F *h_Count=(TH1F*)file->Get("Count");
            TH1F *h_CountWeighted=(TH1F*)file->Get("CountWeighted");
            TH1F *h_CountPosWeight=(TH1F*)file->Get("CountPosWeight");
            TH1F *h_CountNegWeight=(TH1F*)file->Get("CountNegWeight");
            TTree *tree=(TTree*)file->Get("tree");
            
            std::string cut="(Vtype == -1 || Vtype==4) && HLT_HH4bAll == 1";
            std::cout<<"Copying new " << i << " tree with "<<cut<<"... ";
            std::string OutputFileName=Dest_dir+"/"+infile+to_string(i)+"_Skim.root";
            TFile *outfile=new TFile((OutputFileName).c_str(), "recreate");
            outfile->cd();
            TTree *tree_new=(TTree*)tree->CopyTree(cut.c_str());
            std::cout<<"done."<<std::endl;
            
            tree_new->Write();
            h_Count->Write();
            h_CountWeighted->Write();
            h_CountPosWeight->Write();
            h_CountNegWeight->Write();
            outfile->Close();
            
            std::string TempFileName=Dest_dir+"/temp.root";
            std::string FinalFileName=Dest_dir+"/tree_total.root";
            
            if (i!=from || !gSystem->AccessPathName((FinalFileName).c_str(),kFileExists)){ //Returns true if not found
                gSystem->Exec(("cp "+FinalFileName+" "+TempFileName).c_str());
                //std::cout<<"cp "+FinalFileName+" "+TempFileName<< endl;
                gSystem->Exec(("rm -fr "+FinalFileName).c_str());
                //std::cout<<"rm -fr "+FinalFileName<< endl;
                gSystem->Exec(("hadd "+FinalFileName+" "+TempFileName+" "+OutputFileName).c_str());
                gSystem->Exec(("rm -fr "+OutputFileName).c_str());
                //std::cout<<"rm -fr "+OutputFileName<< endl;
                
            }
            else{
                gSystem->Exec(("mv "+OutputFileName+" "+FinalFileName).c_str());
                std::cout<<"mv "+OutputFileName+" "+FinalFileName<< endl;
            }
        }
        else{
            flag = true;
            if (gSystem->AccessPathName((Dest_dir+"/problem.txt").c_str(),kFileExists)) {
                std::ofstream myfile;
                myfile.open((Dest_dir+"/problem.txt").c_str());
                myfile << "File" << "    "  << " Problem" << "    " << "File" <<"  "<< endl;
                myfile << endl;
                myfile.close();
            }
            
            std::ofstream myfile;
            myfile.open((Dest_dir+"/problem.txt").c_str(), ios::app);
            std:: string err_file = "tree_total_from_"+to_string(from)+"_to_"+to_string(to)+".root";
            myfile << err_file << "    "  << "Not found file " << "    " << to_string(i) <<"  "<< endl;
            myfile.close();
        }
    }
    gSystem->Exec(("mv "+Dest_dir+"/tree_total.root"+" "+Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+".root").c_str());
    gSystem->Exec(("rm -fr "+Dest_dir+"/temp.root").c_str());
    std::cout<<"rm -fr "+Dest_dir+"/temp.root"<< endl;
    
    if (flag) {
        std::cout<<"\033[1;31m WARNING CREATED ERROR FILE \033[0m\n"<< endl;
    }
    
    if (!gSystem->AccessPathName((Dest_dir+"/tree_total_from_"+to_string(from)+"_to_"+to_string(to)+"_OLD.root").c_str(),kFileExists)){ //Returns true if not found
        std::cout<<"\033[1;31m WARNING CREATED OLD FILE \033[0m\n"<< endl;
    }
    
    return;
    
}
