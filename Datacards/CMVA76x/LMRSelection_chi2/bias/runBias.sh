#!/bin/bash
for i in 260 270 300 350 400 
do
	for j in 1 3 5 10
	do
	echo "mass point $i"
	combine HbbHbb_$i\.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=1 --toysFrequentist -t 200 --expectSignal $j --saveToys -m 125 --freezeNuisances pdf_index
	combine HbbHbb_$i\.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=0 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 200 --rMin -20 --rMax 20 --freezeNuisances pdf_index
	mv mlfit.root mlfit_${i}_mu${j}.root
	root -l -b -q "BiasStudies.C($i,$j)" >& log_${i}_$j
	#grep "ASDASD" log_${i}_$j 
	#text2workspace.py HbbHbb_$i\.txt  -o HbbHbb_$i\.root
	#combine -M Asymptotic HbbHbb_$i\.txt --noFitAsimov	&> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 100 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#mv higgsCombineCMSHH4b.Asymptotic.mH$i\.root Limits/CMS_$i\_HH4b_13TeV_asymptoticCLs.root
	# combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out Limits/sig$i bias_study/HbbHbb_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
	done
done

for i in 400 450 500 550
do
        for j in 1 
        do
        echo "mass point $i"
        ##combine HbbHbb_$i\.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=1 --toysFrequentist -t 200 --expectSignal $j --saveToys -m 125 --freezeNuisances pdf_index
        #combine HbbHbb_$i\.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=0 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 200 --rMin -30 --rMax 30 --freezeNuisances pdf_index
        #mv mlfit.root mlfit_${i}_mu${j}.root
        #root -l -b -q "BiasStudies.C($i,$j)"
        #text2workspace.py HbbHbb_$i\.txt  -o HbbHbb_$i\.root
        #combine -M Asymptotic HbbHbb_$i\.txt --noFitAsimov     &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        #combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 100 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        #mv higgsCombineCMSHH4b.Asymptotic.mH$i\.root Limits/CMS_$i\_HH4b_13TeV_asymptoticCLs.root
        # combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out Limits/sig$i bias_study/HbbHbb_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        done
done

