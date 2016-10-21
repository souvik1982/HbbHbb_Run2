setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V23/

#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV0","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV1","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV2","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV3","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV4","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
##root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV5","grav_all_upTo1400.xml")'
