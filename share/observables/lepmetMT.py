from QFramework import *
from ROOT import *

def addObservables(config):

    m_lepmetMT = lepmetMT("lepmet_mt")
    if not TQTreeObservable.addObservable(m_lepmetMT):
        INFO("failed to add lepmet_mt observable")
        return False
    print(m_lepmetMT.getExpression())

    return True
