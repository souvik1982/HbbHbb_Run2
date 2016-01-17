{
  std::vector<std::string> files={
                                   "Histograms_Graviton300GeV.root",
                                   "Histograms_Graviton400GeV.root",
                                   "Histograms_Graviton600GeV.root",
                                   "Histograms_Graviton800GeV.root"
                                 };
  gROOT->LoadMacro("../../DisplaymHmX.cc");
  DisplaymHmX(files);
}
