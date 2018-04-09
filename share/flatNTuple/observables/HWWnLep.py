from QFramework import *
from ROOT import *

def addObservables():
    nLep = ROOT.HWW.NLeptonObservableTool("nLep"       )
    nLep1= ROOT.HWW.NLeptonObservableTool("nVetoMuon"  )
    nLep2= ROOT.HWW.NLeptonObservableTool("nVetoEle"   )
    nLep3= ROOT.HWW.NLeptonObservableTool("nVetoLepton")
    nLep4= ROOT.HWW.NLeptonObservableTool("VetoLepPt")
    nLep5= ROOT.HWW.NLeptonObservableTool("VetoLepEta")
    nLep6= ROOT.HWW.NLeptonObservableTool("VetoLepPhi")
    nLep7= ROOT.HWW.NLeptonObservableTool("TriLep")
    nLep8= ROOT.HWW.NLeptonObservableTool("Mll3")
    nLep9= ROOT.HWW.NLeptonObservableTool("Mll3Low")
    nLep10= ROOT.HWW.NLeptonObservableTool("nVetoLepton4")
    nLep11= ROOT.HWW.NLeptonObservableTool("nOtherJets")
        

    if not TQToolObservable.registerTool(nLep):  return False
    if not TQToolObservable.registerTool(nLep1): return False
    if not TQToolObservable.registerTool(nLep2): return False
    if not TQToolObservable.registerTool(nLep3): return False
    if not TQToolObservable.registerTool(nLep4): return False
    if not TQToolObservable.registerTool(nLep5): return False
    if not TQToolObservable.registerTool(nLep6): return False
    if not TQToolObservable.registerTool(nLep7): return False
    if not TQToolObservable.registerTool(nLep8): return False
    if not TQToolObservable.registerTool(nLep9): return False
    if not TQToolObservable.registerTool(nLep10): return False
    if not TQToolObservable.registerTool(nLep11): return False

    return True;

#  LocalWords:  nVetoMuon3
