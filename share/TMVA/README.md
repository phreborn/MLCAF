How to use TMVA in BSMtautauCAF
====================================

To find out more about TMVA (A Toolkit for Multivariate Data Analysis with ROOT), please refer to the [manual](https://root.cern.ch/guides/tmva-manual). Examples can be found [here](https://root.cern.ch/doc/v610/group__tutorial__tmva.html).



Step 1. Make the input ntuples
------------------------------ 

TMVA takes ntuples as inputs for training and testing. You can use the "dump ntuple" option in CAF to make small, post-selection ntuples with all event weights factored in, or use full ntuples and set weights yourself.

To use ntuple dumping in CAF:

- modify `TMVA/dumpNtuples/ntuples.txt`
	- make a list of TTree branches which you want in your TMVA inputs
	- choose a name for your ntuple
	- choose which cut you want to use: `CutBveto*`, `CutBtag*`, etc.

- make sure that the following line is present and uncommented in `bsmtautau_lephad/config-SignalControlRegion/master/master.cfg`:
``` 
ntuples: TMVA/dumpNtuples/ntuples.txt
```
- in `bsmtautau_lephad/config-Common/jobLists/`, make sure the signal txt files have each mass hypothesis listed separately, else they will all be in one ntuple: ex. instead of `/sig/?/c16*/ggH/?` you should have `/sig/?/c16*/ggH/200`, etc.


If you want to train a parameterised neural net (with the signal mass as an extra input variable), you have to add a new `signal_mass` branch to your ntuples. This can be done with the `copytree_addSignalMass.py` script with appropriately set signal masses. To run the script, you might first need to install scipy:

```bash
pip install --user scipy
```




Step 2. Train and test
----------------------

Use `TMVA_train_201215.C` (this is compatible with the 201215 ntuples). Make sure to customize the following in the code:

- which MVA methods you want to use --> set Use[<your_chosen_method>] to 1

- which input files you want to use
	- define TFiles
	- open TFiles
	- register TTrees
	- set signal and background TTrees --> `dataloader->AddBackgroundTree(), dataloader->AddSignalTree()`
		- comment/uncomment so that you have either bveto or btag TTrees
		- for the PNN keep all signal hypotheses. For training on a single mass point, make sure to only keep the mass point you want
		- you might run out of memory if attempting to use all files for the PNN. You might want to just use c16e, etc.

- output root file name --> this file contains MVA response histograms and can be viewed 

- dataloader name --> this will determine the name of the directory created to store training weights

- factory name --> this will determine the name of weight files 

   ^make sure to change the dataloader and/or factory name if you don't want to overwrite weights from previous trainings

- k-folding
	- turned off by default 
	- to turn on: uncomment the block starting with `k-folding` and anything starting with `cv.`
		- use TMVA::CrossValidation instead of TMVA::Factory
		- ex. do cv.BookMethod() instead of factory->BookMethod()
	- event_number is typically used to define the folds; there was some issue with this var though (duplicate values for fakes), so instead I used the first decimal place of mttot instead - this was determined to be non-biasing. In this case, mttot needs to be added as a spectator (`dataloader->AddSpectator()`)

- which input variables you want to use --> `dataloader->AddVariable()`
	- you can use variable expressions, ex. `"var1+var2"`

- event weights --> `dataloader->SetSignalWeightExpression(), dataloader->SetBackgroundWeightExpression()`
	- if you use ntuple dumping, the weight expression is just `weight` (this includes all scale factors, cross-sections, pile-up, etc.)
	- negative weights shouldn't be used; we are using fabs(weight) instead
	- you can also set global weights for input TTrees in the `dataloader->AddBackground(Signal)Tree()` step
	- after these weights are applied, TMVA will automatically normalize combined signal and combined background samples, so there won't a huge discrepancy between the number of signal and background events

- hyperparameters in your MVA method(s) of choice --> `factory/cv->BookMethod()`

- additional cuts beyond what was applied to make the input ntuples --> `mycuts = "", mycutsb = ""`

- event split mode --> `dataloader->PrepareTestingAndTrainTree()`
	- random 50:50 test-train split by default

You can look at control plots at any time by launching the GUI in root:

```
TMVA::TMVAGui( outfileName )
```

However, the ROC AUC will not be shown in the GUI. It is only printed out during the MVA evaluation phase. If you want to calculate it outside of TMVA, you can use `TMVA_apply_201215.py`


Step 3. Apply your trained model
--------------------------------

MVA weight files are stored by default in `TMVA/dataset/weights`. To apply these weights to full ntuples (not our small dumped ntuples), you must modify variable names in the xml files to match branches in the full ntuples. This is especially relevant for 4-vector variables (like tau_0_p4.Pt()), which had to be given different names (like tau_pt) in the ntuple dumping process. Modify and run `hackWeightFiles.sh` to change the names.

To make histograms with the MVA response, use the following type of expression in `bsmtautau_lephad/config-SignalControlRegion/histograms/histograms.txt`:

```
TH1F('MVAResponse','',50000,-1,1) << (TMVA/dataset/weights/TMVAClassification_MLP.weights.xml : "MVA response");
```

Keep the binning fine if the distribution is narrow. 50000 bins might be too many, though. Make sure to update the path / file name in this line if you modified the dataloader name, factory name, or MVA method. For k-folding, you will need something like:
```
TH1F('MVAResponse','',50000,-1,1) << ( { int(fabs([MTtot]*10.))%5==0 ? [TMVA/dataset/weights/TMVACrossValidation_MLP_fold1.weights.xml] : {int(fabs([MTtot]*10.))%5==1 ? [TMVA/dataset/weights/TMVACrossValidation_MLP_fold2.weights.xml] : {int(fabs([MTtot]*10.))%5==2 ? [TMVA/dataset/weights/TMVACrossValidation_MLP_fold3.weights.xml] : {int(fabs([MTtot]*10.))%5==3 ? [TMVA/dataset/weights/TMVACrossValidation_MLP_fold4.weights.xml] : {int(fabs([MTtot]*10.))%5==4 ? [TMVA/dataset/weights/TMVACrossValidation_MLP_fold5.weights.xml] : 1}}}}} : "MVA response" );
```

