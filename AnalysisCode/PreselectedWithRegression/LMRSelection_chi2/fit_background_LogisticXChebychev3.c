{
  gSystem->Load("../../PDFs/LogisticXChebychev3_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_LogisticXChebychev3.cc");
  BackgroundPrediction_Kinematic_LogisticXChebychev3("Histogram_BTagCSV.root",
                                          251, 501, 5, // plot range
                                          251, 502,    // fit range
                                          241, 281,    // range of logistic center
                                          0.01, 1.,    // slope of logistic
                                          -.1, 0.9,   // p0
                                          -.1, 0.9,   // p1
                                          -.1, 0.9,   // p2
                                          -.1, 0.9,   // p3
                                          "h_mX_SB_kinFit", // histogram
                                          "lin");
}
