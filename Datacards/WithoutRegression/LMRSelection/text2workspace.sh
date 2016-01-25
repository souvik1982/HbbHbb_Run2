#!/bin/tcsh

setenv dir ../../../AnalysisCode/PDFs

foreach imass (260 270 300 400 600)
  echo Processing HbbHbb_$imass.txt
  text2workspace.py HbbHbb_$imass.txt  -o HbbHbb_13TeV_mX$imass.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
  echo Done.
end
