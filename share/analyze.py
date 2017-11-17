#!/bin/env python

from CommonAnalysisHelpers import common,analyze

def main(config):
    """execute your analysis according to the given configuration (can be created from a config file)"""

    # TODO: remove, just for debugging!
    #print "Exiting successfully!"
    #sys.exit(0)

    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # check writeability of the output destination to discover typos ahead of time
    common.testWriteSampleFolder(config, samples)

    # load all the observables that allow access of the physics-content of your samples
    analyze.loadObservables(config)

    # load all the cuts that are defined
    cuts = analyze.loadCuts(config)

    # load all the analysis jobs, booking histograms, event counters for cutflows and much more
    analyze.bookAnalysisJobs(config, cuts)

    # create an analysis sample visitor that will successively visit all the samples and execute the analysis when used
    visitor = analyze.createSampleVisitor(config)
    
    # perform any pre-processing of the sample folder for handling of systematic uncertainties
    # this step is likely to be highly analysis-dependent, so this is just an example implementation
    analyze.prepareSystematicsExample(config, samples, visitor)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)
    
    # book algorithms that will be executed on the events before any cuts are applied or analysis jobs are executed
    analyze.bookAlgorithms(config, visitor)

    # execute analysis, visiting every sample and running over every event
    # this step might take a VERY LONG time
    nEvents = analyze.executeAnalysis(config, samples, visitor)

    # train any multivariate classifiers
    analyze.trainMVA(config, samples, cuts)

    # write the sample folder to disk
    common.writeSampleFolder(config, samples)

    # write and print some performance information like memory usage and runtime
    common.printExecutionStatistics(config)

if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = analyze.DefaultArgumentParser()

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # call the main function
    main(config)
