{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_GaussExp_malara.cc");
  BackgroundPrediction_Kinematic_GaussExp_malara(150, 1950, 20, // plot range
                                          450, 1400, // fit range
                                          450, 650,
                                          10, 100,
                                          0.01, 2.1,
                                          "h_mX_SB_kinFit", // histogram
                                          "log",
					  "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/Histograms_MMR_chi2_tree_total.root",
					  "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit");
}
