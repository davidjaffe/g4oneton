#!/bin/bash 
#
# Start a cosmic muon job
# Arguments
# 1 = string for output log, root files, control files
# 2 = number of events to generate
#
std_control_file=gps_cosmic.mac
#
# process inputs
preName=$1
nevts=10000
if [ $# -gt 1 ] ; then
    nevts=$2
fi
D="`date "+%Y%m%d_%H%M%S"`"
prefix=${preName}_${D}
ofn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/output/${prefix}.root
lfn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/log/${prefix}.log
cfn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/control/${prefix}.mac
OUTPUT_ROOT_FILE=$ofn
export OUTPUT_ROOT_FILE
#
# create control file from standard file
echo "/control/verbose 2"           > ${cfn}
grep -v beamOn ${std_control_file} >> ${cfn}
echo "/run/beamOn ${nevts}"        >> ${cfn}
#
# report 
echo "Output root file ${OUTPUT_ROOT_FILE}"
echo "Log file ${lfn}"
echo "Control file ${cfn} Events to produce ${nevts}"
#
# add report to output file
echo "This is ${lfn}"                        > ${lfn}
echo "Output root file ${OUTPUT_ROOT_FILE}" >> ${lfn}
echo "Control file ${cfn}"                  >> ${lfn}
echo "Events to produce ${nevts}"           >> ${lfn}
echo "Begin Geant4 at `date`"               >> ${lfn}
#
# execute the suck
./OpNovice -m ${cfn} >> ${lfn} 2>&1 < /dev/null 
echo "Begin analysis at `date`"               >> ${lfn}

#
# run python analysis job
echo "python ../python/oneton.py ${ofn}>> ${lfn} 2>&1 < /dev/null " >> ${lfn}
python ../python/oneton.py ${ofn}>> ${lfn} 2>&1 < /dev/null
echo "Job completed at `date`"               >> ${lfn}

