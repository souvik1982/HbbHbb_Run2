 { gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so"); gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so");
gROOT->LoadMacro("Display_SignalFits_malara.cc"); 
Display_SignalFits_malara("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression","reg","../../MMR_test","/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR_test/fit","Histograms_MMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-",1000,"true"); }
