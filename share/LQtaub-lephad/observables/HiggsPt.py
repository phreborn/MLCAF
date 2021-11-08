import QFramework
from BSMtautauCAF import HiggsPt

def addObservables(config):
    myObs = HiggsPt("HiggsPt")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
