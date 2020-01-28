FAQ
==============================

1. Failed to submit jobs via HTCondor in IHEP

For job submission in IHEP, we need to modify the controllers.
In [condor.py](https://gitlab.cern.ch/atlas-caf/CAFCore/blob/master/CommonAnalysisHelpers/python/submissionControllers/condor.py), 
add the following statement in Line 202.
```
payload.append("Accounting_Group = {:s}".format(accGroup))
```

2. When running jobs in muhad channel, the following error messages are observed:
```ERROR in TQMultiChannelAnalysisSampleVisitor::analyseTree(...) : No cuts were activated for processing sample```
is observedd.

It is a known issue in CAF. We still obtain the right results with this error. For now, we need to live with it.

