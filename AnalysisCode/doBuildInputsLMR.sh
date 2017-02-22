#!/bin/bash

mass=$1
#fitModel=$3

dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/Data/PreselectedWithWithRegression"
dir_selection="LMRSelection_chi2"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/LMR_fit"
#DA MODIFICARE ANCHE IN /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/LMRSelection_chi2/fit_background.c
fit_folder="/scratch/malara/WorkingArea/IO_file/output_file/LMR_fit"

file_histograms="Histograms_LMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

folder=LMR_${mass}
rm -fr ${dest_dir}"/SignalFits_LMRreg"
mkdir ${dest_dir}"/SignalFits_LMRreg"
folder=${dest_dir}/LMR_${mass}
rm -fr $folder
mkdir $folder
echo

rm -f test.c
echo " { gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so\"); 
gROOT->LoadMacro(\"Display_SignalFits_LMR.cc\"); 
Display_SignalFits_LMR(\"$dir_preselection\",\"reg\",\"$dir_selection\",\"$dest_dir\",\"$file_histograms\",${mass},\"true\"); }" > test.c

echo 
root -x -b -l -q test.c > $folder/signal${mass}_sig.log
mv ${dest_dir}/SignalFits_LMRreg/*${mass}* $folder/
mv ${dest_dir}/SignalFits_LMRreg/index.html $folder/

echo
echo "root -x -b -l -q PreselectedWithRegression/LMRSelection_chi2/fit_background.c "
echo
root -x -b -l -q PreselectedWithRegression/LMRSelection_chi2/fit_background.c > $folder/data_bkg.log

mv $fit_folder/w_background_GaussExp.root $folder/
mv $fit_folder/w_data.root $folder/ 
