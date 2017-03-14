export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/LMR"

root -l -b -q 'processLMRSelection_Data_malara_2L2T.c++' 
root -l -b -q 'processLMRSelection_Graviton_malara_2L2T.c++'

