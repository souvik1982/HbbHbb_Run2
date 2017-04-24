mass=$1
cards=""
dirName="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/MMR/fit/MMR_${mass}"
dcardName="datacard_${mass}.txt" #conv bern
bgLogName="data_bkg.log"
sig_norm=`grep 'norm =' ${dirName}/index.html | awk '{print $3/10}'`    
Type="Crystal" #"Convolution" "Crystal" #GaussExp
datacardtype="background" #"Convolution" "background"
data_file="w_background_Convolution.root" #"w_background_Crystal.root" #w_data.root 

echo ${sig_norm}
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
shapes data_obs   HbbHbb $data_file                 HbbHbb:data_obs
----------
## Observation
bin                     HbbHbb
observation             -1
----------
bin                   HbbHbb          HbbHbb
process               signal      background
process               0           1
rate                  ${sig_norm} ${bkg_norm}
lumi_13TeV  lnN   1.062       -     
bTag      lnN     1.10    -
trigger   lnN     1.10    -
bgFloat   lnU     -          1.80
EOF
#bgFloat   lnU     -          2.00

#now add the systematics to the card
#grep 'signal_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}

#grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
#grep 'param' ${dirName}/${bgLogName}  >> ${dirName}/${dcardName}

#grep 'bg_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
#grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}

sed -i 's/crystalball_mean/bg_p2/g' ${dirName}/${dcardName}
sed -i 's/crystalball_width/bg_p3/g' ${dirName}/${dcardName}
sed -i 's/crystalball_switch/bg_p0/g' ${dirName}/${dcardName}
sed -i 's/crystalball_exponent/bg_p1/g' ${dirName}/${dcardName}

cards+="${dirName}/${dcardName} "


