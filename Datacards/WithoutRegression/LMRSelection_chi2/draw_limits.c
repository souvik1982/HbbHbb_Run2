{
  std::vector<double> masses={260, 270, 300, 400, 600};
  gROOT->LoadMacro("../../DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 10, 1e5);
}
