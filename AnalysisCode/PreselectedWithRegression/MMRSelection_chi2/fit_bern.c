{
//   gSystem->Load("../../PDFs/GaussExpPol_cxx.so");
   gSystem->Load("HZGRooPdfs_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_Bern.c");
  BackgroundPrediction_Kinematic_Bern(350, 1400, 10, // plot range
                                          350, 1400, // fit range
                                          450, 550,
                                          50, 120,
                                          0.01, 2.1,
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
