{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_AntiTag.cc++");
  HbbHbb_LMRSelection_AntiTag("Data", "Data_BTagCSV_2015_Skim");
}
