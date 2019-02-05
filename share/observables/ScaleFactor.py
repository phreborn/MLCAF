from QFramework import *
from ROOT import *

def addObservables(config):

  weightSystematic = config.getTagStringDefault("weightvar","nominal")

  names = ["ScaleFactor"]
  names += ["ScaleFactor_%s" % weightSystematic]
  for name in names:
    myScaleFactor = ScaleFactor(name)
    if not TQTreeObservable.addObservable(myScaleFactor):
        INFO("failed to add myScaleFactor observable named as " + name)
        return False
    print(myScaleFactor.getExpression())

  return True
