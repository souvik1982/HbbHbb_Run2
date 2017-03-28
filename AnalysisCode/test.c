 { gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so"); gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so");
gROOT->LoadMacro("Display_SignalFits_LMR_malara.cc"); 
Display_SignalFits_LMR_malara("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression","reg","../../LMR","/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit","Histograms_LMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-",550,"true"); }
