from ROOT import *
from QFramework import *
def addObservables(config):
    # observables used for cutting
    for name in ["LooseElec","LooseMuon","TightElec","TightMuon"]:
        myFakeLepSel = FakeLepSel_ll("Third"+name+"Sel")
        if not TQTreeObservable.addObservable(myFakeLepSel):
            INFO("failed to add myFakeLepSel observable")
            return False
        print(myFakeLepSel.getExpression())
    # observables used for plotting
    for particle in ["Muon","Elec"]:
        for variable in ["Eta","Pt","DRjet", "DRlep0", "DRlep1"]:
            myFakeLepKin = FakeLepSel_ll("Third"+particle+variable+"Kin")
            if not TQTreeObservable.addObservable(myFakeLepKin):
                INFO("failed to add myFakeLepKin observable")
                return False
            print(myFakeLepKin.getExpression())
    return True
