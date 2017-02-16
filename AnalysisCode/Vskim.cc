#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include <TSystem.h>
#include <fstream>



void Vskim(std::string source_dir, std::string dest_dir, std::string infile, int from, int to)
{
    bool flag = false;
    int a = from;
    int b = to;
    
    std::string source=source_dir.substr(12, 20);
    std::string Source_dir=gSystem->ExpandPathName((source_dir).c_str());
    std::string Dest_dir=gSystem->ExpandPathName((dest_dir).c_str());
    std::string FinalFileName=Dest_dir+"/tree_"+source+"_from_"+to_string(from)+"_to_"+to_string(to)+".root";
    std::string old_file_test=Dest_dir+"/tree_"+source+"_from_"+to_string(from)+"_to_"+to_string(to)+"_OLD.root";
    
    // Avoid overwrite files
    if(!gSystem->AccessPathName((FinalFileName).c_str(),kFileExists)){ //Returns true if not found
        gSystem->Exec(("mv "+FinalFileName+" "+old_file_test).c_str());
        std::cout<<"\033[1;31m mv "+FinalFileName+" "+old_file_test+"\033[0m"<< endl;
    }
    
    // Files loop
    for (int i = from; i<=to; i++) {
        std::string InputFileName=Source_dir+"/"+infile+to_string(i)+".root";
        // Check if file exist
        if(!gSystem->AccessPathName((InputFileName).c_str(),kFileExists)){
            TFile *file=new TFile((InputFileName).c_str());
            TH1F *h_Count=(TH1F*)file->Get("Count");
            TH1F *h_CountWeighted=(TH1F*)file->Get("CountWeighted");
            TH1F *h_CountPosWeight=(TH1F*)file->Get("CountPosWeight");
            TH1F *h_CountNegWeight=(TH1F*)file->Get("CountNegWeight");
            TTree *tree=(TTree*)file->Get("tree");
            
            // Skim
            std::string cut="(Vtype == -1 || Vtype==4) && HLT_HH4bAll == 1";
            std::cout<<"Copying new " << i << " tree with "<<cut<<"... ";
            
            // Output tree in a new file
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
            
            // HADD
            if (i%50==0) {
                b = i;
                std::string TempFileName=Dest_dir+"/temp_"+to_string(a)+"_"+to_string(b)+".root";
                gSystem->Exec(("hadd "+TempFileName+" "+Dest_dir+"/"+infile+"*_Skim.root").c_str());
		gSystem->Exec(("rm -fr "+Dest_dir+"/"+infile+"*_Skim.root").c_str());
                a=i;
            }
        }
        else{
            // Save not found files
            flag = true;
            if (gSystem->AccessPathName((Dest_dir+"/problem_"+source+".txt").c_str(),kFileExists)) {
                std::ofstream myfile;
                myfile.open((Dest_dir+"/problem_"+source+".txt").c_str());
                myfile << "File" << "    "  << " Problem" << "    " << "File" <<"  "<< endl;
                myfile << endl;
                myfile.close();
            }
            
            std::ofstream myfile;
            myfile.open((Dest_dir+"/problem_"+source+".txt").c_str(), ios::app);
            std:: string err_file = "tree_"+source+"_from_"+to_string(from)+"_to_"+to_string(to)+".root";
            myfile << err_file << "    "  << "Not found file " << "    " << to_string(i) <<"  "<< endl;
            myfile.close();
        }
    }
    // HADD of all files
    gSystem->Exec(("hadd "+FinalFileName+" "+Dest_dir+"/temp_*.root").c_str());
    gSystem->Exec(("rm -fr "+Dest_dir+"/temp_*.root").c_str());
    gSystem->Exec(("rm -fr "+Dest_dir+"/"+infile+"*_Skim.root").c_str());
    
    // Warning of not found files
        if (flag) {
        std::cout<<"\033[1;31m WARNING CREATED ERROR FILE \033[0m\n"<< endl;
    }
    // Remember of previous files 
    if (!gSystem->AccessPathName((Dest_dir+"/tree_"+source+"_from_"+to_string(from)+"_to_"+to_string(to)+"_OLD.root").c_str(),kFileExists)){ //Returns true if not found
        std::cout<<"\033[1;31m WARNING CREATED OLD FILE \033[0m\n"<< endl;
    }
    
    return;
    
}
