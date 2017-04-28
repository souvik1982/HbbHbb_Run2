mass=$1
cards=""
background="_new" # "" "_bern"
dirName="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit/LMR_${mass}${background}"
dcardName="datacard_${mass}${background}.txt" #conv bern
bgLogName="data_bkg.log"
Type="Crystal" #"Convolution" "Crystal" "GaussExp" "Bern"
datacardtype="background" #"Convolution" "bg" "background"
data_file="w_data_Crystal.root" #"w_background_Convolution.root" "w_background_Crystal.root" w_data.root w_background_Bern.root

sig_norm=`grep 'norm =' ${dirName}/index.html | awk '{print $3}'`    
jec_norm=`grep 'JEC       lnN' ${dirName}/index.html | awk '{print $3}'` 
jer_norm=`grep 'JER       lnN' ${dirName}/index.html | awk '{print $3}'`
btag_norm=`grep 'btag lnN' ${dirName}/index.html | awk '{print $3}'`
pdf_norm=`grep 'PDF lnN' ${dirName}/${pdfLogName} | awk '{print $3}'`

echo sig_norm ${sig_norm}
echo JEC ${jec_norm}
echo JER ${jer_norm}
echo bTag ${btag_norm}
echo PDF ${pdf_norm}

echo "norm"

bkg_norm=`grep ' Background number of events = ' ${dirName}/${bgLogName} | awk '{print $6}'`

#let's build a datacard!
cat > ${dirName}/${dcardName} <<EOF
imax 1 number of channels
jmax * number of backgrounds
kmax * number of systematic uncertainty sources
----------
shapes signal     HbbHbb w_signal_${mass}.root      HbbHbb:signal_fixed
shapes background HbbHbb w_background_$Type.root    HbbHbb:$datacardtype
shapes data_obs   HbbHbb $data_file      HbbHbb:data_obs
----------
## Observation
bin                     HbbHbb
observation             -1
----------
bin                   HbbHbb          HbbHbb
process               signal      background
process               0           1
rate                  ${sig_norm} ${bkg_norm}
lumi_13TeV  lnN   1.026       -     
JER       lnN     ${jer_norm}   - 
JEC       lnN     ${jec_norm}   -
trigger   lnN     1.10    -
EOF
#bgFloat   lnU     -          2.00
#PDF       lnN     ${pdf_norm}   -
#bTag      lnN     ${btag_norm}    -

#now add the systematics to the card
#grep 'signal_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}

#grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}

#grep 'bg_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
#grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}

#sed -i 's/crystalball_mean/bg_p2/g' ${dirName}/${dcardName}
#sed -i 's/crystalball_width/bg_p3/g' ${dirName}/${dcardName}
#sed -i 's/crystalball_switch/bg_p0/g' ${dirName}/${dcardName}
#sed -i 's/crystalball_exponent/bg_p1/g' ${dirName}/${dcardName}

cards+="${dirName}/${dcardName} "


