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
#include <sstream>
using namespace std;
void plotTH1(){


  gROOT->SetStyle("Plain");
  // gStyle->SetOptStat(000000000);
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
 TCanvas * c = new TCanvas ("c", "c");
    c->Divide(5,2);

for(int j =0; j<5; j++){ 
TH1F * h_pull_300 = new TH1F("h_pull_300", "pull 300", 50, -5., 5.);
TH1F * h_res_300 = new TH1F("h_res_300", "res 300", 50, -5., 5.);
TH1F * h_pull_400 = new TH1F("h_pull_400", "pull 400", 50, -5., 5.);
TH1F * h_res_400 = new TH1F("h_res_400", "res 400", 50, -5., 5.);
TH1F * h_pull_350 = new TH1F("h_pull_350", "pull 350", 50, -5., 5.);
TH1F * h_res_350 = new TH1F("h_res_350", "res 350", 50, -5., 5.);
TH1F * h_pull_450 = new TH1F("h_pull_450", "pull 450", 50, -5., 5.);
TH1F * h_res_450 = new TH1F("h_res_450", "res 450", 50, -5., 5.);
TH1F * h_pull_270 = new TH1F("h_pull_270", "pull 270", 100, -10., 15.);
TH1F * h_res_270 = new TH1F("h_res_270", "res 270", 100, -10., 15.);

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

/////////270
    indata0.open(("max270_"+ss.str()+".txt").c_str());
    indata00.open(("max_err_270_"+ss.str()+".txt").c_str());
    if(!indata1||!indata2){
            cout<<"Error in path"<<endl;
            cout << "Error: file could not be opened" << ("max270_"+ss.str()+".txt").c_str()<<"  or "<< ("max_err_270_"+ss.str()+".txt").c_str()<<endl;
            exit(1);
    }

    float sum =0.;
    float err =0.;
    while (!indata0.eof() && !indata00.eof() ) {
            //prendo 1 had
            indata0 >> val1;
            indata00 >> val2;
            hq.push_back(val1);
            hq2.push_back(val2);
            h_res_270->Fill(val1);
if(j==0)	   std::cout<<"  asd "<<val1<<std::endl;	
            sum = sum + val1;
            err = err + val2;
            h_pull_270->Fill((val1-xsec[j])/val2);
    }
    indata0.close();
    indata00.close();
    xsec0[j]=sum/hq.size();
    std::cout<< xsec0[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg0[j]=err/hq.size();



    c->cd(j+1);
    h_pull_270->Draw();
    c->cd(j+6);
    h_res_270->SetTitle(("#mu= "+ss.str()).c_str());
    h_res_270->Draw();
	
    //c->Print(("pull300"+ss.str()+".png").c_str());

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

    float sum =0.; 
    float err =0.;
    while (!indata1.eof() && !indata2.eof() ) {
	    //prendo 1 had
	    indata1 >> val1;
	    indata2 >> val2;
	    hq.push_back(val1);
	    hq2.push_back(val2);
	    h_res_300->Fill(val1-xsec[j]);
	    sum = sum + val1;
	    err = err + val2;
	    h_pull_300->Fill((val1-xsec[j])/val2);	
    }
    indata1.close();
    indata2.close();

    xsec1[j]=sum/hq.size()*(1.2);
    std::cout<< xsec1[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;   
    expNeg1[j]=err/hq.size();



    ///c->cd(2);
    //h_pull_300->Draw();
    //c->cd(7);
    //h_res_300->Draw();
    //c->Print(("pull300"+ss.str()+".png").c_str());

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
            h_res_350->Fill(val1-xsec[j]);
            sum = sum + val1;
            err = err + val2;
            h_pull_350->Fill((val1-xsec[j])/val2);
    }
    indata15.close();
    indata150.close();

    xsec15[j]=sum/hq.size()*(1.3);
    std::cout<< xsec15[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg15[j]=err/hq.size();



    /*.c->cd(3);
    h_pull_350->Draw();
    c->cd(8);
    h_res_350->Draw();
    //c->Print(("pull300"+ss.str()+".png").c_str());
*/
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
	    h_res_400->Fill(val1-xsec[j]);
	    h_pull_400->Fill((val1-xsec[j])/val2);
    }
    indata3.close();
    indata4.close();
    xsec2[j]=sum2/hq2.size()*(1.4);
    expNeg2[j]=err2/hq2.size();

  /*  c->cd(4);
    h_pull_400->Draw();
    c->cd(9);
    h_res_400->Draw();
    *///c->Print(("pull_"+xss.str()+".png").c_str());
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
            h_res_450->Fill(val1-xsec[j]);
            sum = sum + val1;
            err = err + val2;
            h_pull_450->Fill((val1-xsec[j])/val2);
    }
    indata35.close();
    indata350.close();

    xsec25[j]=sum/hq.size();
    std::cout<< xsec25[j] << "  " <<sum<<"   "<<hq.size()<<std::endl;
    expNeg25[j]=err/hq.size();

 hq.clear();
    hq2.clear();

   /* c->cd(5);
    h_pull_450->Draw();
    c->cd(10);
    h_res_450->Draw();
  */  c->Print(("pull_"+xss.str()+".png").c_str());

    //c->Print(("pull300"+ss.str()+".png").c_str());

    hq.clear();
    hq2.clear();


}


int nPoints=5;
TGraphAsymmErrors *g_xsec_0sigma=new TGraphAsymmErrors(nPoints, xsec, xsec0, 0, 0, expNeg0, expNeg0);
g_xsec_0sigma->SetLineColor(kPink+2);
g_xsec_0sigma->SetFillColor(kPink+2);
g_xsec_0sigma->SetLineWidth(2);
TGraphAsymmErrors *g_xsec_1sigma=new TGraphAsymmErrors(nPoints, xsec, xsec1, 0, 0, expNeg1, expNeg1);
g_xsec_1sigma->SetLineColor(kOrange+2);
g_xsec_1sigma->SetFillColor(kOrange+2);
g_xsec_1sigma->SetLineWidth(2);
TGraphAsymmErrors *g_xsec_2sigma=new TGraphAsymmErrors(nPoints, xsec, xsec2, 0, 0, expNeg2, expNeg2);
g_xsec_2sigma->SetLineColor(kBlue+1);
g_xsec_2sigma->SetFillColor(kBlue+1);
g_xsec_2sigma->SetLineWidth(2);
TGraphAsymmErrors *g_xsec_15sigma=new TGraphAsymmErrors(nPoints, xsec, xsec15, 0, 0, expNeg15, expNeg15);
g_xsec_15sigma->SetLineColor(kGreen+1);
g_xsec_15sigma->SetFillColor(kGreen+1);
g_xsec_15sigma->SetLineWidth(2);
TGraphAsymmErrors *g_xsec_25sigma=new TGraphAsymmErrors(nPoints, xsec, xsec25, 0, 0, expNeg25, expNeg25);
g_xsec_25sigma->SetLineColor(kMagenta+2);
g_xsec_25sigma->SetFillColor(kMagenta+2);
g_xsec_25sigma->SetLineWidth(2);

TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
//c_xsec->SetLogy();
g_xsec_1sigma->SetMaximum(12.0); g_xsec_1sigma->SetMinimum(-1.50);
g_xsec_1sigma->Draw("AL*");
g_xsec_2sigma->Draw("L* SAME");
g_xsec_25sigma->Draw("L* SAME");
g_xsec_15sigma->Draw("L* SAME");
g_xsec_0sigma->Draw("L* SAME");
TLine * a = new TLine();
a->SetLineColor(kRed+1);
a->SetLineStyle(2);
a->SetLineWidth(3);
a->DrawLine(0.,0., 10., 10.);
// g_obs->Draw("L* SAME");
TLegend *leg=new TLegend(0.45, 0.6, 0.9, 0.85);
// TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
leg->SetFillStyle(0);
leg->SetLineColor(0);
//leg->SetTextFont(4);
//leg->AddEntry((TObject*)0, "CMS Experiment #sqrt{s} = 8 TeV, L = 18.6 fb^{-1}", "");
//leg->AddEntry((TObject*)0, "X#rightarrowH(b#bar{b}) H(b#bar{b})", "");
leg->AddEntry(g_xsec_0sigma, "#mu X(270)","LP");
leg->AddEntry(g_xsec_1sigma, "#mu X(300)","LP");
leg->AddEntry(g_xsec_15sigma, "#mu X(350)","LP");
leg->AddEntry(g_xsec_2sigma, "#mu X(400)","LP");
leg->AddEntry(g_xsec_25sigma, "#mu X(450)", "LP");
// leg->AddEntry(g_obs, "Observed Limit with fake data (background + 1 pb signal)", "LP");
leg->Draw();

 TLatex * tPrel = new TLatex();
        tPrel->SetNDC();
         tPrel->SetTextColor(kBlack);
         tPrel->SetTextSize(0.04027386);
         tPrel->DrawLatex(0.09821429,0.9194523,"CMS Preliminary; #sqrt{s} =  8 TeV L = 17.9 fb^{-1}");
c_xsec->SaveAs("Strenght.root");





}
