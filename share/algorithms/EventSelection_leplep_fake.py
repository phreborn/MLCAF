from ROOT import *
from QFramework import *

def addAlgorithms(visitor,config):
    systematics_number=-1
    dataset=config.getTagStringDefault("dataset","")
    if (dataset=="2015"):
        flag=15
    elif (dataset=="2016"):
        flag=16
    else:
        WARN("no dataset choosen, please use dataset=2015 or dataset=2016")
        flag=-1
    try:
        eventselection = EventSelection_leplep_fake("EventSelection_leplep_fake",systematics_number,flag)
        return visitor.addAlgorithm(eventselection)
    except:
        return False
