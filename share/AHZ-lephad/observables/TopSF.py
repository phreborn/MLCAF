import QFramework
from BSMtautauCAF import TopSF

def addObservables(config):
    myObs = TopSF("TopSF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
