import QFramework
from BSMtautauCAF import JetFakes

def addObservables(config):
    myObs = JetFakes("JetFakes")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
