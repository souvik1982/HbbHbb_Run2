#!/bin/bash
for i in 260 270 300 350 400 450 500 550
do
	echo "mass point $i"
	#combine -M MaxLikelihoodFit -t -1 --expectSignal 0 HbbHbb_$i\.txt &> CMS_HH4b_$i\_test.out
	#python diffNuisances.py -a mlfit.root -g plots$i\_.root
	#combine -M MaxLikelihoodFit -t -1 --expectSignal 1 HbbHbb_$i\.txt &> CMS_HH4b_$i\_test1.out
	#python diffNuisances.py -a mlfit.root -g plots2$i\_.root

	text2workspace.py HbbHbb_$i\.txt  -o HbbHbb_$i\.root
	combine -M Asymptotic HbbHbb_$i\.txt --noFitAsimov	&> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 1000 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	mv higgsCombineCMSHH4b.Asymptotic.mH$i\.root Limits/CMS_$i\_HH4b_13TeV_asymptoticCLs.root
	 combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out Limits/sig$i bias_study/HbbHbb_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
done
