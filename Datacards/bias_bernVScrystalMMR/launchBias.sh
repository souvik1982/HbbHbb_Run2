#combine hgg_toy_datacard.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0  -t 200 --expectSignal 1 --saveToys -m 125 --freezeNuisances pdf_index
#combine hgg_toy_datacard.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=1 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 200 --rMin -10 --rMax 10 --freezeNuisances pdf_index


combine datacard_450_alt.txt -M GenerateOnly -m 450 -t 200 --saveToys -s 334477 --expectSignal 2.00 -n biasTest  --freezeNuisances bTag,Trigger
combine datacard_450.txt -M MaxLikelihoodFit -m 450 --expectSignal 2.00  --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH450.334477.root -s 334477 -n output450_1 --robustFit 1

combine datacard_550_alt.txt -M GenerateOnly -m 550 -t 200 --saveToys -s 334477 --expectSignal 2.00 -n biasTest   --freezeNuisances bTag,Trigger 
combine datacard_550.txt -M MaxLikelihoodFit -m 550 --expectSignal 2.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH550.334477.root -s 334477 -n output550_1 --robustFit 1


combine datacard_650_alt.txt -M GenerateOnly -m 650 -t 200 --saveToys -s 334477 --expectSignal 2.00 -n biasTest  --freezeNuisances bTag,Trigger 
combine datacard_650.txt -M MaxLikelihoodFit -m 650 --expectSignal 2.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH650.334477.root -s 334477 -n output650_1  --robustFit 1
combine datacard_alt_750.txt -M GenerateOnly -m 750 -t 200 --saveToys -s 334477 --expectSignal 2.00 -n biasTest --freezeNuisances bTag,Trigger 
combine datacard_750.txt -M MaxLikelihoodFit -m 750 --expectSignal 2.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH750.334477.root -s 334477 -n output750_1  --robustFit 1

combine datacard_900_alt.txt -M GenerateOnly -m 900 -t 200 --saveToys -s 334477 --expectSignal 2.00 -n biasTest --freezeNuisances bTag,Trigger 
combine datacard_900.txt -M MaxLikelihoodFit -m 900 --expectSignal 2.00 --rMin=-2000 --rMax=2000 -t 200 --toysFile=higgsCombinebiasTest.GenerateOnly.mH900.334477.root -s 334477 -n output900_1 --robustFit 1
