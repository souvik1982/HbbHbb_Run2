#!/bin/sh

from=1
to=1552
source_dir="/gpfs/ddn/srm/cms/store/user"
folder=$source_dir"/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016G-23Sep2016-v1/170206_164902/"

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

root -l -b -q "../../countFile.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", $from, $to)"
