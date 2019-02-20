from QFramework import TQTreeObservable, INFO, ERROR
import ROOT

from CAFExample import HWWZBosonPairFakeIndex

def addObservables(config):

  INFO("adding Z boson pairing fake index observable")
  #======================
  #===== import trigger config, needed by trigger observables
  try:
    from CAFExample import TrigConfig
  except Exception as error:
    ERROR("Couldn't import TrigConfig module!\n"+"Message from python:\n"+str(error))
    return False


  ### which triggers to use and for what periods are specified in the HWWTrigConfig.py snippet
  # only single-lepton triggers
  triggerConfigsSingleLepOnly = TrigConfig.getTrigConfigVector()

  #======================
  #===== import lepton ID helper snippet, wil pass object to observable
  try:
    from CAFExample import LeptonIDHelper
  except Exception as error:
    ERROR("Couldn't import LeptonIDHelper module!\n"+"Message from python:\n"+str(error))
    return False

  #lepTag = config.getTagStringDefault("lepIDSelectionTag","VH")
  lepTag = config.getTagStringDefault("lepIDZCandSelectionTag","2L")
  lepIDHelper = LeptonIDHelper.getLepIDHelper(lepTag)
  INFO("in HWWZBosonPairFakeIndex: Using lepton ID selection '{}' (see CAFExample/python/LeptonIDHelper.py for details)".format(lepTag))


  hwwZbosonPairFakeIndex = HWWZBosonPairFakeIndex("ZBosonPairFakeIndex", triggerConfigsSingleLepOnly, lepIDHelper)

  if not TQTreeObservable.addObservable(hwwZbosonPairFakeIndex):
    INFO("failed to add Zboson-pair fake index observable")
    return False

  return True

if __name__ == "__main__":
  print "inside main of HWWZBosonPairFakeIndex python snippet, will try to add observable"

  tags = TQTaggable()
  if not addObservables(tags):
    print "failed to add observable(s)!"
  else:
    print "Successfully added observable(s)!"
