# this script reads all the different config files
# and makes plots for all regions

LABEL_PROCESS="H#rightarrow#tau_{lep}#tau_{had}"
LABEL_EHAD="(e#tau_{had})"
LABEL_MUHAD="(#mu#tau_{had})"
LABEL_LEPHAD="(#tau_{lep}#tau_{had})"


#############################
###
### WCR
###
##############################
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR $LABEL_MUHAD"



python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjets_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjets_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR W+jets $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjets_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjets_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR W+jets $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_qcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_qcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_qcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_qcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR QCD $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjetsqcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjetsqcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR W+jets QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjetsqcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS WCR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_wcr_wjetsqcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS WCR W+jets QCD $LABEL_MUHAD"





#############################
###
### VR
###
##############################
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR $LABEL_MUHAD"



python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjets_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjets_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR W+jets $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjets_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjets_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR W+jets $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_qcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_qcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_qcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_qcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR QCD $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjetsqcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjetsqcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR W+jets QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjetsqcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS VR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_vr_wjetsqcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS VR W+jets QCD $LABEL_MUHAD"




#############################
###
### TCR
###
##############################
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR $LABEL_MUHAD"



python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjets_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjets_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR W+jets $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjets_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR W+jets $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjets_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR W+jets $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_qcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_qcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_qcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_qcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR QCD $LABEL_MUHAD"




python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjetsqcd_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjetsqcd_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR W+jets QCD $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjetsqcd_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS TCR W+jets QCD $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_tcr_wjetsqcd_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS TCR W+jets QCD $LABEL_MUHAD"



#############################
###
### SR
###
##############################
python readAnalysis.py ConfigSignalRegion/htautau_lephad_sr_mc16a.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS SR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_sr_mc16a.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS SR $LABEL_MUHAD"

python readAnalysis.py ConfigSignalRegion/htautau_lephad_sr_mc16c.cfg --options channels:ehad  plotter.labels.process:"$LABEL_PROCESS SR $LABEL_EHAD"
python readAnalysis.py ConfigSignalRegion/htautau_lephad_sr_mc16c.cfg --options channels:muhad plotter.labels.process:"$LABEL_PROCESS SR $LABEL_MUHAD"
