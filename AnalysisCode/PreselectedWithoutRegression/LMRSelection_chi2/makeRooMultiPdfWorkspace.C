#include "TFile.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TLatex.h"
#include "TMacro.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TArrow.h"
#include "TKey.h"
#include "GaussExp.cc"
//#include "HZGRooPdfs.cxx"

//#include "/uscms_data/d3/cvernier/DiH_13TeV/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
//#include "HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
void makeRooMultiPdfWorkspace(){

   // Load the combine Library 
   gSystem->Load("libHiggsAnalysisCombinedLimit.so");

   // Open the dummy H->gg workspace 
   TFile *f_hgg = TFile::Open("w_background_Bern.root");
   RooWorkspace *w_hgg = (RooWorkspace*)f_hgg->Get("HbbHbb");
   // The observable (CMS_hgg_mass in the workspace)
   RooRealVar *mass =  w_hgg->var("x");

   // Get three of the functions inside, exponential, linear polynomial, power law
   RooAbsPdf *pdf_exp = w_hgg->pdf("bg_exp");
   RooAbsPdf *pdf_pol = w_hgg->pdf("bg");


   // Fit the functions to the data to set the "prefit" state (note this can and should be redone with combine when doing 
   // bias studies as one typically throws toys from the "best-fit"
   RooAbsData *data = w_hgg->data("data_obs");
   pdf_exp->fitTo(*data);  // index 0
   pdf_pol->fitTo(*data);   // index 2

   // Make a plot (data is a toy dataset)
   RooPlot *plot = mass->frame();   data->plotOn(plot);
   pdf_exp->plotOn(plot,RooFit::LineColor(kBlue));
   pdf_pol->plotOn(plot,RooFit::LineColor(kRed));
   plot->SetTitle("PDF fits to toy data");
   plot->Draw();

   // Make a RooCategory object. This will control which of the pdfs is "active"
   RooCategory cat("pdf_index","Index of Pdf which is active");

   // Make a RooMultiPdf object. The order of the pdfs will be the order of their index, ie for below 
   // 0 == exponential
   // 1 == linear function
   // 2 == powerlaw
   RooArgList mypdfs;
   mypdfs.add(*pdf_exp);
   mypdfs.add(*pdf_pol);
   
   RooMultiPdf multipdf("roomultipdf","All Pdfs",cat,mypdfs);
   
   // As usual make an extended term for the background with _norm for freely floating yield
   RooRealVar norm("roomultipdf_norm","Number of background events",0,10000);
   
   // Save to a new workspace
   TFile *fout = new TFile("background_pdfs.root","RECREATE");
   RooWorkspace wout("backgrounds","backgrounds");
   wout.import(cat);
   wout.import(norm);
   wout.import(multipdf);
   wout.Print();
   wout.Write();

}
