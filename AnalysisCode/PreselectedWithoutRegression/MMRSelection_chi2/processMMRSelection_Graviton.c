{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
 /* HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph");
  //HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph");
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph");
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph");*/
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph", 400);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph", 450);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph", 500);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph", 550);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph", 600);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph", 650);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph", 700);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph", 750);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph", 800);
  HbbHbb_MMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph", 900);
 /* HbbHbb_MMRSelection_chi2("Signal", "BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph");
  HbbHbb_MMRSelection_chi2("Signal", "BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph");
  HbbHbb_MMRSelection_chi2("Signal", "BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph");*/
}
