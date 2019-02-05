from QFramework import *
from ROOT import *

def addObservables(config):
    myVptReweight= VpTReweight("vptreweight")
    variation = config.getTagStringDefault("variation","nominal")
    if not TQTreeObservable.addObservable(myVptReweight):
        INFO("failed to add myVptReweight observable")
        return False
    INFO("using weights for variation '{:s}'".format(variation))
    print(myVptReweight.getExpression()) 
    return True
