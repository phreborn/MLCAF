#example for python based cut definition, equivalent to the tqfolder based version
#to use this style of cut definitions it is sufficient to list this file just like
#the TQFolder syntax based ones (even mixed usage is possible)

from CommonAnalysisHelpers.analyze import PyCut

def addCuts(config,baseCut):
  print("adding cuts via python...")
  #use += if you want to continue assigning more subsequent cuts
  baseCut+= PyCut("CutChannels", cut="$(fitsChannel)", weight="Weight_$(weightname):$(cand)", options={".title":"Channel Selection"} )
  baseCut+= PyCut("CutVgammaVjet_overlap", cut="{ $(isVjets) ? $(Truth_hasFSRPhotonDR01)==0 : 1 }", options={".title":"Overlap: Vgamma/Vjets"} )
  baseCut+= PyCut("CutOtherLep", cut="$(lllFinalState)", options={".title":"lll final state"} )
  baseCut+= PyCut("CutZMass", cut="[ZBosonPairFakeIndex]==3 || [ZBosonPairFakeIndex]==2 || [ZBosonPairFakeIndex]==1", options={".title":"Z-tagging"} )
  baseCut+= PyCut("CutLeptonsPt", cut="$(lep0).pt() > 15000 && $(lep1).pt() > 15000 && $(otherPart0).pt() > 15000", options={".title":"lep $p_T > 15$ GeV"} )
  baseCut+= PyCut("CutWZVeto", cut="$(PassWZVeto)", options={".title":"WZ veto"} )
  
  #create cut branches after "CutWZVeto"
  fakeEl = baseCut["CutWZVeto"] 
  fakeEl += PyCut("CutFakeEl", cut="$(fakeLepCand_type) == $(electron)", options={".title":"fake type: electron"} )
  fakeEl += PyCut("CutEtaFakeElec", cut="(fabs($(fakeLepCand_eta)) < 2.47 && (fabs($(fakeLepCand_eta)) < 1.37 || fabs($(fakeLepCand_eta)) > 1.52))", options={".title":"Fake el eta cut"} )
  
  #create more sub branches (without explicit re-assignment)
  fakeEl["CutEtaFakeElec"] + PyCut("CutFakeElecID", cut = "$(fakeLepCand_id)", options={".title": "Fake el ID"} )
  fakeEl["CutEtaFakeElec"] + PyCut("CutFakeElecAntiID", cut = "$(fakeLepCand_antiid)", options={".title": "Fake el Anti-ID"} )
  
  #create cut branches after "CutWZVeto"
  fakeMu = baseCut["CutWZVeto"] 
  fakeMu += PyCut("CutFakeMu", cut="$(fakeLepCand_type) == $(muon)", options={".title":"fake type: muon"} )
  fakeMu += PyCut("CutEtaFakeMuon", cut="fabs($(fakeLepCand_eta)) < 2.5", options={".title":"Fake mu |eta|<2.5"} )
  
  #create more sub branches (without explicit re-assignment)
  fakeMu["CutEtaFakeMuon"] + PyCut("CutFakeMuonID", cut = "$(fakeLepCand_id)", options={".title": "Fake mu ID"} )
  fakeMu["CutEtaFakeMuon"] + PyCut("CutFakeMuonAntiID", cut = "$(fakeLepCand_antiid)", options={".title": "Fake mu Anti-ID"} )
  
  
  return True
