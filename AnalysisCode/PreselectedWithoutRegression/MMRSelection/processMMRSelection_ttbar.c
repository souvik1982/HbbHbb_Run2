{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("ttbar", "TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim");
}
