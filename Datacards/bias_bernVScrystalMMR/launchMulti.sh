#combine hgg_toy_datacard.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0  -t 100 --expectSignal 1 --saveToys -m 125 --freezeNuisances pdf_index
#combine hgg_toy_datacard.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=1 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 100 --rMin -10 --rMax 10 --freezeNuisances pdf_index


combine datacard_alt_260.txt -M GenerateOnly -m 260 -t 250 --saveToys -s 334477 --expectSignal=1 -n biasTest   
combine datacard_260.txt -M MaxLikelihoodFit -m 260 --expectSignal=3.0 --noErrors --minos none --rMin=-50000 --rMax=50000 -t 250 --toysFile=higgsCombinebiasTest.GenerateOnly.mH260.334477.root -s 334477 -n output260_1

combine datacard_alt_270.txt -M GenerateOnly -m 270 -t 250 --saveToys -s 334477 --expectSignal=1 -n biasTest   
combine datacard_270.txt -M MaxLikelihoodFit -m 270 --expectSignal=3.0 --noErrors --minos none --rMin=-50000 --rMax=50000 -t 250 --toysFile=higgsCombinebiasTest.GenerateOnly.mH270.334477.root -s 334477 -n output270_1


combine datacard_alt_300.txt -M GenerateOnly -m 300 -t 250 --saveToys -s 334477 --expectSignal=1 -n biasTest    
combine datacard_300.txt -M MaxLikelihoodFit -m 300 --expectSignal=3.0 --noErrors --minos none --rMin=-50000 --rMax=50000 -t 250 --toysFile=higgsCombinebiasTest.GenerateOnly.mH300.334477.root -s 334477 -n output300_1

combine datacard_alt_350.txt -M GenerateOnly -m 350 -t 250 --saveToys -s 334477 --expectSignal=1 -n biasTest   
combine datacard_350.txt -M MaxLikelihoodFit -m 350 --expectSignal=3.0 --noErrors --minos none --rMin=-50000 --rMax=50000 -t 250 --toysFile=higgsCombinebiasTest.GenerateOnly.mH350.334477.root -s 334477 -n output350_1

combine datacard_alt_400.txt -M GenerateOnly -m 400 -t 250 --saveToys -s 334477 --expectSignal=1 -n biasTest    
combine datacard_400.txt -M MaxLikelihoodFit -m 400 --expectSignal=3.0 --noErrors --minos none --rMin=-50000 --rMax=50000 -t 250 --toysFile=higgsCombinebiasTest.GenerateOnly.mH400.334477.root -s 334477 -n output400_1
