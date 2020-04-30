import QFramework
from BSMtautauCAF import TopReweightLQ

def addObservables(config):
    myObs = TopReweightLQ("TopReweightLQ")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
