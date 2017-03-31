#combine hgg_toy_datacard.txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0  -t 300 --expectSignal 1 --saveToys -m 125 --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5 pdf_index
#combine hgg_toy_datacard.txt -M MaxLikelihoodFit  --setPhysicsModelParameters pdf_index=1 --toysFile higgsCombineTest.GenerateOnly.mH125.123456.root  -t 300 --rMin -10 --rMax 10 --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5 pdf_index


combine datacard_260.txt -M GenerateOnly -m 260 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3
combine datacard_260.txt -M MaxLikelihoodFit -m 260 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH260.334477.root -s 334477 -n closure260_1

combine datacard_270.txt -M GenerateOnly -m 270 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3
combine datacard_270.txt -M MaxLikelihoodFit -m 270 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH270.334477.root -s 334477 -n closure270_1


combine datacard_300.txt -M GenerateOnly -m 300 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3    
combine datacard_300.txt -M MaxLikelihoodFit -m 300 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH300.334477.root -s 334477 -n closure300_1

combine datacard_350.txt -M GenerateOnly -m 350 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3 
combine datacard_350.txt -M MaxLikelihoodFit -m 350 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH350.334477.root -s 334477 -n closure350_1

combine datacard_400.txt -M GenerateOnly -m 400 -t 300 --saveToys -s 334477 --expectSignal=1.0 -n biasTest --freezeNuisances signal_p0,signal_p1,signal_p2,signal_p3,signal_p4,signal_p5,bg_p0,bg_p1,bg_p2,bg_p3    
combine datacard_400.txt -M MaxLikelihoodFit -m 400 --expectSignal=1.0 --noErrors --minos none --rMin=-50 --rMax=50 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH400.334477.root -s 334477 -n closure400_1
