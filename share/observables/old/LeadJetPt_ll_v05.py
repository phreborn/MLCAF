from QFramework import *
from ROOT import *

def addObservables(config):

    myLeadJetPt = LeadJetPt_ll_v05("LeadJetPt")

    if not TQTreeObservable.addObservable(myLeadJetPt):
        INFO("failed to add myLeadJetPt observable")
        return False
    
    return True


