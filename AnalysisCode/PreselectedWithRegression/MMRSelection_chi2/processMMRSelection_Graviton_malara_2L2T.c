{
  gSystem->Load("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_MMRSelection_chi2_malara_2L2T.cc++");
  
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph", 1000, true );
  //HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph", 1600, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph", 2000, true );
  //HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph", 2500, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph", 3000, true );
  //HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph", 4000, true );
  //HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph", 4500, true );
  
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph", 260, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph", 270, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph", 300, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph", 350, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph", 400, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph", 450, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph", 500, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph", 550, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph", 600, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph", 650, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph", 750, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph", 800, true );
  HbbHbb_MMRSelection_chi2_malara_2L2T("Signal","$source_dir_MC","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph", 900, true );
}
