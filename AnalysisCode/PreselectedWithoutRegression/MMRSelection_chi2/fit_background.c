{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(150, 1950, 20, // plot range
                                          250, 1850, // fit range
                                          450, 650,
                                          10, 100,
                                          0.01, 2.1,
                                          "h_mX_SB_kinFit", // histogram
                                          "log");
}
