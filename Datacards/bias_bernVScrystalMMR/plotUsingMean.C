#include <vector>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"
#include <fstream>
using namespace std;
void plotUsingMean(){


  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetTextFont(4);
  gStyle->SetTextSize(.05);//.055
  gStyle->SetTextFont(42);
  gStyle->SetStatFont(42);
  gStyle->SetTitleFont(42,"");
  gStyle->SetTitleFont(42,"Z");
  gStyle->SetTitleFont(42,"X");
  gStyle->SetTitleFont(42,"Y");
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelFont(42,"Z");


double xsec[5] = {0.,1.,2.,5.,10.}; 
for(int j =0; j<5; j++){ 

    double xsec0[5];
    double expNeg0[5];
    double expPos0[5];

    double xsec1[5];
    double expNeg1[5];
    double expPos1[5];

    double xsec2[5];
    double expNeg2[5];
    double expPos2[5];

    double xsec15[5];
    double expNeg15[5];
    double expPos15[5];

    double xsec25[5];
    double expNeg25[5];
    double expPos25[5];

    Float_t val1, val2;
    string s1;	
    std::vector<float> hq;
    std::vector<float> hq2;
    ifstream indata1, indata2;
    ifstream indata3, indata4;
    ifstream indata0, indata00; 
    ifstream indata15, indata150;
    ifstream indata35, indata350; 
    stringstream ss, xss;
    ss << j;
    xss << xsec[j];
//TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -4, 4.);

/////////270
    indata0.open(("max270_"+ss.str()+".txt").c_str(),ios::in);
    indata00.open(("max_err_270_"+ss.str()+".txt").c_str(),ios::in);
    if(!indata1||!indata2){
            cout<<"Error in path"<<endl;
            cout << "Error: file could not be opened" << ("max270_"+ss.str()+".txt").c_str()<<"  or "<< ("max_err_270_"+ss.str()+".txt").c_str()<<endl;
            exit(1);
    }
    TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -4.5, 4.5);
    if(j==1) TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -7, 7.);
    if(j==2) TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -7, 7.);
    if(j==3) TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -15, 15.);
    if(j==4) TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270",50, -1, 20.);
  
    float sum =0.;
    float err =0.;
    while (!indata0.eof() && !indata00.eof() ) {
            indata0 >> s1;
	    val1 = atof(s1.c_str()); 
            indata00 >> val2;
//	  std::cout<< val1<<std::endl;	

            hq.push_back(val1);
            hq2.push_back(val2);

	     h_pull_270->Fill(val1);	
            sum = sum + val1;
	    //std::cout<< sum <<" sum  "<<val1<<" iter "<<hq.size()<<std::endl;
            err = err + val2;
    }
    indata0.close();
    indata00.close();
    xsec0[j]= h_pull_270->GetMean();//sum/hq.size();
    //else xsec0[j]= sum/hq.size();
    std::cout<< xsec0[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg0[j]=h_pull_270->GetRMS();//err/hq2.size();
    

  TCanvas * c = new TCanvas ("c", "c");
    //c->Divide(5,2);
    c->cd();
    h_pull_270->Draw();
    std::cout<<h_pull_270->GetMean()<<std::endl;
    c->Print(("pull270_"+ss.str()+".png").c_str());



    hq.clear();
    hq2.clear();




/////////300
    indata1.open(("max300_"+ss.str()+".txt").c_str());
    indata2.open(("max_err_300_"+ss.str()+".txt").c_str());
    if(!indata1||!indata2){
	    cout<<"Error in path"<<endl;
	    cout << "Error: file could not be opened" << ("max300_"+ss.str()+".txt").c_str()<<"  or "<< ("max_err_300_"+ss.str()+".txt").c_str()<<endl;
	    exit(1);
    }


    TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300",50, -4.5, 4.5);
    if(j==1) TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300",50, -7, 7.);
    if(j==2) TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300",50, -7, 7.);
    if(j==3) TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300",50, -10, 10.);
    if(j==4) TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300",50, -15, 15.);
 


    float sum =0.; 
    float err =0.;
    while (!indata1.eof() && !indata2.eof() ) {
	    //prendo 1 had
	    indata1 >> val1;
	    indata2 >> val2;
	    hq.push_back(val1);
            h_pull_300->Fill(val1);

	    hq2.push_back(val2);
	    sum = sum + val1;
	    err = err + val2;
    }
    indata1.close();
    indata2.close();

    xsec1[j]=h_pull_300->GetMean();//sum/hq.size();
    std::cout<< xsec1[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;   
    expNeg1[j]=h_pull_300->GetRMS();//err/hq.size();

    hq.clear(); 
    hq2.clear();


/////////350

    indata15.open(("max350_"+ss.str()+".txt").c_str());
    indata150.open(("max_err_350_"+ss.str()+".txt").c_str());
    if(!indata15||!indata150){
            cout<<"Error in path"<<endl;
            cout << "Error: file could not be opened" << ("max350_"+ss.str()+".txt").c_str()<<"  or "<< ("max_err_350_"+ss.str()+".txt").c_str()<<endl;
            exit(1);
    }

    float sum =0.;
    float err =0.;
    while (!indata15.eof() && !indata150.eof() ) {
            //prendo 1 had
            indata15 >> val1;
            indata150 >> val2;
            hq.push_back(val1);
            hq2.push_back(val2);
            sum = sum + val1;
            err = err + val2;
    }
    indata15.close();
    indata150.close();

    xsec2[j]=sum/hq.size();
    std::cout<< xsec15[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg2[j]=err/hq.size();


    hq.clear();
    hq2.clear();

/////400

    indata3.open(("max400_"+ss.str()+".txt").c_str());
    indata4.open(("max_err_400_"+ss.str()+".txt").c_str());
    if(!indata3||!indata4){
	    cout<<"Error in path"<<endl;
	    cout << "Error: file could not be opened" << endl;
	    exit(1);
    }

    float sum2 =0.;
    float err2 =0.;

    while (!indata3.eof() && !indata4.eof() ) {
	    //prendo 1 had
	    indata3 >> val1;
	    indata4 >> val2;
	    hq.push_back(val1);
	    hq2.push_back(val2);
	    sum2 = sum2 + val1;
	    err2 = err2 + val2;
    }
    indata3.close();
    indata4.close();
    xsec15[j]=sum2/hq.size();
    expNeg15[j]=err2/hq.size();

//////////450


    hq.clear();
    hq2.clear();

    indata35.open(("max450_"+ss.str()+".txt").c_str());
    indata350.open(("max_err_450_"+ss.str()+".txt").c_str());
    if(!indata35||!indata350){
            cout<<"Error in path"<<endl;
            cout << "Error: file could not be opened" << ("max450_"+ss.str()+".txt").c_str()<<"  or "<< ("max_err_450_"+ss.str()+".txt").c_str()<<endl;
            exit(1);
    }

    float sum =0.;
    float err =0.;
    while (!indata35.eof() && !indata350.eof() ) {
            //prendo 1 had
            indata35 >> val1;
            indata350 >> val2;
            hq.push_back(val1);
            hq2.push_back(val2);
            sum = sum + val1;
	    //h_pull_270->Fill((val1-xsec[j])/val2);
            err = err + val2;
    }
    indata35.close();
    indata350.close();

    xsec25[j]=sum/hq.size();
    std::cout<< xsec25[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg25[j]=err/hq.size();

    hq.clear();
    hq2.clear();


}


int nPoints=5;
double  mass[5]={270,300,350,400,450};
double inj0[5]={xsec0[0],xsec1[0],xsec2[0],xsec15[0],xsec25[0]};
double inj1[5]={xsec0[1],xsec1[1],xsec2[1],xsec15[1],xsec25[1]};
double inj2[5]={xsec0[2],xsec1[2],xsec2[2],xsec15[2],xsec25[2]};
double inj5[5]={xsec0[3],xsec1[3],xsec2[3],xsec15[3],xsec25[3]};
double inj10[5]={xsec0[4],xsec1[4],xsec2[4],xsec15[4],xsec25[4]};
double Errinj0[5]={expNeg0[0],expNeg1[0],expNeg2[0],expNeg15[0],expNeg25[0]};
double Errinj1[5]={expNeg0[1],expNeg1[1],expNeg2[1],expNeg15[1],expNeg25[1]};
double Errinj2[5]={expNeg0[2],expNeg1[2],expNeg2[2],expNeg15[2],expNeg25[2]};
double Errinj5[5]={expNeg0[3],expNeg1[3],expNeg2[3],expNeg15[3],expNeg25[3]};
double Errinj10[5]={expNeg0[4],expNeg1[4],expNeg2[4],expNeg15[4],expNeg25[4]};
std::cout<< inj0[0] <<"  "<<inj0[1]<<"  "<<inj0[2]<<"  "<<inj0[3]<<"  " <<inj0[4]<<std::endl;

TGraphAsymmErrors *g_xsec_0sigma=new TGraphAsymmErrors(nPoints, mass, inj0, 0, 0, Errinj0, Errinj0);
g_xsec_0sigma->SetLineWidth(2);
for(int g = 0; g<nPoints;g++) mass[g] = mass[g]*1.005;

TGraphAsymmErrors *g_xsec_1sigma=new TGraphAsymmErrors(nPoints, mass, inj1, 0, 0, Errinj1, Errinj1);
for(int g = 0; g<nPoints;g++) mass[g] = mass[g]*1.005;
g_xsec_1sigma->SetLineWidth(2);
TGraphAsymmErrors *g_xsec_2sigma=new TGraphAsymmErrors(nPoints, mass, inj2, 0, 0, Errinj2, Errinj2);
g_xsec_2sigma->SetLineWidth(2);
for(int g = 0; g<nPoints;g++) mass[g] = mass[g]*1.005;
TGraphAsymmErrors *g_xsec_15sigma=new TGraphAsymmErrors(nPoints, mass, inj5, 0, 0, Errinj5, Errinj5);
g_xsec_15sigma->SetLineWidth(2);
for(int g = 0; g<nPoints;g++) mass[g] = mass[g]*1.005;
TGraphAsymmErrors *g_xsec_25sigma=new TGraphAsymmErrors(nPoints,  mass, inj10, 0, 0, Errinj10, Errinj10);
g_xsec_25sigma->SetLineWidth(2);


TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
//c_xsec->SetLogy();
g_xsec_1sigma->GetXaxis()->SetTitle("M_{X} [GeV/c^{2}]");
g_xsec_1sigma->SetMaximum(17.0); g_xsec_1sigma->SetMinimum(-3.0);
g_xsec_1sigma->SetTitle("");
g_xsec_1sigma->Draw("AL*");
g_xsec_2sigma->SetLineColor(kGray+2);
g_xsec_2sigma->Draw("L* SAME");
g_xsec_25sigma->SetLineColor(kGray+1);
g_xsec_25sigma->Draw("L* SAME");
g_xsec_15sigma->SetLineColor(kGray);
g_xsec_15sigma->Draw("L* SAME");
g_xsec_0sigma->SetLineColor(kGray+3);
g_xsec_0sigma->Draw("L* SAME");
TLine * a = new TLine();
a->SetLineColor(kRed);
a->SetLineStyle(2);
a->SetLineWidth(3);
a->DrawLine(270.,0., 450., 0.);
a->DrawLine(270.,1., 450., 1.);
a->DrawLine(270.,2., 450., 2.);
a->DrawLine(270.,5., 450., 5.);
a->DrawLine(270.,10., 450., 10.);
  TLatex * tPrel = new TLatex();
        tPrel->SetNDC();
         tPrel->SetTextColor(kBlack);
         tPrel->SetTextSize(0.04027386);
         tPrel->DrawLatex(0.09821429,0.9194523,"CMS Preliminary; #sqrt{s} =  8 TeV L = 17.9 fb^{-1}");
// g_obs->Draw("L* SAME");
//TLegend *leg=new TLegend(0.45, 0.6, 0.9, 0.85);
// TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
//leg->SetFillStyle(0);
//leg->SetLineColor(0);
//leg->SetTextFont(4);
//leg->AddEntry((TObject*)0, "CMS Experiment #sqrt{s} = 8 TeV, L = 18.6 fb^{-1}", "");
//leg->AddEntry((TObject*)0, "X#rightarrowH(b#bar{b}) H(b#bar{b})", "");
//leg->AddEntry(g_xsec_0sigma, "#mu X(270)","LP");
//leg->AddEntry(g_xsec_1sigma, "#mu X(300)","LP");
//leg->AddEntry(g_xsec_15sigma, "#mu X(350)","LP");
//leg->AddEntry(g_xsec_2sigma, "#mu X(400)","LP");
//leg->AddEntry(g_xsec_25sigma, "#mu X(450)");
// leg->AddEntry(g_obs, "Observed Limit with fake data (background + 1 pb signal)", "LP");
//leg->Draw();
c_xsec->SaveAs("Strenght.root");





}
