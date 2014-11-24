#!/bin/tcsh

##############
# This script creates a configuration file that uses the HcalClosureTest's dijet balancing reponse corrections for a reconstruction.
# To run this script, e.g., from the same directory it is in, do source ./makeRerecoConfig.csh <option 1> <option 2> <option 3>
# option 1 can be either "data" or "mc", option 2 is the Global Tag, which must be specified depending on the sample, and option 3 is the number of events to reconstruct
# example: source ./makeRerecoConfig.csh mc START53_V29A 7
##############

#get dijet balancing response corrections from the root file and format them into the correct format
python scriptingtools/dumprespcorrsandformat.py

#create a rereco config file without using new response corrections. user should change the below file to the one you want to reconstruct
cmsDriver.py reco -s RAW2DIGI,L1Reco,RECO --filein file:/eos/uscms/store/user/maravin/HCAL/singlePiPt50_9_REDIGI_DIGI_L1_DIGI2RAW_HLT_NOPU.root --fileout file:rereco.root --$1 --conditions ${2}::All --eventcontent RECO --datatier GEN-SIM-RECO -n $3 --no_exec

#edit the config file so that it rerecos using the dijet balancing response corrections 
cat reco_RAW2DIGI_L1Reco_RECO.py scriptingtools/useDumpedDijetRespcorrs.txt > reco_useDijetRespCorrs.py

#remove the config file that doesn't use the new response corrections
rm reco_RAW2DIGI_L1Reco_RECO.py

#make the scriptingtools be visible in the CMSSW_SEACH_PATH. user should change the directory to their own environment (security recommendation: don't put "." here)
setenv CMSSW_SEARCH_PATH ${CMSSW_SEARCH_PATH}:/uscms_data/d3/jhakala/cmssw/CMSSW_5_3_20/src/HcalClosureTest/Rereco

