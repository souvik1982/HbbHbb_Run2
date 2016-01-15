{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(150, 2650, // plot range
                                          250, 2550, // fit range
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
