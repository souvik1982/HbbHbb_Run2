{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_LMRSelection_chi2_malara.cc++");
  HbbHbb_LMRSelection_chi2_malara("Data","$source_dir_Data","$dest_dir", "tree_total",300, true); 

}
