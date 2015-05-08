HcalClosureTest
===============

Code to calibrate CMS's HCAL in eta using dijet balance. Created by J. P. Chou (Brown) https://github.com/johnpaulchou/usercode/tree/master/HcalClosureTest and updated by David G. Sheffield (Rutgers).

Runs in CMSSW_5_3_18.

# Creating the tree

Running Analyzers/test/testRespCorrDiJets_cfg.py creates a tree containing the information needed for dijet balancing. It is set by default to run over CaloJets, PFJets, and GenJets. Any of these can be shut off by adding the lines

```
process.calcrespcorrdijets.doCaloJets = cms.bool(False)
process.calcrespcorrdijets.doPFJets   = cms.bool(False)
process.calcrespcorrdijets.doGenJets  = cms.bool(False)
```

When using PFJets, the dataset being run over must be RECO as AOD does not save the necessary PF block information. When using GenJets, the dataset must contain SIM information.

## Testing the results

The source code Analyzers/test/testRespCorrDiJetsTree.cc creates an executable CMSSW_5_3_18/test/slc5_amd64_gcc462/testRespCorrDiJetsTree that creates plots to validate the tree.

# Getting response corrections

The source code  DataFormat/test/runCaloJetCorr.cc creates an excecutable CMSSW_5_3_18/test/slc5_amd64_gcc462/runPFJetCorr that takes the tree and determines the response corrections.

## Testing the results

The source code DataFormat/test/testResponseCorr.cc creates an executable CMSSW_5_3_18/test/slc5_amd64_gcc462/testResponseCorr that creates plots of E<sub>reconstructed</sub>/E<sub>gen</sub> for response corrections of unity and response corrections found in the last step to compare their performance.

## Using the response corrections in re-reconstruction
The script Rereco/makeRerecoConfig.sh creates a cmssw configuration file that generates RECO from a RAW sample. To run it, copy the response corrections root file from the code into the Rereco directory, naming it 'DijetRespCorrs.root'. Then, cd to the Rereco directory and do:
 ./makeRerecoConfig.csh <1> <2> <3> <4> <5> <6>

option 1 can be either data or mc
option 2 is the file to be rereco'd
option 3 is the Global Tag, which must be specified depending on the sample
option 4 is the name of the tag corresponding to the HcalRespCorrsRcd of that global tag
option 5 is the run number (iod) for that tag
option 6 is the number of events to be reconstructed

example: ./makeRerecoConfig.sh data file:/my/data/file.root FT_53_V6C_AN4 HcalRespCorrs_v4.2_offline 189778 7 

To find the global tag go here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
Then click on the correct global tag to find the HcalRespCorrsRcd and the run number.
