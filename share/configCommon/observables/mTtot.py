import QFramework
import ROOT
from BSMtautauCAF import mTtot

def addObservables(config):
    m_mTtot = mTtot("lephad_mttot")
    if not QFramework.TQTreeObservable.addObservable(m_mTtot,"lephad_mttot"):
        INFO("failed to add lephad_mttot observable")
        return False
    #print(m_mTtot.getExpression())
    return True
