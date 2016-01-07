{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection.cc++");
  HbbHbb_LMRSelection("ttbar", "TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim");
}
