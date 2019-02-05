from QFramework import *
from ROOT import *

def addObservables(config):

    variation = config.getTagStringDefault("fakevar","nominal")

    myptReweight= ptReweight("ptreweight_"+variation)
    if not TQTreeObservable.addObservable(myptReweight):
        INFO("failed to add myptReweight observable")
        return False
    print(myptReweight.getExpression())

    return True
