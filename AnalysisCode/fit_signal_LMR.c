{
  gSystem->Load("PDFs/ExpGaussExp_cxx.so");
  gROOT->LoadMacro("Display_SignalFits_LMR.cc");
  Display_SignalFits_LMR("PreselectedWithoutRegression",
                     "LMRSelection_chi2",
                     "Histograms_GluGluToBulkGravitonToHHTo4B_M-");
}
