import QFramework
import ROOT
from BSMtautauCAF import TruthTauSelector

def addObservables(config):
    myObs = TruthTauSelector("TruthTauSelector")
    if not QFramework.TQTreeObservable.addObservable(myObs,"TruthTauSelector"):
        INFO("failed to add TruthSelector Observable!")
        return False
    return True
