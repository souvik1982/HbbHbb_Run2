echo '0'
python text2workspace.py HbbHbb_19invfb_mX300_gaus0.txt -o HbbHbb_19invfb_mX300_0.root
python text2workspace.py HbbHbb_19invfb_mX400_gaus0.txt -o HbbHbb_19invfb_mX400_0.root
echo '1'
python text2workspace.py HbbHbb_19invfb_mX300_gaus1.txt -o HbbHbb_19invfb_mX300_1.root
python text2workspace.py HbbHbb_19invfb_mX400_gaus1.txt -o HbbHbb_19invfb_mX400_1.root
echo '2'
python text2workspace.py HbbHbb_19invfb_mX300_gaus2.txt -o HbbHbb_19invfb_mX300_2.root
python text2workspace.py HbbHbb_19invfb_mX400_gaus2.txt -o HbbHbb_19invfb_mX400_2.root
echo '5'
python text2workspace.py HbbHbb_19invfb_mX300_gaus5.txt -o HbbHbb_19invfb_mX300_5.root
python text2workspace.py HbbHbb_19invfb_mX400_gaus5.txt -o HbbHbb_19invfb_mX400_5.root
echo '10'
python text2workspace.py HbbHbb_19invfb_mX300_gaus10.txt -o HbbHbb_19invfb_mX300_10.root
python text2workspace.py HbbHbb_19invfb_mX400_gaus10.txt -o HbbHbb_19invfb_mX400_10.root
echo 'mu'
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_0.root --saveNormalizations --plot --out mX300_0 > HbbHbb_19invfb_mX300_MaxLikelihood_0.log 
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_0.root --saveNormalizations --plot --out mX400_0 > HbbHbb_19invfb_mX400_MaxLikelihood_0.log 
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_1.root --saveNormalizations --plot --out mX300_1 > HbbHbb_19invfb_mX300_MaxLikelihood_1.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_1.root --saveNormalizations --plot --out mX400_1 > HbbHbb_19invfb_mX400_MaxLikelihood_1.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_2.root --saveNormalizations --plot --out mX300_2 > HbbHbb_19invfb_mX300_MaxLikelihood_2.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_2.root --saveNormalizations --plot --out mX400_2 > HbbHbb_19invfb_mX400_MaxLikelihood_2.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_5.root --saveNormalizations --plot --out mX300_5 > HbbHbb_19invfb_mX300_MaxLikelihood_5.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_5.root --saveNormalizations --plot --out mX400_5 > HbbHbb_19invfb_mX400_MaxLikelihood_5.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_10.root --saveNormalizations --plot --out mX300_10 > HbbHbb_19invfb_mX300_MaxLikelihood_10.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_10.root --saveNormalizations --plot --out mX400_10 > HbbHbb_19invfb_mX400_MaxLikelihood_10.log
echo 'limits'
combine -M Asymptotic HbbHbb_19invfb_mX300_0.root  > HbbHbb_19invfb_mX300_Asymptotic_0.log
combine -M Asymptotic HbbHbb_19invfb_mX400_0.root  > HbbHbb_19invfb_mX400_Asymptotic_0.log
combine -M Asymptotic HbbHbb_19invfb_mX300_1.root  > HbbHbb_19invfb_mX300_Asymptotic_1.log
combine -M Asymptotic HbbHbb_19invfb_mX400_1.root  > HbbHbb_19invfb_mX400_Asymptotic_1.log
combine -M Asymptotic HbbHbb_19invfb_mX300_2.root  > HbbHbb_19invfb_mX300_Asymptotic_2.log
combine -M Asymptotic HbbHbb_19invfb_mX400_2.root  > HbbHbb_19invfb_mX400_Asymptotic_2.log
combine -M Asymptotic HbbHbb_19invfb_mX300_5.root  > HbbHbb_19invfb_mX300_Asymptotic_5.log
combine -M Asymptotic HbbHbb_19invfb_mX400_5.root  > HbbHbb_19invfb_mX400_Asymptotic_5.log
combine -M Asymptotic HbbHbb_19invfb_mX300_10.root  > HbbHbb_19invfb_mX300_Asymptotic_10.log
combine -M Asymptotic HbbHbb_19invfb_mX400_10.root  > HbbHbb_19invfb_mX400_Asymptotic_10.log



