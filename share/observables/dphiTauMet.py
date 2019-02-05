from QFramework import *
from ROOT import *

def addObservables(config):

    dphitaumet = dphiTauMet("dphiTauMet")
    if not TQTreeObservable.addObservable(dphitaumet):
        INFO("failed to add dphitaumet observable")
        return False
    print(dphitaumet.getExpression())

    return True
