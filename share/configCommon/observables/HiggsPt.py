import QFramework
import ROOT
from BSMtautauCAF import HiggsPt

def addObservables(config):
    myObs= HiggsPt("HiggsPt")
    if not QFramework.TQTreeObservable.addObservable(myObs,"HiggsPt"):
        INFO("failed to add lephad_higgspt observable")
        return False
    #print(m_HiggsPt.getExpression())
    return True
