#!/bin/sh

run="RunHv3"
#folder="VHBB_HEPPY_V24_JetHT__Run2016B-PromptReco-v2/160910_205020/"
#folder="VHBB_HEPPY_V24_JetHT__Run2016B-PromptReco-v2/160912_07022/"
folder="/eos/uscms/store/user/lpchbb/HeppyNtuples/V25/BTagCSV/VHBB_HEPPY_V25_BTagCSV__Run2016H-PromptReco-v3/170206_164802/"
mkdir $run
for i in {1..46}
do    
    if test $i -lt 1000 
        then subfolder="0000/"
    elif test $i -lt 2000 
        then subfolder="0001/"
    elif test $i -lt 3000
        then subfolder="0002/"
    else 
        subfolder="0003/"
    fi
    file="tree_"$i
    echo $folder$subfolder
    ln -s ../../HbbHbb_PreSelection.cc .
    #cd $run
#    root -b -l -q "TE_presel.cc(\"$run\", \"$folder\", \"$subfolder\", \"$file\" )"
    root -l -b -q "HbbHbb_PreSelection.cc++(\"$folder$subfolder\",  \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"/uscms_data/d3/cvernier/4b/HbbHbb_2016/HbbHbb_Run2/AnalysisCode//gravall-v25.weights.xml\")"
    cd $run
#    root -b -l -q "TE_presel.cc(\"$run\", \"$folder\", \"$subfolder\", \"$file\" )"
    #root -l -b -q "../../HbbHbb_PreSelection.cc++(\"$folder$subfolder\",  \"$file\",\"JEC\",\"JER\",\"Trig\",\"bTag\",\"../grav_all_upTo1400.xml\")"
done        


#sfs="0000 0001 0002 0003"
#out_L1=""

#for f in $sfs
#do
#    name="SingleMuonSkimmed$f.root"    
#    echo "Output file: $name"
#    echo "Input files:"
#    files=$(ls $run/$f)
#    new_files=""
#    for file in $files
#    do 
   #     echo $file
#        new_files="$new_files $run/$f/$file"
#    done
#    hadd -f $run/$name $new_files
#    out_L1="$out_L1 $run/$name"
#done

#hadd -f "SingleMuonSkimmed$run.root" $out_L1


