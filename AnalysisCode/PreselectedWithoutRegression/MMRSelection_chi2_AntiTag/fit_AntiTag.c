{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(300, 2000, 20, // range of plot
                                        400, 1800,     // range of fit
                                        400, 650,      // range of gaussExp mean
                                        50, 150,       // range of gaussExp width
                                        0.01, 1.1,     // range of gaussExp exponent
                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
