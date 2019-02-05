from QFramework import *
from ROOT import *

def addObservables(config):
    syst=0
    systematic=str(config.getTagStringDefault("systematic",""))
    if systematic == "PU_weight_up": 
        syst=1
        INFO("PU_weight_up "+str(syst))
    elif systematic == "PU_weight_down": 
        syst=-1
        INFO("PU_weight_down "+str(syst))
    elif systematic == "fac_high":
        syst=10
        INFO("fac_high "+str(syst))
    elif systematic == "fac_low":
        syst=-10
        INFO("fac_low "+str(syst))
    elif systematic == "ren_high":
        syst=20
        INFO("ren_high "+str(syst))
    elif systematic == "ckkw_low":
        syst=-20
        INFO("ckkw_low "+str(syst))
    elif systematic == "ckkw_high":
        syst=20
        INFO("ckkw_high "+str(syst))
    elif systematic == "ckkw_low":
        syst=-20
        INFO("ckkw_low "+str(syst))
    elif systematic == "qsf_high":
        syst=20
        INFO("qsf_high "+str(syst))
    elif systematic == "qsf_low":
        syst=-20
        INFO("qsf_low "+str(syst))


    myPUweight = PU_weight_ll_v05("PU_weight_mc",syst)
    if not TQTreeObservable.addObservable(myPUweight):
        INFO("failed to add PU_weight observable")
        return False
    myRRN = PU_weight_ll_v05("random_run_number",syst)
    if not TQTreeObservable.addObservable(myRRN):
        INFO("failed to add RRN observable")
        return False
    return True
