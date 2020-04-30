import QFramework
from BSMtautauCAF import InvMTauJet

def addObservables(config):
    myObs = InvMTauJet("InvMTauJet")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
