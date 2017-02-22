export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export source_dir="$TEST_PATH/input_file"
export dest_dir="$TEST_PATH/output_file"

root -l -b -q 'processLMRSelection_Data.c++' 
#root -l -b -q 'processLMRSelection_Graviton.c++'
