{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph");
 // HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-1000_narrow_13TeV-madgraph");
}
