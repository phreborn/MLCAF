import QFramework
import ROOT
from BSMtautauCAF import BSMLepHad_TopSys

def addObservables(config):
    variation = config.getTagStringDefault("ttbarweight","nominal")
    myBSMLepHad_TopSys= BSMLepHad_TopSys("bsmlephad_topsys_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myBSMLepHad_TopSys,"bsmlephad_topsys_"+variation):
        INFO("failed to add myBSMLepHad_TopSys observable")
        return False
    #print(myBSMLepHad_TopSys.getExpression())
    return True
