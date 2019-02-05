from QFramework import *
from ROOT import *

def addObservables(config):

    dphilepmet = dphiLepMet("dphiLepMet")
    if not TQTreeObservable.addObservable(dphilepmet):
        INFO("failed to add dphilepmet observable")
        return False
    print(dphilepmet.getExpression())

    return True
