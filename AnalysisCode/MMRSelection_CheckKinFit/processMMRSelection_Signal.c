{
  gSystem->Load("../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../HbbHbb_MMRSelection_CheckKinFit.cc++");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion260GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion270GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion300GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion350GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion400GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion450GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion500GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion550GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion600GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion650GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion700GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion800GeV");
  HbbHbb_MMRSelection_CheckKinFit("Signal", "Radion900GeV");
}
