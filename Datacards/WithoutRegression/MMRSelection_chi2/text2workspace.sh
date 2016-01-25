setenv dir ../../../AnalysisCode/PDFs
text2workspace.py HbbHbb_13TeV_mX400.txt  -o HbbHbb_13TeV_mX400.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
text2workspace.py HbbHbb_13TeV_mX600.txt  -o HbbHbb_13TeV_mX600.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
text2workspace.py HbbHbb_13TeV_mX800.txt  -o HbbHbb_13TeV_mX800.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
text2workspace.py HbbHbb_13TeV_mX1000.txt -o HbbHbb_13TeV_mX1000.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
text2workspace.py HbbHbb_13TeV_mX1200.txt -o HbbHbb_13TeV_mX1200.root -L $dir/GaussExp_cxx.so -L $dir/ExpGaussExp_cxx.so
