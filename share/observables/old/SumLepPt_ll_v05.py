from QFramework import *
from ROOT import *

def addObservables(config):

    mySumLepPt = SumLepPt_ll_v05("SumLepPt")
    if not TQTreeObservable.addObservable(mySumLepPt):
        INFO("failed to add mySumLepPt observable")
        return False

    mySumLepPt_fake = SumLepPt_ll_v05("SumLepPt_fake")
    if not TQTreeObservable.addObservable(mySumLepPt_fake):
        INFO("failed to add mySumLepPt_fake observable")
        return False

    myLep0_Pt = SumLepPt_ll_v05("Lep0_Pt")
    if not TQTreeObservable.addObservable(myLep0_Pt):
        INFO("failed to add myLep0_Pt observable")
        return False

    myLep1_Pt = SumLepPt_ll_v05("Lep1_Pt")
    if not TQTreeObservable.addObservable(myLep1_Pt):
        INFO("failed to add myLep1_Pt observable")
        return False

    myLep0_Pt_fake = SumLepPt_ll_v05("Lep0_Pt_fake")
    if not TQTreeObservable.addObservable(myLep0_Pt_fake):
        INFO("failed to add myLep0_Pt_fake observable")
        return False

    myLep1_Pt_fake = SumLepPt_ll_v05("Lep1_Pt_fake")
    if not TQTreeObservable.addObservable(myLep1_Pt_fake):
        INFO("failed to add myLep1_Pt_fake observable")
        return False
    
    return True


