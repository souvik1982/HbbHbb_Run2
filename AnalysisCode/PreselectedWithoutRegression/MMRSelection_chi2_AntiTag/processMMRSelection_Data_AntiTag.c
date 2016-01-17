{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2_AntiTag.cc++");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "Data_BTagCSV_2015_Skim");
}
