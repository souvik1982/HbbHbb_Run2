setenv dir /eos/uscms/store/user/souvik/HbbHbb_Run2/V14

root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton260GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton270GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton300GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton400GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton600GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton800GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton1000GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton1200GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton1600GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton2000GeV")'
root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Graviton3000GeV")'
