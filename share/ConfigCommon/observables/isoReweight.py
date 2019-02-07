import QFramework
from ROOT import *

from Htautau import isoReweight

def addObservables(config):
    variation = config.getTagStringDefault("isovar","nominal")
    myisoReweight= isoReweight("isoreweight_"+variation)
    if not QFramework.TQTreeObservable.addObservable(myisoReweight,"isoReweight"):
        INFO("failed to add myisoReweight observable")
        return False
#    print(myisoReweight.getExpression())
    return True
