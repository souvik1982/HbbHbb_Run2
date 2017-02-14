{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Data","$source_dir","$dest_dir", "tree_VHBBHeppyV25-BTagCSV-VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2-170130_123206-0000");

}
