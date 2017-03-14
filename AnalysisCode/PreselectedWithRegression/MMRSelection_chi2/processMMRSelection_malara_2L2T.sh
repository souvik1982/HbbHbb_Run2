export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2T/MMR"

root -l -b -q 'processMMRSelection_Data_malara_2L2T.c++' 
#root -l -b -q 'processMMRSelection_Graviton_malara_2L2T.c++'
