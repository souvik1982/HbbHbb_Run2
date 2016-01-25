setenv dir ../../../AnalysisCode/PDFs
combine -M Asymptotic HbbHbb_13TeV_mX400.root --noFitAsimov -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX400_Asymptotic.log 
echo mX400 done
combine -M Asymptotic HbbHbb_13TeV_mX600.root --noFitAsimov -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX600_Asymptotic.log
echo mX600 done
combine -M Asymptotic HbbHbb_13TeV_mX800.root --noFitAsimov -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX800_Asymptotic.log
echo mX800 done
combine -M Asymptotic HbbHbb_13TeV_mX1000.root --noFitAsimov -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX1000_Asymptotic.log
echo mX1000 done
combine -M Asymptotic HbbHbb_13TeV_mX1200.root --noFitAsimov -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so >&! HbbHbb_13TeV_mX1200_Asymptotic.log
echo mX1200 done
