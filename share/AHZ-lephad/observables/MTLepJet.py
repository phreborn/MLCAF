import QFramework
from BSMtautauCAF import MTLepJet

def addObservables(config):
    myObs = MTLepJet("MTLepJet")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
