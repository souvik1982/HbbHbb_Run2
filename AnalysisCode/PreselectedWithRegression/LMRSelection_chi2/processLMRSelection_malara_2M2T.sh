export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/LMR"

root -l -b -q 'processLMRSelection_Data_malara_2M2T.c++' 
root -l -b -q 'processLMRSelection_Graviton_malara_2M2T.c++'
