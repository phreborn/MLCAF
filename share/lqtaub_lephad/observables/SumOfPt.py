import QFramework
from BSMtautauCAF import SumOfPt

def addObservables(config):
    myObs = SumOfPt("SumOfPt")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
