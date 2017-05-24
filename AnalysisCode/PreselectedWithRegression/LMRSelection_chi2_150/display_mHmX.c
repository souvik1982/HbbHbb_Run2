{
  std::vector<std::string> files={
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"
                                 };
                                 
  std::vector<double> mean_gen={260,300,350,400,450};
  
  gROOT->LoadMacro("../../DisplaymHmX.cc");
  DisplaymHmX(files, mean_gen, 120, 25, 120, 25);
}
