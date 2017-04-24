#!/bin/bash


#rebin=$1
mass=$1
#fitModel=$3



mkdir LMR_${mass}
echo

echo "root -x -b -l -q Display_SignalFits_LMR.cc\(\"PreselectedWithRegressionDeepCSV\",\"reg\",\"LMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"false\"\) > LMR_${mass}/signal${mass}_sig.log"
echo
root -x -b -l -q Display_SignalFits_LMR.cc\(\"PreselectedWithRegressionDeepCSV\",\"reg\",\"LMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"False\"\) > LMR_${mass}/signal${mass}_sig.log
cp SignalFits_LMRreg/*${mass}* LMR_${mass}/
cp SignalFits_LMRreg/index.html LMR_${mass}/

echo
cd PreselectedWithRegressionDeepCSV/LMRSelection_chi2	
echo "root -x -b -l -q fit_background.c "
echo
root -x -b -l -q fit_crystal.c > ../../LMR_${mass}/data_bkg.log
cp w_background_Crystal.root ../../LMR_${mass}/
cp w_data.root ../../LMR_${mass}/
cd ../../

python PDFSyst.py --mass $1 > LMR_${mass}/pdf.log 

