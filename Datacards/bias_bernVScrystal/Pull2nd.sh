#!/bin/bash
for c in `seq 50 100`; do
 for i in 0 1 2 3 4    
do
#cp HbbHbb_19invfb_mX300_$i.txt HbbHbb_19invfb_mX300_$i\_$c.txt
echo '300'
echo $i
sed "s/w_background_LowMass300_$i\_0/w_background_LowMass300_$i\_$c/g" HbbHbb_19invfb_mX300_$i.txt  > HbbHbb_19invfb_mX300_$i\_$c.txt
echo '270'
sed "s/w_background_LowMass270_$i\_0/w_background_LowMass270_$i\_$c/g" HbbHbb_19invfb_mX270_$i.txt  > HbbHbb_19invfb_mX270_$i\_$c.txt
echo '350'
sed "s/w_background_LowMass350_$i\_0/w_background_LowMass350_$i\_$c/g" HbbHbb_19invfb_mX350_$i.txt  > HbbHbb_19invfb_mX350_$i\_$c.txt
echo '400'
sed "s/w_background_LowMass400_$i\_0/w_background_LowMass400_$i\_$c/g" HbbHbb_19invfb_mX400_$i.txt  > HbbHbb_19invfb_mX400_$i\_$c.txt
#echo '450'
#sed "s/w_background_LowMass450_$i\_0/w_background_LowMass450_$i\_$c/g" HbbHbb_19invfb_mX450_$i.txt  > HbbHbb_19invfb_mX450_$i\_$c.txt
#echo '500'
#sed "s/w_background_LowMass500_$i\_0/w_background_LowMass500_$i\_$c/g" HbbHbb_19invfb_mX500_$i.txt  > HbbHbb_19invfb_mX500_$i\_$c.txt
#sed "s/w_background_LowMass550_$i\_0/w_background_LowMass550_$i\_$c/g" HbbHbb_19invfb_mX550_$i.txt  > HbbHbb_19invfb_mX550_$i\_$c.txt
#cp HbbHbb_19invfb_mX400_$i.txt HbbHbb_19invfb_mX400_$i\_$c.txt
#perl -pi -e 's/w_background_LowMass400_'$i'/w_background_LowMass400_'$i'_'$c'/g' HbbHbb_19invfb_mX400_$i\_$c.txt
echo $i $c
echo '300'
python text2workspace.py HbbHbb_19invfb_mX300_$i\_$c.txt -o HbbHbb_19invfb_mX300_$i\_$c.root
echo '270'
python text2workspace.py HbbHbb_19invfb_mX270_$i\_$c.txt -o HbbHbb_19invfb_mX270_$i\_$c.root
echo '350'
python text2workspace.py HbbHbb_19invfb_mX350_$i\_$c.txt -o HbbHbb_19invfb_mX350_$i\_$c.root
echo '400'
python text2workspace.py HbbHbb_19invfb_mX400_$i\_$c.txt -o HbbHbb_19invfb_mX400_$i\_$c.root
#echo '450'
#python text2workspace.py HbbHbb_19invfb_mX450_$i\_$c.txt -o HbbHbb_19invfb_mX450_$i\_$c.root
#echo '500'
#python text2workspace.py HbbHbb_19invfb_mX500_$i\_$c.txt -o HbbHbb_19invfb_mX500_$i\_$c.root
#python text2workspace.py HbbHbb_19invfb_mX550_$i\_$c.txt -o HbbHbb_19invfb_mX550_$i\_$c.root
echo 'mu'
echo $i $c
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX300_MaxLikelihood$i\_$c.log                      
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX270_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX270_MaxLikelihood$i\_$c.log                      
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX350_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX350_MaxLikelihood$i\_$c.log
combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX400_MaxLikelihood$i\_$c.log
#combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX450_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX450_MaxLikelihood$i\_$c.log
#combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX500_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX500_MaxLikelihood$i\_$c.log


#combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX550_$i\_$c.root --saveNormalizations  > HbbHbb_19invfb_mX550_MaxLikelihood$i\_$c.log
#mkdir mX300_$i
#mkdir mX400_$i
#combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX300_$i\_$c.root --saveNormalizations  --plot --out mX300_$i > HbbHbb_19invfb_mX300_MaxLikelihood$i\_$c.log 
#combine -v4 -M MaxLikelihoodFit HbbHbb_19invfb_mX400_$i\_$c.root --saveNormalizations  --plot --out mX400_$i > HbbHbb_19invfb_mX400_MaxLikelihood$i\_$c.log 
#echo 'limits'
#combine -M Asymptotic HbbHbb_19invfb_mX300_$i\_$c.root  > HbbHbb_19invfb_mX300_Asymptotic$i\_$c.log
#combine -M Asymptotic HbbHbb_19invfb_mX400_$i\_$c.root  > HbbHbb_19invfb_mX400_Asymptotic$i\_$c.log

done


done
