from QFramework import *
from ROOT import *
import sys

from CAFExample import HWWTrigConfig

''' trigger config settings

    configure trigger-related settings, so that other observables
    can import and use them, such as HWWTriggerSelection and HWWTriggerMatchingObs.
    These observables takes a vector of HWWTrigConfig objects in their constructor,
    each object corresponding to a specific data period. In this snippet, you can
    create your own list of triggers and implement a function which returns this
    list in vector format. Then import this module and call this function from wherever 
    you are initialising your trigger selection/matching observables.
    
    The HWWTrigConfig object assumes there are three types of triggers: 
    single electron, single muon and di-lepton, each for both data and MC
    (in case you use different triggers for data and MC)

    NOTE: this is not an observable, and should not be used as such (i.e. don't 
          add it in your runAnalysis config '''

# period identifiers
g_periods = ["2015", "2016", "2016D"]

# corresponding run numbers 
runNrLow = {"2015": 276261, "2016": 297729, "2016D": 302918}
runNrUp = {"2015": 284485, "2016": 302919, "2016D": 320000} # 2016D large upper number

# the list of analysis triggers
# 2015
single_el_data_2015 = ["HLT_e24_lhmedium_L1EM20VH", "HLT_e60_lhmedium", "HLT_e120_lhloose"]
single_el_mc_2015   = ["HLT_e24_lhmedium_L1EM18VH", "HLT_e60_lhmedium", "HLT_e120_lhloose"]
single_mu_2015 = ["HLT_mu20_iloose_L1MU15", "HLT_mu50"]
dilep_2015 = ["HLT_e17_lhloose_mu14", "HLT_e7_lhmedium_mu24"]

# 2016
single_el_2016 = ["HLT_e24_lhtight_nod0_ivarloose", "HLT_e60_lhmedium_nod0", "HLT_e140_lhloose_nod0"]
single_mu_2016 = ["HLT_mu24_ivarmedium", "HLT_mu50"]
dilep_2016 = ["HLT_e17_lhloose_nod0_mu14", "HLT_e7_lhmedium_nod0_mu24"]

# 2016D
single_el_2016D = ["HLT_e26_lhtight_nod0_ivarloose", "HLT_e60_lhmedium_nod0", "HLT_e140_lhloose_nod0"]
single_mu_2016D = ["HLT_mu26_ivarmedium", "HLT_mu50"]
dilep_2016D = ["HLT_e17_lhloose_nod0_mu14", "HLT_e7_lhmedium_nod0_mu24"]

# dictionaries sorted by period, holding the corresponding trigger lists
single_el_data = {"2015": single_el_data_2015, "2016": single_el_2016, "2016D": single_el_2016D}
single_el_mc   = {"2015": single_el_mc_2015, "2016": single_el_2016, "2016D": single_el_2016D}
single_mu_data = {"2015": single_mu_2015, "2016": single_mu_2016, "2016D": single_mu_2016D}
single_mu_mc   = single_mu_data
dilep_data     = {"2015": dilep_2015, "2016": dilep_2016, "2016D": dilep_2016D}
dilep_mc       = dilep_data
# dilep dictionary with only the first of the two dilep triggers ("HLT_e17...")
dilep1_data     = {"2015": [dilep_2015[0]], "2016": [dilep_2016[0]], "2016D": [dilep_2016D[0]]}
dilep1_mc       = dilep1_data

# corresponding pt cuts for trigger SFs (for combined OR trigger expressions). They seem to always be 1 GeV larger than lowest trigger threshold
ptcut_single_el = {"2015": 25000., "2016": 25000., "2016D": 27000.}
ptcut_single_mu = {"2015": 20000.*1.05, "2016": 24000.*1.05, "2016D": 26000.*1.05}
ptcut_dilep_elleg = {"2015": 8000., "2016": 8000., "2016D": 8000.}
ptcut_dilep_muleg = {"2015": 15000., "2016": 15000., "2016D": 15000.}
# ptcut's for dilep1 should be 18000. (TODO: check what trigger SFs actually exist and how they are configured. Should use this file too)
ptcut_dilep1_elleg = {"2015": 18000., "2016": 18000., "2016D": 18000.}
ptcut_dilep1_muleg = ptcut_dilep_muleg

# list of prescaled triggers used for dijet FF measurement
single_el_prescale = ["HLT_e12_lhvloose_nod0_L1EM10VH"]
single_mu_prescale = ["HLT_mu14"]
# corresponding pt cuts for trigger SFs: TODO: do those SFs look OK? We anyway cut at 15 GeV so should be a small effect anyway. 
# For now just put dummy values
ptcut_single_el_prescale = 0.
ptcut_single_mu_prescale = 0.

def vectorize(type, python_list):
	# make an std::vector out of a python list, return it. needed to call c++ functions taking vectors as arguments
	vec = vector(type)()
	for el in python_list: vec.push_back(el)
	return vec
	
def checkPeriod(period):
  if period not in g_periods: 
    print("Unrecognised period identifier! Existing periods are ", g_periods)
    sys.exit(0)

def setSingleElTriggers(trigConf, period):
  ''' set the single electron triggers on the HWWTrigConf object '''

  checkPeriod(period)
  trigConf.setTriggersSingleEl_Data(vectorize("TString", single_el_data[period]), ptcut_single_el[period])
  trigConf.setTriggersSingleEl_MC(vectorize("TString", single_el_mc[period]), ptcut_single_el[period])


