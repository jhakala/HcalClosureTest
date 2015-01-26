import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYSIS')

process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.autoCond import autoCond
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.GlobalTag.globaltag=autoCond['startup']

#load the response corrections calculator
process.load('HcalClosureTest.Analyzers.calcrespcorrdijets_cfi')

# run over files

process.calcrespcorrdijets.rootHistFilename = cms.string('tree.root')
#process.calcrespcorrdijets.doCaloJets = cms.bool(False)
#process.calcrespcorrdijets.doPFJets = cms.bool(False)
#process.calcrespcorrdijets.doGenJets = cms.bool(False)
#process.calcrespcorrdijets.debug = cms.untracked.bool(True)
#process.calcrespcorrdijets.maxDeltaEta = cms.double(0.5)
process.calcrespcorrdijets.minJetEt = cms.double(10.)
process.calcrespcorrdijets.minSumJetEt = cms.double(0.0)
process.calcrespcorrdijets.maxThirdJetEt = cms.double(50.)

#import FWCore.Python.FileUtils as FileUtils
#readFiles = cms.untracked.vstring( FileUtils.loadListFromFile ('Pion_Pt-50.list') )
#process.source = cms.Source ("PoolSource",fileNames = readFiles)
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
        'file:/eos/uscms/store/user/dgsheffi/QCD_Pt-120To170_13TeV_0002E63C-FC89-E411-B8D6-003048FFCBA8.root'
        #'file:/uscms_data/d1/dgsheffi/HCal/001288D3-2AE3-E111-A943-0030487D5E5F.root'
))

#print readFiles

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery=cms.untracked.int32(100)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

# Load pfNoPileUP

#process.load("CommonTools.ParticleFlow.pfNoPileUp_cff")
#process.load("CommonTools.ParticleFlow.PF2PAT_cff")
#from RecoJets.JetProducers.ak5PFJets_cfi import *
#process.ak5PFJetsCHS = ak5PFJets.clone(
#    src = cms.InputTag("pfNoPileUp")
#    )
#process.load('HcalClosureTest.Analyzers.calcrespcorr_CHSJECs_cff')

# timing
#process.Timing = cms.Service('Timing')

#process.p = cms.Path(process.pfNoPileUpSequence+process.PF2PAT+process.ak5PFJetsCHS+process.calcrespcorrdijets)
process.p = cms.Path(process.calcrespcorrdijets)
