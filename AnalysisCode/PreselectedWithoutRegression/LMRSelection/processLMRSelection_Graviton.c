{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-1000_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-1200_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-1600_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-2000_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("Signal", "GluGluToBulkGravitonToHHTo4B_M-3000_narrow_13TeV-madgraph");
}
