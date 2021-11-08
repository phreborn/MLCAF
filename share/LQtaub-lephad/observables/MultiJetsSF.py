import QFramework
from BSMtautauCAF import MultiJetsSF

def addObservables(config):
    myObs = MultiJetsSF("MultiJetsSF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
