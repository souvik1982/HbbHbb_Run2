{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_CrystalBall_malara.cc");
  BackgroundPrediction_Kinematic_CrystalBall_malara(252, 455,3, // plot range
                                                    252,455,    // fit range
                                                    240, 280,    // range of crystalBall mean
                                                    3, 30,       // range of crystalBall width
                                                    0.01, 5.1,   // range of crystalBall exponent
                                                    0.01, 5.1, // range of crystalBall switch
					            250, 350,    // range of gaussExp mean
                                                    3., 50,     // range of gaussExp width
                                                    0.01, 3.1,   // range of gaussExp exponent
                                             "h_mX_SB_kinFit", // histogram
                                             "lin", "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root",
                                             "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit");
}
