import QFramework
import ROOT
from BSMtautauCAF import Pzeta

def addObservables(config):
    myObs = Pzeta("Pzeta")
    if not QFramework.TQTreeObservable.addObservable(myObs,"Pzeta"):
        INFO("failed to add Pzeta observable")
        return False
    #print(m_Pzeta.getExpression())
    return True
