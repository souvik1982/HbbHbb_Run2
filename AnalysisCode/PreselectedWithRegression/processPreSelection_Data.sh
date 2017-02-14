setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V24/

export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export source_dir="$TEST_PATH/input_file"
export dest_dir="$TEST_PATH/output_file"

root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_VHBBHeppyV25-BTagCSV-VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2-170130_123206-0000","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'







#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV0","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV1","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV2","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV3","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV4","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV5","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV6","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV6_1","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV8","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV7","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV9","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV11","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "BTagCSV10","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'

