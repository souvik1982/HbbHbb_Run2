{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/../../HbbHbb_LMRSelection_chi2_malara.cc++");
  HbbHbb_MMRSelection_chi2_malara("Data","$source_dir_Data","$dest_dir", "tree_total",300, true); 

}
