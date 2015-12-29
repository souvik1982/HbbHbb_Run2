{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Data", "TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8");
}
