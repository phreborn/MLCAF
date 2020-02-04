import QFramework
import ROOT
from BSMtautauCAF import MTtot

def addObservables(config):
    myObs = MTtot("MTtot")
    if not QFramework.TQTreeObservable.addObservable(myObs,"MTtot"):
        INFO("failed to add lephad_mttot observable")
        return False
    #print(m_MTtot.getExpression())
    return True
