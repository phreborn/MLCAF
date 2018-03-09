from ROOT import *
from QFramework import *

def addAlgorithms(visitor,config):
  # create a CxAODReader Algorithm
  try:
    cxaodreader = CxAODReaderAlgorithm(False,False)
    cxaodreader.select(CxAODSelectors.IntAccessor("isVVLooseSignalElectron"),
                       CxAODSelectors.IntAccessor("isVVLooseMuon"),
                       CxAODSelectors.PassThrough())
    visitor.addAlgorithm(cxaodreader)
    return True
  except NameError:
    ERROR("you need the CxAODUtils package in order to use the CxAODReader which is included in CAFCore on git!")
    BREAK("missing package!")
