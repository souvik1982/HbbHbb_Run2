#!/bin/bash

mass=$1

background="_novo_455_854" # "" "_bern"

#Modify also in /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/fit_background_malara.c
dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
dir_selection="../../LMR_AntiTag"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR_AntiTag/fit"
background_type="fit_split_malara.c" #"fit_convolution_malara.c" "fit_crystal_malara.c" fit_background_malara.c fit_bern_malara.c
Type="Split" #"Convolution" Crystal GaussExp Bern

file_histograms="Histograms_LMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

rm -fr ${dest_dir}"/SignalFits_LMRreg"
mkdir ${dest_dir}"/SignalFits_LMRreg"
folder=${dest_dir}/LMR_${mass}${background}
rm -fr $folder
mkdir $folder
echo

rm -f test.c
echo " { gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so\"); gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so\");
gROOT->LoadMacro(\"Display_SignalFits_LMR_malara.cc\"); 
Display_SignalFits_LMR_malara(\"$dir_preselection\",\"reg\",\"$dir_selection\",\"$dest_dir\",\"$file_histograms\",${mass},\"true\"); }" > test.c

echo 
root -x -b -l -q test.c > $folder/signal${mass}_sig.log
mv ${dest_dir}/SignalFits_LMRreg/*${mass}* $folder/
mv ${dest_dir}/SignalFits_LMRreg/index.html $folder/

echo "done"
echo "root -x -b -l -q PreselectedWithRegression/LMRSelection_AntiTag/"$background_type
echo
root -x -b -l -q /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_AntiTag/$background_type > $folder/data_bkg.log

mv $dest_dir/w_background$background.root $folder/
mv $dest_dir/w_data_$Type.root $folder/ 
mv $dest_dir/*BackgroundFit_*${background}*.png* $folder/ 
echo "end"
