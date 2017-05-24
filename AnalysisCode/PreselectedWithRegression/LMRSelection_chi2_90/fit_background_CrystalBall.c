{
  gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_CrystalBall.cc");
  BackgroundPrediction_Kinematic_CrystalBall("Histogram_BTagCSV.root",
                                          251, 501, 5, // plot range
                                          251, 501,    // fit range
                                          240, 300,    // range of crystalBall mean
                                          3, 50,       // range of crystalBall width
                                          0.01, 5.1,   // range of crystalBall exponent
                                          0.01, 5.1, // range of crystalBall switch
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
