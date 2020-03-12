Estimation of fakes in Att lephad analysis
=========================
The fakes, including lepton faking tau and jet faking tau, are estimated using the fake factor method.
In case you want to obtain these fake-factors, please follow the instructions below.

Lepton fake factor (Multijet)
-------------------------
The lepton fake factor (LFF) are derived from the lepton fake region (LFR). It is parameterized as 
a function of lepton pT and dphi. To obtain the LFF, 

```bash
# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-LeptonFakeRegion/scriptMerge.sh

# Calculate the lepton fake factor based on the histgrams 
python scripts/calculateFakeFactor.py LFR

# Put all the LFFs into one root file
hadd bsmtautau_lephad/auxData/FakeFactors/LFR_FF.root bsmtautau_lephad/auxData/FakeFactors/LFR*FF.root
```

After obtaining the LFF, we perform a closure test to check the modeling by applying the LFF back to the LFR.

```bash
# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptMerge.sh

# Visialize plots
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptVisualize.sh
```

From the above plots, we find the tau pT in muhad channel is not modelled well. Thus, a correction of the fake factor
is applied to the LFF in muhad channel. To obatin the correction factor

```bash
python scripts/calculateScaleFactor.py LFR

# Put all the LSFs into one root file
hadd bsmtautau_lephad/auxData/ScaleFactors/LFR_SF.root bsmtautau_lephad/auxData/ScaleFactors/LFR*SF.root
```

After obtaining the scale factor, we need to perfrom the closure test again.

```bash
# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptMerge.sh

# Visialize plots
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptVisualize.sh
``` 


Jet fake factor (Wjets/Top)
-------------------------
The jet fake factor are derived from the W/Top fake region. The Multijet backgrounds in WFR are estimated 
using the lepton fake factor. For the jet fake factor, it is parameterized as a function of tau pT.  
The b-tag category suffers from huge backgrounds from Top samples which overshots data in TCR. 
In order to obtain a accurate fake factor in b-tag category, we derive a top scale factor from TCR. 
The jet fakes are one of the backgrounds in TCR. As a start point, we need to assume the jet fake factor are 
the same as those in b-veto category when calculating the top scale factor. Then, we can derive the
jet factor in WFR. It is found that the dependence on tauPt are similar in
b-tag and b-veto category. So, we decide to apply the jet fake factors in b-veto category to b-tag cateogy
with a normalization factor. The normalization factor is defined as the ratio of the overall (1 bin) jet fake 
factor between b-tag and b-veto cateogy. The detailed procedures are listed below:

```bash
# As a starting point, assume the jet fake factor are the same between b-veto and b-tag category.
# Edit ../Root/JetFakes.cxx, comment Line 173 and Line 176, and recompile
cafcomple

# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-WjetsFakeRegion/scriptMerge.sh

# Calculate the jet fake factor based on the histgrams 
python scripts/calculateFakeFactor.py WFR

# Put all the jet fake factos into one root file
hadd bsmtautau_lephad/auxData/FakeFactors/WFR_FF.root bsmtautau_lephad/auxData/FakeFactors/WFR*FF.root
```

After obtaining the WFF, we perform a closure test to check the modeling by applying the WFF back to the WFR.

```bash
# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptMerge.sh

# Visialize plots
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptVisualize.sh
```

From the above plots, we find the lepton pT is not modelled well. Thus, a correction of the fake factor
is applied to the WFF. In addition, the top backgrounds in b-tag category is overestimated. A correction 
factor of top backgrounds are derived from TCR. To obtain these correction factors,

```bash
# Obtain the correction factor for fake factor
python scripts/calculateScaleFactor.py WFR

# Put all the scale factors into one root file
hadd bsmtautau_lephad/auxData/ScaleFactors/WFR_SF.root bsmtautau_lephad/auxData/ScaleFactors/WFR*SF.root

# Obtain the correction factor for top samples
python scripts/calculateScaleFactor.py TCR

# Put all the scale factors into one root file
hadd bsmtautau_lephad/auxData/ScaleFactors/TCR_SF.root bsmtautau_lephad/auxData/ScaleFactors/TCR*SF.root
```

After obtaining the scale factors, we need to perfrom the closure test again.

```bash
# The dependence on tauPt are similar between b-veto and b-tag categoy. Thus, we apply the jet fake factor
# in b-veto category to b-tag cateogy with a normalization factor. The normalization factor is defined as
# the ratio of the overall jet fake factor between b-tag and b-veto category. The values are 0.862 and 0.881
# for 1p and 3p, respectively. 
# Edit ../Root/JetFakes.cxx, uncomment Line 173 and Line 176, and recompile
cafcomple

# Debug test before sending the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptMerge.sh

# Visialize plots
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptVisualize.sh
``` 
