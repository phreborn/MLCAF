from QFramework import *
from ROOT import *

def addObservables(config):
    syst=0
    systematic=str(config.getTagStringDefault("systematic",""))
    if systematic=="jets_FT_EFF_Eigen_B_0_1down"                :
        syst = 1
        INFO("jets_FT_EFF_Eigen_B_0_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_0_1up":
        syst = 2
        INFO("jets_FT_EFF_Eigen_B_0_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_1_1down":
        syst = 3
        INFO("jets_FT_EFF_Eigen_B_1_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_1_1up":
        syst = 4
        INFO("jets_FT_EFF_Eigen_B_1_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_2_1down":
        syst = 5
        INFO("jets_FT_EFF_Eigen_B_2_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_2_1up":
        syst = 6
        INFO("jets_FT_EFF_Eigen_B_2_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_3_1down":
        syst = 7
        INFO("jets_FT_EFF_Eigen_B_3_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_3_1up":
        syst = 8
        INFO("jets_FT_EFF_Eigen_B_3_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_4_1down":
        syst = 9
        INFO("jets_FT_EFF_Eigen_B_4_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_B_4_1up":
        syst = 10
        INFO("jets_FT_EFF_Eigen_B_4_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_0_1down":
        syst = 11
        INFO("jets_FT_EFF_Eigen_C_0_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_0_1up":
        syst = 12
        INFO("jets_FT_EFF_Eigen_C_0_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_1_1down":
        syst = 13
        INFO("jets_FT_EFF_Eigen_C_1_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_1_1up":
        syst = 14
        INFO("jets_FT_EFF_Eigen_C_1_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_2_1down":
        syst = 15
        INFO("jets_FT_EFF_Eigen_C_2_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_2_1up":
        syst = 16
        INFO("jets_FT_EFF_Eigen_C_2_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_3_1down":
        syst = 17
        INFO("jets_FT_EFF_Eigen_C_3_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_C_3_1up":
        syst = 18
        INFO("jets_FT_EFF_Eigen_C_3_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_0_1down":
        syst = 19
        INFO("jets_FT_EFF_Eigen_Light_0_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_0_1up":
        syst = 20
        INFO("jets_FT_EFF_Eigen_Light_0_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_1_1down":
        syst = 21
        INFO("jets_FT_EFF_Eigen_Light_1_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_1_1up":
        syst = 22
        INFO("jets_FT_EFF_Eigen_Light_1_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_10_1down":
        syst = 23
        INFO("jets_FT_EFF_Eigen_Light_10_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_10_1up":
        syst = 24
        INFO("jets_FT_EFF_Eigen_Light_10_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_11_1down":
        syst = 25
        INFO("jets_FT_EFF_Eigen_Light_11_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_11_1up":
        syst = 26
        INFO("jets_FT_EFF_Eigen_Light_11_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_12_1down":
        syst = 27
        INFO("jets_FT_EFF_Eigen_Light_12_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_12_1up":
        syst = 28
        INFO("jets_FT_EFF_Eigen_Light_12_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_13_1down":
        syst = 29
        INFO("jets_FT_EFF_Eigen_Light_13_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_13_1up":
        syst = 30
        INFO("jets_FT_EFF_Eigen_Light_13_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_2_1down":
        syst = 31
        INFO("jets_FT_EFF_Eigen_Light_2_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_2_1up":
        syst = 32
        INFO("jets_FT_EFF_Eigen_Light_2_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_3_1down":
        syst = 33
        INFO("jets_FT_EFF_Eigen_Light_3_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_3_1up":
        syst = 34
        INFO("jets_FT_EFF_Eigen_Light_3_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_4_1down":
        syst = 35
        INFO("jets_FT_EFF_Eigen_Light_4_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_4_1up":
        syst = 36
        INFO("jets_FT_EFF_Eigen_Light_4_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_5_1down":
        syst = 37
        INFO("jets_FT_EFF_Eigen_Light_5_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_5_1up":
        syst = 38
        INFO("jets_FT_EFF_Eigen_Light_5_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_6_1down":
        syst = 39
        INFO("jets_FT_EFF_Eigen_Light_6_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_6_1up":
        syst = 40
        INFO("jets_FT_EFF_Eigen_Light_6_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_7_1down":
        syst = 41
        INFO("jets_FT_EFF_Eigen_Light_7_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_7_1up":
        syst = 42
        INFO("jets_FT_EFF_Eigen_Light_7_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_8_1down":
        syst = 43
        INFO("jets_FT_EFF_Eigen_Light_8_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_8_1up":
        syst = 44
        INFO("jets_FT_EFF_Eigen_Light_8_1up "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_9_1down":
        syst = 45
        INFO("jets_FT_EFF_Eigen_Light_9_1down "+str(syst))
    if systematic=="jets_FT_EFF_Eigen_Light_9_1up":
        syst = 46
        INFO("jets_FT_EFF_Eigen_Light_9_1up "+str(syst))
    if systematic=="jets_FT_EFF_extrapolation_1down":
        syst = 47
        INFO("jets_FT_EFF_extrapolation_1down "+str(syst))
    if systematic=="jets_FT_EFF_extrapolation_1up":
        syst = 48
        INFO("jets_FT_EFF_extrapolation_1up "+str(syst))
    if systematic=="jets_FT_EFF_extrapolation_from_charm_1down":
        syst = 49
        INFO("jets_FT_EFF_extrapolation_from_charm_1down "+str(syst))
    if systematic=="jets_FT_EFF_extrapolation_from_charm_1up":
        syst = 50
        INFO("jets_FT_EFF_extrapolation_from_charm_1up "+str(syst))
    mySFMVX = SF_MVX_ll_v05("SF_MVX",syst)
    if not TQTreeObservable.addObservable(mySFMVX):
        WARN("failed to add mySFMVX observable")
        return False
    return True
