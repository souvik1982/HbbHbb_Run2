#combine hgg_toy_datacard.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0  -t 200 --expectSignal 1 --saveToys -m 125 --freezeNuisances pdf_index
#combine hgg_toy_datacard.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=1 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 200 --rMin -10 --rMax 10 --freezeNuisances pdf_index


combine datacard_alt_260.txt -M GenerateOnly -m 260 -t 200 --saveToys -s 334473 --expectSignal 1.00 -n biasTest  --freezeNuisances bTag,Trigger
combine datacard_260.txt -M MaxLikelihoodFit -m 260 --expectSignal 1.00  --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH260.334473.root -s 334473 -n output260_1 --robustFit 1

combine datacard_alt_270.txt -M GenerateOnly -m 270 -t 200 --saveToys -s 334477 --expectSignal 1.00 -n biasTest    --freezeNuisances bTag,Trigger

combine datacard_270.txt -M MaxLikelihoodFit -m 270 --expectSignal 1.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH270.334477.root -s 334477 -n output270_1 --robustFit 1


combine datacard_alt_300.txt -M GenerateOnly -m 300 -t 200 --saveToys -s 334477 --expectSignal 1.00 -n biasTest    --freezeNuisances bTag,Trigger

combine datacard_300.txt -M MaxLikelihoodFit -m 300 --expectSignal 1.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH300.334477.root -s 334477 -n output300_1  --robustFit 1

combine datacard_alt_350.txt -M GenerateOnly -m 350 -t 200 --saveToys -s 334477 --expectSignal 1.00 -n biasTest   --freezeNuisances bTag,Trigger

combine datacard_350.txt -M MaxLikelihoodFit -m 350 --expectSignal 1.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH350.334477.root -s 334477 -n output350_1  --robustFit 1

combine datacard_alt_400.txt -M GenerateOnly -m 400 -t 200 --saveToys -s 334477 --expectSignal 1.00 -n biasTest   --freezeNuisances bTag,Trigger

combine datacard_400.txt -M MaxLikelihoodFit -m 400 --expectSignal 1.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH400.334477.root -s 334477 -n output400_1 --robustFit 1
