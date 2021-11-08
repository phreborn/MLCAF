import QFramework
from BSMtautauCAF import TruthTauSelector

def addObservables(config):
    myObs = TruthTauSelector("TruthTauSelector")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
