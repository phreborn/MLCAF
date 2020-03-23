import QFramework
from BSMtautauCAF import JetFakesReweight

def addObservables(config):
    myObs = JetFakesReweight("JetFakesReweight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
