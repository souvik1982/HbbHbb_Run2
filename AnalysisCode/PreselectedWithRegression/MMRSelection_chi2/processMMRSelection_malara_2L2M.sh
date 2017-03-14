export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/MMR"

root -l -b -q 'processMMRSelection_Data_malara_2L2M.c++' 
#root -l -b -q 'processMMRSelection_Graviton_malara_2L2M.c++'
