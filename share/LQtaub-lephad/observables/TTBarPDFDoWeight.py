import QFramework
from BSMtautauCAF import TTBarPDFDoWeight

def addObservables(config):
    myObs = TTBarPDFDoWeight("TTBarPDFDoWeight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
