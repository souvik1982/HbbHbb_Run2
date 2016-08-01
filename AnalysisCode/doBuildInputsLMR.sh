#!/bin/bash


#rebin=$1
mass=$1
#fitModel=$3



mkdir LMR_${mass}
echo

echo "root -x -b -l -q Display_SignalFits_LMR.cc\(\"PreselectedWithoutRegression\",\"LMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"true\"\) > LMR_${mass}/signal${mass}_sig.log"
echo
root -x -b -l -q Display_SignalFits_LMR.cc\(\"PreselectedWithoutRegression\",\"LMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"true\"\) > LMR_${mass}/signal${mass}_sig.log
echo
cd PreselectedWithoutRegression/LMRSelection_chi2	
echo "root -x -b -l -q fit_background.c "
echo
root -x -b -l -q fit_background.c > ../../LMR_${mass}/data_bkg.log
cp w_background_GaussExp.root ../../LMR_${mass}/
cp w_data.root ../../LMR_${mass}/
cd ../../

