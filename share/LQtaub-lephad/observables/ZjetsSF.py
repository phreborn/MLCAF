import QFramework
from BSMtautauCAF import ZjetsSF

def addObservables(config):
    myObs = ZjetsSF("ZjetsSF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
