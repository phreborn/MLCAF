from QFramework import *
from ROOT import *

def addObservables():
    myMjj = Mjjleplep("Mjjleplep")
    #variation = config.getTagStringDefault("variation","nominal")
    if not TQTreeObservable.addObservable(myMjj):
        INFO("failed to add myMjj observable")
        return False
    #INFO("using weights for variation '{:s}'".format(variation))
    #print(myptReweight.getExpression()) 
    return True
