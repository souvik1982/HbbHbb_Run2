{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MeasureResolutionBias.cc++");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph");
  HbbHbb_MeasureResolutionBias( "$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph");

}


