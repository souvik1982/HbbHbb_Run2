{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("Data", "Data_BTagCSV_2015_Skim");
}
