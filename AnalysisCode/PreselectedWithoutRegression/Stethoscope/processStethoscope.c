{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_Selection_Stethoscope.cc++");
  
  // Run the selection
  for (double mean_H1_mass=50.; mean_H1_mass<200.; mean_H1_mass+=15)
  {
    for (double mean_H2_mass=50.; mean_H2_mass<200; mean_H2_mass+=15)
    {
      HbbHbb_Selection_Stethoscope("Data_BTagCSV_2015_Skim", mean_H1_mass, 15, mean_H2_mass, 15);
    }
  }
  
  // Fit mX in SB and SR
  
  // Illustrate on mH1 vs mH2
  
  // Plot in HTML dashboard
  
}
