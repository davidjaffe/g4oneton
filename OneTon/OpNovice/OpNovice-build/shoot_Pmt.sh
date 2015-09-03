#!/bin/bash 
#
# create a shootPmt.mac file to shoot low energy electrons at a PMT
# Arguments
# 1 = pmt#
# pmt# will be used to determine position and number of electrons to shoot
# 2 = relative position in z (0,1)
#
# process inputs
pmtN=0
if [ $# -gt 0 ] ; then
    pmtN=$1
fi
relZ=1.0
if [ $# -gt 1 ] ; then
    relZ=$2
fi

nElectrons=`expr ${pmtN} + 1`

# output mac file
cfn=shootPmt.mac

# eliminate annoying optical photon messages at every boundary
cat No_Optical_Messages.mac >> ${cfn}

# verbose tracking info
####echo "/tracking/verbose 1" >> ${cfn}

# particle info: type, energy, direction, position
echo "/gps/particle e-" >> ${cfn}
#
# max energy for 137Cs compton electron
echo "/gps/energy 478. keV"            >> ${cfn}
if [ ${pmtN} -lt 100 ] ; then
    echo "/gps/direction 0 0 -1"   >> ${cfn}
else
    echo "/gps/direction 0 0 1"    >> ${cfn}
fi
echo "/gps/polarization 0 0 1"     >> ${cfn}

## determine position (centered on PMT in radius, ~1" from top or bottom of liquid volume
## pmtRad = 497.5/2 mm
## |zElectron| = 625 - 25 mm
pN=`expr ${pmtN} % 100`
if [ ${pmtN} -lt 100 ] ; then
    zE=-600.
else
    zE=600.
fi
zE=`echo "${zE}*${relZ}" | bc -l`
pmtRad=248.75
if [ ${pN} -eq 0 ] ; then
    pos="0 0 ${zE} mm"
elif [ ${pN} -eq 1 ] ; then
    pos="${pmtRad} 0 ${zE} mm"
elif [ ${pN} -eq 2 ] ; then
    pos="-${pmtRad} 0 ${zE} mm"
elif [ ${pN} -eq 3 ] ; then
    pos="0 ${pmtRad} ${zE} mm"
elif [ ${pN} -eq 4 ] ; then
    pos="0 -${pmtRad} ${zE} mm"
fi
echo "/gps/position ${pos}" >> ${cfn}
   

echo "/run/beamOn ${nElectrons}"     >> ${cfn}
