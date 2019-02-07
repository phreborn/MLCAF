import QFramework
import ROOT
from Htautau import TruthSelector

def addObservables(config):
    myObs = TruthSelector("TruthSelector")
    if not QFramework.TQTreeObservable.addObservable(myObs,"TruthSelector"):
        INFO("failed to add TruthSelector Observable!")
        return False
    return True
