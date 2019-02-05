from QFramework import *
from ROOT import *

def addObservables(config):

    comb = [ "medmed", 
             "tighttight", 
             "tightloose" ]

    for lep_comb in comb:
        mySF = ScaleFactor_ll("ScaleFactor_"+lep_comb)
        if not TQTreeObservable.addObservable(mySF):
            INFO("failed to add mySF observable")
            print(mySF.GetExpression())
            return False

    return True
