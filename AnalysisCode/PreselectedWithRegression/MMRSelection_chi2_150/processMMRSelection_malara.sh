export source_dir_Data="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR_150"

root -l -b -q 'processMMRSelection_Graviton_malara.c++'
root -l -b -q 'processMMRSelection_Data_malara.c++' 
