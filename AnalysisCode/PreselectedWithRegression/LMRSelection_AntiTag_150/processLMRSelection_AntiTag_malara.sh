export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag_150"

root -l -b -q 'processLMRSelection_Data_AntiTag.c++'
#root -l -b -q 'processLMRSelection_Data_AntiTag_l3.c++'
#root -l -b -q 'processLMRSelection_Data_AntiTag_l4.c++'
#root -l -b -q 'processLMRSelection_Graviton_AntiTag_malara.c++'
