Estimation of fakes in Att lephad analysis
=========================
The fakes, including lepton faking tau and jet faking tau, are estimated using the fake factor method.
In case you want to obtain these fake-factors, please follow the instructions below.

Lepton fake factor (Multijet)
-------------------------
The lepton fake factor (LFF) are derived from the lepton fake region (LFR). It is parameterized as 
a function of lepton pT. To obtain the LFF, 

```bash
# Debug test before sending the jobs to a cluster
source configLeptonFakeRegion/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configSignalControlRegion/scriptMerge.sh

# Calculate the lepton fake factor based on the histgrams 
python scripts/calculateFakeFactor.py LFR
```

After obtaining the LFF, we perform a closure test to check the modeling by applying the LFF back to the LFR.

```bash
# Debug test before sending the jobs to a cluster
source configLeptonFakeRegion/appFF/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/appFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configLeptonFakeRegion/appFF/scriptMerge.sh

# Visialize plots
source configLeptonFakeRegion/appFF/scriptVisualize.sh
```

From the above plots, we find the tau pT in muhad channel is not modelled well. Thus, a correction of the fake factor
is applied to the LFF in muhad channel. To obatin the correction factor

```bash
python scripts/calculateScaleFactor.py LFR
```

After obtaining the scale factor, we need to perfrom the closure test again.

```bash
# Debug test before sending the jobs to a cluster
source configLeptonFakeRegion/appFF/appSF/scriptDebug.sh

# Submit the analysis to a cluster
source configLeptonFakeRegion/appFF/appSF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configLeptonFakeRegion/appFF/appSF/scriptMerge.sh

# Visialize plots
source configLeptonFakeRegion/appFF/appSF/scriptVisualize.sh
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
```

After obtaining the WFF, we perform a closure test to check the modeling by applying the WFF back to the WFR.

```bash
# Debug test before sending the jobs to a cluster
source configWjetsFakeRegion/appFF/scriptDebug.sh

# Submit the analysis to a cluster
source configWjetsFakeRegion/appFF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configWjetsFakeRegion/appFF/scriptMerge.sh

# Visialize plots
source configWjetsFakeRegion/appFF/scriptVisualize.sh
```

From the above plots, we find the lepton pT is not modelled well. Thus, a correction of the fake factor
is applied to the WFF. In addition, the top backgrounds in b-tag category is overestimated. A correction 
factor of top backgrounds are derived from TCR. To obtain these correction factors,

```bash
# Obtain the correction factor for fake factor
python scripts/calculateScaleFactor.py WFR

# Obtain the correction factor for top samples
python scripts/calculateScaleFactor.py TCR
```

After obtaining the scale factors, we need to perfrom the closure test again.

```bash
# Debug test before sending the jobs to a cluster
source configWjetsFakeRegion/appFF/appSF/scriptDebug.sh

# Submit the analysis to a cluster
source configWjetsFakeRegion/appFF/appSF/scriptSubmit.sh

# Merge the output after all jobs are finished successfully
source configWjetsFakeRegion/appFF/appSF/scriptMerge.sh

# Visialize plots
source configWjetsFakeRegion/appFF/appSF/scriptVisualize.sh
``` 
