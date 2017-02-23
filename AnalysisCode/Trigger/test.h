#include <iostream>
#include <vector>

std::vector<float> pts;
std::vector<float> csvs;


float Pt4(float pt, float eta, int Jet_puId, int element, int iteration, int length){
    float value = 0;
    if(iteration==0){
        pts.clear();
    }
    if (abs(eta)<2.4 && Jet_puId>=4){
        pts.push_back(pt);
    }
    if (iteration==length-1){
//        pts.sort();
                if (pts.size()>=4){
                            value= pts[element];
                             pts.clear();
                 }
    }
   return value;
}

float CSV(float csv, float eta, int Jet_puId, int element, int iteration, int length){
    float value = -10;
    if(iteration==0){
        csvs.clear();
    }
    if (abs(eta)<2.4 && Jet_puId>=4 && csvs.size()<=4){
        csvs.push_back(csv);
    }
    if (iteration==length-1){
//        pts.sort();
                if (csvs.size()>=4){
                            std::sort( csvs.begin(), csvs.end(), std::greater<Float_t>() );
                         //   std::cout<<"here"<<std::endl;for(int i=0;i<4;i++)std::cout<<csvs[i]<<std::endl;
                            value= csvs[element];
                            csvs.clear();
                 }
    }
   
   return value;
}


//
//                                                        // tree->Scan("Sum$(Pt4(Jet_pt,Jet_eta,3,Iteration$,Length$)):Jet_pt[3]")
//
//
