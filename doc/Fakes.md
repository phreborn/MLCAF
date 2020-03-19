Fake background estimation
==========================

Part of the background estimation for this analysis strongly involves contributions from misidentified candidates (fakes).  
The fakes are estimated using a data-driven Fake Factor (FF) method, by comparing the ratio of data passing/failing certain requirements:  

$`FF = \frac{ (N_{\textrm{data}} - N_{\textrm{bkg}})^{\textrm{pass}} }{ (N_{\textrm{data}} - N_{\textrm{bkg}})^{\textrm{fail}} }`$

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
hadd -f bsmtautau_lephad/auxData/FakeFactors/LFR_FF.root bsmtautau_lephad/auxData/FakeFactors/LFR*FF.root
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
hadd -f bsmtautau_lephad/auxData/ScaleFactors/LFR_SF.root bsmtautau_lephad/auxData/ScaleFactors/LFR*SF.root

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

The W+jets/Top Fake Factors (WFF/TFF) are parameterized as a function of tau $`p_{\textrm{T}}`$.  
The WFF is calculated in the b-veto category, while the TFF is calculated in the b-tag category.  

The LFF is applied into this region, forming part of the background subtraction, so it must be calculated first.  
Likewise, while it may be inversely true that the WFF would form a contribution in the LFR, the W+jets fake component in the LFR is instead estimated by MC.  
It would be found that an interative re-calculation of these pairs of fake factors leads to negligible differences in the results.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-WjetsFakeRegion/scriptMerge.sh

# Calculate the fake factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateFakeFactor.py WFR
hadd -f bsmtautau_lephad/auxData/FakeFactors/WFR_FF.root bsmtautau_lephad/auxData/FakeFactors/WFR*FF.root
```

After obtaining the WFF/TFF, perform a closure test to check the modelling by applying the WFF/TFF back into the WFR/TFR.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptMerge.sh

# Visualize the plots
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/scriptVisualize.sh
```

It is found that lepton $`p_{\textrm{T}}`$ in the WFR is not well modelled.  
Thus, a W+jets Scale Factor (WSF) is calculated and the closure test re-performed.  

Additionally, it is observed that the b-tag category would suffer from strong mismodelling in tau $`p_{\textrm{T}}`$ due to the real top-quark contribution.  
As such, the Top Scale Factor (TSF) derived from the real Top Control Region (TCR) is required to obtain an accurate TFF.  
However, since the TFF would form a contribution in the TCR, the TFF is instead assumed to be the same as the WFF from the b-veto category.  
Once the TSF has been calculated, the TFF (now the same as the WFF) can then be reweighted to give more accurate modelling in the b-tag category.  
But since the TFF itself is no longer being directly used, it still turns out that the dependence on tau $`p_{\textrm{T}}`$ between the b-veto and b-tag categories are not too dissimilar.  
As such, the WFF is applied in the b-tag category with an additional normalisation factor, defined as the ratio of the overall (single bin) FF between the original TFF and the WFF.  
These normalisation factors are evaluated separately for 1-prong and 3-prong taus.  

```bash
# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py WFR
hadd -f bsmtautau_lephad/auxData/ScaleFactors/WFR_SF.root bsmtautau_lephad/auxData/ScaleFactors/WFR*SF.root

# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py TCR
hadd -f bsmtautau_lephad/auxData/ScaleFactors/TCR_SF.root bsmtautau_lephad/auxData/ScaleFactors/TCR*SF.root

# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptSubmit.sh

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptMerge.sh

# Visualize the plots
source bsmtautau_lephad/config-WjetsFakeRegion/applyFF/applySF/scriptVisualize.sh
```
