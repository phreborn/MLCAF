import QFramework
from BSMtautauCAF import LeptonFakes

def addObservables(config):
    myObs = LeptonFakes("LeptonFakes")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
