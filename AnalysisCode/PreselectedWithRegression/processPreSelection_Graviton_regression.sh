setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V24/

export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export source_dir="$TEST_PATH/input_file"
export dest_dir="$TEST_PATH/output_file"

#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'


#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$source_dir", "$dest_dir", "tree_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'



