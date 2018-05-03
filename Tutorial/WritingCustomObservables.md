This document is intended to provide hands-on instructions on how to write a custom observable for the [CAF tutorial](https://indico.cern.ch/event/719951/). General reading on observables can be found in the tutorial and also in the observable [README](https://gitlab.cern.ch/atlas-caf/CAFExample/tree/master/share/common/observables).

Prerequesite for the tutorial is a working [CAF](https://gitlab.cern.ch/atlas-caf/CAFCore) installation. You can check this
by running

```bash
$ python -c "import QFramework"
RooFit v3.60 -- Developed by Wouter Verkerke and David Kirkby 
                Copyright (C) 2000-2013 NIKHEF, University of California & Stanford University
                All rights reserved, please read http://roofit.sourceforge.net/license.txt
```

# Basic steps to create a new observable 
There are three main steps that need to be performed to introduce a new observable to an existing analysis:
1. Create and write the observable class including a source and header file. This is the main part of the observable creation where the actual calculation of the desired quantity needs to be implemented. In this hands-on exercise the helper script [wizard.py](https://gitlab.cern.ch/atlas-caf/CAFCore/blob/master/QFramework/share/TQObservable/wizard.py) is used for these purposes. In general it is also a good idea to look at already defined observable classes and start from those as a baseline to implement your own observable.
2. Create dedicated python snippet for instantiating the class and adding it to the observable database.
3. Implement observable in analysis flow in terms of histograms, cuts, weights, etc.

# Creating the MjjMaxObservable
We want to create a new observable that calculates the invariant mass (called Mjj in the following) for every possible combination of two jets in an event and returns the maximum of those values. 
The new observable class is to be implemented in the [xAOD Example analysis](https://gitlab.cern.ch/atlas-caf/CAFExample/tree/Tutorial/share/xAOD). It is assumed that this example analysis was already conducted.

## The magic wizard.py script
[CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) provides the python script [wizard.py](https://gitlab.cern.ch/atlas-caf/CAFCore/blob/master/QFramework/share/TQObservable/wizard.py) helping you to create a source and header file for your new observable. Make sure you are setup (`source setup/setupAnalysis.sh`) and are in the main directory of the CAFExample repository (which you can ensure e.g. with `cd $CAFANALYSISSHARE/../`). Then, you can call the script via
```bash
./CAFCore/QFramework/share/TQObservable/wizard.py
```

The wizard will ask a couple of questions that we answer as follows
```
Please enter the path to the package you want to create an observable for (default: CAFExample): CAFExample
What is the name of the observable you would like to create? MjjMaxObservable
Please specify the type of observable, choose  from {Event,Tree,<empty>}: Event
Do you want to create a vector observable that can return multiple values? (y/N) N
Should your class have an 'expression' member variable? (y/N) N
Are you planning to provide a factory for your observable class? (y/N)N

```
After providing the answers the wizard will summarize the made choices and asks for confirmation to build the observable:

```
Your choices:
class name: MjjMaxObservable
inherits from: TQEventObservable
in package: CAFExample
written to directory: .
not including expression member
build this observable now? (y/N) y
wrote './CAFExample/MjjMaxObservable.h'!
wrote './Root/MjjMaxObservable.cxx'!
the wizard has detected a LinkDef.h file in the target package - do you want to add an entry for your observable class? (y/N) y
```
We can also directly add our new class to the `LinkDef.h` to ensure that the framework will pick up our new class (although this step might not be necessary, since the link definition file of CAFExample (and CAFCore) is created automatically).
Once we have confirmed that the wizard should build the observable, two new files are created: `CAFExample/MjjMaxObservable.h` and `Root/MjjMaxObservable.h`. The important parts in the files contain comments that guide you through the further process. There are example blocks given that provide very adequate pieces of code which we want to use.
Let's have a look at `MjjMaxObservable.h` first. You should modify it such that it looks like the following:

```c++
//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __MJJMAXOBSERVABLE__
#define __MJJMAXOBSERVABLE__
#include "CAFxAODUtils/TQEventObservable.h"

class MjjMaxObservable : public TQEventObservable {
protected:
  // Put here data members you wish to use.
  // For example you might want to add a variable
  // for the name of the xAOD container to be retrieved that
  // will be initialized in the initialize function.
  
  TString mContName = ""; 

public:
  virtual double getValue() const override;
protected:
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
public:
  MjjMaxObservable();
  MjjMaxObservable(const TString& name);
  virtual ~MjjMaxObservable();
  ClassDefOverride(MjjMaxObservable, 1);

};
#endif
```
Three main functions are declared (`initializeSelf()`, `finalizeSelf()` and `getValue()`) that we have to define in the source file of the observable now.
In `initializeSelf()` we will initialize the member variable `mContName` by retrieving the tag from the sample folder with the following lines of code (By doing this in the initialize function one prevents from running time costly string parsing functions for each event):
```c++
TString ContName = "";
if(!this->fSample->getTagString("~cand",ContName)) return false;
this->mContName = "Event"+ContName;
```
Now we have to implement the actual calculation of the quantity that is to be derived. Therefore, the `getValue()` function needs to be modified. For our example the following lines should be included:
```c++
  // retrieve candidate
  const xAOD::CompositeParticleContainer *cand = 0;
  if(!this->fEvent->retrieve(cand, this->mContName.Data()).isSuccess()){
    DEBUGclass("failed to retrieve candidates!");
    return false;
  }
  // after you have retrieved your data members, you can proceed to calculate the return value
  // probably, you first have to retrieve an element from the container
  const xAOD::CompositeParticle *Evt = cand->at(0);
  int nParts = Evt->nParts();
  double MjjMax = 0;
  for ( int i=2; i < nParts; ++i ){
    for ( int j=i+1; j < nParts; ++j ){
      double tmp_Mjj = Evt->p4(i,j).M();
      if (tmp_Mjj > MjjMax){
        MjjMax = tmp_Mjj;
      }
    }
  }

  const double retval = MjjMax;
  return retval;
```
After implementing the above (don't forget to make potential includes), the observable should be ready to be compiled. This can be done with `cafcompile`  which invokes an alias and automatically runs cmake and finds the new class.
Once your class compiles fine along with the other observable classes we can move on to the next step.

Remark: The line at the top of `MjjMaxObservable.cxx` saying `// #define _DEBUG__` can be uncommented to enable printouts from the DEBUGclass(...) function. This might be useful for initial tests and checks of the new observable.

## Creating an observable snippet
A small python snippet needs to be added for the new observable to the designated observable/ of the analysis.
In the xAOD Example analysis, the observable snippets are located [here](https://gitlab.cern.ch/atlas-caf/CAFExample/tree/master/share/xAOD/observables) (If you write an observable that is used by multiple analyses, you should think of creating the observable snippet in [common/](https://gitlab.cern.ch/atlas-caf/CAFExample/tree/master/share/common/observables).
The snippet will instantiate the observable class and adds it to the observable database. The python script should have the same name as the observable itself (in our case MjjMaxObservable.py) and can look like this:

```python
from QFramework import *
from ROOT import *

from CAFExample import MjjMaxObservable

def addObservables():
	
    obs = MjjMaxObservable("MjjMax")
    if not TQObservable.addObservable(obs, "MjjMax"):
        INFO("failed to add MjjMax Observable")
        return False
    return True;
```
Here, calling the constructor of the new observable class with `MjjMaxObservable("MjjMax")` will set the name of the observable to `MjjMax`, which will be used later.
All we need to do then, is to list the path to your script in the config file of the analyze step such that the framework executes your code and adds your observable to the database. The relevant part you should add to [analyze-xAOD-Example.cfg](https://gitlab.cern.ch/atlas-caf/CAFExample/blob/master/share/xAOD/config/master/analyze-xAOD-Example.cfg) is:
```
customObservables.directories: xAOD/observables
customObservables.snippets: [...all other observables...], MjjMaxObservable
```

## Defining histograms/cuts/...
The observable can now be used to define histograms, cuts, event lists, etc. Let's define a simple histogram with the MjjMax distribution.
Therefore we add a new histogram definition in the appropriate [histogram definition file](https://gitlab.cern.ch/atlas-caf/CAFExample/blob/master/share/xAOD/config/histograms/xAOD-Example-histograms.txt) and add it at the desired cut stages e.g.:
```
TH1F('MjjMax', '', 50, 0., 500.) << ( [MjjMax]*0.001 : 'm_{jj}^{max} [GeV]');
@CutChannels/*: MjjMax;

```
The second line here books a histogram at the cut CutChannels and all subsequent cuts.

## Running the analysis and looking at newly booked histogram
If the analysis is executed (you only have to perform the analyzing step) and everything was correctly implemented, the new histogram should appear in the output sample folder.
<!-- It is assumed that you have already learned how to run a complete analysis.-->
You can check this by opening the respective sample folder with `tqroot -sfr sampleFolders/analyzed/samples-analyzed-xAOD-Example.root` and draw one of the histograms with
```
r_samples->getHistogram("bkg/[ee+mm]/top/ttbar", "CutChannels/MjjMax")->Draw("")
```
Now, you can also define cuts/cutflows, event lists, etc. with your new observable. 

# Creating a custom vector observable (Advanced)
There is also the possibility to create observables that return multiple values per event. This can be useful for a bunch of things, especially in combination with `TQVectorAuxObservables` it will give you the opportunity to manipulate the output of the observable just by modifying a small string in config files later on. Let's do an example. Call the observable script `wizard.py`, answer the questions as above except choosing a different observable name and answering the following question with yes:
```
Do you want to create a vector observable that can return multiple values? (y/N) N
```
New files `CAFExample/YourObservableName.h` and `Root/YourObservableName.cxx` are being created from the wizard. Vector observables have additional functions with respect to simple scalar functions. You will again find many comments and example blocks in the code that will help you establishing your observable class. At this point you are asked to explore yourself and to implement a working vector observable (You need to follow the same 3 steps as for scalar observables). As a suggestion, you might want to create a vector observable returning a list with invariant masses for every two jet combinations. Then, booking a histogram like
```
TH1F('MjjMaxVec', '', 50, 0., 500.) << ( [VecMAX(MjjMaxVec)]*0.001 : 'm_{jj}^{max} [GeV]');
```
should give you the same results than for the previously booked histogram with using the `MjjMaxObservable`. You can then also make use of other `TQVectorAuxObservables` such as `VecSUM`, `VecMAX/MIN`, `VecAND` and many more (see [observable README](https://gitlab.cern.ch/atlas-caf/CAFExample/tree/master/share/common/observables) or simply browse through the [code](https://gitlab.cern.ch/atlas-caf/CAFCore/blob/master/QFramework/Root/TQVectorAuxObservable.cxx) for more information).

If you managed to write your vector observable you can also compare it with [MjjVectorObservable](https://gitlab.cern.ch/atlas-caf/CAFExample/blob/master/Root/MjjVectorObservable.cxx) which should already be available in your CAFExample fork.

