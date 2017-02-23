{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
  HbbHbb_MMRSelection_chi2("Data","$source_dir","$dest_dir", "tree_total"); 

}
