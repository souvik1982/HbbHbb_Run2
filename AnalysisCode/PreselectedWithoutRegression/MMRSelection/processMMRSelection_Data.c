{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("Data", "BTagCSV_2015_Skim");
}
