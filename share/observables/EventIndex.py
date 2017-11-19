from QFramework import *
from ROOT import *
def addObservables():
    if not TQObservable.addObservable(TQEventIndexObservable("EventIndex")):
        INFO("failed to add event index observable")
        return False
    return True
