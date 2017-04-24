{
   gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/HZGRooPdfs_cxx.so");
   gSystem->Load("../../PDFs/GaussExp_cxx.so");
   gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_Bern_malara.c");

       BackgroundPrediction_Kinematic_Bern_malara(350, 1200 ,3, // plot range
                                          400, 1200,    // fit range
					  400, 550,    // range of gaussExp mean
                                          50, 120,     // range of gaussExp width
                                          0.01, 2.1,   // range of gaussExp exponent
                                          "h_mX_SB_kinFit", // histogram
                                          "lin",
                                "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/Histograms_MMR_chi2_tree_total.root",
                                          "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit");
}
