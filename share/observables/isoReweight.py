from QFramework import *
from ROOT import *

def addObservables(config):

    variation = config.getTagStringDefault("isovar","nominal")

    myisoReweight= isoReweight("isoreweight_"+variation)
    if not TQTreeObservable.addObservable(myisoReweight):
        INFO("failed to add myisoReweight observable")
        return False
    print(myisoReweight.getExpression())

    return True
