{
  gSystem->Load("../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton260GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton270GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton300GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton400GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton600GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton800GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton1000GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton1200GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton1600GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton2000GeV");
  HbbHbb_LMRSelection_chi2("Signal", "Graviton3000GeV");
}
