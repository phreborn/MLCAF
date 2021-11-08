import QFramework
from BSMtautauCAF import MultiJetsLFF

def addObservables(config):
    myObs = MultiJetsLFF("MultiJetsLFF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
