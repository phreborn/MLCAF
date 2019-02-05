from QFramework import *
from ROOT import *

def addObservables(config):

    comb = [ "medmed", 
             "tighttight", 
             "tightloose" ]

    for lep_comb in comb:
        myLepSelec = LepSelec_ll("LeptonSelection_"+lep_comb)
        if not TQTreeObservable.addObservable(myLepSelec):
            INFO("failed to add myLepSelec observable")
            return False

    return True