def setSingleMuTriggers(trigConf, period):
  ''' set the single muon triggers on the HWWTrigConf object '''
  checkPeriod(period)
  trigConf.setTriggersSingleMu_Data(vectorize("TString", single_mu_data[period]), ptcut_single_mu[period])
  trigConf.setTriggersSingleMu_MC(vectorize("TString", single_mu_mc[period]), ptcut_single_mu[period])

def setDilepTriggers(trigConf, period):
  ''' set the dilepton triggers on the HWWTrigConf object '''
  checkPeriod(period)
  trigConf.setTriggersDilep_Data(vectorize("TString", dilep_data[period]), ptcut_dilep_elleg[period], ptcut_dilep_muleg[period])
  trigConf.setTriggersDilep_MC(vectorize("TString", dilep_mc[period]), ptcut_dilep_elleg[period], ptcut_dilep_muleg[period])

def setDilepTriggers1(trigConf, period):
  # like above fcn, but use only the first of the dilep triggers ("HLT_e17...")
  checkPeriod(period)
  trigConf.setTriggersDilep_Data(vectorize("TString", dilep1_data[period]), ptcut_dilep1_elleg[period], ptcut_dilep1_muleg[period])
  trigConf.setTriggersDilep_MC(vectorize("TString", dilep1_mc[period]), ptcut_dilep1_elleg[period], ptcut_dilep1_muleg[period])

def getTrigConf(period):
  ''' create a HWWTrigConf object, set its run numbers based on passed period identifier, return it '''
  checkPeriod(period)
  
  # create the HWWTrigConfig object
  trigConfig = HWWTrigConfig(period)
  
  # set period (run numbers)
  trigConfig.setRunNumbers(runNrLow[period], runNrUp[period])
  
  return trigConfig

def getTrigConfigList(periods = g_periods):
  # list of HWWTrigConfig objects, single lepton triggers only
  trigConfigList = []

  for period in periods: 
    trigConf = getTrigConf(period)
    setSingleElTriggers(trigConf, period)
    setSingleMuTriggers(trigConf, period)
    trigConfigList.append(trigConf)

  return trigConfigList

def getTrigConfigListDilep(periods = g_periods):
  # list of HWWTrigConfig objects, both single and dilepton triggers
  trigConfigList = []
  for period in periods: 
    trigConf = getTrigConf(period)
    setSingleElTriggers(trigConf, period)
    setSingleMuTriggers(trigConf, period)
    setDilepTriggers(trigConf, period)
    trigConfigList.append(trigConf)

  return trigConfigList

def getTrigConfigListDilep1(periods = g_periods):
  # list of HWWTrigConfig objects, single and one of the dilepton triggers ("HLT_e17...")
  trigConfigList = []
  for period in periods: 
    trigConf = getTrigConf(period)
    setSingleElTriggers(trigConf, period)
    setSingleMuTriggers(trigConf, period)
    setDilepTriggers1(trigConf, period)
    trigConfigList.append(trigConf)

  return trigConfigList

def getTrigPrescaleConfigList():
  # list of HWWTrigConfig objects for prescaled triggers used in dijet nominal FF measurement
  trigConfPrescale=HWWTrigConfig("prescaled")
  trigConfPrescale.setTriggersSingleMu(vectorize("TString", single_mu_prescale), ptcut_single_mu_prescale)
  trigConfPrescale.setTriggersSingleEl(vectorize("TString", single_el_prescale), ptcut_single_el_prescale)
  # set run numbers to "full range"
  trigConfPrescale.setRunNumbers(runNrLow["2015"], runNrUp["2016D"])
  return [trigConfPrescale]  

# add the usual addObservables() function to be able to give a meaningful error
# message when wrongly trying to include this helper as an observable
def addObservables():
  ERROR("HWWTrigConfig provides helper functions, it's not an observable. You should not add it in your runAnalysis config file.")
  return False

# vector of trigger configs, this is the one that will be used by other observables
def getTrigConfigVector(period = ""):
  # if specified period, return only those triggers
  if period in g_periods:
    return vectorize("HWWTrigConfig*", getTrigConfigList([period])) 
  # else, return full list of triggers
  return vectorize("HWWTrigConfig*", getTrigConfigList())

# like above, but including dilep triggers
def getTrigConfigVectorDilep(period = ""):
  # if specified period, return only those triggers
  if period in g_periods:
    return vectorize("HWWTrigConfig*", getTrigConfigListDilep(period))
  # else, return full list of triggers
  return vectorize("HWWTrigConfig*", getTrigConfigListDilep())

# like above, but including only one of the dilep triggers ("HLT_e17_...")
def getTrigConfigVectorDilep1(period = ""):
  # if specified period, return only those triggers
  if period in g_periods:
    return vectorize("HWWTrigConfig*", getTrigConfigListDilep1(period))
  # else, return full list of triggers
  return vectorize("HWWTrigConfig*", getTrigConfigListDilep1())

# vector of trigger configs for dijet FF measurement (prescaled triggers, period not relevant)
def getTrigConfigVectorPrescale():
  return vectorize("HWWTrigConfig*", getTrigPrescaleConfigList())

if __name__ == "__main__":
  print "Inside main of HWWTrigConfig snippet"
  #getTrigConfigListDilep1()

