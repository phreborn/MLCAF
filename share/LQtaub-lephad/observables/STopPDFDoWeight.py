import QFramework
from BSMtautauCAF import STopPDFDoWeight

def addObservables(config):
    myObs = STopPDFDoWeight("STopPDFDoWeight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
