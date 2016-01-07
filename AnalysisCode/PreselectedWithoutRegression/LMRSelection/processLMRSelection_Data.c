{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection.cc++");
  HbbHbb_LMRSelection("Data", "Data_BTagCSV_2015_Skim");
}
