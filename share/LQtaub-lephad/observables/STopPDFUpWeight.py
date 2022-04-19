import QFramework
from BSMtautauCAF import STopPDFUpWeight

def addObservables(config):
    myObs = STopPDFUpWeight("STopPDFUpWeight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
