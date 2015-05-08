#/bin/bash

echo -e import FWCore.ParameterSet.Config as cms$'\n'\
$'\n'\
process = cms.Process\(\"DUMP\"\)$'\n'\
process.load\(\"CondCore.DBCommon.CondDBSetup_cfi\"\)$'\n'\
process.load\(\"CondCore.DBCommon.CondDBCommon_cfi\"\)$'\n'\
process.load\(\"Configuration.Geometry.GeometryIdeal_cff\"\)$'\n'\
$'\n'\
process.maxEvents = cms.untracked.PSet\($'\n'\
    input = cms.untracked.int32\(1\)$'\n'\
\)$'\n'\
$'\n'\
process.source = cms.Source\(\"EmptySource\",$'\n'\
    numberEventsInRun = cms.untracked.uint32\(1\),$'\n'\
    firstRun = cms.untracked.uint32\($3\)$'\n'\
\)$'\n'\
$'\n'\
process.hcal_db_producer = cms.ESProducer\(\"HcalDbProducer\",$'\n'\
    dump = cms.untracked.vstring\(\'\'\),$'\n'\
    file = cms.untracked.string\(\'\'\)$'\n'\
\)$'\n'\
$'\n'\
process.es_pool = cms.ESSource\(\"PoolDBESSource\",$'\n'\
    process.CondDBSetup,$'\n'\
    timetype = cms.string\(\'runnumber\'\),$'\n'\
    toGet = cms.VPSet\($'\n'\
        cms.PSet\($'\n'\
            record = cms.string\(\"Hcal$1Rcd\"\),$'\n'\
            tag = cms.string\(\"$2\"\)$'\n'\
        \)\),$'\n'\
      connect = cms.string\(\'$4\'\),$'\n'\
  authenticationMethod = cms.untracked.uint32\(0\),$'\n'\
\)$'\n'\
$'\n'\
process.dumpcond = cms.EDAnalyzer\(\"HcalDumpConditions\",$'\n'\
       dump = cms.untracked.vstring\(\"$1\"\)$'\n'\
\)$'\n'\
process.p = cms.Path\(process.dumpcond\)$'\n'\
>temp_dump_cfg.py

cmsRun temp_dump_cfg.py

rm -f temp_dump_cfg.py

mv Dump${1}_Run${3}.txt scriptingtools/preexisting_RespCorrs.txt
