{
//   gSystem->Load("../../PDFs/GaussExpPol_cxx.so");
  gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
   gSystem->Load("HZGRooPdfs_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_Bern.c");
  BackgroundPrediction_Kinematic_Bern(350, 1400, 5, // plot range
                                          350, 1400, // fit range
					  400, 600,    // range of crystalBall mean
                                             10, 200,       // range of crystalBall width
                                             0.01, 5.1,   // range of crystalBall exponent
                                             0.01, 5.1, // range of crystalBall switch
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
