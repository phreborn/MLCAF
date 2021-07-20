Running the $`\tau_{\textrm{Lep}}\tau_{\textrm{Had}}`$ analysis
===============================================================

Navigate to the execution directory to begin
```bash
cd BSMtautauCAF/share
```

Preparing and initializing inputs
---------------------------------

First you need to collect the list of input sample ROOT files you will be running over in the analysis.  
These will include both data recorded by the ATLAS detector and simulated Monte Carlo (MC), for each year and campaign of operation.  
Our framework is currently designed to run over flat ntuples produced by the [xTauFramework](https://gitlab.cern.ch/atlas-phys-hdbs-htautau/xTauFramework).  
It may be preferable to use pre-slimmed/skimmed samples where possible, in order to gain an improvement in performance.  
Unless you change these samples, this step will only need to be run once.  
```bash
# Define the remote locations of your input samples by pinging them on EOS through XRootD
source AHZ-lephad/config/common/samples/inputFileLists/collectSamples.sh eosatlas "/eos/atlas/path/to/my/ntuples/YYMMDD"
# Alternatively, this can be switched to access the EOS user area instead
#source AHZ-lephad/config/common/samples/inputFileLists/collectSamples.sh eosuser "/eos/user/path/to/my/ntuples/YYMMDD"
# Or, you could set the input path to your samples by pointing to any other local directory
#source AHZ-lephad/config/common/samples/inputFileLists/collectSamples.sh local "/any/other/path/to/my/ntuples/YYMMDD"
# Or if on lxplus you can link samples stored on rucio 
#source AHZ-lephad/config/common/samples/inputFileLists/collectSamples.sh grid 201215 # Or the latest ntuple version
```

Then prepare a `TQSampleFolder` representation of your input samples, with their metadata weights initialized.  
Unless you change the cross-section values, this step will also only need to be run once.  
```bash
# Prepare and initialize your samples

source AHZ-lephad/config/common/prepare.sh
source AHZ-lephad/config/common/initialize.sh
```

Fake background estimation
--------------------------

This step of the analysis calculates the background contribution from misidentified candidates (fakes).  
For this cycle of the analysis we have two methods to calculate the fake contribution. 

**Fake factor method**

Fake Factors (FF) are derived as ROOT files which serve as input for the later analysis.  
They can be calculated by following these [instructions](doc/FakeFactor.md).  

To help shortcut with this procedure, we can also provide a pre-calculated set of FF ROOT files.  
Please feel free to copy a set from within: `/eos/user/x/xiaozhon/BSMAtt/CAFInput/Run2`  
However, it is highly recommended to process these FFs for yourself, especially in the case of a new ntuple or analysis developments.  

**Fake rate method**
They can be calculated by following these [instructions](doc/FakeRate.md). (PENDING)

Real background and signal estimation
-------------------------------------

Before the Signal Region (SR) can be studied, the background estimation must be completely verified that the modelling performs well. These checks are done in Control Regions (CR).  
From the last section, the Fake Control Regions (FCR) with their FFs calculated should have been studied and their modelling verified.  
In this section, we define a Top Control Region (TCR) to check the performance of real top quarks. However, during the fake background estimations, the TCR was already established and a Top Scale Factor (TSF) derived with reasonable accuracy.  
Finally, to establish a smooth transition of assumptions and corrections between the CR and the SR, a Validation Region (VR) is defined closely to the kinematics of the SR.  Where any mismodelling is encountered, a Validation Scale Factor (VSF) is calculated, but will only be used as a systematic uncertainity in the next chapter.  


```bash
# Debug test the analysis before submitting the jobs to a cluster
source AHZ-lephad/config/SR/analyze-debug-FF.sh # Or alternativeFR if using fake rate method

# Submit the full analysis to a cluster
source AHZ-lephad/config/SR/analyze-submit-FF.sh # Or alternativeFR if using fake rate method

# After all jobs are finished successfully, merge the output
source AHZ-lephad/config/SR/analyze-merge-FF.sh # Or alternativeFR if using fake rate method

# Visualize the plots
source AHZ-lephad/config/SR/visualize-FF.sh

# Calculate the scale factors based on the histograms
# Merge into a single ROOT file
python scripts/calculateScaleFactor.py AHZ-lephad ExtrapSS # Use hadd command given in output

```

This concludes the nominal analysis where the results will be as presented, but with statistical uncertainties only.  
Until unblinding approval, the data in the SR remains hidden.  

Systematic uncertainty estimation
---------------------------------
Refer to [instructions](doc/Systematics.md).
