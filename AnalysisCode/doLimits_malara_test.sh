#!/bin/bash

function show_help { 
    echo "./doLimits_malara.sh [-c to clean up] [-d debug combine]" 
}

massesLMR=(
#270 300 350 400 450 500 550 600 650
#260 270 300 350
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

for m in ${massesLMR[@]}
do
    if [ $cleanUp -eq 0 ]; then
	echo  'LMR'
        source doBuildInputsLMR_malara_test.sh $m
        source doDatacardsLMR_malara_test.sh $m
        #./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done




massesMMR=(
#450 500 550 600 650 750
500 550 600 650 750 800 900 1000
#260 270 300 350
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

for m in ${massesMMR[@]}
do
    if [ $cleanUp -eq 0 ]; then
        echo  'MMR'
        source doBuildInputs_malara_test.sh $m
        source doDatacards_malara_test.sh $m
        #./runLimits.sh $debug $m
    fi

    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done
