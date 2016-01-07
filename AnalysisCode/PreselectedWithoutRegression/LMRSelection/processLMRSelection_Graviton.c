{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection.cc++");
  HbbHbb_LMRSelection("Signal", "Graviton260GeV");
  HbbHbb_LMRSelection("Signal", "Graviton270GeV");
  HbbHbb_LMRSelection("Signal", "Graviton300GeV");
  HbbHbb_LMRSelection("Signal", "Graviton400GeV");
  HbbHbb_LMRSelection("Signal", "Graviton600GeV");
  HbbHbb_LMRSelection("Signal", "Graviton800GeV");
  HbbHbb_LMRSelection("Signal", "Graviton1000GeV");
}
