/* ************************************
 *  *                Library             *
 *   **************************************/

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>

#include "TArrow.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TColor.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TFractionFitter.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TMinuit.h"
#include "TMath.h"
#include "TMatrixDSym.h"
#include "TPaveText.h"
#include "TPaveText.h"
#include "TProfile.h"
#include "TRandom3.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include "TView.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooConstVar.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooIntegralMorph.h"
#include "RooNLLVar.h"
#include "RooPolynomial.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooWorkspace.h"
#include "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp.h"

using namespace RooFit ;

/*************************************
 **      Function Declaration        *
 *************************************/
Double_t straight_line(Double_t *x, Double_t *par);
Double_t pol_line(Double_t *x, Double_t *par);
void PrintArray(Double_t *v, Int_t dim, Int_t precision);
std::string itoa(int i);
void interpolation_normalization(bool);
bool flag_crystal = 1; //1 for CrystalBall 0 for ExpGaussExp

void InterpolateSignal() {
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so");
    bool flag_MMR = 1; //1 for MMR 0 for LMR
    interpolation_normalization(flag_MMR);
    // I m p o r t   p d f   s h a p e s
    // ------------------------------------------------------
    
    // Observable
    RooRealVar x("x","x",0,1000);
    
    std::string dir;
    const double step = 10;
    std::vector<double> masses;
    if (flag_MMR) {
        dir = "MMR";
        std::vector<double> masses_temp= {400, 450, 500, 550, 600, 650, 750, 800, 900};
        for (unsigned int i = 0 ; i< masses_temp.size(); i++) {
            masses.push_back(masses_temp[i]);
        }
    }
    else{
        dir = "LMR";
        std::vector<double> masses_temp= {260, 270, 300, 350, 400, 450, 500, 550};
        for (unsigned int i = 0 ; i< masses_temp.size(); i++) {
            masses.push_back(masses_temp[i]);
        }
        
    }
    const unsigned int nMCpoints=masses.size();
    
    TFile *f[nMCpoints];
    RooWorkspace* xf[nMCpoints];
    RooAbsPdf* PDF_mass[nMCpoints];
    
    for (unsigned int i = 0; i<nMCpoints; i++ ) {
        TString name = Form("%s_%d/w_signal_%d.root", dir.c_str(), int(masses[i]),int(masses[i]));
        if (!gSystem->AccessPathName(name)) {
            f[i] = new TFile(name);
            xf[i] = (RooWorkspace*)f[i]->Get("HbbHbb");
            xf[i]->Print();
            PDF_mass[i] = xf[i]->pdf("signal_fixed");
            PDF_mass[i]->Print("t");
        } else {
            std::cout<<"File is not found: "<<name<<std::endl;
            return;
        }
    }
    
    RooWorkspace* w_test= new RooWorkspace("w_test");
    for (unsigned int i = 0; i!=nMCpoints; ++i ) {
        RooWorkspace w("w");
        TString name = Form("mass_%d",int(masses[i]));
        cout<<"test_1" << endl;
        PDF_mass[i]->Print();
        cout<<"test_2" << endl;
        w.import(*PDF_mass[i],RooFit::RenameConflictNodes(name),RooFit::RenameAllVariablesExcept(name,"x"),RooFit::RenameVariable("signal_fixed","signal_fixed_"+name), RooFit::RenameVariable("signalCore_fixed","signalCore_fixed_"+name), RooFit::RenameVariable("signalComb_fixed","signalComb_fixed_"+name) );
        cout<<"test_3" << endl;
        w.Print();
        cout<<"test_4" << endl;
        PDF_mass[i]->Print();
        cout<<"test_5" << endl;
        PDF_mass[i] = w.pdf("signal_fixed_"+name);
        cout<<"test_6" << endl;
        PDF_mass[i]->Print();
        cout<<"test_7" << endl;
        w_test= new RooWorkspace("w_test");
        w_test->import(*PDF_mass[i]);
        w_test->Print();
        PDF_mass[i] = w_test->pdf("signal_fixed_"+name);
        w_test->Print();
        cout<<"test_8" << endl;
        if (i!=0)PDF_mass[i-1]->Print();
    }
    cout<<"test_9" << endl;
    w_test->Print();
    for (unsigned int i = 0; i!=nMCpoints; ++i ) {
        cout<<"test_10" << endl;
        PDF_mass[i]->Print("t");
    }
    
    // C r e a t e   i n t e r p o l a t i n g   p d f
    // -----------------------------------------------
    
    // Create interpolation variable
    RooRealVar alpha("alpha","alpha",0,1.0) ;
    
    // Specify sampling density on observable and interpolation variable
    x.setBins(10000,"cache") ;
    alpha.setBins(2200,"cache") ;
    
    TCanvas* c[nMCpoints];
    TCanvas* c_tot;
    RooPlot* frame1[nMCpoints];
    RooPlot* frame_tot;
    frame_tot = x.frame() ;
    
    for (unsigned int iPoint = 0; iPoint<nMCpoints-1; iPoint++) {
        
        RooIntegralMorph lmorph("lmorph","lmorph",*PDF_mass[iPoint+1],*PDF_mass[iPoint],x,alpha) ;
        
        frame1[iPoint] = x.frame() ;
        PDF_mass[iPoint]->plotOn(frame1[iPoint]) ;
        PDF_mass[iPoint+1]->plotOn(frame1[iPoint]) ;
        PDF_mass[iPoint]->plotOn(frame_tot) ;
        PDF_mass[iPoint+1]->plotOn(frame_tot) ;
        cout<< " Interpolate from " << masses[iPoint] << " to " << masses[iPoint+1] << endl;
        
        int nPoints = int((masses[iPoint+1]-masses[iPoint])/step);
        for (int i=0; i<=nPoints; i++) {
            
            alpha.setVal(double(i)/double(nPoints)) ;
            cout<< " Interpolate mass : " << int(masses[iPoint]+i*step) << endl;
            lmorph.plotOn(frame1[iPoint],LineColor(kRed)) ;
            lmorph.plotOn(frame_tot,LineColor(kRed)) ;
            
            TH1D* hist = (TH1D*)lmorph.createHistogram("m_X (GeV)",x,Binning(1000,0,1000));
            TCanvas* c_temp = new TCanvas(Form("linearmorph_%d",iPoint),Form("linearmorph_%d",iPoint),700,700) ;
            hist->Draw();
            c_temp->SaveAs(Form("%s_%d/c_mX_SR_KinFit_%d.png", dir.c_str(), int(masses[iPoint]+i*step),int(masses[iPoint]+i*step)));
            delete c_temp;
            
            
            RooRealVar *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3,*sg_p4;
            double m=masses[iPoint]+i*step;
            
            if (flag_MMR) {
                double rangeHi = 0.9*m + 160;
                double rangeLo = 0.7*m + 80;
                if (rangeLo<250) rangeLo=250;
                sg_p0=new RooRealVar("sg_p0", "sg_p0", 0.9*m+20, m+30);
                sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 35.);
                sg_p2=new RooRealVar("sg_p2", "sg_p2", 0., 0.5);
                sg_p3=new RooRealVar("sg_p3", "sg_p3", 0.,7.);
                x=new RooRealVar("x", "m_{X} (GeV)", rangeLo-100., rangeHi+100.);
                ExpGaussExp signal("signal", "Signal Prediction", *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3);
                RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), hist);
                signal.fitTo(signalHistogram, RooFit::Range(rangeLo, rangeHi), RooFit::Save());
                
                RooRealVar signal_p0("signal_p0", "signal_p0", sg_p0->getVal());
                RooRealVar signal_p1("signal_p1", "signal_p1", sg_p1->getVal());
                RooRealVar signal_p2("signal_p2", "signal_p2", sg_p2->getVal());
                RooRealVar signal_p3("signal_p3", "signal_p3", sg_p3->getVal());
                ExpGaussExp signal_fixed("signal_fixed", "Signal Prediction Fixed", *x, signal_p0, signal_p1, signal_p2, signal_p3);
                RooWorkspace *w=new RooWorkspace("HbbHbb");
                w->import(signal_fixed);
                w->SaveAs(Form("MMR_%d/w_signal_%d.root",int(masses[iPoint]+i*step),int(masses[iPoint]+i*step)));
            }
            else{
                double rangeHi = 1.1*m + 50;
                double rangeLo = m/3. + 160;
                if (rangeLo<250) rangeLo=250;
                sg_p0=new RooRealVar("sg_p0", "sg_p0", 0.94*m, 1.1*m);
                sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 0.1*m-20.);
                double mu_min = 1.6*m-440.; if (mu_min<0) mu_min=10.;
                sg_p2=new RooRealVar("sg_p2", "sg_p2", mu_min, 0.95*m+100.);
                double sigma_max;
                if (m<300) {sigma_max=300.;}else{ sigma_max = 150.;}
                sg_p3=new RooRealVar("sg_p3", "sg_p3", 10.,sigma_max);
                sg_p4=new RooRealVar("sg_p4", "sg_p4", 0., 1.);
                
                x=new RooRealVar("x", "m_{X} (GeV)", rangeLo, rangeHi);
                RooGaussian signalCore("signalCore", "Signal Prediction", *x, *sg_p0, *sg_p1);
                RooGaussian signalComb("signalComb", "Combinatoric", *x, *sg_p2, *sg_p3);
                RooAddPdf signal("signal", "signal", RooArgList(signalCore, signalComb), *sg_p4);
                RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), hist);
                signal.fitTo(signalHistogram, RooFit::Range(rangeLo-50, rangeHi), RooFit::Save());
                RooRealVar signal_p0("signal_p0", "signal_p0", sg_p0->getVal());
                RooRealVar signal_p1("signal_p1", "signal_p1", sg_p1->getVal());
                RooRealVar signal_p2("signal_p2", "signal_p2", sg_p2->getVal());
                RooRealVar signal_p3("signal_p3", "signal_p3", sg_p3->getVal());
                RooRealVar signal_p4("signal_p4", "signal_p4", sg_p4->getVal());
                RooGaussian signalCore_fixed("signalCore_fixed", "Signal Prediction", *x, signal_p0, signal_p1);
                RooGaussian signalComb_fixed("signalComb_fixed", "Combinatoric", *x, signal_p2, signal_p3);
                RooAddPdf signal_fixed("signal_fixed", "signal", RooArgList(signalCore_fixed, signalComb_fixed), signal_p4);
                
                RooWorkspace *w=new RooWorkspace("HbbHbb");
                w->import(signal_fixed);
                w->SaveAs(Form("%s_%d/w_signal_%d.root", dir.c_str(), int(masses[iPoint]+i*step),int(masses[iPoint]+i*step)));
            }
        }
        c[iPoint] = new TCanvas(Form("linearmorph_%d",iPoint),Form("linearmorph_%d",iPoint),700,700) ;
        frame1[iPoint]->Draw();
        c[iPoint]->SaveAs(Form("fig/linearmorph_%d_%d.png",int(masses[iPoint]), int(masses[iPoint+1])));
        c[iPoint]->SaveAs(Form("fig/linearmorph_%d_%d.pdf",int(masses[iPoint]), int(masses[iPoint+1])));
        c[iPoint]->SaveAs(Form("fig/linearmorph_%d_%d.root",int(masses[iPoint]), int(masses[iPoint+1])));
        
    }
    c_tot = new TCanvas("linearmorph_tot","linearmorph_tot",700,700) ;
    frame_tot->Draw();
    c_tot->SaveAs("fig/linearmorph_tot.png");
    c_tot->SaveAs("fig/linearmorph_tot.pdf");
    c_tot->SaveAs("fig/linearmorph_tot.root");
    return ;
}

