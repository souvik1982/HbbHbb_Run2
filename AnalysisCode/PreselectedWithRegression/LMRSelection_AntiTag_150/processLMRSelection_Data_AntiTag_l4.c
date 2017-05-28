{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_LMRSelection_chi2_AntiTag_malara_l4.cc++");
  HbbHbb_LMRSelection_chi2_AntiTag_malara_l4("Data","$source_dir_Data","$dest_dir", "tree_total"); 

}
