#!/bin/sh

run="RunH"
#folder="VHBB_HEPPY_V24a_SingleMuon__Run2016G-PromptReco-v1/161010_142542/"
folder="VHBB_HEPPY_V25_SingleMuon__Run2016H-PromptReco-v2/170130_120108/"
#folder="VHBB_HEPPY_V24_BTagCSV__Run2016G-PromptReco-v1/160912_065427/"

for i in {1..1909}
#3820} # 2159 >90 
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
    root -b -l -q "TE_presel.cc(\"$run\", \"$folder\", \"$subfolder\", \"$file\" )"
done        

sfs=( 0000 0001 0002 ) #, "0001", "0002", "0003" }
out_L1=""

for f in $sfs
do
    name="SingleMuonSkimmed$f.root"    
    echo "Output file: $name"
    echo "Input files:"
    files=$(ls $run/$f)
    new_files=""
    for file in $files
    do 
   #     echo $file
        new_files="$new_files $run/$f/$file"
    done
    hadd -f $run/$name $new_files
    out_L1="$out_L1 $run/$name"
done

hadd -f "SingleMuonSkimmed$run.root" $out_L1


