mass=$1
cards=""
dirName="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/LMR/fit/LMR_${mass}"
dcardName="datacard_${mass}.txt"
bgLogName="data_bkg.log"
sig_norm=`grep 'norm =' ${dirName}/index.html | awk '{print $3}'`    
Type="Crystal" #GaussExp
data_file="w_background_Crystal.root" #w_data.root 

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
shapes background HbbHbb w_background_$Type.root    HbbHbb:background
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
EOF
#bgFloat   lnU     -          2.00

#now add the systematics to the card
#grep 'signal_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}

#grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}

#grep 'bg_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
#grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
cards+="${dirName}/${dcardName} "


