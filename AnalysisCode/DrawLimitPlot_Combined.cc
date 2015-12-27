#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "CMS_lumi.h"
#include "tdrstyle.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLatex.h"
bool noHbb=false;
bool compareATLAS=false;
bool graviton=false;

double br_Hbb=5.77E-01;
double br_Hgg=0.23E-02*2.;
void divideGraph(TGraph *g, double val)
{
  int n=g->GetN();
  double *a=g->GetY();
  double *hi=g->GetEYhigh();
  double *lo=g->GetEYlow();
  
  for (unsigned int i=0; i<n; ++i)
  {
    a[i]=a[i]/val;
    if (hi!=0)
    {
      hi[i]=hi[i]/val;
      lo[i]=lo[i]/val;
    }
  }
}
void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }

  cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }

  pad->cd();

  float posX_;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = 1-t - 0.045*(1-t-b);
          float xl_0 = posX_;
          float yl_0 = posY_ - 0.15;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, posY_, cmsText);
          if( writeExtraText )
            {
              latex.SetTextFont(extraTextFont);
              latex.SetTextAlign(align_);
              latex.SetTextSize(extraTextSize*t);
              latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
        {
          posX_ =   l +  relPosX*(1-l-r);
          posY_ =   1-t+lumiTextOffset*t;
        }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
  return;
}

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void DrawLimitPlot_Combined()
{
   const unsigned int nPoints=5;
 // const unsigned int nPoints=96;
  double xsec[nPoints], xsecNeg1[nPoints], xsecPos1[nPoints], xsecNeg2[nPoints], xsecPos2[nPoints];
  double obs[nPoints];
  double expNeg2[nPoints], expNeg1[nPoints], expPos1[nPoints], expPos2[nPoints];
  double mass[nPoints]={260, 270, 300, 400, 600};
  //double mass[nPoints]={270, 273, 276, 279, 282, 285, 288, 291, 294, 297, 300, 305, 310, 315, 320, 325, 330, 335, 340, 345, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590 , 600, 610, 620, 630, 640, 650, 660, 670, 680,690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000, 1010, 1020, 1030, 1040, 1050, 1060, 1070, 1080, 1090, 1100};
  
  for (unsigned int i=0; i<nPoints; ++i)
  {
    std::string mass_string=itoa(mass[i]);
    std::string filename;
    if (i<30)filename ="CMS_HH4b_"+mass_string+"_13TeV_asymptoticCLs.out";
   // else if(i>=30 &&  i<59)    filename ="InterpolDatacards_10GeV/f_datacard_"+mass_string+".log";
   // else if(i>=59)  filename ="interpolatedHMR/f_datacard_"+mass_string+".log";
  
  //  if (i<=3) filename="LMA/HbbHbb_19invfb_mX"+mass_string+"_Asymptotic.log";
    std::ifstream file(filename.c_str(), ios::in);
    // std::cout<<"Opened file "<<filename<<std::endl;
    std::string line;
    getline(file, line);
    getline(file, line);
    getline(file, line);
    
if(i<59){    getline(file, line); obs[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecNeg2[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecNeg1[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsec[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecPos1[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    getline(file, line); xsecPos2[i]=atof(line.substr(line.find("<")+1).c_str())*1000;
    }
else{
    getline(file, line); obs[i]=atof(line.substr(line.find("<")+1).c_str())*100;
    getline(file, line); xsecNeg2[i]=atof(line.substr(line.find("<")+1).c_str())*100;
    getline(file, line); xsecNeg1[i]=atof(line.substr(line.find("<")+1).c_str())*100;
    getline(file, line); xsec[i]=atof(line.substr(line.find("<")+1).c_str())*100;
    getline(file, line); xsecPos1[i]=atof(line.substr(line.find("<")+1).c_str())*100;
    getline(file, line); xsecPos2[i]=atof(line.substr(line.find("<")+1).c_str())*100;
}
    expNeg2[i]=xsec[i]-xsecNeg2[i];
    expNeg1[i]=xsec[i]-xsecNeg1[i];
    expPos1[i]=xsecPos1[i]-xsec[i];
    expPos2[i]=xsecPos2[i]-xsec[i];
      std::cout<<"i " <<i<<"  mX=  "<<mass[i]<<" obs="<<obs[i]<<", exp="<<xsec[i]<<", -2sigma = "<<expNeg2[i]<<", +2sigma = "<<expPos2[i]<<std::endl;

    // std::cout<<"obs="<<obs[i]<<", exp="<<xsec[i]<<", -1sigma = "<<expNeg1[i]<<", +1sigma = "<<expPos1[i]<<std::endl;
  //  std::cout<<"mX = "<<mass_string<<", exp limit ="<<xsec[i]<<", -1 sigma = "<<expNeg1[i]<<", +1 sigma = "<<expPos1[i]<<std::endl;
  //  std::cout<<"Mass "<<mass[i]<<" GeV  Exp. Limit "<<xsec[i]<<", -1sigma = "<<expNeg1[i]<<", +1sigma = "<<expPos1[i]<<std::endl;
  }
  
  gROOT->SetStyle("Plain");
  // gStyle->SetOptStat(000000000);
  gROOT->LoadMacro("tdrstyle.h");
  setTDRStyle();

  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = false;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "17.93 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_13TeV = "2.19 fb^{-1}"; 	

  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV
  int iPos = 11;
 
  // ATLAS curve
  double masses_ATLAS[8]={500, 600, 700, 800, 900, 1000, 1100};
  double limit_ATLAS[8]={80, 25, 15, 12, 10, 9, 8};
  double limit_bbgg[15] = {2.40,2.73,2.23,1.87,1.42,0.97,0.80,0.69, 0.6,0.54,0.46,0.43,0.43, 0.48}	;  for(int i=0; i<15; i++ ) limit_bbgg[i]=limit_bbgg[i]/0.00266;
  double mass_bbgg[15] = {270, 300, 350, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1100};
  TGraph *g_ATLAS=new TGraph(7, masses_ATLAS, limit_ATLAS); g_ATLAS->SetLineWidth(2); g_ATLAS->SetLineColor(kRed); g_ATLAS->SetFillColor(kWhite);
  
  // Graviton curve
  double masses_graviton[20]={260,     300,350,     400,     450,     500,     550,     600,     650,    700,     750,     800,     850,     900,   950,     1000,    1050,    1100,    1150};
  double x_graviton[20]=     {10.7403, 185.658, 295.209,265.788, 199.824, 141.978, 97.9176, 68.5976, 47.067, 32.7501, 22.8192, 16.2399, 11.5632, 8.363, 6.01585, 4.44136, 3.24999, 2.42234, 1.8144};
  double masses_radion[11]={300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000};
  double x_radion[11]= { 2272.0725413375076, 1446.7421962329545,  830.6271984524935,  581.3817599746898,  426.34584069784813,320.7551137323525, 246.3303275668544,152.53424031123356, 100.55254575140823, 69.89048380004162, 50.7888474680315};
  for(int i=0; i<11; i++ ) x_radion[i]=x_radion[i]*0.25*3; //BR X->HH 
 
  TGraph *g_graviton=new TGraph(18, masses_graviton, x_graviton); g_graviton->SetLineWidth(2); g_graviton->SetLineColor(kBlue+1); g_graviton->SetFillColor(kWhite);
  TGraph *g_radion=new TGraph(11, masses_radion, x_radion); g_radion->SetLineWidth(2); g_radion->SetLineColor(kOrange+2); g_radion->SetFillColor(kWhite);
  
  TGraph *g_xsec=new TGraph(nPoints, mass, xsec);
  //g_xsec->SetTitle("");	
  g_xsec->SetTitle("; m_{X} (GeV); 95% CL limit on #sigma(pp#rightarrow X#rightarrowHH #rightarrow b#bar{b}b#bar{b}) (fb)"); 
  //g_xsec->GetYaxis()->SetTitleSize(0.3);
	
  g_xsec->SetLineWidth(2);
  g_xsec->SetLineStyle(2);
  TGraphAsymmErrors *g_xsec_1sigma=new TGraphAsymmErrors(nPoints, mass, xsec, 0, 0, expNeg1, expPos1);
  g_xsec_1sigma->SetLineColor(kGreen);
  g_xsec_1sigma->SetFillColor(kGreen);
  TGraphAsymmErrors *g_xsec_2sigma=new TGraphAsymmErrors(nPoints, mass, xsec, 0, 0, expNeg2, expPos2);
  g_xsec_2sigma->SetLineColor(kYellow);
  g_xsec_2sigma->SetFillColor(kYellow);
  TGraph *g_obs=new TGraph(nPoints, mass, obs);
  g_obs->SetLineWidth(2);
  g_obs->SetLineStyle(1);
  TGraph *g_bbgg=new TGraph(14, mass_bbgg, limit_bbgg);
  g_bbgg->SetLineWidth(2);
  g_bbgg->SetLineStyle(1); 
  g_bbgg->SetFillColor(0); 
  if (noHbb)
  {
    divideGraph(g_xsec,        br_Hbb*br_Hbb);
    divideGraph(g_xsec_1sigma, br_Hbb*br_Hbb);
    divideGraph(g_xsec_2sigma, br_Hbb*br_Hbb);
    divideGraph(g_ATLAS, br_Hbb*br_Hbb);
    divideGraph(g_graviton, br_Hbb*br_Hbb);
    //divideGraph(g_radion, br_Hbb*br_Hbb);
  }
  
  TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 700, 700);
  c_xsec->SetLogy(); //g_xsec->SetTitle("");
  c_xsec->SetGridx(0); c_xsec->SetGridy(0);
  g_xsec->SetMaximum(50000.0); g_xsec->SetMinimum(1.0);
  //if (noHbb) {g_xsec->SetMaximum(15.0*1e3/(br_Hbb*br_Hbb)); g_xsec->SetMinimum(0.005*1e3/(br_Hbb*br_Hbb));}
  g_xsec->Draw("AL");
  
  g_xsec_2sigma->Draw("3");
  g_xsec_1sigma->Draw("3");
  g_xsec->Draw("L");
 // g_obs->SetMarkerStyle(20);
  //g_obs->Draw("LP SAME");

  if (compareATLAS) g_ATLAS->Draw("L* same");
  //g_bbgg->SetMarkerColor(kAzure+1);
//g_graviton->Draw("C same");
//  g_bbgg->SetLineColor(kAzure+1);
//  divideGraph(g_bbgg, 0.00266);
  //g_bbgg->Draw("L* same");
//  if (graviton){ g_graviton->Draw("C same"); g_radion->Draw("C same");}

  TLatex * tPrel = new TLatex();  tPrel->SetNDC();
  tPrel->SetTextSize(0.04);tPrel->SetTextFont(42);
  //tPrel->DrawLatex(0.1, 0.94, "CMS Preliminary; #sqrt{s} = 8 TeV, L = 17.93 fb^{-1}");
  CMS_lumi(c_xsec, iPeriod, iPos );
  //tPrel->DrawLatex(0.45, 0.45, "RS1 Radion Excluded");
  //tPrel->DrawLatex(0.45, 0.35, "kL = 35, BR(X#rightarrow HH)=0.25, no R/H mixing");


  TLegend *leg=new TLegend(0.65, 0.6, 0.9, 0.8);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

  // TLegend *leg=new TLegend(0.45, 0.5, 0.9, 0.7);
  leg->SetFillStyle(0);
  leg->AddEntry(g_xsec, "Expected limit ", "lp");
  leg->AddEntry(g_xsec_1sigma, "Expected #pm 1 #sigma" ,"f");
  leg->AddEntry(g_xsec_2sigma, "Expected #pm 2 #sigma", "f");
 // leg->AddEntry(g_obs, "Observed limit","lp");
  //if (compareATLAS) leg->AddEntry(g_ATLAS, "ATLAS b#bar{b}b#bar{b} expected limit");
  //leg->AddEntry(g_bbgg, "CMS b#bar{b}#gamma#gamma expected limit");
//  leg->AddEntry(g_graviton, "RS1 KK-Graviton, #tilde{k} = 0.2");}
 // {leg->AddEntry(g_graviton, "KK-Graviton","l");}

 ///leg->AddEntry(g_radion, "Radion #Lambda_{R}=1 TeV");
  // leg->AddEntry(g_obs, "Observed Limit with fake data (background + 1 pb signal)", "LP");
  leg->Draw();
  c_xsec->SaveAs("UpperLimit_Combined.root");
  c_xsec->SaveAs("UpperLimit_Combined.pdf");
  
  TFile *file=new TFile("UpperLimits_Combined_xsec.root", "RECREATE");
  g_obs->Write("g_obs");
  g_xsec->Write("g_xsec");
  g_xsec_1sigma->Write("g_xsec_1sigma");
  g_xsec_2sigma->Write("g_xsec_2sigma");
 g_radion->Write("g_radion");
  file->Close();
  
}
    
