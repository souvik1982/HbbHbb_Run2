{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("Signal", "Graviton260GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton270GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton300GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton400GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton600GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton800GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton1000GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton1200GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton1600GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton2000GeV_regressed");
  HbbHbb_MMRSelection("Signal", "Graviton3000GeV_regressed");
}
