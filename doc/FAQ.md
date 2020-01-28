FAQ
==============================

1. Failed to submit jobs via HTCondor in IHEP

For job submission in IHEP, we need to modify the controllers.
In `CAFCore/CommonAnalysisHelpers/python/submissionControllers/condor.py`, replace
`payload.append("+AccountingGroup = \"{:s}\"".format(accGroup))` with `payload.append("Accounting_Group = {:s}".format(accGroup))`

2. For muhad channel, `ERROR in TQMultiChannelAnalysisSampleVisitor::analyseTree(...) : No cuts were activated for processing sample`
is observedd.

It is a known issue in CAF. We still obtain the right results with this error. For now, we need to live with it.

