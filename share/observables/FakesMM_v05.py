from ROOT import *
from QFramework import *

def addObservables(config):
    dataset=config.getTagStringDefault("dataset","")
    if (dataset=="2015"):
        flag=15
    elif (dataset=="2016"):
        flag=16
    else:
        WARN("no dataset choosen, please use dataset=2015 or dataset=2016")
        flag=-1
    #release 20.1
    #infile = "fakes/FakesMM_150616.root"
    #infile = "fakes/FakesMM_220616.root"
    #release 20.7
    if flag==15:
        infile = "fakes/FakesMM_100716_ds2015.root"
    elif flag==16:
        infile = "fakes/FakesMM_150716_ds2016.root"
    syst=0
    systematic=str(config.getTagStringDefault("systematic",""))
    if systematic == "fakes_eff_var1":
        syst = 1
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var2":
        syst = 2
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var3":
        syst = 3
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var4":
        syst = 4
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var5":
        syst = 5
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var6":
        syst = 6
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var7":
        syst = 7
        INFO("fakes_eff_var "+str(syst))
    elif systematic == "fakes_eff_var8":
        syst = 8
        INFO("fakes_eff_var "+str(syst))
    FakeWeight = FakesMM_v05("FakeWeight", infile, syst,flag)
    if not TQTreeObservable.addObservable(FakeWeight):
        INFO("failed to add FakeWeight observable")
        return False
    return True
