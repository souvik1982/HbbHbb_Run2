{
  std::vector<double> masses={400, 600, 800, 1000, 1200};
  gROOT->LoadMacro("../../DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 10, 1e5);
}
