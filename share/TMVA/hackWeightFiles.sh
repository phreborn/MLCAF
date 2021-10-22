#!/bin/bash

sed -i 's/tau_pt/tau_0_p4.Pt()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/lep_pt/lep_0_p4.Pt()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/tau_eta/tau_0_p4.Eta()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/lep_eta/lep_0_p4.Eta()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/tau_phi/tau_0_p4.Phi()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/lep_phi/lep_0_p4.Phi()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/MET/met_reco_p4.Et()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/vis_mass/lephad_p4.M()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/bjet_pt/bjet_0_p4.Pt()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/bjet_phi/bjet_0_p4.Phi()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/bjet_eta/bjet_0_p4.Eta()/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
#sed -i 's/signal_mass/\[signal_mass\]/g' dataset_bveto_201215_NN_*GeV_fabsWeights/weights/*.xml
#sed -i 's/MTtot/\[MTtot\]/g' dataset_bveto_201215_NN_*GeV_fabsWeights/weights/*.xml
#sed -i 's/lephad_p4.M()/\[lephad_p4.M()\]/g' dataset_bveto_201215_NN_*GeV_fabsWeights/weights/*.xml
sed -i 's/\_D\_/\//g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
sed -i 's/\_M\_/-/g' dataset_bveto_201215_BDT_*GeV_fabsWeights/weights/*.xml
