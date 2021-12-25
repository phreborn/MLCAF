import QFramework
from BSMtautauCAF import TruthLepSelector

def addObservables(config):
    myObs = TruthLepSelector("TruthLepSelector")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
