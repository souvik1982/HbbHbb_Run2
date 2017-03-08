export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/LMR"

root -l -b -q 'processLMRSelection_Data_malara_CMVA.c++' 
root -l -b -q 'processLMRSelection_Graviton_malara_CMVA.c++'
