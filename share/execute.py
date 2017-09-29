#!/bin/env python

from CommonAnalysisHelpers import *

def main():
    # create a pre-configures argument parser
    parser = DefaultArgumentParsers.forExecute()

    # use the argument parser to read the command line arguments and config options from the config file
    config = getConfigOptions(parser.parse_args())

    # load the sample folder from disk
    samples = loadSampleFolder(config)

    # check writeability of the output destination to discover typos ahead of time
    testWriteSampleFolder(config, samples)

    # load all the observables that allow access of the physics-content of your samples
    loadObservables(config)

    # load all the cuts that are defined
    cuts = loadCuts(config)

    # load all the analysis jobs, booking histograms, event counters for cutflows and much more
    bookAnalysisJobs(config, cuts)

    # create an analysis sample visitor that will successively visit all the samples and execute the analysis when used
    visitor = createSampleVisitor(config)
    
    # perform any pre-processing of the sample folder for handling of systematic uncertainties
    # this step is likely to be highly analysis-dependent, so this is just an example implementation
    prepareSystematicsExample(config, samples, visitor)

    # apply patches as given by the config
    patchSampleFolder(config.getTagVStandardString("patches"), samples)
    
    # book algorithms that will be executed on the events before any cuts are applied or analysis jobs are executed
    bookAlgorithms(config, visitor)

    # execute analysis, visiting every sample and running over every event
    # this step might take a VERY LONG time
    nEvents = executeAnalysis(config, samples, visitor)

    # train any multivariate classifiers
    trainMVA(config, samples, cuts)

    # write the sample folder to disk
    writeSampleFolder(config, samples)

    # write and print some performance information like memory usage and runtime
    printExecutionStatistics(config)

if __name__ == "__main__":
    main()
