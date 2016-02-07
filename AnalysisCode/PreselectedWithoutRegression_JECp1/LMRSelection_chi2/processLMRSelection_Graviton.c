{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton260GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton270GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton300GeV");
//  HbbHbb_LMRSelection_chi2("Signal", "Graviton350GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton400GeV");
//  HbbHbb_LMRSelection_chi2("Signal", "Graviton450GeV");
 // HbbHbb_LMRSelection_chi2("Signal", "Graviton500GeV");
 // HbbHbb_LMRSelection_chi2("Signal", "Graviton550GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton600GeV");
 // HbbHbb_LMRSelection_chi2("Signal", "Graviton650GeV");
  //HbbHbb_LMRSelection_chi2("Signal", "Graviton1000GeV");
}
