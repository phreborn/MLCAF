from ROOT import *
from QFramework import *
def addObservables():
    myFakeWeights = FakesMM("FakeWeights")
    if not TQTreeObservable.addObservable(myFakeWeights):
        INFO("failed to add myFakeWeights observable")
        return False
    return True
