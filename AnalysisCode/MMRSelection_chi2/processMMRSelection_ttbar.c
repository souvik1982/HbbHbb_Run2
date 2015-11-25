{
  gSystem->Load("../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../HbbHbb_MMRSelection_chi2.cc++");
  HbbHbb_MMRSelection_chi2("Data", "TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Skim");
}
