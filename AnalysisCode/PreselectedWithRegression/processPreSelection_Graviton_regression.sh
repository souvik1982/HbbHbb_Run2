setenv dir /eos/uscms/store/user/souvik/HbbHbb_Run2/V14

root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton260GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton270GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton300GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton400GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton600GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton800GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton1000GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton1200GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton1600GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton2000GeV", "TMVARegression_BDTG.weights.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "Graviton3000GeV", "TMVARegression_BDTG.weights.xml")'
