### SR and VR
SYSTYPES="
         CP_jet_p4_common
         CP_jet_p4_bkg
         CP_jet_p4_sig
         CP_lep_p4
         CP_lep_weight
         CP_tau_weight
         CP_other_weight
         MCFakes
         MultiJetsLFR
         Theory_Top_FSRdo
         Theory_Top_FSRup
         Theory_Top_ISRdo
         Theory_Top_ISRup
         Theory_Top_ME
         Theory_Top_PS
         Theory_Top_STopFSRdo
         Theory_Top_STopFSRup
         Theory_Top_STopISRdo
         Theory_Top_STopISRup
         Theory_Top_STopME
         Theory_Top_STopPS
         Theory_Top_STopWTInt
         Theory_Zjets
         Top_Reweight
         Top_Residual
         "
#SYSTYPES="
#         Theory_Top_PDFdo
#         Theory_Top_PDFup
#         Theory_Top_STopPDFdo
#         Theory_Top_STopPDFup
#         "
#SYSTYPES="MCFakes"
### MultiJetsLFR
#SYSTYPES="
#         MultiJetsLFR
#         Top_Reweight
#         "
### OtherJetsSSR
#SYSTYPES="
#         MCFakes
#         MultiJetsLFR
#         Theory_Top_FSRdo
#         Theory_Top_FSRup
#         Theory_Top_ISRdo
#         Theory_Top_ISRup
#         Theory_Top_ME
#         Theory_Top_PS
#         Theory_Top_STopFSRdo
#         Theory_Top_STopFSRup
#         Theory_Top_STopISRdo
#         Theory_Top_STopISRup
#         Theory_Top_STopME
#         Theory_Top_STopPS
#         Top_Reweight
#         "

for systype in ${SYSTYPES}
do
#  python LQtaub-lephad/config/SYS/submit_systematics.py --systype ${systype}
#  python LQtaub-lephad/config/MultiJetsLFR-SYS/submit_systematics.py --systype ${systype}
#  python LQtaub-lephad/config/OtherJetsSSR-SYS/submit_systematics.py --systype ${systype}
  python LQtaub-lephad/config/ZCR-SYS/submit_systematics.py --systype ${systype}
done
