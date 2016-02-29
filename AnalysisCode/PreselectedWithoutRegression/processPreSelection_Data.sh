setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/H21b/

root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV_Skim")'
