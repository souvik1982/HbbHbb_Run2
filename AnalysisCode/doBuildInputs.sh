#!/bin/bash


mass=$1
#fitModel=$3



mkdir MMR_${mass}
echo

echo " { gSystem->Load(\"PDFs/ExpGaussExp_cxx.so\"); gROOT->LoadMacro(\"Display_SignalFits.cc\"); Display_SignalFits(\"PreselectedWithRegressionDeepCSV\",\"reg\",\"MMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"false\"); }" > test.c
echo 
root -x -b -l -q test.c > MMR_${mass}/signal${mass}_sig.log
cp SignalFitsreg/*${mass}* MMR_${mass}/
cp SignalFitsreg/index.html MMR_${mass}/
#Display_SignalFits.cc\(\"PreselectedWithRegressionDeepCSV\",\"MMRSelection_chi2\",\"Histograms_GluGluToBulkGravitonToHHTo4B_M-\",${mass},\"true\"\) > MMR_${mass}/signal${mass}_sig.log
echo
cd PreselectedWithRegressionDeepCSV/MMRSelection_chi2	
echo "root -x -b -l -q fit_background.c "
echo
root -x -b -l -q fit_crystal.c > ../../MMR_${mass}/data_bkg.log
cp w_background_Crystal.root ../../MMR_${mass}/
cp w_data.root ../../MMR_${mass}/
cd ../../

python PDFSyst.py --mass $1 > MMR_${mass}/pdf.log

