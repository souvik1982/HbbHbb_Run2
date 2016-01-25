{
  gSystem->Load("PDFs/ExpGaussExp_cxx.so");
  gROOT->LoadMacro("Display_SignalFits.cc");
  Display_SignalFits("PreselectedWithoutRegression",
                     "MMRSelection_chi2",
                     "Histograms_Graviton");
}
