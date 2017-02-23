#!/bin/sh

from=1
to=2018
source_dir="/gpfs/ddn/srm/cms/store/user"
folder=$source_dir"/cvernier/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v2/170130_123206/"

TEST_PATH="/scratch/malara/WorkingArea/IO_file"
dest_dir="$TEST_PATH/output_file"

for (( i=$from; i<=$to; i++ ))
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
    echo $file
    #root -l -b -q "../../HbbHbb_PreSelection.cc++(\"$folder$subfolder\",\"$dest_dir\", \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"../../PreselectedWithRegression/grav_all_upTo1400.xml\")"
done

subfolder="0000"
root -l -b -q "../../countFile.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", $from, 999)"
subfolder="0001"
root -l -b -q "../../countFile.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", 1000, 1999)"
subfolder="0002"
root -l -b -q "../../countFile.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", 2000, $to)"


