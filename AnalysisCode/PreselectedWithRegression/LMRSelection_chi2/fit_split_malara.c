{
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/GaussExp_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/HZGRooPdfs_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/Falling_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/Falling_1_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/NovoErf_cxx.so");
    gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/LogisticXChebychev3_cxx.so");
    gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_Split_malara.c");
    //gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/BackgroundPrediction_Kinematic_Split_malara_old.c");
    
    BackgroundPrediction_Kinematic_Split_malara(252, 330, 3, // plot range
                                               252, 330,    // fit range
                                               240, 280,    // range of crystalBall mean
                                               3, 30,       // range of crystalBall width
                                               0.01, 5.1,   // range of crystalBall exponent
                                               0.01, 5.1, // range of crystalBall switch
                                               "h_mX_SB_kinFit", // histogram
                                               "lin",
                                               "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_test/Histograms_LMR_chi2_tree_total.root",
                                               "/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_test/fit");
}



