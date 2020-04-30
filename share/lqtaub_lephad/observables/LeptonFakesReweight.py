import QFramework
from BSMtautauCAF import LeptonFakesReweight

def addObservables(config):
    myObs = LeptonFakesReweight("LeptonFakesReweight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
