from QFramework import *
from ROOT import *

def addObservables(config):
    syst=0
    systematic=str(config.getTagStringDefault("systematic",""))
    low=["fakes_ee_set_low", 
    "fakes_ee_det_low", 
    "fakes_mm_smt_low", 
    "fakes_mm_dmt_low", 
    "fakes_em_set_low", 
    "fakes_em_smt_low", 
    "fakes_em_emt_low", 
    "fakes_me_set_low", 
    "fakes_me_smt_low", 
    "fakes_me_emt_low", 
    ]
    high=[
    "fakes_ee_set_high",
    "fakes_ee_det_high",
    "fakes_mm_smt_high",
    "fakes_mm_dmt_high",
    "fakes_em_set_high",
    "fakes_em_smt_high",
    "fakes_em_emt_high",
    "fakes_me_set_high",
    "fakes_me_smt_high",
    "fakes_me_emt_high",]
    
    if systematic == "fake_weight_up" or systematic in high: 
        syst=1
        INFO("fake_weight_up "+str(syst))
    elif systematic == "fake_weight_down" or systematic in low: 
        syst=-1
        INFO("fake_weight_down "+str(syst))
    myTFweight = TemplateFake_weight_ll("TFweight",syst)
    if not TQTreeObservable.addObservable(myTFweight):
        INFO("failed to add fake_weight observable")
        return False
    return True
