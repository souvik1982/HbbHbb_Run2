#!/bin/sh

from=501
to=999
source_dir="/gpfs/ddn/srm/cms/store/user"
folder=$source_dir"/anmalara/VHBBHeppyV25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016G-23Sep2016-v1/170206_164902/"

dest_dir="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV2M2T/Data/Original/G_v_1"

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
    root -l -b -q "/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/HbbHbb_PreSelection_malara_Gv1_2M2T_2.cc++(\"$folder$subfolder\",\"$dest_dir\", \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"/scratch/malara/WorkingArea/HbbHbb_Run2/AnalysisCode/PreselectedWithRegression/gravall-v25.weights.xml\")"
done

subfolder="0000"
root -l -b -q "../../countFile.cc++(\"$folder$subfolder\", \"$dest_dir\",\"tree_\", $from, $to)"


