{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_CrystalBall_malara.cc");
  BackgroundPrediction_Kinematic_CrystalBall_malara(350, 1200, 10, // plot range
                                                    350, 1200,    // fit range
                                                    400, 600,    // range of crystalBall mean
                                                    10, 200,       // range of crystalBall width
                                                    0.01, 5.1,   // range of crystalBall exponent
                                                    0.01, 5.1, // range of crystalBall switch
					            450, 550,    // range of gaussExp mean
                                                    50, 120,     // range of gaussExp width
                                                    0.01, 2.1,   // range of gaussExp exponent
                                             "h_mX_SB_kinFit", // histogram
                                             "lin", "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/Histograms_MMR_chi2_tree_total.root",
                                             "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit");
}
