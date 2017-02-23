#!/bin/bash
#cd ../../../../../DiH_13TeV/CMSSW_7_1_5/src/ 
#cmsenv
#cd -
#for i in 260 270 300 350 400 450 500
#do
#	echo "mass point $i"
#	cd /uscms_data/d3/cvernier/4b/HbbHbb_2016/HbbHbb_Run2/Datacards/22fb_regression/LMR_$i
#	text2workspace.py datacard_$i\.txt  -o datacard_$i\.root
#	combine -M Asymptotic datacard_$i\.root  --noFitAsimov -t -1 > CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 1000 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#mv higgsCombineCMSHH4b.Asymptotic.mH$i\.root Limits/CMS_$i\_HH4b_13TeV_asymptoticCLs.root
	# combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out Limits/sig$i bias_study/HbbHbb_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out	
	
#done

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd /scratch/malara/WorkingArea/backup/CMSSW_7_4_14/src/HiggsAnalysis/CombinedLimit 
cmsenv
cd $DIR

masses=(
    300 350 400 450 500 550 600 650 700 750 800 900 1000 1200
)

echo 'MMR'
for i in ${masses[@]}

do
	folder="/scratch/malara/WorkingArea/IO_file/output_file/MMR_fit/MMR_${i}"
	if [ -d $folder ]
	then
        echo "mass point $i"
	cd $folder 
        text2workspace.py datacard_$i\.txt  -o datacard_$i\.root
        combine -M Asymptotic datacard_$i\.root -t -1  --noFitAsimov 
#&> ../LMRSelection_chi2_Regression/CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	fi	
done

cd $DIR

echo 'LMR'
for i in ${masses[@]}

do
        folder="/scratch/malara/WorkingArea/IO_file/output_file/LMR_fit/LMR_${i}"
        if [ -d $folder ]
        then
        echo "mass point $i"
        cd $folder
        text2workspace.py datacard_$i\.txt  -o datacard_$i\.root
        combine -M Asymptotic datacard_$i\.root -t -1  --noFitAsimov
#&> ../LMRSelection_chi2_Regression/CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        fi
done\

cd $DIR
