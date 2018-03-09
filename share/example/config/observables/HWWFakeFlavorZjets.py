from QFramework import *
from ROOT import *

def addObservables():

	MCTC_mode = 0 # 0 = MCTruthClassifier
	Run1_mode = 1 # 1 = Run1 (Keisuke's method, implemented by Javier)

	leadLepFake = 1
	subleadLepFake = 2
	otherLepFake = 3

	# Default cases, finding flavor of otherPart(0)
	hwwFakeFlavorZjets        = HWWFakeFlavorZjets("FakeFlavorZjets", Run1_mode)
	hwwFakeFlavorZjetsMCTC    = HWWFakeFlavorZjets("FakeFlavorZjetsMCTC", MCTC_mode)

	# Specific cases, finding flavor of given index
	hwwFakeFlavorZjets_leadLep    = HWWFakeFlavorZjets("FakeFlavorZjets_leadLep", Run1_mode, leadLepFake)
	hwwFakeFlavorZjets_subleadLep = HWWFakeFlavorZjets("FakeFlavorZjets_subleadLep", Run1_mode, subleadLepFake)
	hwwFakeFlavorZjets_otherLep   = HWWFakeFlavorZjets("FakeFlavorZjets_otherLep", Run1_mode, otherLepFake)
	hwwFakeFlavorZjetsMCTC_leadLep    = HWWFakeFlavorZjets("FakeFlavorZjetsMCTC_leadLep", MCTC_mode, leadLepFake)
	hwwFakeFlavorZjetsMCTC_subleadLep = HWWFakeFlavorZjets("FakeFlavorZjetsMCTC_subleadLep", MCTC_mode, subleadLepFake)
	hwwFakeFlavorZjetsMCTC_otherLep   = HWWFakeFlavorZjets("FakeFlavorZjetsMCTC_otherLep", MCTC_mode, otherLepFake)
 
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjets):
		INFO("failed to add Zjets Fake Flavor Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjetsMCTC):
		INFO("failed to add Zjets Fake Flavor Observable")
		return False

	if not TQTreeObservable.addObservable(hwwFakeFlavorZjets_leadLep):
		INFO("failed to add Zjets Fake Flavor Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjets_subleadLep):
		INFO("failed to add Zjets Fake Flavor Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjets_otherLep):
		INFO("failed to add Zjets Fake Flavor Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjetsMCTC_leadLep):
		INFO("failed to add Zjets Fake Flavor MCTC Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjetsMCTC_subleadLep):
		INFO("failed to add Zjets Fake Flavor MCTC Observable")
		return False
	if not TQTreeObservable.addObservable(hwwFakeFlavorZjetsMCTC_otherLep):
		INFO("failed to add Zjets Fake Flavor MCTC Observable")
		return False
 
	return True;
