export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export source_dir="/gpfs/ddn/srm/cms/store/user/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2/170130_123206/0000/" 
export dest_dir="$TEST_PATH/output_file" 

#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",1,5)'

root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",1,100)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",101,200)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",201,300)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",301,400)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",401,500)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",501,600)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",601,700)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",701,800)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",801,900)'
#root -l -b -q 'Vskim.cc++("$source_dir","$dest_dir", "tree_",901,1000)'


#root -l -b -q 'Vskim.cc++("BTagCSV0")'
#root -l -b -q 'Vskim.cc++("BTagCSV1")'
#root -l -b -q 'Vskim.cc++("BTagCSV2")'
#root -l -b -q 'Vskim.cc++("BTagCSV3")'
#root -l -b -q 'Vskim.cc++("BTagCSV4")'
#root -l -b -q 'Vskim.cc++("BTagCSV5")'
