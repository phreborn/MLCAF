from QFramework import *
from ROOT import *
from CAFExample import HWWTriggerSelection,HWWTriggerMatchingObs

def addObservables(config):
  INFO("adding different trigger observables and trigger matching tools")

  #======================
  #===== import trigger config, needed by trigger observables
  try: 
    import HWWTrigConfig as hwwtrigconf
  except:
    ERROR("Couldn't import HWWTrigConfig")
    return False  

  #======================
  #===== import lepton ID helper snippet, will pass object to observables that need it
  #try: 
  #  import HWWLepIDHelper as hwwLepIDHelper
  #except:
  #  ERROR("Couldn't import HWWLeptonIDHelper")
  #  return False
  #lepIDSelectionTag = config.getTagStringDefault("lepIDSelectionTag","VH")
  #lepIDHelper = hwwLepIDHelper.getLepIDHelper(lepIDSelectionTag)
  #INFO("in HWWTrigger: Using lepton ID selection '{}' (see observables/HWWLepIDHelper.py for details)".format(lepIDSelectionTag))
  
  ### which triggers to use and for what periods are specified in the HWWTrigConfig.py snippet
  ### these objects will be passed to and operated on by the trigger selection/matching observables
  ### initialised below
  # triggers to use: single-lepton + one of the dilepton triggers ("HLT_e17_lhloose.._mu14")
  triggerConfigs = hwwtrigconf.getTrigConfigVectorDilep1()
  # only single-lepton triggers
  triggerConfigsSingleLepOnly = hwwtrigconf.getTrigConfigVector()

  #############
  #ForHighMass#
  doHighMasslvlv = config.getTagBoolDefault("doHighMasslvlv", False)
  if doHighMasslvlv:
    print("INFO:: Using single lepton trigger for high mass.")
    triggerConfigs = hwwtrigconf.getTrigConfigVector()
  #############

  #=================
  #=== trigger selection observables
  #=================
  # trigger decision observables will return true/false for the trigger decision,
  # assuming an OR between the triggers you put in your triggerConfigs objects.
  TriggerSelectionObs = HWWTriggerSelection("TriggerSelectionObs", triggerConfigs)
  if not TQTreeObservable.addObservable(TriggerSelectionObs):
    ERROR("Failed to register trigger selection observable")
    return False

  #For single-lepton-triggers only
  TriggerSelectionSingleLepOnlyObs = HWWTriggerSelection("TriggerSelectionSingleLepOnlyObs", triggerConfigsSingleLepOnly)
  if not TQTreeObservable.addObservable(TriggerSelectionSingleLepOnlyObs):
    ERROR("Failed to register trigger selection observable for single-lepton-only triggers")
    return False
  
  #=================
  #=== trigger matching observables
  #=================
  # trigger matching observables will return true/false if there is a trigger match,
  # assuming an OR between the triggers you put in your triggerConfigs objects.
  TriggerMatchingObs = HWWTriggerMatchingObs("TriggerMatchingObs", triggerConfigs)
  if not TQTreeObservable.addObservable(TriggerMatchingObs):
    ERROR("Failed to register trigger matching observable")
    return False

  TriggerMatchingSingleLepOnlyObs = HWWTriggerMatchingObs("TriggerMatchingSingleLepOnlyObs", triggerConfigsSingleLepOnly)
  if not TQTreeObservable.addObservable(TriggerMatchingSingleLepOnlyObs):
    ERROR("Failed to register trigger matching observable")
    return False

  #==============================
  #====== Triggered-by-fake observables
  #==============================
  # triggered-by-fake observables are intended to be used for the fake lepton estimate and 
  # will return true/false based on if anti-id object is the sole object firing the trigger. 
  # See https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/HiggsPhys/HSG3/HSG3AnalysisCode/HWWlvlv2015/trunk/HWWlvlv2015/HWWTriggeredByFake.h for more explanation
  #TriggeredByFakeObs = HWWTriggeredByFake("TrigByFakeObs",  triggerConfigs, lepIDHelper)
  #if not TQTreeObservable.addObservable(TriggeredByFakeObs):
  #  ERROR("Failed to register triggered-by-fake observable")
  #  return False
  
  # with single-lep trigger only
  #TriggeredByFakeSingleLepOnlyObs = HWWTriggeredByFake("TrigByFakeSingleLepOnlyObs",  triggerConfigsSingleLepOnly, lepIDHelper)
  #if not TQTreeObservable.addObservable(TriggeredByFakeSingleLepOnlyObs):
  #  ERROR("Failed to register triggered-by-fake observable")
  #  return False

  # extra trig-by-fake, looking explicitly at electron or muon fake 
  # (required for double fakes where there's two fakable objects)
  #TriggeredByFakeObsElectron = HWWTriggeredByFake("TrigByFakeObsElectron", triggerConfigs, lepIDHelper, 1) # 1=Electron, 2=Muon
  #if not TQTreeObservable.addObservable(TriggeredByFakeObsElectron):
  #  ERROR("Failed to register triggered-by-fake observable")
  #  return False

  #TriggeredByFakeObsMuon = HWWTriggeredByFake("TrigByFakeObsMuon", triggerConfigs, lepIDHelper, 2) # 1=Electron, 2=Muon
  #if not TQTreeObservable.addObservable(TriggeredByFakeObsMuon):
  #  ERROR("Failed to register triggered-by-fake observable")
  #  return False

  ##=============================
  #==== Trigger classifier observable
  #=============================
  # this observable sorts events based on which triggers fired. 
  # The different categories and their corresponding return values 
  # are listed at https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/HiggsPhys/HSG3/HSG3AnalysisCode/HWWlvlv2015/trunk/HWWlvlv2015/HWWTriggerClassifier.h
  #TriggerClassifierObsDilep = HWWTriggerClassifier("TriggerClassifierObs", triggerConfigs)
  #if not TQTreeObservable.addObservable(TriggerClassifierObsDilep):
  #  ERROR("Failed to register trigger classifier observable")
  #  return False

  

  return True


if __name__ == "__main__":
  print("Inside main of HWWTrigger snippet, will now call addObservables")
  tags = TQTaggable()
  addObservables(tags)
