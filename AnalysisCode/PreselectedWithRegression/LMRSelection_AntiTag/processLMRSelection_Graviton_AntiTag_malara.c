{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_LMRSelection_chi2_AntiTag_malara.cc++");
  
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph");
  //HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph");
  
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2_AntiTag_malara("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph");
}
