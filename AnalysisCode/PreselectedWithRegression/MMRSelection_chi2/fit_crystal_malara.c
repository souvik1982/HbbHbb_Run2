{
  gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_CrystalBall_malara.cc");
  BackgroundPrediction_Kinematic_CrystalBall_malara("/scratch/malara/WorkingArea/IO_file/output_file/Data/PreselectedWithWithRegression/MMRSelection_chi2/Histograms_MMR_chi2_tree_total.root",
                                             350, 1200, 10, // plot range
                                             350, 1200,    // fit range
                                             400, 600,    // range of crystalBall mean
                                             10, 200,       // range of crystalBall width
                                             0.01, 5.1,   // range of crystalBall exponent
                                             0.01, 5.1, // range of crystalBall switch
					      450, 550,
                                          50, 120,
                                          0.01, 2.1,
                                             "h_mX_SB_kinFit", // histogram
                                             "lin","/scratch/malara/WorkingArea/IO_file/output_file/MMR_fit");
}
