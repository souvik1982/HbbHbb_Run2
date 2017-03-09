#!/bin/sh

from=1
to=1989
source_dir="/gpfs/ddn/srm/cms/store/user"
folder=$source_dir"/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016B-23Sep2016-v3/170206_165040/"

dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2L2M/Data/Original/B_v_3"

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
    root -l -b -q "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_PreSelection_malara_Bv3_2L2M.cc++(\"$folder$subfolder\",\"$dest_dir\", \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/gravall-v25.weights.xml\")"
done

subfolder="0000"
root -l -b -q "../../countFile_2L2M.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", $from, 999)"
subfolder="0001"
root -l -b -q "../../countFile_2L2M.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", 1000, $to)"


