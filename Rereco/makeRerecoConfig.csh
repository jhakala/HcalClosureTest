#!/bin/tcsh

##############
# This script creates a configuration file that uses the HcalClosureTest's dijet balancing reponse corrections for a reconstruction.
#
# To run this script, e.g., from the same directory it is in, do source ./makeRerecoConfig.csh <1> <2> <3> <4> <5> <6>
#
# option 1 can be either "data" or "mc"
# option 2 is the file to be rereco'd
# option 3 is the Global Tag, which must be specified depending on the sample
# option 4 is the name of the tag corresponding to the HcalRespCorrsRcd of that global tag
# option 5 is the run number (iod) for that tag
# option 6 is the number of events to be reconstructed
# 
# example: source ./makeRerecoConfig.csh data /my/data/file.root FT_53_V6C_AN4 HcalRespCorrs_v4.2_offline 189778 7 
#
# To find the global tag go here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
# Then click on the correct global tag to find the HcalRespCorrsRcd and the run number.
#
# If scriptingtools isn't found, make sure CMSSW_SEARCH_PATH is pointing to the right place. You need to edit this script accordingly.
##############

echo "\n Beginning creation of a rereco config file implementing dijet balancing response corrections. \n \n"

#dump the preexisting response corrections from the conddb
cmsRun scriptingtools/dump_conditions.py tag=$4 run=$5 acct=CMS_COND_31X_HCAL
echo "\n Preexisting response corrections dumped. \n \n"

#move the dumped respcorrs into the correct file in the scriptingtools directory
mv Dump_RespCorrs_Run${5}.txt scriptingtools/preexisting_RespCorrs.txt
echo "\n Dumped response corrections moved into place. \n \n"

#get dijet balancing response corrections from the root file and format them into the correct format
python scriptingtools/dumprespcorrsandformat.py
echo "\n Created the updated response corrections. \n \n"

#create a rereco config file without using new response corrections. user should change the below file to the one you want to reconstruct
cmsDriver.py reco -s RAW2DIGI,L1Reco,RECO --filein file:${2} --fileout file:rereco.root --$1 --conditions ${3}::All --eventcontent RECO --datatier GEN-SIM-RECO -n $6 --no_exec
echo "\n Created a rereco config file. Not yet modified to use updated response correctons. \n \n"

#edit the config file so that it rerecos using the dijet balancing response corrections 
cat reco_RAW2DIGI_L1Reco_RECO.py scriptingtools/useDumpedDijetRespcorrs.txt > reco_useDijetRespCorrs.py
echo "\n Created a modified rereco config file that uses the updated response corrections. \n \n"

#remove the config file that doesn't use the new response corrections
rm reco_RAW2DIGI_L1Reco_RECO.py
echo "\n Removed the rereco config file that doesn't use the updated response corrections. \n \n"

#make the scriptingtools be visible in the CMSSW_SEACH_PATH. user should change the directory to their own environment (security recommendation: don't put "." here)
setenv CMSSW_SEARCH_PATH ${CMSSW_SEARCH_PATH}:/uscms_data/d3/jhakala/cmssw/CMSSW_5_3_20/src/HcalClosureTest/Rereco
echo " \n Changed the CMSSW search path. \n \n"
