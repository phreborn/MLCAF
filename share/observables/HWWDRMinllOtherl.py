from QFramework import *
from ROOT import *

def addObservables():

	obs = HWWDRMinllOtherl("HWWDRMinllOtherl")
	if not TQObservable.addObservable(obs):
		INFO("failed to add HWWDRMinllOtherl Observable")
		return False
	return True