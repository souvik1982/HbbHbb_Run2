{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_MMRSelection_chi2_malara_CMVA.cc++");
  HbbHbb_MMRSelection_chi2_malara_CMVA("Data","$source_dir_Data","$dest_dir", "tree_total",300, true); 

}
