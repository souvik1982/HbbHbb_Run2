{
  std::vector<double> masses={400,450,500,550,650,700,750,800,900,1000,1200};
  gROOT->LoadMacro("../../DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 10, 1e5);
}
