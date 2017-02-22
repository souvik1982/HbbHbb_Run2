 { gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so"); 
gROOT->LoadMacro("Display_SignalFits_LMR.cc"); 
Display_SignalFits_LMR("/scratch/malara/WorkingArea/IO_file/output_file/Data/PreselectedWithWithRegression","reg","LMRSelection_chi2","/scratch/malara/WorkingArea/IO_file/output_file/LMR_fit","Histograms_LMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-",300,"true"); }
