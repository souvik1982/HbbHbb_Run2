{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(252, 455,3, // plot range
                                          252,455,    // fit range
                                          260, 300,    // range of gaussExp mean
                                          9, 40,     // range of gaussExp width
                                          0.05, 3.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
