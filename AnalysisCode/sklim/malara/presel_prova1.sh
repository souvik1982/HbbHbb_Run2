#!/bin/sh

source_dir="/gpfs/ddn/srm/cms/store/user"
folder=$source_dir"/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v1/170130_123051/"

TEST_PATH="/scratch/malara/WorkingArea/IO_file"
dest_dir="$TEST_PATH/output_file"

for i in {1..191}
do    
    if test $i -lt 1000 
        then subfolder="0000"
    elif test $i -lt 2000 
        then subfolder="0001"
    elif test $i -lt 3000
        then subfolder="0002"
    else 
        subfolder="0003"
    fi
    file="tree_"$i
    echo $folder$subfolder
    echo $dest_dir
    echo $file
    root -l -b -q "../../HbbHbb_PreSelection.cc++(\"$folder$subfolder\",\"$dest_dir\", \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"../PreselectedWithRegression/grav_all_upTo1400.xml\")"
done        

