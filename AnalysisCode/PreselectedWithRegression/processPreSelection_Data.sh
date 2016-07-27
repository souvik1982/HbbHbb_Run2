setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V22reHLT/

root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV0","ttbar-fall15-TargetGenOverPt.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV1","ttbar-fall15-TargetGenOverPt.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV2","ttbar-fall15-TargetGenOverPt.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV3","ttbar-fall15-TargetGenOverPt.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV4","ttbar-fall15-TargetGenOverPt.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV5","ttbar-fall15-TargetGenOverPt.xml")'
