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
source configLeptonFakeRegion/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configLeptonFakeRegion/scriptMerge.sh

# Calculate the lepton fake factor based on the histgrams 
python scripts/calculateFakeFactor.py LFR

# Put all the LFFs into one root file
hadd FakeFactors/LFR_FF.root FakeFactors/LFR*FF.root
```

After obtaining the LFF, we perform a closure test to check the modeling by applying the LFF back to the LFR.

```bash
# Debug test before sending the jobs to a cluster
source configLeptonFakeRegion/applyFF/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/applyFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configLeptonFakeRegion/applyFF/scriptMerge.sh

# Visialize plots
source configLeptonFakeRegion/applyFF/scriptVisualize.sh
```

From the above plots, we find the tau pT in muhad channel is not modelled well. Thus, a correction of the fake factor
is applied to the LFF in muhad channel. To obatin the correction factor

```bash
python scripts/calculateScaleFactor.py LFR

# Put all the LSFs into one root file
hadd ScaleFactors/LFR_SF.root ScaleFactors/LFR*SF.root
```

After obtaining the scale factor, we need to perfrom the closure test again.

```bash
# Debug test before sending the jobs to a cluster
source configLeptonFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/applyFF/applySF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configLeptonFakeRegion/applyFF/applySF/scriptMerge.sh

# Visialize plots
source configLeptonFakeRegion/applyFF/applySF/scriptVisualize.sh
``` 


Jet fake factor (Wjets/Top)
-------------------------
The jet fake factor are derived from the W/Top fake region. The Multijet backgrounds in WFR are estimated 
using the lepton fake factor. For the jet fake factor, it is parameterized as a function of tau pT. To obtain
the jet fake factor,

```bash
# Debug test before sending the jobs to a cluster
source configWjetsFakeRegion/scriptDebug.sh

# Submit the analysis to a cluster
source configWjetsFakeRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configWjetsFakeRegion/scriptMerge.sh

# Calculate the jet fake factor based on the histgrams 
python scripts/calculateFakeFactor.py WFR

# Put all the jet fake factos into one root file
hadd FakeFactors/WFR_FF.root FakeFactors/WFR*FF.root
```

After obtaining the WFF, we perform a closure test to check the modeling by applying the WFF back to the WFR.

```bash
# Debug test before sending the jobs to a cluster
source configWjetsFakeRegion/applyFF/scriptDebug.sh

# Submit the analysis to a cluster
source configWjetsFakeRegion/applyFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configWjetsFakeRegion/applyFF/scriptMerge.sh

# Visialize plots
source configWjetsFakeRegion/applyFF/scriptVisualize.sh
```

From the above plots, we find the lepton pT is not modelled well. Thus, a correction of the fake factor
is applied to the WFF. In addition, the top backgrounds in b-tag category is overestimated. A correction 
factor of top backgrounds are derived from TCR. To obtain these correction factors,

```bash
# Obtain the correction factor for fake factor
python scripts/calculateScaleFactor.py WFR

# Put all the scale factors into one root file
hadd ScaleFactors/WFR_SF.root ScaleFactors/WFR*SF.root

# Obtain the correction factor for top samples
python scripts/calculateScaleFactor.py TCR

# Put all the scale factors into one root file
hadd ScaleFactors/TCR_SF.root ScaleFactors/TCR*SF.root
```

After obtaining the scale factors, we need to perfrom the closure test again.

```bash
# Debug test before sending the jobs to a cluster
source configWjetsFakeRegion/applyFF/applySF/scriptDebug.sh

# Submit the analysis to a cluster
source configWjetsFakeRegion/applyFF/applySF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configWjetsFakeRegion/applyFF/applySF/scriptMerge.sh

# Visialize plots
source configWjetsFakeRegion/applyFF/applySF/scriptVisualize.sh
``` 