/*********************************
 **           Functions          *
 *********************************/

//================================================================================

void interpolation_normalization(bool flag_MMR=0){
    
    std::vector<double> mass_0;
    std::vector<double> mass;
    std::string dir;
    if (flag_MMR) {
        dir = "MMR";
        std::vector<double> mass_0_temp= {400, 450, 500, 550, 600, 650, 750, 800, 900};
        std::vector<double> mass_temp={400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900};
        for (unsigned int i = 0 ; i< mass_0_temp.size(); i++) {
            mass_0.push_back(mass_0_temp[i]);
        }
        for (unsigned int i = 0 ; i< mass_temp.size(); i++){
            mass.push_back(mass_temp[i]);
        }
    }
    else{
        dir = "LMR";
        std::vector<double> mass_0_temp= {260, 270, 300, 350, 400, 450, 500, 550};
        std::vector<double> mass_temp={260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550};
        for (unsigned int i = 0 ; i< mass_0_temp.size(); i++) {
            mass_0.push_back(mass_0_temp[i]);
        }
        for (unsigned int i = 0 ; i< mass_temp.size(); i++){
            mass.push_back(mass_temp[i]);
        }
    }
    const unsigned int nPoints=mass.size();
    const unsigned int nPoints_0=mass_0.size();
    double signal[nPoints], lin[nPoints],interpol[nPoints];
    double signal_0[nPoints_0];
    int j=0;
    
    
    for (unsigned i = 0; i<nPoints; i++) {
        if (std::find(mass_0.begin(), mass_0.end(), mass[i]) != mass_0.end()){
            continue;
        }
        if (gSystem->AccessPathName(Form("%s_%d", dir.c_str(), int(mass[i])))) {
            gSystem->Exec(Form("mkdir %s_%d", dir.c_str(), int(mass[i])));
        }
        int lMarker=0;
        for (auto m : mass_0){
            if (m > mass[i]){
                break;
            }
            lMarker++;
        }
        gSystem->Exec(Form("cp -r %s_%d/datacard_%d.txt %s_%d/datacard_%d.txt", dir.c_str(), int(mass_0[lMarker]), int(mass_0[lMarker]), dir.c_str(), int(mass[i]), int(mass[i])));
        gSystem->Exec(Form("cp -r %s_%d/index.html %s_%d/index.html", dir.c_str(), int(mass_0[lMarker]), dir.c_str(), int(mass[i])));
        if (flag_crystal) {
            gSystem->Exec(Form("cp -r %s_%d/w_background_Crystal.root %s_%d/w_background_Crystal.root", dir.c_str(), int(mass_0[lMarker]), dir.c_str(), int(mass[i])));
        }
        else{
            gSystem->Exec(Form("cp -r %s_%d/w_background_GaussExp.root %s_%d/w_background_GaussExp.root", dir.c_str(), int(mass_0[lMarker]), dir.c_str(), int(mass[i])));
            gSystem->Exec(Form("cp -r %s_%d/w_data.root %s_%d/w_data.root", dir.c_str(), int(mass_0[lMarker]), dir.c_str(), int(mass[i])));
        }
        gSystem->Exec(Form("sed -i 's/%d/%d/g' %s_%d/datacard_%d.txt", int(mass_0[lMarker]), int(mass[i]), dir.c_str(), int(mass[i]), int(mass[i])));
        
    }
    
    
    
    for (unsigned i = 0; i<nPoints; i++) {
        
        std::string mass_string= itoa(mass[i]);
        std::cout<< mass_string << std::endl;
        std::string filename=dir+"_"+mass_string+"/index.html";
        
        std::ifstream file(filename.c_str(), ios::in);
        
        bool found= false;
        std::string line;
        while (!found && !file.eof()) {
            getline(file, line);
            std::size_t pos = line.find("norm");
            if (pos!=std::string::npos){
                found=true;
                signal[i] = atof(line.substr(line.find("norm")+7,line.find_last_of(" ")).c_str());
                if (std::find(mass_0.begin(), mass_0.end(), mass[i]) != mass_0.end()){
                    signal_0[j] = atof(line.substr(line.find("norm")+7,line.find_last_of(" ")).c_str());
                    j++;
                }
            }
        }
        file.close();
    }
    
    //PrintArray(signal, nPoints, 5);
    //PrintArray(signal_0, nPoints_0, 5);
    
    TCanvas *c1 = new TCanvas("canvas","canvas",800,800);
    c1->SetGrid();
    TH1F* hr_1;
    if (flag_MMR) {
        hr_1 = c1->DrawFrame(200,0,1000,2500);
        hr_1->SetTitle("MMR");
    } else {
        hr_1 = c1->DrawFrame(200,0,600,1600);
        hr_1->SetTitle("LMR");
    }
    hr_1->SetXTitle("mass");
    hr_1->GetYaxis()->SetTitleOffset(1.2);
    hr_1->SetYTitle("norm");
    c1->GetFrame()->SetBorderSize(12);
    
    
    TGraphErrors* g_signal = new TGraphErrors(nPoints, &(mass[0]), signal);
    g_signal->SetMarkerColor(kBlue);
    g_signal->SetMarkerStyle(20);
    g_signal->SetLineColor(0);
    //g_signal->Draw("P");
    
    TGraphErrors* g_signal_0 = new TGraphErrors(nPoints_0, &(mass_0[0]), signal_0);
    g_signal_0->SetMarkerColor(kRed);
    g_signal_0->SetMarkerStyle(21);
    g_signal_0->SetLineColor(0);
    g_signal_0->Draw("P");
    
    TF1 *fit_lin = new TF1("fit_lin",straight_line,100,1000,2);
    fit_lin->SetParameter(0, -1000.);
    fit_lin->SetParameter(1, 5.);
    fit_lin->SetParName(0, "q");
    fit_lin->SetParName(1, "m");
    if (flag_MMR) {
        g_signal_0->Fit(fit_lin,"","",400,900);
    }
    else{
        g_signal_0->Fit(fit_lin,"","",260,550);
    }
    
    for (unsigned i = 0; i<nPoints; i++) {
        lin[i]=fit_lin->GetParameter(1)*mass[i]+fit_lin->GetParameter(0);
    }
    TGraphErrors* g_signal_1 = new TGraphErrors(nPoints, &(mass[0]), lin);
    g_signal_1->SetMarkerColor(8);
    g_signal_1->SetMarkerStyle(22);
    g_signal_1->SetLineColor(0);
    //g_signal_1->Draw("P");
    
    
    
    
    for (unsigned i = 0; i<nPoints; i++) {
        if (std::find(mass_0.begin(), mass_0.end(), mass[i]) != mass_0.end()){
            interpol[i]=signal[i];
        }
        else{
            int lMarker=0;
            for (auto pVal : mass_0){
                if (pVal > mass[i]){
                    break;
                }
                lMarker++;
            }
            interpol[i] =( (signal_0[lMarker]-signal_0[lMarker-1])*(mass[i]-mass_0[lMarker-1])/(mass_0[lMarker]-mass_0[lMarker-1])+signal_0[lMarker-1]);
        }
    }
    TGraphErrors* g_signal_2 = new TGraphErrors(nPoints, &(mass[0]), interpol);
    g_signal_2->SetMarkerColor(kBlue);
    g_signal_2->SetMarkerStyle(20);
    g_signal_2->SetLineColor(0);
    g_signal_2->Draw("P");
    g_signal_0->Draw("P");
    
    
    TF1 *fit_pol = new TF1("fit_lin",pol_line,100,1000,4);
    fit_pol->SetParameter(0, 2386.);
    fit_pol->SetParameter(1, -20.);
    fit_pol->SetParameter(2, 0.07 );
    fit_pol->SetParameter(3, -1.e-05);
    fit_pol->SetParName(0, "x_0");
    fit_pol->SetParName(1, "x_1");
    fit_pol->SetParName(2, "x_2");
    fit_pol->SetParName(3, "x_3");
    if (flag_MMR) {
        g_signal_0->Fit(fit_pol,"","", 400,900);
    }
    else{
        g_signal_0->Fit(fit_pol,"","", 260,550);
    }
    
    
    TLegend *leg=new TLegend(0.2, 0.65, 0.65, 0.85);
    leg->SetFillStyle(1); leg->SetFillColor(kWhite);
    leg->AddEntry(g_signal_0, "Norm for MC masses", "lep");
    //leg->AddEntry(g_signal_1, "Linear fit of MC masses", "lep");
    leg->AddEntry(g_signal_2, "Interpolation", "lep");
    leg->AddEntry(fit_pol, "Pol3 fit of MC masses", "l");
    leg->SetFillColor(kWhite);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
    leg->Draw();
    
    gPad->Update();
    if (flag_MMR) {
        c1->SaveAs("interpolation_MMR.pdf");
        c1->SaveAs("interpolation_MMR.png");
        
    } else {
        c1->SaveAs("interpolation_LMR.pdf");
        c1->SaveAs("interpolation_LMR.png");
        
    }
    //PrintArray(interpol, nPoints, 5);
    
    for (unsigned i = 0; i<nPoints; i++) {
        
        std::string mass_string= itoa(mass[i]);
        std::string filename=dir+"_"+mass_string+"/datacard_"+mass_string+".txt";
        
        std::ifstream file(filename.c_str(), ios::in);
        
        bool found= false;
        std::string line;
        double background_temp=0.;
        
        
        
        while (!found && !file.eof()) {
            getline(file, line);
            std::size_t pos = line.find("rate");
            if (pos!=std::string::npos){
                found=true;
                background_temp = atof((line.substr(line.find_last_of(" "))).c_str());
            }
            
        }
        
        
        if (std::find(mass_0.begin(), mass_0.end(), mass[i]) != mass_0.end()){
            continue;
        }
        
        int lMarker=0;
        for (auto m : mass_0){
            if (m > mass[i]){
                break;
            }
            lMarker++;
        }
        gSystem->Exec(Form("sed -i 's/.*rate.*/rate                  %f %f/g' %s_%d/datacard_%d.txt", interpol[i], background_temp, dir.c_str(), int(mass[i]), int(mass[i])));
    }
    cout<<"end"<<endl;
}





