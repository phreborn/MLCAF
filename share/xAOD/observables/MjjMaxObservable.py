from QFramework import *
from ROOT import *

def addObservables():
	
    obs = MjjMaxObservable("MjjMax")
    if not TQObservable.addObservable(obs):
        INFO("failed to add MjjMax Observable")
        return False
    return True;