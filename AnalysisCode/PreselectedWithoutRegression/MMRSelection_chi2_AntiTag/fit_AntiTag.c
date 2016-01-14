{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(250, 1800, 350, 1600, "h_mX_SB_kinFit", "h_mX_SR_kinFit", "log");
}
