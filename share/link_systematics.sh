SYSTYPES="
         CP_jet_p4
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
         Theory_Zjets
         Top_Reweight
         Top_Residual
         "

for systype in ${SYSTYPES}
do
  python LQtaub-lephad/config/SYS/submit_systematics.py --systype ${systype}
done
