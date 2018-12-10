This document is intended as hands-on instructions for the [CAF
tutorial](https://indico.cern.ch/event/771763/). Since the
instructions should be self-contained, it can also be used as an offline resource. The only
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
helpers. The [example script](hello_world.py) `hello_world.py` submits a single
job to the local
batch system. The submission code searches the current environment to find a
suitable batch system. If no batch system is found, it runs the jobs locally as a
sub-process.

The submitted job simply sleeps for 60 seconds and then leaves a *footprint*
by creating the empty file `hello_world`.

To run the example, enter
```
$ python hello_world.py
```
So lets look at the `hello_world.py` script in more detail. The core of the
script consists of a task object. This object represents a job to be submitted
to the batch system. The object contains all the job properties like the number of
cores, memory requirements and the payload script.

```python
task = submit.task("hello_world", "sleep 60; touch hello_world.txt",
                   memory=args.memory,
                   ncores=args.ncores,
                   time=args.time,
                   setup=submit.getSetupCommand(args),
                   outputs=["hello_world.txt"])
```

In order to actually submit the job, we can let the submission helpers guess the
local batch system and send the task object to it.

```python
controller = submit.guessSubmissionController()
controller.submitTasks(args, [task])
```
