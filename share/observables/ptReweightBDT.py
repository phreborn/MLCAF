from QFramework import *
from ROOT import *

def addObservables(config):

    variation = config.getTagStringDefault("fakevar","nominal")
    names = [    'BDT1',    'BDT2',    'BDT3',    'BDT4'    ]
    for name in names:
    	print 'ptreweight_'+name+'_'+variation
        myptReweight= ptReweightBDT('ptreweight_'+name+'_'+variation)
        if not TQTreeObservable.addObservable(myptReweight):
            INFO("failed to add myptReweight observable")
            return False
        print(myptReweight.getExpression())

    return True
