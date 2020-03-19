import QFramework
from BSMtautauCAF import Pzeta

def addObservables(config):
    myObs = Pzeta("Pzeta")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
