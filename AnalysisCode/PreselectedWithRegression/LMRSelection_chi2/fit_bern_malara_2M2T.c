{
//   gSystem->Load("../../PDFs/GaussExpPol_cxx.so");
   gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/HZGRooPdfs_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
   gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_Bern_malara_2M2T.c");

       BackgroundPrediction_Kinematic_Bern_malara_2M2T(252, 455,3, // plot range
                                          252, 455,    // fit range
					  260, 280,    // range of gaussExp mean
                                          3., 50,     // range of gaussExp width
                                          0.01, 3.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin",
                                "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/LMR/Histograms_LMR_chi2_tree_total.root",
                                          "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/LMR");
}
