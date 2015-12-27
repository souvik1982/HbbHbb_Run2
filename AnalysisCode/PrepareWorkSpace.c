#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>

double H_mass=125.0;
double mH_diff_cut=40.;
double mH_mean_cut=20.;
double btagSF=1.0;
double rebin=10;
bool bReg=false;

std::string tags="MMMM"; // MMMM

double VR_lo=250.;
double VR_hi=651.;
double SR_lo=250.;//252.;
double SR_hi=650;//651.;

double r1=15., r2=35.;
struct Params
{
  double sg_p0;
  double sg_p1;
  double sg_p2;
  double sg_p3;
  double sg_p4;
  double sg_p0_err;
  double sg_p1_err;
  double sg_p2_err;
  double sg_p3_err;
  double sg_p4_err;
};

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f, 0.5);
}
/*
RooPlot* fitttbar(RooDataHist r, int color, Params &params, RooWorkspace *w)
{
  RooRealVar *x=new RooRealVar("x", "m_{X} [GeV]", SR_lo, SR_hi);
  std::cout<<"x="<<x<<std::endl;

  RooRealVar *tt_p0=new RooRealVar("tt_p0", "tt_p0", 400, 450);
  RooRealVar *tt_p1=new RooRealVar("tt_p1", "tt_p1", 60, 90);
  RooRealVar *tt_p2=new RooRealVar("tt_p2", "tt_p2", 0.3, 0.9);

  GaussExp ttbar("ttbar", "ttbar", *x, *tt_p0, *tt_p1, *tt_p2);
  RooFitResult *r_ttbar=ttbar.fitTo(r, RooFit::Range(SR_lo, SR_hi), RooFit::Save());

  params.sg_p0=tt_p0->getVal(); params.sg_p0_err=tt_p0->getError();
  params.sg_p1=tt_p1->getVal(); params.sg_p1_err=tt_p1->getError();
  params.sg_p2=tt_p2->getVal(); params.sg_p2_err=tt_p2->getError();
  RooPlot *plot=x->frame();
  r.plotOn(plot);
  if (color==kBlack)
  {
    // ttbar.plotOn(plot, RooFit::VisualizeError(*r_ttbar, 2), RooFit::FillColor(kGreen));
    ttbar.plotOn(plot, RooFit::VisualizeError(*r_ttbar, 1), RooFit::FillColor(kGray));
    }
     ttbar.plotOn(plot, RooFit::LineColor(color));
  r.plotOn(plot, RooFit::MarkerColor(color));
  if (color==kBlack)
  {
    RooRealVar ttbar_p0("ttbar_p0", "ttbar_p0", tt_p0.getVal());
    RooRealVar ttbar_p1("ttbar_p1", "ttbar_p1", tt_p1.getVal());
    RooRealVar ttbar_p2("ttbar_p2", "ttbar_p2", tt_p2.getVal());
    GaussExp ttbar_fixed("ttbar", "ttbar", *x, ttbar_p0, ttbar_p1, ttbar_p2);
    w->import(ttbar_fixed);
              }
               return plot;
                       }
 */  	


