from ROOT import *
from QFramework import *

def addAlgorithms(visitor,config):
    try:
        eventselection = EventSelection_leplep_tight("EventSelection_leplep_tight")
        return visitor.addAlgorithm(eventselection)
    except:
        return False
