#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include <TSystem.h>
#include <fstream>



void countFile(std::string source_dir, std::string dest_dir, std::string infile, int from, int to)
{
    bool flag = false;
    int a = from;
    int b = to;
    std::string source=source_dir.substr(source_dir.find("VHBB_HEPPY_V25_BTagCSV__Run2016")+31, 1)+source_dir.substr(source_dir.find("-v"),3);
    std::string Source_dir=gSystem->ExpandPathName((source_dir).c_str());
    std::string Dest_dir=gSystem->ExpandPathName((dest_dir).c_str());
    

    for (int i = from; i<=to; i++) {
        std::string InputFileName=Source_dir+"/"+infile+to_string(i)+".root";
        
        if(gSystem->AccessPathName((InputFileName).c_str(),kFileExists)){
            flag = true;
            if (gSystem->AccessPathName((Dest_dir+"/problem_"+source+".txt").c_str(),kFileExists)) {
                std::ofstream myfile;
                std:: string err_file = "tree_"+source+"_from_"+to_string(from)+"_to_"+to_string(to)+".root";
                myfile.open((Dest_dir+"/problem_"+source+".txt").c_str());
                myfile << "#File" << "    "  << " Problem : Not found file" << "    " << "File: " <<"  "<< err_file<< endl;
                myfile << endl;
                myfile.close();
            }
           cout<<(Dest_dir+"/problem_"+source+".txt").c_str()<<endl; 
            std::ofstream myfile;
            myfile.open((Dest_dir+"/problem_"+source+".txt").c_str(), ios::app);
            myfile << to_string(i) <<"  "<< endl;
            myfile.close();
        }
    }
    
    if (flag) {
        std::cout<<"\033[1;31m WARNING CREATED ERROR FILE \033[0m\n"<< endl;
    }
    
    return;
    
}

