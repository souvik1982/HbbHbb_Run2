{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_LMRSelection_chi2_malara_overlap.cc++");
  HbbHbb_LMRSelection_chi2_malara_overlap("Data","$source_dir_Data","$dest_dir", "tree_total",300, true); 

}
