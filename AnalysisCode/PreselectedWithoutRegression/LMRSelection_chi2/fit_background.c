{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(250, 550, 5, // plot range
                                          250, 550,    // fit range
                                          250., 350.,    // range of gaussExp mean
                                          1., 50.,     // range of gaussExp width
                                          0.01, 5.1,   // range of gaussExp exponent
                                          "h_mX_SR_kinFit", // histogram
                                          "lin");
}
