from QFramework import *
from ROOT import *

def addObservables(config):

    #############################
    ## loose ID:  idwp = 1     ##
    ## medium ID: idwp = 2     ##
    ## tight ID:  idwp = 3     ##
    ## no Iso: isowp = 0       ##
    #############################
    ## loose Iso: isowp = 10   ## 
    ## tight Iso: isowp = 100  ##
    ## GradientLoose Iso: 1000 ## 
    ## Gradient Iso: 10000     ##
    #############################
    
    ## looseIso
    #mySF_v05_lep0tightIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep0tightIdlooseIso", 3,10,0)
    #if not TQTreeObservable.addObservable(mySF_v05_lep0tightIdlooseIso):
    #    INFO("failed to add mySF_v05_lep0tightIdlooseIso observable")
    #    return False
    #
    #mySF_v05_lep1tightIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep1tightIdlooseIso", 3,10,1)
    #if not TQTreeObservable.addObservable(mySF_v05_lep1tightIdlooseIso):
    #    INFO("failed to add mySF_v05_lep1tightIdlooseIso observable")
    #    return False
    #
    #mySF_v05_lep0mediumIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep0mediumIdlooseIso", 2,10,0)
    #if not TQTreeObservable.addObservable(mySF_v05_lep0mediumIdlooseIso):
    #    INFO("failed to add mySF_v05_lep0mediumIdlooseIso observable")
    #    return False
    #
    #mySF_v05_lep1mediumIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep1mediumIdlooseIso", 2,10,1)
    #if not TQTreeObservable.addObservable(mySF_v05_lep1mediumIdlooseIso):
    #    INFO("failed to add mySF_v05_lep1mediumIdlooseIso observable")
    #    return False
    #
    #mySF_v05_lep0looseIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep0looseIdlooseIso", 1,10,0)
    #if not TQTreeObservable.addObservable(mySF_v05_lep0looseIdlooseIso):
    #    INFO("failed to add mySF_v05_lep0looseIdlooseIso observable")
    #    return False
    #
    #mySF_v05_lep1looseIdlooseIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep1looseIdlooseIso", 1,10,1)
    #if not TQTreeObservable.addObservable(mySF_v05_lep1looseIdlooseIso):
    #    INFO("failed to add mySF_v05_lep1looseIdlooseIso observable")
    #    return False
    #
    ### Gradient Iso                                                                                                                                                                
    #mySF_v05_lep0mediumIdGradientIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep0mediumIdGradientIso", 2,10000,0)
    #if not TQTreeObservable.addObservable(mySF_v05_lep0mediumIdGradientIso):
    #    INFO("failed to add mySF_v05_lep0mediumIdGradientIso observable")
    #    return False
    #
    #mySF_v05_lep1mediumIdGradientIso = ScaleFactor_ll_v05("ScaleFactor_v05_lep1mediumIdGradientIso", 2,10000,1)
    #if not TQTreeObservable.addObservable(mySF_v05_lep1mediumIdGradientIso):
    #    INFO("failed to add mySF_v05_lep1mediumIdGradientIso observable")
    #    return False

    mySF_LepSelec_def = ScaleFactor_ll_v05("SF_LepSelec_def")                                                                         
    if not TQTreeObservable.addObservable(mySF_LepSelec_def):
        INFO("failed to add mySF_LepSelec_def observable")
        return False

    mySF_LepSelec_fake = ScaleFactor_ll_v05("SF_LepSelec_fake")
    if not TQTreeObservable.addObservable(mySF_LepSelec_fake):
        INFO("failed to add mySF_LepSelec_fake observable")
        return False

    return True
