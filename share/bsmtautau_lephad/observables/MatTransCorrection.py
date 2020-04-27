import QFramework
from BSMtautauCAF import MatTransCorrection

def addObservables(config):
    myObs = MatTransCorrection("MatTransCorrection")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
