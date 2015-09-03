#!/bin/bash 
#
# Run a job
# Arguments
# 1 = prefix for control file : gps_cosmic optPhoton
# 2 = string for output log, root files, control files
# 3 = number of events to generate
# 4 = relative Z position if cName is "shootPmt"
#
#
# process inputs
if [ $# -lt 1 ]; then
    echo "run_a_job.sh CONTROL_FILE_PREFIX STRING_FOR_OUTPUT_FILES NUMBER_OF_EVENTS"
    exit 22
fi
cName=$1
std_control_file=${cName}.mac
if [ ${cName} == "shootPmt" ] ; then
    rm ${std_control_file}
    relZ=1.
    if [ $# -gt 3 ] ; then
	relZ=$4
    fi
    ./shoot_Pmt.sh $3 ${relZ}
fi
if [ ! -f ${std_control_file} ]; then
    echo "control file ${std_control_file} does NOT EXIST. Check first argument"
    exit 33
fi
if [ $# -gt 1 ] ; then
    preName=$2
else
    preName=""
fi
nevts=10000
if [ $# -gt 2 ] ; then
    nevts=$3
fi
D="`date "+%Y%m%d_%H%M%S"`"
prefix=${preName}_${cName}_${D}
ofn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/output/${prefix}.root
lfn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/log/${prefix}.log
cfn=/Users/djaffe/work/GIT/G4ONETON/OneTon/OpNovice/control/${prefix}.mac
OUTPUT_ROOT_FILE=$ofn
export OUTPUT_ROOT_FILE
#
# create control file from standard file
echo "/control/verbose 2"           > ${cfn}
if [ ${nevts} -gt 0 ] ; then
    grep -v beamOn ${std_control_file} >> ${cfn}
    echo "/run/beamOn ${nevts}"        >> ${cfn}
else
    grep -v greasyGrimyGopherGuts ${std_control_file} >> ${cfn}
fi
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
#
# don't want this to persist
unset OUTPUT_ROOT_FILE
