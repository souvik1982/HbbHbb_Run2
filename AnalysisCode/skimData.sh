export SOURCE_DIR="/gpfs/ddn/srm/cms/store/user"
export source_dir_B_v2="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016B-23Sep2016-v2/170130_122257/0000"
export source_dir_C_v1="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016C-23Sep2016-v1/170130_122516/0000"
export source_dir_E_v1="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016E-23Sep2016-v1/170130_122704/0000"
export source_dir_F_v1="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016F-23Sep2016-v1/170130_122818/0000"
export source_dir_H_v1="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v1/170130_123051/0000"
export source_dir_H_v2="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2/170130_123206/0000"
export source_dir_H_v2_1="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2/170130_123206/0001"
export source_dir_H_v2_2="$SOURCE_DIR/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2/170130_123206/0002"

export source_dir_B_v3="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016B-23Sep2016-v3/170206_165040/0000"
export source_dir_B_v3_1="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016B-23Sep2016-v3/170206_165040/0001"
export source_dir_D_v1="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016D-23Sep2016-v1/170206_164949/0000"
export source_dir_D_v1_1="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016D-23Sep2016-v1/170206_164949/0001"
export source_dir_G_v1="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016G-23Sep2016-v1/170206_164902/0000"
export source_dir_G_v1_1="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016G-23Sep2016-v1/170206_164902/0001"
export source_dir_H_v3="$SOURCE_DIR/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v3/170206_164802/0000"

export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export dest_dir="$TEST_PATH/output_file"

##root -l -b -q 'Vskim.cc++("$source_dir_B_v2","$dest_dir", "tree_",1,222)'
root -l -b -q 'Vskim.cc++("$source_dir_C_v1","$dest_dir", "tree_",1,627)'
#root -l -b -q 'Vskim.cc++("$source_dir_E_v1","$dest_dir", "tree_",1,907)'
#root -l -b -q 'Vskim.cc++("$source_dir_F_v1","$dest_dir", "tree_",1,653)'
##root -l -b -q 'Vskim.cc++("$source_dir_H_v1","$dest_dir", "tree_",1,191)'
#root -l -b -q 'Vskim.cc++("$source_dir_H_v2","$dest_dir", "tree_",1,1000)'
#root -l -b -q 'Vskim.cc++("$source_dir_H_v2_1","$dest_dir", "tree_",1000,2000)'
#root -l -b -q 'Vskim.cc++("$source_dir_H_v2_2","$dest_dir", "tree_",2000,2018)'
#root -l -b -q 'Vskim.cc++("$source_dir_B_v3","$dest_dir", "tree_",1,1000)'
#root -l -b -q 'Vskim.cc++("$source_dir_B_v3_1","$dest_dir", "tree_",1000,1989)'
#root -l -b -q 'Vskim.cc++("$source_dir_D_v1","$dest_dir", "tree_",1,1000)'
#root -l -b -q 'Vskim.cc++("$source_dir_D_v1_1","$dest_dir", "tree_",1000,1010)'
#root -l -b -q 'Vskim.cc++("$source_dir_G_v1","$dest_dir", "tree_",1,1000)'
#root -l -b -q 'Vskim.cc++("$source_dir_G_v1_1","$dest_dir", "tree_",1000,1552)'
##root -l -b -q 'Vskim.cc++("$source_dir_H_v3","$dest_dir", "tree_",1,46)'


