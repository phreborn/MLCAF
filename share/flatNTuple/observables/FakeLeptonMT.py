import QFramework
import ROOT

from CAFExample import FakeLeptonMT

def addObservables():

  myObs = FakeLeptonMT("FakeLeptonMT")
  if not QFramework.TQTreeObservable.addObservable(myObs, "FakeLeptonMT"):
    return False

  return True
