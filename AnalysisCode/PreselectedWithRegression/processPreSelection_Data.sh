#setenv dir /eos/uscms/store/user/souvik/HbbHbb_Run2/V15

#root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Data_BTagCSV_2015C_Skim", "TMVARegression_BDTG.weights.xml")'
#root -l -b -q 'HbbHbb_PreSelection.cc++("$dir", "Data_BTagCSV_2015D_Skim", "TMVARegression_BDTG.weights.xml")'

#hadd -f PreSelected_Data_BTagCSV_2015_Skim.root PreSelected_Data_BTagCSV_2015C_Skim.root PreSelected_Data_BTagCSV_2015D_Skim.root
#hadd -f Histograms_Data_BTagCSV_2015_Skim.root Histograms_Data_BTagCSV_2015D_Skim.root Histograms_Data_BTagCSV_2015D_Skim.root 

setenv dir /eos/uscms/store/user/cvernier/

root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV_2015_Skim", "TMVARegression_BDTG.weights.xml")'
