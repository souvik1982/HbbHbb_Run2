masses_LMR=(
    #260 270 300 350 400 450 500 550
#260 265 270 275 280 285 290 295 300 310 320 330 340 350 360 370 380 390 400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550
370 420
)

for i in ${masses_LMR[@]}

do
     echo $i
     python mlfitNormsToText.py LMR_$i/mlfit.root
done

for i in ${masses_LMR[@]}
do
     echo $i
     python diffNuisances.py LMR_$i/mlfit.root -a -A  -p r
done