void PrepareWorkSpace()
{

  gROOT->SetStyle("Plain");

  TFile *f_MMMM_a=new TFile("LMRSelection/Histograms_BTagCSV_2015_Skim.root");
  f_MMMM_a->cd(); 

  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", SR_lo, SR_hi);
 
  std::cout<<" = MMMM Background Prediction ==== "<<std::endl;
  TH1F *h_mMMMMa_3Tag_CR24=(TH1F*)f_MMMM_a->Get("h_mX_SB");
  TH1F *h_mMMMMa_3Tag_SR;
  h_mMMMMa_3Tag_SR=(TH1F*)f_MMMM_a->Get("h_mX_SR");
  h_mMMMMa_3Tag_CR24->SetLineColor(kBlue);
  h_mMMMMa_3Tag_SR->SetLineColor(kBlue);
  TH1F *h_mMMMMa_3Tag_SR_Prediction=(TH1F*)h_mMMMMa_3Tag_CR24->Clone("h_mMMMMa_3Tag_SR_Prediction");
  double aC=h_mMMMMa_3Tag_CR24->Integral(h_mMMMMa_3Tag_CR24->FindBin(SR_lo), h_mMMMMa_3Tag_CR24->FindBin(SR_hi));

std::cout<<"  asd "<<std::endl;

 RooRealVar bg_p0("bg_p0", "bg_p0", 400., 500.);
 RooRealVar bg_p1("bg_p1", "bg_p1", 60., 90.1);
 RooRealVar bg_p2("bg_p2", "bg_p2", 0.3, 0.7);
  
 GaussExp bg("bg", "Background Prediction PDF", *x, bg_p0, bg_p1, bg_p2);
 RooDataHist pred("pred", "Prediction from SB", RooArgList(*x), h_mMMMMa_3Tag_SR_Prediction);

  bg.fitTo(pred, RooFit::Range(SR_lo, SR_hi),RooFit::SumW2Error(kTRUE));
  RooPlot *aC_plot=x->frame();
  pred.plotOn(aC_plot, RooFit::LineColor(kRed), RooFit::MarkerColor(kRed));
  bg.plotOn(aC_plot, RooFit::LineColor(kRed));
  TCanvas *c_rooFit=new TCanvas("c_rooFit", "c_rooFit", 1000, 700);
  if (tags!="MMMM") h_mMMMMa_3Tag_CR24->Draw("Ep9 SAME");
  aC_plot->Draw();



  std::cout<<" --------------------- Building Envelope --------------------- "<<std::endl;
  std::cout<< " bg_p0 "<<bg_p0.getVal() <<  "  err  "<<bg_p0.getError()<<std::endl;
  std::cout<< " bg_p1 "<<bg_p1.getVal() <<  "  err  "<<bg_p1.getError()<<std::endl;
  std::cout<< " bg_p2 "<<bg_p2.getVal() <<  "  err  "<<bg_p2.getError()<<std::endl;


std::string point[5]={"260","270","300","400","600"};

///// keep ttbar


  double totalLuminosity=2190; // /pb
/*
  double xsec_ttbar_fulllept=24.56;
  double xsec_ttbar_semilept=103.12;
  double xsec_ttbar_hadronic=106.32;


  TFile *ttbar_fulllept=new TFile("MMMM_nominal/a_KinFit/Histograms_DiJetPt_TTJets_FullLeptMGDecays_8TeV-madgraph_selected.root");
  TFile *ttbar_semilept=new TFile("MMMM_nominal/a_KinFit/Histograms_DiJetPt_TTJets_SemiLeptMGDecays_8TeV-madgraph_selected.root");
  TFile *ttbar_hadronic=new TFile("MMMM_nominal/a_KinFit/Histograms_DiJetPt_TTJets_HadronicMGDecays_8TeV-madgraph_selected.root");
  TFile *ttbar_fulllept_old=new TFile("/gpfs/ddn/cms/user/cvernier/H4b_step2/CMSSW_5_3_3_patch2/src/VHbbAnalysis/VHbbDataFormats/bin/DiJetPt_TTJets_FullLeptMGDecays_8TeV-madgraph.root");
  TFile *ttbar_semilept_old=new TFile("/gpfs/ddn/cms/user/cvernier/H4b_step2/CMSSW_5_3_3_patch2/src/VHbbAnalysis/VHbbDataFormats/bin/DiJetPt_TTJets_SemiLeptMGDecays_8TeV-madgraph.root");
  TFile *ttbar_hadronic_old=new TFile("/gpfs/ddn/cms/user/cvernier/H4b_step2/CMSSW_5_3_3_patch2/src/VHbbAnalysis/VHbbDataFormats/bin/DiJetPt_TTJets_HadronicMGDecays_8TeV-madgraph.root");
	
  TH1F *h_mX_SR_ttbar_fulllept=(TH1F*)ttbar_fulllept->Get("h_mX_SR");
  TH1F *h_mX_SR_ttbar_semilept=(TH1F*)ttbar_semilept->Get("h_mX_SR");
  TH1F *h_mX_SR_ttbar_hadronic=(TH1F*)ttbar_hadronic->Get("h_mX_SR");
  double init_ttbar_fulllept=((TH1F*)ttbar_fulllept_old->Get("CountWithPU"))->GetBinContent(1);
  double init_ttbar_semilept=((TH1F*)ttbar_semilept_old->Get("CountWithPU"))->GetBinContent(1);
  double init_ttbar_hadronic=((TH1F*)ttbar_hadronic_old->Get("CountWithPU"))->GetBinContent(1);

  std::cout<<"init_ttbar_fulllept = "<<init_ttbar_fulllept<<std::endl;
  std::cout<<"init_ttbar_semilept = "<<init_ttbar_semilept<<std::endl;
  std::cout<<"init_ttbar_hadronic = "<<init_ttbar_hadronic<<std::endl;

  double scale_ttbar_fulllept=totalLuminosity*xsec_ttbar_fulllept/init_ttbar_fulllept;
  double scale_ttbar_semilept=totalLuminosity*xsec_ttbar_semilept/init_ttbar_semilept;
  double scale_ttbar_hadronic=totalLuminosity*xsec_ttbar_hadronic/init_ttbar_hadronic;


  h_mX_SR_ttbar_fulllept->Scale(scale_ttbar_fulllept);
  h_mX_SR_ttbar_semilept->Scale(scale_ttbar_semilept);
  h_mX_SR_ttbar_hadronic->Scale(scale_ttbar_hadronic);

	
 
  TH1F *h_mX_SR_ttbar=(TH1F*)h_mX_SR_ttbar_fulllept->Clone("h_mX_SR_ttbar");
  h_mX_SR_ttbar->Add(h_mX_SR_ttbar_semilept);
  h_mX_SR_ttbar->Add(h_mX_SR_ttbar_hadronic);	

  h_mX_SR_ttbar->Rebin(rebin);
  int bin1=h_mX_SR_ttbar->FindBin(SR_lo);
  int bin2=h_mX_SR_ttbar->FindBin(SR_hi)-1;

  // Print out the lnN systematics of normalization
  double ttbar=h_mX_SR_ttbar->Integral(bin1, bin2);
  std::cout<<"TT h_mX_SR_ttbar->Integral(bin1, bin2) = "<<h_mX_SR_ttbar->Integral(bin1, bin2)<<std::endl; 
 	  
 */

for(int h=0; h<5;h++){


  //std::cout<<"Background CR->SR Scale  = "<<h_mX_SR->GetSumOfWeights()/h_mX_CR24->GetSumOfWeights()<<"  num " << h_mX_SR->GetSumOfWeights()<<"  den "<<h_mX_CR24->GetSumOfWeights()<< std::endl;

  std::string filename="LMRSelection/Histograms_Graviton"+point[h]+"GeV.root";
  
  TFile *signal=new TFile(filename.c_str());
  //TFile *signal_old=new TFile(filename_old.c_str());
  // Calculate nSignal events given production cross section, branching fractions and efficiency
  TH1F *h_CountWithPU=(TH1F*)signal->Get("Count");
  double nSignal_init=h_CountWithPU->GetBinContent(1);
  double prodXsec_1[5]={0, 1., 2., 5., 10.}; // pb

  
  int num_toys =h_mMMMMa_3Tag_SR->Integral(h_mMMMMa_3Tag_SR->FindBin(SR_lo), h_mMMMMa_3Tag_SR->FindBin(SR_hi)-1); //GetSumOfWeights();///h_mX_CR24->GetSumOfWeights();

  for(int n =1; n<2; n++){ 
	  for(int toy=0; toy<1; toy++){

		  TH1F *h_mX_SR_signal=(TH1F*)signal->Get("h_mX_SR"); 
		  h_mX_SR_signal->Rebin(rebin);
		  RooRealVar *sg_p0, *sg_p1, *sg_p2, *sg_p3, *sg_p7, *sg_p8;
		  double rangeLo=-1, rangeHi=-1; 
			  if (point[h]=="270")
			  {
				  rangeLo=252, rangeHi=600.;
				      sg_p0=new RooRealVar("sg_p0", "sg_p0", 260., 280.);
                                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 5.);
                                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 530.);
                                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
                                  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0.5, 1.);/*
				sg_p0=new RooRealVar("sg_p0", "sg_p0", 260., 280.);
         			sg_p1=new RooRealVar("sg_p1", "sg_p1", 1., 5.);
		         	sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 500.);
         			sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
         			sg_p8=new RooRealVar("sg_p8", "sg_p8", 0.5, 1.);
*/
	
			  }
			   if (point[h]=="260")
                          {
                                  rangeLo=252., rangeHi=630.;
                                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 250., 270.);
                                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 2., 6.);
                                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 10., 590.);
                                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 300.);
                                  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0.5, 1.);
                          }
			   if (point[h]=="600")
                          {
                                  rangeLo=580., rangeHi=650.;
                                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 580., 630.);
                                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 40.);
                                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 500., 650.);
                                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
                                  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0.7, 1.);
                          }
			  if (point[h]=="500")
                          {
                                  rangeLo=300., rangeHi=600.;
                                  sg_p0=new RooRealVar("sg_p0", "sg_p0", 480., 520.);
                                  sg_p1=new RooRealVar("sg_p1", "sg_p1", 7., 18.);
                                  sg_p2=new RooRealVar("sg_p2", "sg_p2", 400., 590.);
                                  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
                                  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0., 1.);
                          }
			  if (point[h]=="350")
			  {
				  rangeLo=SR_lo, rangeHi=550.;
				  sg_p0=new RooRealVar("sg_p0", "sg_p0", 320., 380.);
				  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 15.);
				  sg_p2=new RooRealVar("sg_p2", "sg_p2", 330., 420.);
				  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
				  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0., 1.);
			  }
			  if (point[h]=="400")
			  {
				  rangeLo=300., rangeHi=600.;
				  sg_p0=new RooRealVar("sg_p0", "sg_p0", 370., 430.);
				  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
				  sg_p2=new RooRealVar("sg_p2", "sg_p2", 370.,460.);
				  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
				  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0., 1.);
			  }
			  if (point[h]=="450")
			  {
				  rangeLo=300., rangeHi=600.;
				  sg_p0=new RooRealVar("sg_p0", "sg_p0", 420., 480.);
				  sg_p1=new RooRealVar("sg_p1", "sg_p1", 3., 15.);
				  sg_p2=new RooRealVar("sg_p2", "sg_p2", 410., 490.);
				  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 100.);
				  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0., 1.);
			  }
			  if (point[h]=="300")
			  {
				  rangeLo=SR_lo, rangeHi=550.;
				  sg_p0=new RooRealVar("sg_p0", "sg_p0", 290., 320.);
				  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 9.);
				  sg_p2=new RooRealVar("sg_p2", "sg_p2", 250., 360.);
				  sg_p3=new RooRealVar("sg_p3", "sg_p3", 10., 130.);
				  sg_p8=new RooRealVar("sg_p8", "sg_p8", 0., 1.);
			  }


		   //	x=new RooRealVar("x", "m_{X} (GeV)", 250, 900);
		        int binning = (abs(SR_lo-SR_hi)/(rebin)); 	std::cout<<"  binning "<<binning<<std::endl;
   			x->setBins(binning);

		  RooGaussian signalCore("signalCore", "Signal Prediction", *x, *sg_p0, *sg_p1);
		  RooGaussian Cpolyn("Cpolyn", "Combinatoric", *x, *sg_p2, *sg_p3);
		  RooAddPdf signal_("signal_", "signal", RooArgList(signalCore, Cpolyn), *sg_p8);
		  RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), h_mX_SR_signal);
		  signal_.fitTo(signalHistogram, RooFit::Range(SR_lo,SR_hi), RooFit::Save(),RooFit::SumW2Error(kFALSE)); 
		  RooPlot *plot=x->frame();
	          //RooRealVar *signal_p0, *signal_p1, *signal_p2, *signal_p3, *signal_p7, *signal_p8;	
		  // signal_p0 = new RooRealVar("signal_p0", "signal_p0", sg_p0->getVal());
                  //signal_p1 = new RooRealVar("signal_p1", "signal_p1", sg_p1->getVal());
                  //signal_p2 = new RooRealVar("signal_p2", "signal_p2", sg_p2->getVal());
                  //signal_p3 = new RooRealVar("signal_p3", "signal_p3", sg_p3->getVal());
                  //signal_p8 = new RooRealVar("signal_p8", "signal_p8", sg_p8->getVal());
               /*                   
                  RooGaussian g1("g1", "Signal Prediction", *x, *sg_p0, *sg_p1);
                  RooGaussian g2("g2", "Combinatoric", *x, *sg_p2,*sg_p3);
                                  
                  RooAddPdf signal_bkg("signal_bkg", "signal_bkg", RooArgList(g1,g2), *sg_p8);
		  RooRealVar * signal_bkg_norm;
		  if(point[h]=="270") signal_bkg_norm= new RooRealVar("signal_bkg_norm","signal_bkg_norm", 0., -0.27, 0.27,"");	
		  if(point[h]=="300") signal_bkg_norm= new RooRealVar("signal_bkg_norm","signal_bkg_norm", 0., -0.55, 0.55,""); 
 		  if(point[h]=="350") signal_bkg_norm= new RooRealVar("signal_bkg_norm","signal_bkg_norm", 0., -0.24, 0.24,"");
	          if(point[h]=="400") signal_bkg_norm= new RooRealVar("signal_bkg_norm","signal_bkg_norm", 0., -0.09, 0.09,"");
*/
	
		   //sg_p8.setConstant(kTRUE);
		 // sg_p2.setConstant(kTRUE);
		 // sg_p3.setConstant(kTRUE);
		 // sg_p1.setConstant(kTRUE);

         	 /* int toyy = toy;

		  RooRandom::randomGenerator()->SetSeed(toyy);

		  std::cout<< "  n  "<<prodXsec_1[n]*totalLuminosity/nSignal_init<<std::endl;
		  std::cout<<h_mX_SR_signal->GetIntegral()<<"  asd  "<<std::endl;
*/
		  double ntoys_signal = h_mX_SR_signal->Integral(h_mX_SR_signal->FindBin(SR_lo),h_mX_SR_signal->FindBin(SR_hi)-1)*prodXsec_1[n]*totalLuminosity/nSignal_init;
                 /*if(int(ntoys_signal*btagSF)>0) RooDataHist data_sig=*(signal_.generateBinned(*x, int(ntoys_signal*btagSF)));
		 RooDataHist  data_=*(bg.generateBinned(*x, num_toys, RooAbsData::Poisson));

		  if(int(ntoys_signal*btagSF)>0){
			  for (int i=0; i<data_sig->numEntries(); i++){
				  RooArgSet args = *((data_sig)->get(i));
				  float oldw = (data_sig)->store()->weight(i);
				  data_->add(args,oldw);
			  }
		  }
		  data_->SetName("obs");
		  data_->SetNameTitle("obs","obs");

		  TH1 * h_fake = data_->createHistogram("h_fake",*x,RooFit::Binning(133, SR_lo,SR_hi));
		  */

                  int num_toys =h_mMMMMa_3Tag_SR->Integral(h_mMMMMa_3Tag_SR->FindBin(SR_lo), h_mMMMMa_3Tag_SR->FindBin(SR_hi)-1);
		  h_mMMMMa_3Tag_CR24->Scale(num_toys/aC);
		  std::cout<<" warning:   "<<h_mMMMMa_3Tag_CR24->Integral()<< "     "<<h_mMMMMa_3Tag_SR->Integral()<<std::endl;
		  RooDataHist obs("obs", "Data", RooArgList(*x), h_mMMMMa_3Tag_CR24);
                  //RooPlot *plot=x->frame();
                  obs.plotOn(plot);
		  TCanvas *c_data=new TCanvas("c_data", "c_data", 500, 500);
		  std::cout<<point[h]<<" Datacard imax 1 number of channels"<<std::endl;
		  std::cout<<point[h]<<" Datacard jmax * number of backgrounds"<<std::endl;
		  std::cout<<point[h]<<" Datacard kmax * number of systematic uncertainty sources"<<std::endl;
		  std::cout<<point[h]<<" Datacard ----------"<<std::endl;
		  std::cout<<point[h]<<" Datacard shapes signal_ HbbHbb w_data_LowMass"<<point[h]<<".root HbbHbb:signal_"<<std::endl;
		  std::cout<<point[h]<<" Datacard shapes background HbbHbb w_data_LowMass"<<point[h]<<".root HbbHbb:bg"<<std::endl;
		  std::cout<<point[h]<<" Datacard shapes data_obs HbbHbb w_data_LowMass"<<point[h]<<".root HbbHbb:obs"<<std::endl;
		  //std::cout<<point[h]<<" Datacard shapes ttbar HbbHbb w_data_LowMass"<<point[h]<<".root HbbHbb:ttbar"<<std::endl;
		  //std::cout<<point[h]<<" Datacard shapes signal_bkg HbbHbb w_data_LowMass"<<point[h]<<".root HbbHbb:signal_bkg"<<std::endl;
		  std::cout<<point[h]<<" Datacard ----------"<<std::endl;
		  std::cout<<point[h]<<" Datacard ## Observation"<<std::endl;
		  std::cout<<point[h]<<" Datacard bin                     HbbHbb"<<std::endl;
		  std::cout<<point[h]<<" Datacard observation              -1"<<std::endl;
		  std::cout<<point[h]<<" Datacard ----------"<<std::endl;

		  std::cout<<point[h]<<" Datacard ----------"<<std::endl;


		  std::cout<<"Datacard bin             HbbHbb          HbbHbb"<<std::endl;
		  std::cout<<"Datacard process         signal_      background"<<std::endl;
		  std::cout<<"Datacard process         0               1"<<std::endl;
		  std::cout<<"Datacard rate            "<<ntoys_signal*btagSF<<"        "<<num_toys<<std::endl;
		  std::cout<<point[h]<<" Datacard lumi            lnN     1.046            -     "<<std::endl;
		  /*std::cout<<point[h]<<" Datacard JEC             lnN     "<<JEC/100.+1.<<"             -  1.00018     -"<<std::endl;
		    std::cout<<point[h]<<" Datacard JER             lnN     "<<JER/100.+1.<<"              -   1.00843  -"<<std::endl;
		    std::cout<<point[h]<<" Datacard trigSFpT    lnN     "<<trigSFpT/100.+1.<<"              -   1.09135      -"<<std::endl;
		    std::cout<<point[h]<<" Datacard trigSFCSV lnN    "<<trigSFCSV/100.+1.<<"      -    1.02758               -"<<std::endl;
		    std::cout<<point[h]<<" Datacard ttbar_xsec lnN  -       -       1.15                       -"<<std::endl;
		    std::cout<<point[h]<<" Datacard bg_free lnU    -   2.0   -   -"<<std::endl;
		    std::cout<<point[h]<<" Datacard btag    lnN   1.1273  - 1.1273  -"<<std::endl;
		    */
		  std::cout<< "Datacard sg_p0   param   "<<sg_p0->getVal() <<  " "<<sg_p0->getError()<<std::endl;
		  std::cout<< "Datacard sg_p1   param   "<<sg_p1->getVal() <<  " "<<sg_p1->getError()<<std::endl;
		  std::cout<< "Datacard sg_p2   param   "<<sg_p2->getVal() <<  " "<<sg_p2->getError()<<std::endl;
		  std::cout<< "Datacard sg_p3   param   "<<sg_p3->getVal() <<  " "<<sg_p3->getError()<<std::endl;
		  std::cout<< "Datacard sg_p8   param   "<<sg_p8->getVal() <<  " "<<sg_p8->getError()<<std::endl;
		  std::cout<< "Datacard bg_p0   param   "<<bg_p0.getVal() <<  " "<<bg_p0.getError()<<std::endl;
		  std::cout<< "Datacard bg_p1   param   "<<bg_p1.getVal() <<  " "<<bg_p1.getError()<<std::endl;
		  std::cout<< "Datacard bg_p2   param   "<<bg_p2.getVal() <<  " "<<bg_p2.getError()<<std::endl;




		  plot->Draw("");
		  // h_fake->Draw("");	

		  stringstream ss, stoy;//create a stringstream
		  ss << n;//prodXsec_1[n];//add number to the stream
		  stoy<<toy;
		  std::cout<<"mass = "<<point[h]<<std::endl;
		  c_data->Print(("c_data_"+point[h]+"_"+ss.str()+".png").c_str());

		  std::cout<<" === === "<<std::endl;
		  std::cout<<"chi^2/ndof of aC = "<<aC_plot->chiSquare()<<std::endl;
		  std::cout<<" === === "<<std::endl;

		  c_rooFit->SaveAs(("c_compareData_"+tags+"_SR_RooFit_GaussExp.png").c_str());


		  RooWorkspace *w=new RooWorkspace("HbbHbb");
		  //  RooDataHist r_ttbar("ttbar", "ttbar", RooArgList(*x), h_mX_SR_ttbar);
		  // Params par;
		  // RooPlot *plotttbar=fitttbar(r_ttbar, kBlack, par, w);


		  //  std::cout<<"Datacard ttbar_p0  param  "<<par.sg_p0<<"  "<<par.sg_p0_err<<std::endl;
		  //  std::cout<<"Datacard ttbar_p1  param  "<<par.sg_p1<<"  "<<par.sg_p1_err<<std::endl;
		  //  std::cout<<"Datacard ttbar_p2  param  "<<par.sg_p2<<"  "<<par.sg_p2_err<<std::endl;

		  w->import(bg);
		  w->import(signal_); //   w->import(signal_bkg);
		  //  w->import(*signal_bkg_norm);
		  w->import(obs);
		  w->SaveAs(("bias_study/w_data_LowMass"+point[h]+"_"+ss.str()+"_"+stoy.str()+".root").c_str()); 

	  }

  }
}
}





