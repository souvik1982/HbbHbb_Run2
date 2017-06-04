#!/bin/bash

mass=$1

background="_crystal_1_550_1200" # "" "_bern"

#Modify also in /scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/MMRSelection_chi2/fit_background_malara.c
dir_preselection="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/Data/PreselectedWithRegression"
dir_selection="../../MMR_test"
dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR_test/fit"
background_type="fit_split_malara.c" #"fit_convolution_malara.c" "fit_crystal_malara.c" fit_background_malara.c fit_bern_malara.c
Type="Split" #"Convolution" Crystal GaussExp Bern

file_histograms="Histograms_MMR_chi2_tree_GluGluToBulkGravitonToHHTo4B_M-"

rm -fr ${dest_dir}"/SignalFitsreg"
mkdir ${dest_dir}"/SignalFitsreg"
folder=${dest_dir}/MMR_${mass}${background}
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

mv $dest_dir/w_background$background.root $folder/
mv $dest_dir/w_spline.root $folder/
mv $dest_dir/w_data_$Type.root $folder/ 
mv $dest_dir/*BackgroundFit_*${background}*.png* $folder/ 
echo "end"
