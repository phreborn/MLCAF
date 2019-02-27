import QFramework
import ROOT
from BSMtautauCAF import higgsPt

def addObservables(config):
    m_higgsPt= higgsPt("lephad_higgspt")
    if not QFramework.TQTreeObservable.addObservable(m_higgsPt,"lephad_higgspt"):
        INFO("failed to add lephad_higgspt observable")
        return False
    #print(m_higgsPt.getExpression())
    return True
