{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(200, 1000, 3, // range of plot, binning
                                        250, 900, // range of fit
                                        250, 550,  // range of gaussExp mean
                                        50, 100,   // range of gaussExp width
                                        0.01, 5.1, // range of gaussExp exponent
                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
