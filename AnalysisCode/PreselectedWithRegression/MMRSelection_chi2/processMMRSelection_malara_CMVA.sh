export source_dir_Dati="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/Data/PreselectedWithRegression"
export source_dir_MC="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/MC/PreselectedWithRegression"
export dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/CMVA/MMR"

#root -l -b -q 'processMMRSelection_Data_malara_CMVA.c++' 
root -l -b -q 'processMMRSelection_Graviton_malara_CMVA.c++'
