from QFramework import *
from ROOT import *

from CAFExample import HWWEventWeight

import os
workdir = ""
if os.getenv("ROOTCOREBIN") :
    workdir = os.getenv("ROOTCOREBIN")
    pass
workdir = workdir.rsplit('RootCoreBin', 1)[0]

def addObservables(config):

    ## Which PxAOD version are we working on
    inputVersion = config.getTagDoubleDefault("InputVersion", 12)

    ## Getting lepton quality working points from config
    electronID = config.getTagStringDefault("ElectronID", "MediumLH")
    electronIDLowPt = config.getTagStringDefault("ElectronIDLowPt", "TightLH")
    muonQuality = config.getTagStringDefault("MuonQuality", "Medium")
    muonQualityLowPt = config.getTagStringDefault("MuonQualityLowPt", "Tight")
    electronIsoLowPt = "IsoGradient"
    if inputVersion > 16:
        electronIsoLowPt = "IsoFixedCutTrackCone40"

    ## Some options for testing
    usePRWTool = config.getTagBoolDefault("UsePRWTool", True)
    useOldTrigWeight = config.getTagBoolDefault("UseOldTrigWeight", True)
    doMCWeightOnly = config.getTagBoolDefault("DoMCWeightOnly", False)

    ## Switches for SFs
    useMuonTTVASF = config.getTagBoolDefault("UseMuonTTVASF", True)

    ## Switches for ttbar NNLO reweighting
    useTTbarNNLORW = config.getTagBoolDefault("UseTTbarNNLORW", False)

    ## For now enforce not using the PRW tool for PAOD versions >= 11
    if usePRWTool and inputVersion > 9:
        INFO("Using the PRW tool with PAOD versions >= 11 currently not supported, switching it off (i.e. using weights from input file)")
        usePRWTool = False
        pass

    if useOldTrigWeight and inputVersion > 11:
        INFO("Using the old trigger weight evaluation with PAOD versions >= 11 not possible anymore, switching to new one")
        useOldTrigWeight = False
        pass

    ## Scaling factor to be applied to data mu in PRW tool
    prwDataScaleFactorNominal = 1./1.09 ### was 1.16
    prwDataScaleFactorDown = 1./1.23
    prwDataScaleFactorUp = 1./1.09
    ## Config files for PRW tool
    confFile  = workdir+"HWWDualUseUtils/data/PRW/mc15ab_defaults.NotRecommended.prw.root"
    lCalcFile = workdir+"HWWDualUseUtils/data/PRW/ilumicalc_histograms_None_276262-284484_v73.root"


    sfsystematics =config.getTagVString("xAODsfSystematics")
    sfsystematics.push_back( 'nominal' )

    for var in sfsystematics:
        if not var or len(var)<1: continue
        prwVarName = "PileupWeight"
        variation = str(var)
        ## Creating weight observable, as default only MC generator weights are considered
        WeightObs = HWWEventWeight("Weight_"+variation+":$(cand)")
        #WeightObs.setExpression(TString("Weight_"+variation+":$(cand)")) #should be done automatically in the ctor of HWWEventWeight

        prwDataScaleFactor = prwDataScaleFactorNominal

        # take care of sf systematics, needs to be done before the SF names are set
        ok = False
        print variation
        # error message when trying to use old namings for pileup weights
        if variation == "$(weightname)" or variation == "nominal":
            # this is "nominal" or any p4 variation
            # nothing to do here
            ok = True
            pass
        elif "EFF" in variation or "MUON_ISO" in variation or "MUON_TTVA" in variation or "PRW" in variation or "JvtEff" in variation:
            varEnum = HWWEventWeight.NoVar
            if "MUON_" in variation:
                if "Trig" in variation   : varEnum = HWWEventWeight.MuonTrig
                elif "ISO" in variation  : varEnum = HWWEventWeight.MuonIso
                elif "EFF" in variation  : varEnum = HWWEventWeight.MuonReco
                elif "TTVA" in variation : varEnum = HWWEventWeight.MuonTTVA
            elif "EL_" in variation:
                if "Reco" in variation   : varEnum = HWWEventWeight.EleReco
                elif "ID" in variation   : varEnum = HWWEventWeight.EleID
                elif "Trig" in variation : varEnum = HWWEventWeight.EleTrig
                elif "Iso" in variation  : varEnum = HWWEventWeight.EleIso
            elif "FT_" in variation:
                varEnum = HWWEventWeight.Btag
            elif "PRW" in variation:
                varEnum = HWWEventWeight.PU
                prwVarName = "PileupWeight___"+variation
            elif "fJvtEff" in variation and inputVersion > 9 :
                varEnum = HWWEventWeight.FJVT
                if "_1down" in variation:
                    variation = "JET_JvtEfficiency__1down"  # need to change naming to match with PAODs
                elif "_1up" in variation:
                    variation = "JET_JvtEfficiency__1up"   # need to change naming to match with PAODs
                else:
                    ERROR("encountered fJvt variation of unknown type: '{:s}'".format(variation))
            elif "JvtEff" in variation and inputVersion > 9 :
                varEnum = HWWEventWeight.JVT
            else:
                ERROR("encountered scale factor efficiency variation of unknown type: '{:s}'".format(variation))

            if varEnum != HWWEventWeight.NoVar:
                ok = True
                WeightObs.setVariation(varEnum,variation)
        elif "PU_" in variation:
            BREAK("Encountered PU scale factor variation of unknown type: '{:s}'. This is probably due to an outdated naming convention. If your naming includes PU_SF, use PRW_DATASF instead!".format(variation))
        elif "qcd_wg1_" in variation:
            varEnum = HWWEventWeight.ggFQCDscale
            #if "mig01" in variation:
            #  varEnum = HWWEventWeight.ggFQCDscale01
            #elif "mig12" in variation:
            #  varEnum = HWWEventWeight.ggFQCDscale12
            #elif "mu" in variation:
            #  varEnum = HWWEventWeight.ggFQCDscalemu
            #if varEnum != HWWEventWeight.NoVar:
            ok = True
            WeightObs.setVariation(varEnum,variation)
        else:
            ERROR("encountered scale factor variation of unknown type: '{:s}'".format(variation))
            pass

        ## Switching on the various weights and setting variable names according to config input
        WeightObs.doMCWeight(True) # This is set to true per default
        if doMCWeightOnly:
            WeightObs.doMCWeightOnly(True) # This is set only for truth samples 
        WeightObs.doLepWeight("effiSFRecoTrk", "effiSF"+str(muonQuality), "effiSF"+str(muonQualityLowPt))
        WeightObs.doElectronIDWeight("effiSF"+str(electronID), "effiSF"+str(electronIDLowPt))
        WeightObs.doElectronIsoWeight("effiSFIsoGradient_wrt"+str(electronID), "effiSF"+str(electronIsoLowPt)+"_wrt"+str(electronIDLowPt))
        WeightObs.doMuonIsoWeight()
        if useMuonTTVASF: WeightObs.doMuonTTVAWeight()
        if useTTbarNNLORW: WeightObs.doTTbarNNLOWeight()
        if not usePRWTool and inputVersion > 9:
            WeightObs.doPRWWeight(prwVarName)
        else:
            WeightObs.doPRWWeight(confFile, confFile, lCalcFile, prwDataScaleFactor)
            pass
        if not useOldTrigWeight and inputVersion > 9:
            if inputVersion < 12:
                WeightObs.doElectronTrigEffWeight("effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronIDLowPt)+"IsoGradient",
                                                  "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronIDLowPt)+"IsoGradient")
                WeightObs.doMuonTrigEffWeight("effiTrig_wrt"+str(muonQuality)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                                              "effiTrig_wrt"+str(muonQualityLowPt)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                                              "effiSFTrig_wrt"+str(muonQuality)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                                              "effiSFTrig_wrt"+str(muonQualityLowPt)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50")
            else:
                INFO("trigger SF applied: ele --> postICHEP flag, muon --> using RunNumber for assigning the correct TrigSF")
                WeightObs.doElectronTrigEffWeight("effiTrig_singleEl_preICHEP_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiTrig_singleEl_preICHEP_wrtOffline_"+str(electronIDLowPt)+"IsoGradient",
                                                  "effiSFTrig_singleEl_preICHEP_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiSFTrig_singleEl_preICHEP_wrtOffline_"+str(electronIDLowPt)+"IsoGradient",
                                                  "effiTrig_singleEl_postICHEP_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiTrig_singleEl_postICHEP_wrtOffline_"+str(electronIDLowPt)+"IsoGradient",
                                                  "effiSFTrig_singleEl_postICHEP_wrtOffline_"+str(electronID)+"IsoGradient",
                                                  "effiSFTrig_singleEl_postICHEP_wrtOffline_"+str(electronIDLowPt)+"IsoGradient")
                WeightObs.doMuonTrigEffWeight("effiTrig_wrt"+str(muonQuality)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu24_ivarmedium_OR_mu50",
                                              "effiTrig_wrt"+str(muonQualityLowPt)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu24_ivarmedium_OR_mu50",
                                              "effiSFTrig_wrt"+str(muonQuality)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu24_ivarmedium_OR_mu50",
                                              "effiSFTrig_wrt"+str(muonQualityLowPt)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu24_ivarmedium_OR_mu50",
                                              "effiTrig_wrt"+str(muonQuality)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu26_ivarmedium_OR_mu50",
                                              "effiTrig_wrt"+str(muonQualityLowPt)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu26_ivarmedium_OR_mu50",
                                              "effiSFTrig_wrt"+str(muonQuality)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu26_ivarmedium_OR_mu50",
                                              "effiSFTrig_wrt"+str(muonQualityLowPt)+"_2015_mu20_iloose_L1MU15_OR_mu50_2016_mu26_ivarmedium_OR_mu50")
                pass
        else:
            WeightObs.doElectronTrigWeight("effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronID)+"IsoGradient",
                                           "effiSFTrig_e24_lhmedium_L1EM20VH_OR_e60_lhmedium_OR_e120_lhloose_wrtOffline_"+str(electronIDLowPt)+"IsoGradient")
            WeightObs.doMuonTrigWeight("effiSFTrig_wrt"+str(muonQuality)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50",
                                       "effiSFTrig_wrt"+str(muonQualityLowPt)+"_HLT_mu20_iloose_L1MU15_OR_HLT_mu50")
            pass

        if inputVersion > 9 and inputVersion < 16:
            WeightObs.doJVTWeight("effiSFJVT") # no forward JVT SFs
            pass
        if inputVersion > 15:
            WeightObs.doJVTWeight("effiSFJVT")
            WeightObs.doForwardJVTWeight("effiSFForwardJVT")


        ## Uncomment only if you want to include the btagging efficiency SFs in the main weight observable
        # WeightObs.doBtagWeight(config.getTagBoolDefault("useSubThresholdBTagWeights",True), "effiSF")

        ## Add the observable to the list of observables
        if not ok or not TQTreeObservable.addObservable(WeightObs):
            WARN("failed to add weight observable for variation '{:s}'".format(variation))
            return False
        #INFO("adding weights for variation '{:s}' as '{:s}' with expression '{:s}'".format(variation,WeightObs.GetName(),WeightObs.getExpression().Data()))

    return True

