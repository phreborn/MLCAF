This document is intended as hands-on instructions for the [CAF
tutorial](https://indico.cern.ch/event/771763/). Since the
instructions should be self-contained, it can also be used as a offline resource. The only
prerequisite of this tutorial is a working
[CAF](https://gitlab.cern.ch/atlas-caf/CAFCore) installation. You can check this
by running

<!-- console -->
```bash
$ python -c "import QFramework"
RooFit v3.60 -- Developed by Wouter Verkerke and David Kirkby 
                Copyright (C) 2000-2013 NIKHEF, University of California & Stanford University
                All rights reserved, please read http://roofit.sourceforge.net/license.txt
```

This part of the tutorial illustrates the submission functionality of the common analysis
helpers. The [example script](hello_world.py) `hello_world.py` submits a single job to local
batch system. The submission code searches the current environment to find a
suitable batch system. If no batch system is found, it runs the jobs locally as a
sub-process.

The submitted job simply sleeps for 60 seconds and then leaves a *footprint*
by creating the empty file `hello_world`.

To run the example, enter
```
$ python hello_world.py
```
