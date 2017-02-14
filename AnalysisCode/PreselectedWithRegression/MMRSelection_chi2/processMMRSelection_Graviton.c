{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph", 1600, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph", 2500, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph", 3000, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph", 4000, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph", 4500, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph", 300, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph", 400, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph", 650, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph", 750, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph", 800, true );
  HbbHbb_MMRSelection_chi2("Signal","$source_dir","$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph", 900, true );
}
