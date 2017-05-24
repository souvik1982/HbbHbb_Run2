{
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/HZGRooPdfs_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/Falling_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/Falling_1_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/NovoErf_cxx.so");
    gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_Split_malara.c");
    
    BackgroundPrediction_Kinematic_Split_malara(350, 1300 ,10, // plot range
                                               350, 1300,    // fit range
                                               400, 600,    // range of crystalBall mean
                                               10, 200,       // range of crystalBall width
                                               0.01, 5.1,   // range of crystalBall exponent
                                               0.01, 5.1, // range of crystalBall switch
                                               "h_mX_SB_kinFit", // histogram
                                               "lin",
                                               "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/Histograms_MMR_chi2_tree_total.root",
                                               "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit");
}



