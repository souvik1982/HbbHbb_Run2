{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2_AntiTag.cc++");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "Data_BTagCSV_2015_Skim");
}
