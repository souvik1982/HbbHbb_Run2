{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("Signal", "Graviton260GeV");
  HbbHbb_MMRSelection("Signal", "Graviton270GeV");
  HbbHbb_MMRSelection("Signal", "Graviton300GeV");
  HbbHbb_MMRSelection("Signal", "Graviton400GeV");
  HbbHbb_MMRSelection("Signal", "Graviton600GeV");
  HbbHbb_MMRSelection("Signal", "Graviton800GeV");
  HbbHbb_MMRSelection("Signal", "Graviton1000GeV");
  HbbHbb_MMRSelection("Signal", "Graviton1200GeV");
  HbbHbb_MMRSelection("Signal", "Graviton1600GeV");
  HbbHbb_MMRSelection("Signal", "Graviton2000GeV");
  HbbHbb_MMRSelection("Signal", "Graviton3000GeV");
}
