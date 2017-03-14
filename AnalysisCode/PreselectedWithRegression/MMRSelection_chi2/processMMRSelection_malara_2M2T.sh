export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/MMR"

root -l -b -q 'processMMRSelection_Data_malara_2M2T.c++' 
#root -l -b -q 'processMMRSelection_Graviton_malara_2M2T.c++'
