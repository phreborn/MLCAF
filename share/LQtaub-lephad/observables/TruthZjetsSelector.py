import QFramework
from BSMtautauCAF import TruthZjetsSelector

def addObservables(config):
    myObs = TruthZjetsSelector("TruthZjetsSelector")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
