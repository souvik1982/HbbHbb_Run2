#!/bin/bash

mass=$1
#fitModel=$3

dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
dir_selection="../../MMR"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit"
background_type="fit_crystal_malara.c" #fit_background_malara.c
Type="Crystal" #GaussExp
#Modify also in /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/MMRSelection_chi2/fit_background_malara.c

file_histograms="Histograms_MMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

rm -fr ${dest_dir}"/SignalFitsreg"
mkdir ${dest_dir}"/SignalFitsreg"
folder=${dest_dir}/MMR_${mass}
rm -fr $folder
mkdir $folder
echo

rm -f test.c
echo " { gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/ExpGaussExp_cxx.so\"); gSystem->Load(\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PDFs/RevCrystalBall_cxx.so\");
gROOT->LoadMacro(\"Display_SignalFits_malara.cc\");
Display_SignalFits_malara(\"$dir_preselection\",\"reg\",\"$dir_selection\",\"$dest_dir\",\"$file_histograms\",${mass},\"true\"); }" > test.c

echo 
root -x -b -l -q test.c > $folder/signal${mass}_sig.log
mv ${dest_dir}/SignalFitsreg/*${mass}* $folder/
mv ${dest_dir}/SignalFitsreg/index.html $folder/

echo "done"
echo "root -x -b -l -q PreselectedWithRegression/MMRSelection_chi2/"$background_type
echo
root -x -b -l -q /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/MMRSelection_chi2/$background_type > $folder/data_bkg.log

mv $dest_dir/w_background_$Type.root $folder/
mv $dest_dir/w_data.root $folder/ 
echo "end"
