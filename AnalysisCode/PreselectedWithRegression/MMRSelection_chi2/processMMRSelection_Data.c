{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
  /* HbbHbb_MMRSelection_chi2("Data", "RunBv2", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunBv3", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunC", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunD", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunE", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunF", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunG", 300, true);
 */ //HbbHbb_MMRSelection_chi2("Data", "RunHv1", 300, true);
  HbbHbb_MMRSelection_chi2("Data", "RunHv2", 300, true);
  //HbbHbb_MMRSelection_chi2("Data", "RunHv3", 300, true);
}
