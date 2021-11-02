import QFramework
from BSMtautauCAF import MultiJetsTFF

def addObservables(config):
    myObs = MultiJetsTFF("MultiJetsTFF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
