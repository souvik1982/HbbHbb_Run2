#!/bin/tcsh

setenv dir ../../../AnalysisCode/PDFs

foreach imass (260 270 300 400 600)
  echo Processing HbbHbb_13TeV_mX$imass.root
  combine -M Asymptotic -v2 HbbHbb_13TeV_mX$imass.root -t -1 -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX$imass\_Asymptotic.log
  echo Done.
end
