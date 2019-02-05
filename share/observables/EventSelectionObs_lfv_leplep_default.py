from ROOT import *
from QFramework import *
import EventSelectionObs_leplep_common

def addObservables(config):
    selection=EventSelectionObs_lfv_leplep_default
    #selection=EventSelectionObs_leplep_default
    if "fakes" in str(config.getTagStringDefault("restrictedPath","")):
        INFO("running over fakes, using fakes EventSelection")
        selection=EventSelectionObs_leplep_fake
    observables=EventSelectionObs_leplep_common.generateCommonObservables();
    for obs in observables:
      thisobs=selection(obs)
      if not TQTreeObservable.addObservable(thisobs):
        INFO("failed to add "+obs+" observable")
        return False
    return True

