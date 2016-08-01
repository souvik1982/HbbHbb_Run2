setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V23

#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV0")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV1")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV2")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV3")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV4")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV5")'
