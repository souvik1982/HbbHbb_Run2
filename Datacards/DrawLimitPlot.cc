#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLatex.h"

#include "../AnalysisCode/TDRStyle.h"

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void DrawLimitPlot(std::vector<double> mass, double ymin, double ymax)
{
  const unsigned int nPoints=mass.size();
  double xsec[nPoints], xsecNeg1[nPoints], xsecPos1[nPoints], xsecNeg2[nPoints], xsecPos2[nPoints];
  double obs[nPoints];
  double expNeg2[nPoints], expNeg1[nPoints], expPos1[nPoints], expPos2[nPoints];
  // double mass[nPoints]={400, 600, 800, 1000, 1200};
  // double mass[nPoints]={400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  
  for (unsigned int i=0; i<nPoints; ++i)
  {
    std::string mass_string=itoa(mass[i]);
    std::string filename="HbbHbb_13TeV_mX"+mass_string+"_Asymptotic.log";
    std::ifstream file(filename.c_str(), ios::in);
    // std::cout<<"Opened file "<<filename<<std::endl;
    std::string line;
    getline(file, line);
    getline(file, line);
    getline(file, line);
    
    getline(file, line); obs[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecNeg2[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecNeg1[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsec[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecPos1[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecPos2[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    
    expNeg2[i]=xsec[i]-xsecNeg2[i];
    expNeg1[i]=xsec[i]-xsecNeg1[i];
    expPos1[i]=xsecPos1[i]-xsec[i];
    expPos2[i]=xsecPos2[i]-xsec[i];
    
    // std::cout<<"obs="<<obs[i]<<", exp="<<xsec[i]<<", -1sigma = "<<expNeg1[i]<<", +1sigma = "<<expPos1[i]<<std::endl;
    std::cout<<"mX = "<<mass_string<<", obs = "<<obs[i]<<", exp limit ="<<xsec[i]<<", -1 sigma = "<<expNeg1[i]<<", +1 sigma = "<<expPos1[i]<<std::endl;
    // std::cout<<mass_string<<" & "<<xsec[i]<<" & "<<expNeg1[i]<<" & "<<expPos1[i]<<" & "<<expNeg2[i]<<" & "<<expPos2[i]<<" \\\\ "<<std::endl;
    
  }
  
  // Graviton curve
  std::vector<double> masses_graviton={200,	
                                       260,  
                                       300,  
                                       350,  
                                       400,  
                                       450,  
                                       500,  
                                       550,  
                                       600,  
                                       650,  
                                       700,  
                                       750,  
                                       800,  
                                       850,  
                                       900,
                                       950,  
                                       1000,
                                       1050,
                                       1100,
                                       1150,
                                       1200,
                                       1250,
                                       1300,
                                       1350,
                                       1400,
                                       1450,
                                       1500,
                                       2000};
  
  
  std::vector<double> x_graviton={
                                  5.649417401247585,   
                                  1.942937143101152,  
                                  1.068487385421470,  
                                  0.551453225607504,  
                                  0.306465209281976,  
                                  0.179648341500263,  
                                  0.110212989072781,  
                                  0.070452805343422,  
                                  0.046310769831789,  
                                  0.031271547303295,  
                                  0.021611330228787,  
                                  0.015241418189689,  
                                  0.010953371285280,  
                                  0.007973233764684,  
                                  0.005886101099004,  
                                  0.004386360642407,  
                                  0.003315318658155,  
                                  0.002533722446469,  
                                  0.001949901492357,  
                                  0.001510666005692,  
                                  0.001179681973057,  
                                  0.000929048536139,  
                                  0.000734267676625,  
                                  0.000585735348110,  
                                  0.000468838667410,  
                                  0.000378059177134,  
                                  0.000307044019540,  
                                  0.000045428801850
                                };
                                  
  // Multiply graviton x-sec with appropriate Br(G->HH)*Br(H->bb)^2 * (k'/k)^2
  for(int i=0; i<masses_graviton.size(); ++i) 
  {
    x_graviton[i]=x_graviton[i]*0.25*(0.57*0.57)*pow(0.2/0.1,2)*1000. ; //BR X->HH 
    std::cout<<"Graviton mass = "<<masses_graviton[i]<<", x-sec = "<<x_graviton[i]<<std::endl;
  }
  TGraph *g_graviton=new TGraph(masses_graviton.size(), &(masses_graviton[0]), &(x_graviton[0])); g_graviton->SetLineWidth(2); g_graviton->SetLineColor(kBlue+1); g_graviton->SetFillColor(kWhite);
  
  gROOT->SetStyle("Plain");
  // gStyle->SetOptStat(000000000);
  
  TStyle *tdrStyle=setTDRStyle();
  tdrStyle->cd();
  
  TGraph *g_xsec=new TGraph(nPoints, &(mass[0]), xsec);
  g_xsec->SetTitle("; m_{X} (GeV); #sigma(pp#rightarrowX) #times Br(X#rightarrowH(b#bar{b}) H(b#bar{b})) (fb)");
  g_xsec->SetLineWidth(2);
  g_xsec->SetLineStyle(2);
  TGraphAsymmErrors *g_xsec_1sigma=new TGraphAsymmErrors(nPoints, &(mass[0]), xsec, 0, 0, expNeg1, expPos1);
  g_xsec_1sigma->SetLineColor(kGreen);
  g_xsec_1sigma->SetFillColor(kGreen);
  TGraphAsymmErrors *g_xsec_2sigma=new TGraphAsymmErrors(nPoints, &(mass[0]), xsec, 0, 0, expNeg2, expPos2);
  g_xsec_2sigma->SetLineColor(kYellow);
  g_xsec_2sigma->SetFillColor(kYellow);
  TGraph *g_obs=new TGraph(nPoints, &(mass[0]), obs);
  g_obs->SetLineWidth(2);
  g_obs->SetLineStyle(1);
  TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
  c_xsec->SetLogy();
  c_xsec->SetGridx(); c_xsec->SetGridy();
  g_xsec->SetMaximum(ymax); g_xsec->SetMinimum(ymin);
  g_xsec->Draw("AL*");
  g_xsec_2sigma->Draw("3");
  g_xsec_1sigma->Draw("3");
  g_xsec->Draw("L*");
  // g_obs->Draw("L* SAME");
  g_graviton->Draw("C same");
  TLegend *leg=new TLegend(0.55, 0.65, 0.9, 0.85);
  // TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
  leg->SetFillStyle(1); leg->SetFillColor(kWhite);
  leg->AddEntry(g_xsec, "Expected Upper Limit", "L");
  leg->AddEntry(g_xsec_1sigma, "Expected #pm 1 #sigma", "F");
  leg->AddEntry(g_xsec_2sigma, "Expected #pm 2 #sigma", "F");
  // leg->AddEntry(g_obs, "Observed Upper Limit", "LP");
  leg->Draw();
  TLatex * tPrel = new TLatex();
  tPrel->SetTextSize(0.05);
  tPrel->DrawLatexNDC(0.1, 0.94, "CMS Preliminary; #sqrt{s} = 13 TeV, L = 2.19 fb^{-1}");
  c_xsec->Update();
  c_xsec->SaveAs("UpperLimit.png");
  c_xsec->SaveAs("UpperLimit.pdf");
  
  TFile *file=new TFile("UpperLimits_xsec.root", "RECREATE");
  g_obs->Write("g_obs");
  g_xsec->Write("g_xsec");
  g_xsec_1sigma->Write("g_xsec_1sigma");
  g_xsec_2sigma->Write("g_xsec_2sigma");
  file->Close();
  
}
    
