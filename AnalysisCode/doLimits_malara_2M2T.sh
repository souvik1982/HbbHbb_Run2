#!/bin/bash

function show_help { 
    echo "./doLimits_malara_2M2T.sh [-c to clean up] [-d debug combine]" 
}

masses=(
   400 450 500 550 600 650 750 800 900
)
massesLMR=(
    260 270 300 350 400 450 500 550
)
cleanUp=0
#rebin=10
debug=0

while getopts "h?cr:d" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    d) 
        debug=1
        ;;
    c)  cleanUp=1
        ;;
    esac
done

for m in ${masses[@]}
do
    if [ $cleanUp -eq 0 ]; then
	 echo 'MMR'	
        source doBuildInputs_malara_2M2T.sh $m
        source doDatacards_malara_2M2T.sh $m
       #./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done
for m in ${massesLMR[@]}
do
    if [ $cleanUp -eq 0 ]; then
	echo  'LMR'
        #source doBuildInputsLMR_malara_2M2T.sh $m
        #source doDatacardsLMR_malara_2M2T.sh $m
        #./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done

