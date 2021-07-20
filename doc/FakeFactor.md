Fake background estimation
==========================

Part of the background estimation for this analysis strongly involves contributions from misidentified candidates (fakes).  
The fakes are estimated using a data-driven Fake Factor (FF) method, by comparing the ratio of data passing/failing certain requirements:  

$`FF = \frac{ (N_{\textrm{data}} - N_{\textrm{bkg}})^{\textrm{pass}} }{ (N_{\textrm{data}} - N_{\textrm{bkg}})^{\textrm{fail}} }`$

Fake Regions (FR) are defined to enrich the contributions from these fakes so that they can be accurately measured, although real background corrections are applied using MC.  

The analysis categorises these fakes into two estimated components:  
- QCD MultiJet Fake Region
  - Lepton/multi-jet (Quantum ChromoDynamic, QCD) processes faking leptons/taus
    - Both are closely orthogonal to each other
  - Generally sourced from gluon-initiated jets
  - Separated by passing/failing lepton isolation requirements
- W+jets/Top (Other) Fake Region (WFR/TFR)
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

Top Correction Factor (TCR)
----------------------------

Firstly, to constrain the top background we calculate a top correction factor which is applied to the SR. 
We must calculate this first as it is effective in the btag region as it prevents zero fake factor values. 

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/TCR/analyze-debug-TCR-SF.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/TCR/analyze-submit-TCR-SF.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/TCR/analyze-merge-TCR-SF.sh

# Calculate the fake factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py AHZ-lephad TCR # Use the hadd command which is output

```

After obtaining the weight, perform a closure test to check the modelling by applying the TSF back into the TCR.

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/TCR/analyze-debug-TCR-SF-closure.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/TCR/analyze-submit-TCR-SF-closure.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/TCR/analyze-merge-TCR-SF-closure.sh

# Visualize the plots
source AHZ-lephad/config/TCR/visualize-TCR-SF-closure.sh
```

QCD MultiJet fake region (QCDLFR)
----------------------------

The QCD Lepton Fake Factor (LFF) is parameterized as a function of lepton $`p_{\textrm{T}}`$ and $`d\phi`$.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-debug-MultiJetsLFR-FF.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-submit-MultiJetsLFR-FF.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/MultiJetsLFR/analyze-merge-MultiJetsLFR-FF.sh

# Calculate the fake factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateFakeFactor.py AHZ-lephad MultiJetLFR # Use the hadd command which is output

```

After obtaining the LFF, perform a closure test to check the modelling by applying the LFF back into the QCDLFR.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-debug-MultiJetsLFR-FF-closure.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-submit-MultiJetsLFR-FF-closure.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/MultiJetsLFR/analyze-merge-MultiJetsLFR-FF-closure.sh

# Visualize the plots
source AHZ-lephad/config/MultiJetsLFR/visualize-MultiJetsLFR-FF-closure.sh
```

It is found that numerous parameters are still mismodelled, a correction gives limited improvement to the fake estimation
Thus, a MultiJet Scale Factor (LSF) is calculated but used as a systematic uncertainty and not applied in the SR

This part is not necessary if not running systematics but if you are it may be useful to check the closure
```bash
# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py AHZ-lephad MultiJetsLFR # use the hadd command which is output

# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-debug-MultiJetsLFR-FF-SF-closure.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/MultiJetsLFR/analyze-submit-MultiJetsLFR-FF-SF-closure.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/MultiJetsLFR/analyze-merge-MultiJetsLFR-FF-SF-closure.sh

# Visualize the plots
source AHZ-lephad/config/MultiJetsLFR/visualize-MultiJetsLFR-FF-SF-closure.sh
``` 

W+jets/Top (OtherJets) Fake Region (WFR/TFR)
--------------------------------

The W+jets/Top Fake Factors (WFF/TFF) are parameterized as a function of tau $`p_{\textrm{T}}`$.  
The WFF is calculated mainly in the b-veto category, while the TFF is calculated mainly in the b-tag category.  
They can be distinguished by allocating the WFF to an Opposite Sign (OS) charged tau selection, and the TFF to a Same Sign (SS).  

The LFF is applied into this region, forming part of the background subtraction, so it must be calculated first.  
Likewise, while it may be inversely true that the WFF would form a contribution in the LFR, the W+jets fake component in the LFR is instead estimated by MC.  
It would be found that an interative re-calculation of these pairs of fake factors leads to negligible differences in the results.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-debug-FF.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-submit-FF.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/OtherJetsTFR/analyze-merge-FF.sh

# Calculate the fake factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateFakeFactor.py AHZ-lephad OtherJetsTFR # use the hadd command which is output

```

After obtaining the WFF/TFF, perform a closure test to check the modelling by applying the WFF/TFF back into the WFR/TFR.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-debug-FF-closure.sh

# Submit the full analysis to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-submit-FF-closure.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/OtherJetsTFR/analyze-merge-FF-closure.sh

# Visualize the plots
source AHZ-lephad/config/OtherJetsTFR/visualize-FF-closure.sh
```

It is found that lepton $`p_{\textrm{T}}`$ in the WFR is not well modelled.  
Thus, a W+jets Scale Factor (WSF) is calculated and the closure test re-performed.  


```bash
# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py AHZ-lephad # use the hadd command which is output

# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-debug-FF-SF-closure.sh 

# Submit the full analysis to a cluster
source AHZ-lephad/config/OtherJetsTFR/analyze-submit-FF-SF-closure.sh

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/OtherJetsTFR/analyze-merge-FF-SF-closure.sh

# Visualize the plots
source AHZ-lephad/config/OtherJetsTFR/visualize-FF-SF-closure.sh
```
