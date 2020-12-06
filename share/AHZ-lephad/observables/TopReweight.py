import QFramework
from BSMtautauCAF import TopReweight

def addObservables(config):
    myObs = TopReweight("TopReweight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
