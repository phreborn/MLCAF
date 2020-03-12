Fake background estimation
==========================

Part of the background estimation for this analysis strongly involves contributions from misidentified candidates (fakes).  
The fakes are estimated using a data-driven Fake Factor (FF) method, by comparing the ratio of data passing/failing certain requirements:  
- formula here
Fake Regions (FR) are defined to enrich the contributions from these fakes so that they can be accurately measured, although real background corrections are applied using MC.  

The analysis categorises these fakes into two estimated components:  
- Lepton/QCD Fake Region (LFR)
  - Lepton/multi-jet (Quantum ChromoDynamic, QCD) processes faking leptons/taus
    - Both are closely orthogonal to each other
  - Generally sourced from gluon-initiated jets
  - Separated by passing/failing lepton isolation requirements
- W+jets/Top Fake Region (WFR/TFR)
  - W+jets/top-quark processes faking taus
    - Depending on the presence of bottom-quarks in the event
      - W+jets fakes correlated with b-veto category (WFR)
      - Top-quark fakes correlated with b-tag category (TFR)
  - Generally sourced from quark-initiated jets
  - Separated by passing/failing tau identification requirements

In each of these regions, the FF is calculated for that process and stored as a ROOT file for later use in the analysis.  
The FF estimation is parameterized as a function of a subset of selected variables.  
The systematic uncertainty attributed to that FF estimation is also calculated and stored.  

After the FF calculation, a closure test is performed to check the background modelling by applying the FF back into the FR.  
We expect the fake contribution to be fully revealed by the FF, and should match well with the data and MC.  
At this stage, the FR becomes a completed Fake Control Region (FCR).  

In case of any further mismodelling, the process is essentially repeated by identifying the troublesome variables.  
An additional Scale Factor (SF) ROOT file is calculated while parameterizing over those variables, where this should meet the difference.  
This SF multiplicatively corrects the FF, while attributing its systematic uncertainity.  

Lepton/QCD Fake Region (LFR)
----------------------------

The Lepton/QCD Fake Factor (LFF) is parameterized as a function of lepton $`p_{\textrm{T}}`$ and $`d\phi`$.

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-LeptonFakeRegion/scriptMerge.sh

# Calculate the fake factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateFakeFactor.py LFR
hadd bsmtautau_lephad/auxData/FakeFactors/LFR_FF.root bsmtautau_lephad/auxData/FakeFactors/LFR*FF.root
```

After obtaining the LFF, perform a closure test to check the modelling by applying the LFF back into the LFR.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptMerge.sh

# Visualize the plots
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/scriptVisualize.sh
```

It is found that tau $`p_{\textrm{T}}`$ in the $`\tau_{\mu}\tau_{\textrm{had}}`$ channel is not well modelled.  
Thus, a Lepton/QCD Scale Factor (LSF) is calculated and the closure test re-performed.  

```bash
# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py LFR
hadd bsmtautau_lephad/auxData/ScaleFactors/LFR_SF.root bsmtautau_lephad/auxData/ScaleFactors/LFR*SF.root

# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptMerge.sh

# Visualize the plots
source bsmtautau_lephad/config-LeptonFakeRegion/applyFF/applySF/scriptVisualize.sh
``` 

W+jets/Top Fake Region (WFR/TFR)
--------------------------------

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
