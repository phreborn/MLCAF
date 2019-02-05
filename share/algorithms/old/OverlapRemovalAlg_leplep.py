from ROOT import *
from QFramework import *

def addAlgorithms(visitor,config):
    try:
        overlapremoval = OverlapRemovalAlg_leplep()
        return visitor.addAlgorithm(overlapremoval)
    except:
        return False
