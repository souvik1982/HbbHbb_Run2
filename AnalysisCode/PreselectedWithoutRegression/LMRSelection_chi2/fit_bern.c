{
//   gSystem->Load("../../PDFs/GaussExpPol_cxx.so");
   gSystem->Load("HZGRooPdfs_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_Bern.c");
  BackgroundPrediction_Kinematic_Bern(251, 700,10, // plot range
                                          251, 700,    // fit range
					  250, 350,    // range of gaussExp mean
                                          3., 50,     // range of gaussExp width
                                          0.01, 3.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
