import FWCore.ParameterSet.Config as cms

process = cms.Process("analysis")

#process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("FWCore.MessageService.MessageLogger_cfi")
#process.load("Configuration.StandardSequences.Services_cff")
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration/StandardSequences/FrontierConditions_GlobalTag_cff")
#process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")


#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.GeometryExtended_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.StandardSequences.Reconstruction_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
#process.load('Configuration/Geometry/GeometryRecoDB_cff')

#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.GeometryExtended_cff')
#process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
#process.load("Configuration.Geometry.GeometryIdeal_cff")
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.Geometry.GeometryDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.GlobalTag.globaltag = "101X_dataRun2_Prompt_v9"

#process.GlobalTag.globaltag = "76X_mcRun2_asymptotic_RunIIFall15DR76_v1"

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000))

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True),
IgnoreCompletely = cms.untracked.vstring('ProductNotFound'),
SkipEvent = cms.untracked.vstring('Error: uninitialized ProxyBase used') )

#sourcefile = 'list259431.txt'

#read input files from source file
#source = []
#with open(sourcefile,'r') as f:
#  lines = f.read().splitlines()
#  for i in lines :
#    source += ['root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259352/' + i]

#process.source = cms.Source("PoolSource", 
#      duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
#      fileNames = cms.untracked.vstring(source))
#process.source = cms.Source("PoolSource",
   #  replace 'myfile.root' with the source file you want to use
   # duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),


#USE THIS BLOCK FOR CONVENTIONAL FILE OPENING!===========
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
#'root://xrootd.unl.edu//store/relval/CMSSW_7_4_1/RelValQCD_FlatPt_15_3000HS_13/GEN-SIM-RECO/MCRUN2_74_V9_gensim_740pre7-v1/00000/5CC8BF5F-2FEC-E411-8011-0025905A48D6.root'
#'file:0228FAE3-200E-E511-BAA9-485B3919F0A3.root',
#'root://xrootd.unl.edu//store/mc/RunIISpring15DR74/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/GEN-SIM-RECO/AsymptNoPUbx25Reco_MCRUN2_74_V9-v3/00000/04B705C0-5407-E511-AB52-00A0D1EE8A20.root'	
#'file:/afs/cern.ch/work/e/ealvesco/Run2015/DAnalysisTotem/CMSSW_7_6_3/src/DStarD0/DStarD0Analysis/python/001496DA-0FD4-E511-9DA9-02163E00EB62.root'
#'file:4A06C225-70D4-E511-B2E8-D8D385AF8AEA.root'
'file:58D0D453-BB59-E811-9F78-1866DA7F9816.root'
	   )
)
#===================================================================



#readFiles = cms.untracked.vstring()
#secFiles = cms.untracked.vstring() 
#process.source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/RunIIFall15DR76/DStarToD0Pi_D0KPi_DStarFilter_TuneCUEP8M1_13TeV-pythia8-evtgen/AODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/001496DA-0FD4-E511-9DA9-02163E00EB62.root'))

#'/store/data/Run2015D/TOTEM_romanPotsTTBB_4/RECO/PromptReco-v4/000/258/922/00000/A8CBB406-4E73-E511-984B-02163E011B5C.root'
#'file:7A5BBA7A-46D1-E511-9AB1-0CC47A6C138A.root'
#'root://xrootd.unl.edu//store/mc/RunIIFall15DR76/MinBias_TuneMBReps08_13TeV-pythia8/GEN-SIM-RECO/25nsNoPUFSQ_castor_76X_mcRun2_asymptotic_v12-v1/60000/009805AB-0DD1-E511-B1EF-003048F5B614.root'
#'file:/afs/cern.ch/work/e/ealvesco/Run2015/CMSSW_7_6_3/src/DStarD0/DStarD0Analysis/python/reco_stream7_9_3AA70990-D978-E511-8B7C-02163E013690.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_12_607CAEE7-D778-E511-80A5-02163E0135CD.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_13_68D18625-D878-E511-87F2-02163E01374A.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_14_6A1ECBE7-D778-E511-8064-02163E01429B.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_15_76920EE8-D778-E511-8423-02163E013823.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_16_7EA042EE-D778-E511-8EF1-02163E0145AE.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_17_8263AE06-D878-E511-A2CD-02163E014241.root',
#''''root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_18_82A2D4E7-D778-E511-A75E-02163E0135BB.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_19_862802E5-D778-E511-87DD-02163E014612.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_1_0AD171F3-D778-E511-9EEE-02163E0142CF.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_20_8A4511F1-D778-E511-9DE0-02163E01469E.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_21_902506E4-D778-E511-A329-02163E01425A.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_22_9A1507F8-D778-E511-9C0B-02163E011F9B.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_23_9AB1DFE2-D778-E511-A027-02163E011F2E.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_24_9C06AC00-D878-E511-A2E6-02163E013471.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_25_A4200729-D878-E511-9AB1-02163E0142AC.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_26_B08E39FA-D778-E511-B9ED-02163E01434F.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_27_B631940A-D878-E511-BAB7-02163E014255.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_28_BCA162F1-D978-E511-80E4-02163E0144C1.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_29_C0CD75E7-D778-E511-9B2B-02163E014172.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_2_183B4FF8-D778-E511-800D-02163E014294.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_30_D2B094E2-D778-E511-A46D-02163E011922.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_31_D485B8E7-D778-E511-81DB-02163E0127EA.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_32_E06F68E2-D778-E511-A0E5-02163E014600.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_33_E4EF68EE-DD78-E511-8B17-02163E0146E9.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_34_E617FCFA-D778-E511-ADA6-02163E0145A3.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_35_E83DC4F6-D778-E511-9A5D-02163E013510.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_36_FE524EE7-D778-E511-B078-02163E01212E.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_3_267F94E3-D778-E511-BCF1-02163E0141C0.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_4_32D46DE5-D778-E511-B850-02163E0144D8.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_5_34973CED-D778-E511-93AC-02163E013858.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_6_38A128EE-D778-E511-BCCD-02163E013811.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_7_408000E4-D778-E511-94CB-02163E011AE4.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_8_5463A7E6-D778-E511-89A9-02163E01431E.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream0_9_56983BE9-D778-E511-818F-02163E0135E1.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_0_00A67523-DE78-E511-91FD-02163E0146E9.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_10_50236A53-D878-E511-9A3A-02163E0142C6.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_11_62823954-D878-E511-BBA8-02163E0138A0.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_12_64704FDA-D878-E511-A050-02163E014255.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_13_6E18E86C-D878-E511-B782-02163E014614.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_14_76883C50-D878-E511-9F3D-02163E011C0C.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_15_7EAF173C-D878-E511-8543-02163E0141B0.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_16_84CD296F-D878-E511-AC8A-02163E014498.root',
#'root://eostotem//eos/totem/data/cmstotem/2015/90m/CMS/RECO/TOTEM_romanPots2_X/Run259431/reco_stream1_17_8A35D54B-D878-E511-B154-02163E011B23.root'
#
#)
#)


