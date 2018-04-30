from QFramework import *
from ROOT import *

from CAFExample import MjjVectorObservable

def addObservables():
	
    obs = MjjVectorObservable("MjjVec")
    if not TQObservable.addObservable(obs, "MjjVec"):
        INFO("failed to add MjjVectorObservable")
        return False
    return True;
