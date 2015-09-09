{
  gSystem->Load("../libPhysicsToolsKinFitter.dylib");
  gROOT->LoadMacro("../HbbHbb_MMRSelection.cc++");
  HbbHbb_MMRSelection("Signal", "Radion260GeV");
  HbbHbb_MMRSelection("Signal", "Radion270GeV");
  HbbHbb_MMRSelection("Signal", "Radion300GeV");
  HbbHbb_MMRSelection("Signal", "Radion350GeV");
  HbbHbb_MMRSelection("Signal", "Radion400GeV");
  HbbHbb_MMRSelection("Signal", "Radion450GeV");
  HbbHbb_MMRSelection("Signal", "Radion500GeV");
  HbbHbb_MMRSelection("Signal", "Radion550GeV");
  HbbHbb_MMRSelection("Signal", "Radion600GeV");
  HbbHbb_MMRSelection("Signal", "Radion650GeV");
  HbbHbb_MMRSelection("Signal", "Radion700GeV");
  HbbHbb_MMRSelection("Signal", "Radion800GeV");
  HbbHbb_MMRSelection("Signal", "Radion900GeV");
}
