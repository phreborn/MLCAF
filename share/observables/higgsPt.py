from QFramework import *
from ROOT import *

def addObservables(config):

    m_higgsPt= higgsPt("lephad_higgspt")
    if not TQTreeObservable.addObservable(m_higgsPt):
        INFO("failed to add lephad_higgspt observable")
        return False
    print(m_higgsPt.getExpression())

    return True
