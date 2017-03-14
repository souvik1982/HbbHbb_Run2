export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/LMR"

root -l -b -q 'processLMRSelection_Data_malara_2L2M.c++' 
#root -l -b -q 'processLMRSelection_Graviton_malara_2L2M.c++'
