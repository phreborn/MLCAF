from QFramework import *
from ROOT import *

def addObservables(config):

    myNSelecLep_ee = NSelecLep_ll_v05("NSelecLep_ee", "ee")
    if not TQTreeObservable.addObservable(myNSelecLep_ee):
        INFO("failed to add myNSelecLep_ee observable")
        return False

    myNSelecLep_mm = NSelecLep_ll_v05("NSelecLep_mm", "mm")
    if not TQTreeObservable.addObservable(myNSelecLep_mm):
        INFO("failed to add myNSelecLep_mm observable")
        return False

    myNSelecLep_em = NSelecLep_ll_v05("NSelecLep_em", "em")
    if not TQTreeObservable.addObservable(myNSelecLep_em):
        INFO("failed to add myNSelecLep_em observable")
        return False
    
    myNSelecLep_me = NSelecLep_ll_v05("NSelecLep_me", "me")
    if not TQTreeObservable.addObservable(myNSelecLep_me):
        INFO("failed to add myNSelecLep_me observable")
        return False

    myNSelecLep_ee_fake = NSelecLep_ll_v05("NSelecLep_ee_fake", "ee")
    if not TQTreeObservable.addObservable(myNSelecLep_ee_fake):
        INFO("failed to add myNSelecLep_ee_fake observable")
        return False

    myNSelecLep_mm_fake = NSelecLep_ll_v05("NSelecLep_mm_fake", "mm")
    if not TQTreeObservable.addObservable(myNSelecLep_mm_fake):
        INFO("failed to add myNSelecLep_mm_fake observable")
        return False

    myNSelecLep_em_fake = NSelecLep_ll_v05("NSelecLep_em_fake", "em")
    if not TQTreeObservable.addObservable(myNSelecLep_em_fake):
        INFO("failed to add myNSelecLep_em_fake observable")
        return False

    myNSelecLep_me_fake = NSelecLep_ll_v05("NSelecLep_me_fake", "me")
    if not TQTreeObservable.addObservable(myNSelecLep_me_fake):
        INFO("failed to add myNSelecLep_me_fake observable")

    return True


