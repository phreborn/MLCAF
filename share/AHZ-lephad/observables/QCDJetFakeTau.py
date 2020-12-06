import QFramework
from BSMtautauCAF import QCDJetFakeTau

def addObservables(config):
    myObs = QCDJetFakeTau("QCDJetFakeTau")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
