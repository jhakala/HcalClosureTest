#!/bin/bash

##############
# This script creates a configuration file that uses the HcalClosureTest's dijet balancing reponse corrections for a reconstruction.
#
# To run this script, e.g., from the same directory it is in, do:  ./makeRerecoConfig.csh <1> <2> <3> <4> <5> <6>
#
# option 1 can be either "data" or "mc"
# option 2 is the file to be rereco'd
# option 3 is the Global Tag, which must be specified depending on the sample
# option 4 is the name of the tag corresponding to the HcalRespCorrsRcd of that global tag
# option 5 is the run number (iod) for that tag
# option 6 is the number of events to be reconstructed
# 
# example: source ./makeRerecoConfig.sh data file:/my/data/file.root FT_53_V6C_AN4 HcalRespCorrs_v4.2_offline 189778 7 
#
# To find the global tag go here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
# Then click on the correct global tag to find the HcalRespCorrsRcd and the run number.
##############

echo -e "\n--> Beginning creation of a rereco config file implementing dijet balancing response corrections."

#dump the preexisting response corrections from the conddb
scriptingtools/makedump2.sh RespCorrs $4 $5 frontier://FrontierProd/CMS_CONDITIONS
if [ $? =  0  ];  then
	echo -e "\n--> Preexisting response corrections dumped."
else
	echo -e "\n--> Error dumping preexisting respcorrs."
	exit 0
fi

#get dijet balancing response corrections from the root file and format them into the correct format
python scriptingtools/dumprespcorrsandformat.py
if [ $? =  0  ];  then
	echo -e "\n--> Created the updated response corrections."
else
	echo -e "\n--> Error creating updated response corrections."
	exit 0
fi

#create a rereco config file without using new response corrections. user should change the below file to the one you want to reconstruct
cmsDriver.py reco -s RAW2DIGI,L1Reco,RECO --filein ${2} --fileout file:rereco.root --$1 --conditions ${3} --eventcontent RECO --datatier GEN-SIM-RECO -n $6 --processName PRIVATERECO --no_exec
if [ $? =  0  ];  then
	echo -e "\n--> Created a rereco config file. Not yet modified to use updated response correctons."
else
	echo -e "\n--> Error creating rereco config file."
	exit 0
fi

#edit the config file so that it rerecos using the dijet balancing response corrections 
cat reco_RAW2DIGI_L1Reco_RECO.py scriptingtools/useDumpedDijetRespcorrs.txt > reco_useDijetRespCorrs.py
if [ $? =  0  ];  then
	echo -e "\n--> Created a modified rereco config file that uses the updated response corrections."
else
	echo -e "\n--> Error modifying rereco config file to use new respcorrs."
	exit 0
fi

#remove the config file that doesn't use the new response corrections
rm reco_RAW2DIGI_L1Reco_RECO.py
if [ $? =  0  ];  then
	echo -e "\n--> Removed the temporary rereco config file (without updated response corrections)."
else
	echo -e "\n--> Error removing the temporary rereco config file."
	exit 0
fi

rm scriptingtools/preexisting_RespCorrs.txt 
if [ $? =  0  ];  then
	echo -e "\n--> Removed the preexisting response correction file."
else
	echo -e "\n--> Error removing tpreexisting response correction file."
	exit 0
fi

