#!/bin/bash

function show_help { 
    echo "./doLimits.sh [-c to clean up] [-d debug combine]" 
}

masses=(
   #400 450 500 550 600 650 700 750 800 900 1000 1200
   400 
)
massesLMR=(
    #260 270 300 350 400 450 500 
    300 
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
        source doBuildInputs.sh $m
        source doDatacards.sh $m
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
        source doBuildInputsLMR.sh $m
        source doDatacardsLMR.sh $m
        #./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done

