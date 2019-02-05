from QFramework import *
from ROOT import *

def addObservables(config):

    sysList = [ 
    "",
    "Eigen_B_0_1down",               
    "Eigen_B_0_1up",                 
    "Eigen_B_1_1down",               
    "Eigen_B_1_1up",                 
    "Eigen_B_2_1down",               
    "Eigen_B_2_1up",                 
    "Eigen_B_3_1down",               
    "Eigen_B_3_1up",                 
    "Eigen_B_4_1down",               
    "Eigen_B_4_1up",                 
    "Eigen_C_0_1down",               
    "Eigen_C_0_1up",                 
    "Eigen_C_1_1down",               
    "Eigen_C_1_1up",                 
    "Eigen_C_2_1down",               
    "Eigen_C_2_1up",                 
    "Eigen_C_3_1down",               
    "Eigen_C_3_1up",                 
    "Eigen_Light_0_1down",           
    "Eigen_Light_0_1up",             
    "Eigen_Light_1_1down",           
    "Eigen_Light_1_1up",             
    "Eigen_Light_10_1down",          
    "Eigen_Light_10_1up",            
    "Eigen_Light_11_1down",          
    "Eigen_Light_11_1up",            
    "Eigen_Light_12_1down",          
    "Eigen_Light_12_1up",            
    "Eigen_Light_13_1down",          
    "Eigen_Light_13_1up",            
    "Eigen_Light_2_1down",           
    "Eigen_Light_2_1up",             
    "Eigen_Light_3_1down",           
    "Eigen_Light_3_1up",             
    "Eigen_Light_4_1down",           
    "Eigen_Light_4_1up",             
    "Eigen_Light_5_1down",           
    "Eigen_Light_5_1up",             
    "Eigen_Light_6_1down",           
    "Eigen_Light_6_1up",             
    "Eigen_Light_7_1down",           
    "Eigen_Light_7_1up",             
    "Eigen_Light_8_1down",           
    "Eigen_Light_8_1up",             
    "Eigen_Light_9_1down",           
    "Eigen_Light_9_1up",             
    "extrapolation_1down",           
    "extrapolation_1up",             

    "extrapolation_charm_down",      
    "extrapolation_charm_up",        
    ];

    for name in sysList : 
        mybtagEffSys= btagEffSys("btagEffSf"+name)
        if not TQTreeObservable.addObservable(mybtagEffSys):
            INFO("failed to add mybtagEffSys observable")
            return False
        print(mybtagEffSys.getExpression()) 

#    for name in ["MuTrigSysStatUp" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 
#
#    for name in ["MuTrigSysStatDo" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 
#
#    for name in ["MuTrigSysSystUp" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 
#
#    for name in ["MuTrigSysSystDo" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 
#
#    for name in ["ElTrigSysUp" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 
#
#    for name in ["ElTrigSysDo" ] : 
#        mybtagEffSys= btagEffSys("btagEffSys"+name)
#        if not TQTreeObservable.addObservable(mybtagEffSys):
#            INFO("failed to add mybtagEffSys observable")
#            return False
#        print(mybtagEffSys.getExpression()) 

    return True
