{
  std::vector<std::string> files={
                                   "Histograms_Graviton300GeV.root",
                                   "Histograms_Graviton400GeV.root",
                                   "Histograms_Graviton600GeV.root",
                                   "Histograms_Graviton800GeV.root",
                                   "Histograms_Graviton1000GeV.root",
                                   "Histograms_Graviton1200GeV.root"
                                 };
  gROOT->LoadMacro("../../DisplaymHmX.cc");
  DisplaymHmX(files, 150, 20, 125, 20);
}