//================================================================================

Double_t straight_line(Double_t *x, Double_t *par)
{
    Double_t m,q; // Exponential slope
    
    q = par[0];
    m = par[1];
    
    return q + m*x[0];
}

//================================================================================

Double_t pol_line(Double_t *x, Double_t *par)
{
    Double_t x_0,x_1,x_2,x_3; // Exponential slope
    
    x_0 = par[0];
    x_1 = par[1];
    x_2 = par[2];
    x_3 = par[3];
    
    return x_0 + x_1*x[0]+ x_2*x[0]*x[0]+ x_3*x[0]*x[0]*x[0];
}

//================================================================================

void PrintArray(Double_t *v, Int_t dim, Int_t precision){
    int i;
    for (i = 0; i < dim; i++){
        switch (precision) {
            case 0: printf("v[%d]: %.0f\n", i, v[i]); break;
            case 1: printf("v[%d]: %.1f\n", i, v[i]); break;
            case 2: printf("v[%d]: %.2f\n", i, v[i]); break;
            case 3: printf("v[%d]: %.3f\n", i, v[i]); break;
            case 4: printf("v[%d]: %.4f\n", i, v[i]); break;
            case 5: printf("v[%d]: %.5f\n", i, v[i]); break;
            case 6: printf("v[%d]: %.6f\n", i, v[i]); break;
            case 7: printf("v[%d]: %.7f\n", i, v[i]); break;
            default : printf("v[%d]: %.8f\n", i, v[i]); break;
        }
    }
    cout << endl;
}

//================================================================================

std::string itoa(int i)
{
    char res[4];
    sprintf(res, "%d", i);
    std::string ret(res);
    return ret;
}

//================================================================================
