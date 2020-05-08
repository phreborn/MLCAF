How to use TMVA in BSMtautau CAFCore
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

- make sure that the following line is uncommented in `bsmtautau_lephad/config-SignalControlRegion/master/master.cfg`:
``` 
ntuples: TMVA/dumpNtuples/ntuples.txt
```

- select **only one sample** per batch submission (if you submit multiple jobs at the same time, the small ntuples will keep getting rewritten, since they will all have the same name)
	- comment out sample categories which you don't want in `bsmtautau_lephad/config-SignalControlRegion/scriptSubmit.sh` (JOBSLIST)
	- comment out unwanted samples in `bsmtautau_lephad/config-Common/jobLists/*.txt` files corresponding to the sample category you chose to keep

- if you want a specific signal mass, make sure to change the path in signal jobs lists, ex.: change `/sig/?/c16*/ggH/` to `/sig/?/c16*/ggH/200` 


If you want to train a parameterised neural net (with the signal mass as an extra input variable), you have to add a new `signal_mass` branch to your ntuples. Use `copytree_addSignalMass.py` with appropriately set signal masses.




Step 2. Train and test
----------------------

Use `TMVA_train.C`. Make sure to customize the following in the code:

- which MVA methods you want to use --> set Use[<your_chosen_method>] to 1

- which input files you want to use
	- define TFiles
	- open TFiles
	- register TTrees
	- set signal and background TTrees --> `dataloader->AddBackgroundTree(), dataloader->AddSignalTree()`

- output root file name --> this file contains MVA response histograms and can be viewed 

- dataloader name --> this will determine the name of the directory created to store training weights

- factory name --> this will determine the name of weight files 

   ^make sure to change the dataloader and/or factory name if you don't want to overwrite weights from previous trainings

- k-folding
	- turned off by default 
		- having it on messes with control plots available via the GUI
		- good for validation, but does not result in an appliable model
	- to turn on: uncomment k-folds blocks
		- use TMVA::CrossValidation instead of TMVA::Factory
		- ex. do cv.BookMethod() instead of factory->BookMethod()

- which input variables you want to use --> `dataloader->AddVariable()`
	- you can use variable expressions, ex. `"var1+var2"`

- event weights --> `dataloader->SetSignalWeightExpression(), dataloader->SetBackgroundWeightExpression()`
	- if you use ntuple dumping, the weight expression is just `weight` (this includes all scale factors, cross-sections, pile-up, etc.)
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

However, the ROC AUC will not be shown in the GUI. It is only printed out during the MVA evaluation phase. 


Step 3. Apply your trained model
--------------------------------

MVA weight files are stored by default in `TMVA/dataset/weights`. To apply these weights to full ntuples (not our small dumped ntuples), you must modify variable names in the xml files to match branches in the full ntuples. This is especially relevant for 4-vector variables (like tau_0_p4.Pt()), which had to be given different names (like tau_pt) in the ntuple dumping process. Change each of the following expressions for variables where there is a name mismatch: 

```
Expression = "", Label = "", Title = "", Internal = ""
```

To make histograms with the MVA response, uncomment the following line in `bsmtautau_lephad/config-SignalControlRegion/histograms/histograms.txt`:

```
TH1F('MVAResponse','',30,-1,1) << (TMVA/dataset/weights/TMVAClassification_MLP.weights.xml : "MVA response");
```

Make sure to update the path / file name in this line if you modified the dataloader name, factory name, or MVA method.

