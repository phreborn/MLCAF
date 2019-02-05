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
    #myLepSelec_v05_lep0tightIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep0tightIdlooseIso", 3, 10, 0)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep0tightIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep0tightIdlooseIso observable")
    #    return False
    #
    #myLepSelec_v05_lep1tightIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep1tightIdlooseIso", 3, 10, 1)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep1tightIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep1tightIdlooseIso observable")
    #    return False
    #
    #myLepSelec_v05_lep0mediumIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep0mediumIdlooseIso", 2, 10, 0)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep0mediumIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep0mediumIdlooseIso observable")
    #    return False
    #
    #myLepSelec_v05_lep1mediumIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep1mediumIdlooseIso", 2, 10, 1)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep1mediumIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep1mediumIdlooseIso observable")
    #    return False
    #
    #myLepSelec_v05_lep0looseIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep0looseIdlooseIso", 1, 10, 0)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep0looseIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep0looseIdlooseIso observable")
    #    return False
    #
    #myLepSelec_v05_lep1looseIdlooseIso = LepSelec_ll_v05("LepSelec_v05_lep1looseIdlooseIso", 1, 10, 1)
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep1looseIdlooseIso):
    #    INFO("failed to add myLepSelec_v05_lep1looseIdlooseIso observable")
    #    return False

    ## Gradient Iso
    #myLepSelec_v05_lep0tightIdGradientIso = LepSelec_ll_v05("LepSelec_v05_lep0tightIdGradientIso")
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep0tightIdGradientIso):
    #    INFO("failed to add myLepSelec_v05_lep0tightIdGradientIso observable")
    #    return False
    #
    #myLepSelec_v05_lep1tightIdGradientIso = LepSelec_ll_v05("LepSelec_v05_lep1tightIdGradientIso")
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep1tightIdGradientIso):
    #    INFO("failed to add myLepSelec_v05_lep1tightIdGradientIso observable")
    #    return False
    #
    #myLepSelec_v05_lep0mediumIdGradientIso = LepSelec_ll_v05("LepSelec_v05_lep0mediumIdGradientIso")
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep0mediumIdGradientIso):
    #    INFO("failed to add myLepSelec_v05_lep0mediumIdGradientIso observable")
    #    return False
    #
    #myLepSelec_v05_lep1mediumIdGradientIso = LepSelec_ll_v05("LepSelec_v05_lep1mediumIdGradientIso")
    #if not TQTreeObservable.addObservable(myLepSelec_v05_lep1mediumIdGradientIso):
    #    INFO("failed to add myLepSelec_v05_lep1mediumIdGradientIso observable")
    #    return False

    myLepSelec_def = LepSelec_ll_v05("LepSelec_def")
    if not TQTreeObservable.addObservable(myLepSelec_def):
        INFO("failed to add myLepSelec_def observable")
        return False

    myLepSelec_fake = LepSelec_ll_v05("LepSelec_fake")
    if not TQTreeObservable.addObservable(myLepSelec_fake):
        INFO("failed to add myLepSelec_fake observable")
        return False

    myLepSelec_fake_tight = LepSelec_ll_v05("LepSelec_fake_tight")
    if not TQTreeObservable.addObservable(myLepSelec_fake_tight):
        INFO("failed to add myLepSelec_fake_tight observable")
        return False

    return True
