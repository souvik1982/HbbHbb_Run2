{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(150, 850, 3, // plot range
                                          250, 750,    // fit range
                                          250, 350,    // range of gaussExp mean
                                          1, 50,     // range of gaussExp width
                                          0.01, 2.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
