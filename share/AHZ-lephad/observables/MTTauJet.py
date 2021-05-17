import QFramework
from BSMtautauCAF import MTTauJet

def addObservables(config):
    myObs = MTTauJet("MTTauJet")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
