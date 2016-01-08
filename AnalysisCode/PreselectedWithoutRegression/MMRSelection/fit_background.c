{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_Kinematic_GaussExp.c");
  BackgroundPrediction_Kinematic_GaussExp(150, 2650, 250, 2550, "log");
}
