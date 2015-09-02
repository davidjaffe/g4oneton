#!/bin/bash 
#
# create a shootPmt.mac file to shoot optical photons at a PMT
# Arguments
# 1 = pmt#
# pmt# will be used to determine position and number of photons to shoot
#
#
#
# process inputs
pmtN=0
if [ $# -gt 0 ] ; then
    pmtN=$1
fi

nPhotons=`expr ${pmtN} + 1`

cfn=shootPmt.mac
echo "/gps/particle opticalphoton" > ${cfn}
echo "/gps/energy 3 eV"            >> ${cfn}
if [ ${pmtN} -lt 100 ] ; then
    echo "/gps/direction 0 0 -1"   >> ${cfn}
else
    echo "/gps/direction 0 0 1"    >> ${cfn}
fi
echo "/gps/polarization 0 0 1"     >> ${cfn}

## determine position
pN=`expr ${pmtN} % 100`
if [ ${pN} -eq 0 ] ; then
    pos="0 0 0"
elif [ ${pN} -eq 1 ] ; then
    pos="497.5 0 0 mm"
elif [ ${pN} -eq 2 ] ; then
    pos="-497.5 0 0 mm"
elif [ ${pN} -eq 3 ] ; then
    pos="0 497.5 0 mm"
elif [ ${pN} -eq 4 ] ; then
    pos="0 -497.5 0 mm"
fi
echo "/gps/position ${pos}" >> ${cfn}
   

echo "/run/beamOn ${nPhotons}"     >> ${cfn}
