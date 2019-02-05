from QFramework import *
from ROOT import *

def addObservables(config):

    m_mTtot = mTtot("lephad_mttot")
    if not TQTreeObservable.addObservable(m_mTtot):
        INFO("failed to add lephad_mttot observable")
        return False
    print(m_mTtot.getExpression())

    return True
