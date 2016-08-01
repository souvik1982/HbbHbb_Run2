setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V23/

root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV0","ttbar-fix-v23.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV1","ttbar-fix-v23.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV2","ttbar-fix-v23.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV3","ttbar-fix-v23.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV4","ttbar-fix-v23.weights.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV5","ttbar-fix-v23.weights.xml")'
