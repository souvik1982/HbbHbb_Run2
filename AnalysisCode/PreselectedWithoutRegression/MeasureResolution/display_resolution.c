{
  std::vector<std::string> files={
                                   "ResolutionHistograms_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root",
                                   "ResolutionHistograms_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root",
                                   "ResolutionHistograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root",
                                   "ResolutionHistograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root",
                                   "ResolutionHistograms_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"
                                 };
  gROOT->LoadMacro("../../DisplayResolutionBias.cc");
  DisplayResolutionBias(files);
}
