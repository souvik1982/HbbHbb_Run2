{ 
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("QCD", "QCD_HT100to200_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT200to300_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT300to500_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT500to700_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT700to1000_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT1000to1500_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT1500to2000_Skim");
  HbbHbb_MMRSelection("QCD", "QCD_HT2000toInf_Skim");
}