process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskAlgoTrigConfig_cff')
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')

process.L1T1coll=process.hltLevel1GTSeed.clone()
process.L1T1coll.L1TechTriggerSeeding = cms.bool(True)
process.L1T1coll.L1SeedsLogicalExpression = cms.string('NOT (36 OR 37 OR 38 OR 39)')


process.trigger = cms.EDFilter("HLTHighLevel",
TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
  HLTPaths = cms.vstring('HLT_MinBias'), # provide list of HLT paths (or patterns) you want
  eventSetupPathsKey = cms.string(''),
  andOr              = cms.bool(True),
  throw              = cms.bool(False),
#  saveTags           = cms.bool(False)

)

#process.primaryVertexFilter = cms.EDFilter("VertexSelector",
#   src = cms.InputTag("offlinePrimaryVertices"),
#   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
#   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
#)

process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4) ,
                                           maxAbsZ = cms.double(24), 
                                           maxd0 = cms.double(2) 
                                           )

process.noscraping = cms.EDFilter("FilterOutScraping",
applyfilter = cms.untracked.bool(True),
debugOn = cms.untracked.bool(False),
numtrack = cms.untracked.uint32(10),
thresh = cms.untracked.double(0.25)
)

#process.DSD0filter = cms.EDFilter('DSD0filter')



process.analysis = cms.EDAnalyzer('DstarD0TTree',
    # Analysis
    doMC=cms.bool(True),
    doRec=cms.bool(True),
    tracks = cms.InputTag('generalTracks'),
    recVtxs = cms.InputTag('offlinePrimaryVertices'),
    #genParticles = cms.InputTag('genParticleCollection'),
	genParticles = cms.InputTag('genParticles'),
    ParticleFlowTag = cms.InputTag("particleFlow"),
    # PF thresholds
    #PFlowThresholds = cms.PSet(
    #Barrel = cms.PSet(
    #    hadronCharged = cms.PSet( pt = cms.double(0.0) ),
    #    hadronNeutral = cms.PSet( energy = cms.double(1.4) ),
    #    electron = cms.PSet( pt = cms.double(0.0) ),
    #    gamma = cms.PSet( energy = cms.double(0.9) )
    #),
    #Endcap = cms.PSet(
    #    hadronCharged = cms.PSet( pt = cms.double(0.0) ),
    #    hadronNeutral = cms.PSet( energy = cms.double(2.7) ),
    #    electron = cms.PSet( pt = cms.double(0.0) ),
    #    gamma = cms.PSet( energy = cms.double(2.5) )
    #),
    #Transition = cms.PSet(
    #    hadronCharged = cms.PSet( pt = cms.double(0.0) ),
    #    hadronNeutral = cms.PSet( energy = cms.double(3.8) ),
    #    electron = cms.PSet( pt = cms.double(0.0) ),
    #    gamma = cms.PSet( energy = cms.double(2.5) ),
    #    hadronHF = cms.PSet( energy = cms.double(4.0) ),
    #    emHF = cms.PSet( energy = cms.double(3.5) )
    #),
    #Forward = cms.PSet(
    #    hadronHF = cms.PSet( energy = cms.double(4.0) ),
    #    emHF = cms.PSet( energy = cms.double(3.5) )
    #)
   #),
    # Misc
    #energyThresholdHB = cms.double(1.5),
    #energyThresholdHE = cms.double(2.0),
    #energyThresholdHF = cms.double(4.0),
    # Options
    comEnergy = cms.double(13000.),
    #applyEnergyScaleHCAL = cms.bool(False),
    #energyScaleFactorHCAL = cms.double(1.0),
#    HLTPath = cms.string("HLT_L1_BscMinBiasOR_BptxPlusORMinus"), 
    HLTPath = cms.string("HLT_MinBias"),  
    TTBIt = cms.int32(34),
    SaveROOTTree = cms.untracked.bool(True)

)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('D0DstarMCAnalysis.root')
)
#process.p = cms.Path(process.noscraping+process.analysis)
#process.p = cms.Path(process.noscraping+process.analysis)
#TEST ----------------
#process.p = cms.Path(process.L1T1coll+process.trigger+process.noscraping+process.analysis)
#---------------------
#process.p = cms.Path(process.L1T1coll+process.trigger+process.primaryVertexFilter+process.noscraping+process.analysis)

process.p = cms.Path(process.primaryVertexFilter+process.noscraping+process.analysis)
