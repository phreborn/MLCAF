import QFramework
from BSMtautauCAF import MCOtherJetsTFF

def addObservables(config):
    myObs = MCOtherJetsTFF("MCOtherJetsTFF")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
