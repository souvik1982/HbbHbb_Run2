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
//    std::string filename="HbbHbb_13TeV_mX"+mass_string+"_Asymptotic.log";
    std::string filename="CMS_HH4b_"+mass_string+"_13TeV_asymptoticCLs.out";
    std::ifstream file(filename.c_str(), ios::in);
    std::cout<<"Opened file "<<filename<<std::endl;
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
  std::vector<double> masses_graviton={//260,300,400,500,600,700,800,900,1000};
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
                                       1500};

  std::vector<double> x_graviton{
			 13189.5110556213,
 7213.724953,
 3724.152306612245,
 2074.118283562500,
 1220.908845777777,
 756.0527086799999,
 484.2628197024792,
 321.127891575,
 219.297103860355, 
 152.2164810122449,
 108.4982254720000,
 78.4962635203125 ,
 57.88419000415223,
 43.08418917777778,
 32.69710000221605,
 24.96632111100000,
 19.26116379591836,
 15.04592709917355,
 11.87132725293005,
 9.391763225,
 7.510401695231998,
 6.032381149171598,
 4.878695042469133,
 3.980540729387755,
 3.259530744827586,
 2.6789518692	
};

  std::vector<double> br_hh={//32.552,593.385,959.755,573.531,308.096,162.880,89.196,50.616,29.627};
				 7.875333606243001e-6,
				0.0002609363907507743,
				0.0008527793007645482 , 
				0.0014748453016228675,
				0.00202120813640487,
				0.0024744221679741125,
				0.002843812476091045,
				0.003144265384982541,
				0.0033897489806557304,
				0.0035917787224510177, 
				0.03759423688146881,
				0.0038997130095539006, 
				0.04018077826392619,
				0.004118727164348574,   
				0.004204942476367313,   
				0.00427930100894505,   
				0.004343843097937954, 
				0.004400197131035117,  
 				0.004449673107888205,
				0.0044933330427632395, 
				0.00453204428524029 , 
				0.004566520194709918,   
				0.004597351400961763, 
				0.004625030011213332, 
				0.00464996849485267,   
 				0.004672514523079795
                              };
  // Multiply graviton x-sec with appropriate Br(G->HH)*Br(H->bb)^2 * (k'/k)^2
  for(int i=0; i<masses_graviton.size(); ++i) 
  {
    x_graviton[i]=x_graviton[i]*br_hh[i]*(0.57*0.57)*1000. ; 
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
    
