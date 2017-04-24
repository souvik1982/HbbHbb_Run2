mass=$1
cards=""
dirName="LMR_${mass}"
dcardName="datacard_${mass}.txt"
bgLogName="data_bkg.log"
pdfLogName="pdf.log"
sig_norm=`grep 'norm =' ${dirName}/signal${mass}_sig.log | awk '{print $3}'`    
jec_norm=`grep 'JEC       lnN' ${dirName}/signal${mass}_sig.log | awk '{print $3}'` 
jer_norm=`grep 'JER       lnN' ${dirName}/signal${mass}_sig.log | awk '{print $3}'`
btag_norm=`grep 'bTag lnN' ${dirName}/signal${mass}_sig.log | awk '{print $3}'`
pdf_norm=`grep 'PDF lnN' ${dirName}/${pdfLogName} | awk '{print $3}'`

echo ${sig_norm}
echo ${jec_norm}
echo ${jer_norm}
echo ${btag_norm}
echo ${pdf_norm}
echo "norm"

bkg_norm=`grep ' Background number of events = ' ${dirName}/${bgLogName} | awk '{print $6}'`

#let's build a datacard!
cat > ${dirName}/${dcardName} <<EOF
imax 1 number of channels
jmax * number of backgrounds
kmax * number of systematic uncertainty sources
----------
shapes signal     HbbHbb w_signal_${mass}.root      HbbHbb:signal_fixed
shapes background HbbHbb w_background_Crystal.root HbbHbb:background
shapes data_obs   HbbHbb w_data.root                HbbHbb:data_obs
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
bTag      lnN     ${btag_norm}    -
JER       lnN     ${jer_norm}   - 
JEC       lnN     ${jec_norm}   -
PDF	  lnN 	  ${pdf_norm}   -
trigger   lnN     1.10    - 
EOF


#now add the systematics to the card
#grep 'signal_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}
#grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
#grep 'bg_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
#grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
cards+="${dirName}/${dcardName} "


