import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("DUMP")
options = VarParsing.VarParsing ()

options.register ("tag",
                                    -1, # default value
                                    VarParsing.VarParsing.multiplicity.singleton,
                                    VarParsing.VarParsing.varType.string,
                                    "Tag to dump")
options.register ("acct",
                                    "CMS_COND_44X_HCAL", # default value
                                    VarParsing.VarParsing.multiplicity.singleton,
                                    VarParsing.VarParsing.varType.string,
                                    "Tag to dump")

options.register ("run",
                                    -1, # default value
                                    VarParsing.VarParsing.multiplicity.singleton,
                                    VarParsing.VarParsing.varType.int,
                                    "Run to dump (specifies IOV)")


# Get and parse the command line arguments
options.parseArguments()

# Set vars
vtag = options.tag
vacct = options.acct
vrun = options.run

# Get the record that corresponds to the tag

tag_fields = vtag.split("_")
vrecord = tag_fields[0]+"Rcd"

# Remove "Hcal" from front of tag_fields[0] for use as
# dumpstring.

dumpstring = ""
for j in range(4,len(tag_fields[0])):
         dumpstring = dumpstring+tag_fields[0][j]


         process.load("CondCore.DBCommon.CondDBSetup_cfi")

         process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
                                                       dump = cms.untracked.vstring(''),
                                                       file = cms.untracked.string('')
                                                   )

         process.prod = cms.EDAnalyzer("HcalDumpConditions",
                                           dump = cms.untracked.vstring(dumpstring),
                                           outFilePrefix = cms.untracked.string('Dump_')
                                       )

         process.source = cms.Source("EmptySource",
                                         numberEventsInRun = cms.untracked.uint32(2),
                                         firstRun = cms.untracked.uint32(vrun)
                                                                 )

         process.es_pool = cms.ESSource("PoolDBESSource",
                                            process.CondDBSetup,
                                            timetype = cms.string('runnumber'),
                                            toGet = cms.VPSet(
					      cms.PSet(
                         		        record = cms.string(vrecord),
                                     	        tag = cms.string(vtag)	 
                                 	      )
                                            ),
					      
					      connect = cms.string('frontier://FrontierProd/'+vacct)
                              		      #connect = cms.string('frontier://FrontierProd/CMS_COND_42X_HCAL')
                                              #    authenticationMethod = cms.untracked.uint32(0)
                                       )


         process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
         process.p = cms.Path(process.prod)

         #os.system("sleep 30; mv Dump_ChannelQuality_Run108686.txt Dump_Run108686.txt")
         

