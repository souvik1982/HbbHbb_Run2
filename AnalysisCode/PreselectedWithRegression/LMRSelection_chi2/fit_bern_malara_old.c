{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/HZGRooPdfs_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_Bern_malara.c");

       BackgroundPrediction_Kinematic_Bern_malara(252, 555,3, // plot range
                                          252, 450,    // fit range
					  260, 280,    // range of gaussExp mean
                                          3., 50,     // range of gaussExp width
                                          0.01, 3.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin",
                                "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/Histograms_LMR_chi2_tree_total.root",
                                          "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit");
}
