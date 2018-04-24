from QFramework import *
from ROOT import *

from CAFExample import FakeLeptonMT

def addObservables():

  myObs = FakeLeptonMT("FakeLeptonMT")
  if not TQTreeObservable.addObservable(myObs, "FakeLeptonMT"):
    return False

  return True
