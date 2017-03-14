{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_GaussExp_malara_2L2T.cc");
  BackgroundPrediction_Kinematic_GaussExp_malara_2L2T(252, 455,3, // plot range
                                          252,455,    // fit range
                                          260, 300,    // range of gaussExp mean
                                          9, 40,     // range of gaussExp width
                                          0.05, 3.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "log",
					  "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/MMR/Histograms_MMR_chi2_tree_total.root",
					  "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/MMR/fit");
}
