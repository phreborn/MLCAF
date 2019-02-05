from QFramework import *
from ROOT import *

def addObservables(config):
    obs = mcWeight("mcweight")
    #variation = config.getTagStringDefault("variation","nominal")
    if not TQTreeObservable.addObservable(obs):
        INFO("failed to add mcweight observable")
        return False
    #INFO("using weights for variation '{:s}'".format(variation))
    #print(myVptReweight.getExpression())
    return True
