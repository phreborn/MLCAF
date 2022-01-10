import QFramework
from BSMtautauCAF import TruthTauSelectorFakeComposition

def addObservables(config):
    myObs = TruthTauSelectorFakeComposition("TruthTauSelectorFakeComposition")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
