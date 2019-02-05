from QFramework import *
from ROOT import *
def addObservables(config):
    variation = config.getTagStringDefault("ttbarweight","nominal")
    myBSMLepHad_TopSys= BSMLepHad_TopSys("bsmlephad_topsys_"+variation)
    if not TQTreeObservable.addObservable(myBSMLepHad_TopSys):
        INFO("failed to add myBSMLepHad_TopSys observable")
        return False
    print(myBSMLepHad_TopSys.getExpression())

    return True
