{
  gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_CrystalBall.cc");
  BackgroundPrediction_Kinematic_CrystalBall("Histogram_BTagCSV.root",
                                             350, 1200, 20, // plot range
                                             350, 1200,    // fit range
                                             400, 600,    // range of crystalBall mean
                                             10, 200,       // range of crystalBall width
                                             0.01, 5.1,   // range of crystalBall exponent
                                             0.01, 5.1, // range of crystalBall switch
                                             "h_mX_SB_kinFit", // histogram
                                             "lin");
}
