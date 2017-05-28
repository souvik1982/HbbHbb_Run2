export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_new"

#root -l -b -q 'processLMRSelection_Data_malara.c++' 
#root -l -b -q 'processLMRSelection_Graviton_malara.c++'
root -l -b -q 'processLMRSelection_Data_malara_overlap.c++' 
