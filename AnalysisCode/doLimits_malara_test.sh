#!/bin/bash

function show_help { 
    echo "./doLimits_malara.sh [-c to clean up] [-d debug combine]" 
}

massesLMR=(
260
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

