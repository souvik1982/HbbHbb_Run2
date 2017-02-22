#!/bin/bash

mass=$1
#fitModel=$3

dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/Data/PreselectedWithWithRegression"
dir_selection="MMRSelection_chi2"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/MMR_fit"
#DA MODIFICARE ANCHE IN /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/MMRSelection_chi2/fit_background.c
fit_folder="/scratch/malara/WorkingArea/IO_file/output_file/MMR_fit"

file_histograms="Histograms_MMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

folder=MMR_${mass}
rm -fr ${dest_dir}"/SignalFitsreg"
mkdir ${dest_dir}"/SignalFitsreg"
folder=${dest_dir}/MMR_${mass}
rm -fr $folder
mkdir $folder
echo

rm -f test.c
echo " { gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so\"); 
gROOT->LoadMacro(\"Display_SignalFits.cc\");
Display_SignalFits(\"$dir_preselection\",\"reg\",\"$dir_selection\",\"$dest_dir\",\"$file_histograms\",${mass},\"true\"); }" > test.c

echo 
root -x -b -l -q test.c > $folder/signal${mass}_sig.log
mv ${dest_dir}/SignalFitsreg/*${mass}* $folder/
mv ${dest_dir}/SignalFitsreg/index.html $folder/

echo "done"
echo "root -x -b -l -q PreselectedWithRegression/MMRSelection_chi2/fit_background.c "
echo
root -x -b -l -q PreselectedWithRegression/MMRSelection_chi2/fit_background.c > $folder/data_bkg.log

mv $fit_folder/w_background_GaussExp.root $folder/
mv $fit_folder/w_data.root $folder/ 
echo "end"
