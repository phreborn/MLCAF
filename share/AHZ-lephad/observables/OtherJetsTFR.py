import QFramework
from BSMtautauCAF import OtherJetsTFR

def addObservables(config):
    myObs = OtherJetsTFR("OtherJetsTFR")
    if not QFramework.TQTreeObservable.addObservable(myObs, myObs.getExpression().Data()):
        QFramework.WARN("Failed to add observable '{:s}'".format(myObs.getExpression().Data()))
        return False
    return True
