import QFramework
from BSMtautauCAF import MTLepTau

def addObservables(config):
    myObs = MTLepTau("MTLepTau")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
