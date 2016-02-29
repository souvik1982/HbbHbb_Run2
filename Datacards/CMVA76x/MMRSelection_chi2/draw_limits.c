{
 std::vector<double> masses={350, 450, 500, 550, 650, 700, 800, 900, 1000, 1200};
  gROOT->LoadMacro("../../DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 10, 1e5);
}
