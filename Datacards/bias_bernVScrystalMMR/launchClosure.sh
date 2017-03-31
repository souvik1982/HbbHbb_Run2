#combine hgg_toy_datacard.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0  -t 300 --expectSignal 1 --saveToys -m 125 --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5 pdf_index
#combine hgg_toy_datacard.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=1 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 300 --rMin -10 --rMax 10 --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5 pdf_index


combine datacard_450.txt -M GenerateOnly -m 450 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3
combine datacard_450.txt -M MaxLikelihoodFit -m 450 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH450.334477.root -s 334477 -n closure450_1

combine datacard_550.txt -M GenerateOnly -m 550 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3
combine datacard_550.txt -M MaxLikelihoodFit -m 550 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH550.334477.root -s 334477 -n closure550_1


combine datacard_650.txt -M GenerateOnly -m 650 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3    
combine datacard_650.txt -M MaxLikelihoodFit -m 650 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH650.334477.root -s 334477 -n closure650_1

combine datacard_750.txt -M GenerateOnly -m 750 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3 
combine datacard_750.txt -M MaxLikelihoodFit -m 750 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH750.334477.root -s 334477 -n closure750_1

combine datacard_900.txt -M GenerateOnly -m 900 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3    
combine datacard_900.txt -M MaxLikelihoodFit -m 900 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH900.334477.root -s 334477 -n closure900_1
