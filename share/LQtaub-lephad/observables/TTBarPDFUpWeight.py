import QFramework
from BSMtautauCAF import TTBarPDFUpWeight

def addObservables(config):
    myObs = TTBarPDFUpWeight("TTBarPDFUpWeight")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
