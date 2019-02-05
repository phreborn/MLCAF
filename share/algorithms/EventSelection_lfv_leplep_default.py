from ROOT import *
from QFramework import *
import systematicsHandler

def addAlgorithms(visitor,config):
    dataset=config.getTagStringDefault("dataset","")
    if (dataset=="2015"):
        flag=15
    elif (dataset=="2016"):
        flag=16
    else:
        WARN("no dataset choosen, please use dataset=2015 or dataset=2016")
        flag=-1
        flag=-1
    systematic=""
    systematics,systematicMap =systematicsHandler.checkForSystematics(config,True)
    plainmap=ROOT.std.map(TString,int)()
    systematics_number=-1
    if systematics:
        systematic=systematics.name
        WARN("systematics found, will run "+systematic+" / "+str(systematics.number))
        for syst in systematicMap:
            plainmap[TString(syst)]=systematicMap[syst].number
        systematics_number=systematics.number
    try:
        eventselection = EventSelection_lfv_leplep_default("EventSelection_lfv_leplep_default",systematics_number,flag)
        eventselection.provideSystematicMap(plainmap); 
        return visitor.addAlgorithm(eventselection)
    except:
        return False
