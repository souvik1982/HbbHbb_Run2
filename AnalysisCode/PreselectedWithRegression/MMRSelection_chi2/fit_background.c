{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(150, 1950, 20, // plot range
                                          250, 1850, // fit range
                                          450, 650,
                                          10, 100,
                                          0.01, 2.1,
                                          "h_mX_SB_kinFit", // histogram
                                          "log",
					  "/scratch/malara/WorkingArea/IO_file/input_file/Histograms_MMR_chi2_tree_total.root",
					  "/scratch/malara/WorkingArea/IO_file/output_file/MMR_fit");
}
