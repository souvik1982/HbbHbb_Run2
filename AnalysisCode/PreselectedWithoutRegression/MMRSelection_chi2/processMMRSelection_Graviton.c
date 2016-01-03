{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton260GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton270GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton300GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton400GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton600GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton800GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton1000GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton1200GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton1600GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton2000GeV");
  HbbHbb_MMRSelection_chi2("Signal", "Graviton3000GeV");
}
