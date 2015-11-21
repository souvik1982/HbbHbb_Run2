setenv dir /eos/uscms/store/user/souvik/HbbHbb_Run2/V14

root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT100to200_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT200to300_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT300to500_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT500to700_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT700to1000_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT1000to1500_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT1500to2000_Skim")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "QCD_HT2000toInf_Skim")'
