#!/bin/bash

mass=$1
#fitModel=$3

dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
dir_selection="../../LMR"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit"
background_type="fit_crystal_malara.c" #fit_background_malara.c
Type="Crystal" #GaussExp
#Modify also in /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/fit_background_malara.c

file_histograms="Histograms_LMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

rm -fr ${dest_dir}"/SignalFits_LMRreg"
mkdir ${dest_dir}"/SignalFits_LMRreg"
folder=${dest_dir}/LMR_${mass}
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
echo "root -x -b -l -q PreselectedWithRegression/LMRSelection_chi2/"$background_type
echo
root -x -b -l -q /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/$background_type > $folder/data_bkg.log

mv $dest_dir/w_background_$Type.root $folder/
mv $dest_dir/w_data.root $folder/ 
echo "end"
