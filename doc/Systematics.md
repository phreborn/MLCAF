Systematic uncertainty estimation
=================================

While the nominal analysis with statistical uncertainties may be calculated, with all the corrections applied, further mismodelling could still be observed in the CR/VR/SR.  
This may be reasonably covered by systematic uncertainties from each of the detector components, the MC simulation and other theory studies.  
The calculation of systematic uncertainties is highly intensive, as essentially it means re-running the entire analysis multiple times over for each responsible variation, of which there can be hundreds.  

Preparing and initializing inputs
---------------------------------

Firstly, it must be recognised that many of the systematics are provided in a second set of input samples, which are commonly produced much later than the first set that would have been used in calculating the nominal analysis.  
Therefore, we classify the systematics into two types depending on which sample inputs they use:
- NOM-based (as used in the nominal analysis)
- SYS-based (produced some time after NOM)
For the time being, you may immediately progress with calculating the NOM-based systematics, skipping to the next section.  
But please check back on this section once you are aware that the SYS-based sample inputs are ready for use.  

Once these SYS-based samples are ready, then please check the input preparation [instructions](doc/Analysis.md) again that you have these samples fully available.  
When you have the SYS-based input samples available, then once again these must be initialized by the framework.
```bash
# Initialize your samples
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptInitialize.sh
```

Calculating systematic uncertainties
------------------------------------

The systematic uncertainties are calculated based on the final CR/VR/SR part of the analysis, and likewise this is where they will be applied.  
There can be hundreds of systematic variations to estimate, but many of which can be grouped together since they share the same methods for calculation.  
Systematics are processed only over MC samples, so data processing is excluded here.  

First calculate the systematic uncertainties using the NOM-based inputs, as these will usually include variations that were calculated during the nominal analysis itself (such as from FFs and SFs).  
Naturally, these systematics will be SF-based, applied as weights to the nominal analysis.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptDebug.sh NOM

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptSubmit.sh lff lsf wff wsf vsf

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptMerge.sh lff lsf wff wsf vsf
```

Once the SYS-based inputs are ready, first referring to the instructions above, calculate these systematic uncertainties next.  
These variations are usually supplied within the input itself, as both SF-based weights provided through branches in the primary input tree, and p4-based selections provided through alternative kinematic trees.  

```bash
# Debug test the analysis before submitting the jobs to a cluster
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptDebug.sh SYS

# Submit the full analysis to a cluster
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptSubmit.sh lpx top weight p4

# After all jobs are finished successfully, merge the output
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptMerge.sh lpx top weight p4
```

With each of these systematic variations calculated, the differences in their results can be taken from the original nominal analysis.  
This generates the systematic uncertainty as a value, which can be applied back into the original nominal results as an additional band of uncertainty.  
This can be used to verify for the final time the full results of the analysis with systematic uncertainties.  

```bash
# After all merges are finished successfully, merge the systematics together with nominal
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptMerge.sh ALL

# Generate the systematic uncertainty band files
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptGenerate.sh

# Visualize the plots
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptVisualize.sh
```

Congratulations, you now have a complete set of results!

Producing workspace inputs
--------------------------

While this concludes the CAF analysis for background, signal and systematic uncertainty estimation, there is still more work that needs to be done.  
This work usually involves post-fitting the results, studying the systematic uncertainty behaviour and applying exclusion limits to BSM models.  
As such, this work is done by alternative frameworks outside of CAF, for which the special TQROOT files generated here are not compatible.  
So we must first convert the output into an appropriate format as input for these external frameworks, by dumping the raw histograms into standard ROOT files.  
We dump the histograms produced in the TCR and SR for each process, with all systematic variations included.  

```bash
# Dump the CAF histograms to standard ROOT files
source bsmtautau_lephad/config-SignalControlRegion/syst/scriptDumpHist.sh
```

The external frameworks will then generate an independent workspace on which it will continue its studies.  
For this, we will use [WSMaker](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/WSMaker_Htautau).
