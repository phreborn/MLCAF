from QFramework import *
from ROOT import *

def addObservables(config):

    pzeta = Pzeta("lephad_Pzeta")
    if not TQTreeObservable.addObservable(pzeta):
        INFO("failed to add pzeta observable")
        return False
    print(pzeta.getExpression())

    return True
