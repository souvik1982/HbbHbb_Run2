{
  std::vector<std::string> files={
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"
                                 };
                                 
  std::vector<double> mean_gen={400, 500, 650, 750, 900};
  
  gROOT->LoadMacro("../../DisplaymHmX.cc");
  DisplaymHmX(files, mean_gen, 120, 20, 120, 20);
}
