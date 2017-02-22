{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_GaussExp.cc");
  BackgroundPrediction_Kinematic_GaussExp(250, 750,5, // plot range
                                          250, 750,    // fit range
                                          250, 350,    // range of gaussExp mean
                                          1, 50,     // range of gaussExp width
                                          0.01, 5.1,   // range of gaussExp exponent
                                          "h_mX_SR_kinFit", // histogram
                                          "lin",
					  "/scratch/malara/WorkingArea/IO_file/input_file/Histograms_MMR_chi2_tree_total.root",
					  "/scratch/malara/WorkingArea/IO_file/output_file/LMR_fit");
}
