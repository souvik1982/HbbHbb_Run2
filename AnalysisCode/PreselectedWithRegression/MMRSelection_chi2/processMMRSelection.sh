export TEST_PATH="/scratch/malara/WorkingArea/IO_file"
export source_dir="$TEST_PATH/input_file"
export dest_dir="$TEST_PATH/output_file"

root -l -b -q 'processMMRSelection_Data.c++' 
root -l -b -q 'processMMRSelection_Graviton.c++'
