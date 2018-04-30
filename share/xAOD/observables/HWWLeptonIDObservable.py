from QFramework import *
from ROOT import *

from CAFExample import HWWLeptonIDObservable

def vectorize(type, python_list):
  # make an std::vector out of a python list, return it. needed to call c++ functions taking vectors as arguments
  vec = vector(type)()
  for el in python_list: vec.push_back(el)
  return vec

def addObservables(config):

  #======================
  #===== import lepton ID helper snippet, wil pass object to observable
  try:
    from CAFExample import HWWLepIDHelper as hwwLepIDHelper
  except:
    ERROR("Couldn't import HWWLepIDHelper")
    return False

  lepIDSelectionTag = config.getTagStringDefault("lepIDSelectionTag","VH")
  lepIDHelper = hwwLepIDHelper.getLepIDHelper(lepIDSelectionTag)
  INFO("in HWWLeptonIDObservable: Using lepton ID selection '{}' (see observables/HWWLepIDHelper.py for details)".format(lepIDSelectionTag))

  INFO("adding HWWLeptonIDObservable")
  #=== The integers must match the correct modes inside HWWLeptonIDObservable.cxx
  leadLepID = HWWLeptonIDObservable("leadLepID", lepIDHelper, 0)
  if not TQTreeObservable.addObservable(leadLepID): return False
  subleadLepID = HWWLeptonIDObservable("subleadLepID", lepIDHelper, 1)
  if not TQTreeObservable.addObservable(subleadLepID): return False
  otherLep0ID   = HWWLeptonIDObservable("otherLep0ID", lepIDHelper, 2) # otherLepton(index_default), default should be = 0
  if not TQTreeObservable.addObservable(otherLep0ID): return False
  # otherLep1ID   = HWWLeptonIDObservable("otherLep1ID", lepIDHelper, 2, 0, 1, 1) # otherLepton(1)
  # if not TQTreeObservable.addObservable(otherLep1ID): return False

  leadLepAntiID = HWWLeptonIDObservable("leadLepAntiID", lepIDHelper, 3)
  if not TQTreeObservable.addObservable(leadLepAntiID): return False
  subleadLepAntiID = HWWLeptonIDObservable("subleadLepAntiID", lepIDHelper, 4)
  if not TQTreeObservable.addObservable(subleadLepAntiID): return False
  otherLep0AntiID = HWWLeptonIDObservable("otherLep0AntiID", lepIDHelper, 5) # otherLepton(index_default), default should be = 0
  if not TQTreeObservable.addObservable(otherLep0AntiID): return False
  # otherLep1AntiID   = HWWLeptonIDObservable("otherLep1AntiID", lepIDHelper, 5, 0, 1, 1) # otherLepton(1)
  # if not TQTreeObservable.addObservable(otherLep1AntiID): return False

  return True

if __name__ == "__main__":
  print "Inside main of HWWLeptonIDObservable python snippet"
  if not addObservables():
    print("Couldn't add HWWLeptonIDObservables!")
  else:
    print("Successfully added HWWLeptonIDObservables")
