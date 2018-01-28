#!/bin/env python

from CommonAnalysisHelpers import common,visualize

def main(config):
    """visualize the results of your analysis according to the given configuration (can be created from a config file)"""

    # print a welcome message
    print(QFramework.TQStringUtils.makeBoldWhite("\nVisualizing Analysis ROOT File\n"))

    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # location to dump results
    outputdir = visualize.getOutputDirName(config)

    # retrieve properties of channels provided in config
    channelsDict = visualize.getDictOfChannels(config)

    # TODO: check that all channels specified in channelsDict is actually found in samples

    # initialize object which will read the results from the sample folder
    reader = visualize.initializeSampleDataReader(config, samples)

    # generate fake data if requested
    if config.getTagStringDefault("fakeData.source",""):
        visualize.generateFakeData(config)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # calculate normalization factors based on a series of config files and save this information in the sample folder
    visualize.generateNormalizationFactors(config, samples)

    # create a document which will summarize all of the results
    summary = visualize.createSummaryDocument(samples, outputdir)

    # write the sample folder to disk
    common.writeSampleFolder(config, samples)
    
if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = visualize.DefaultArgumentParser()

    import sys
    import QFramework
    import ROOT

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # TODO: Do we still need this line?
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    # TODO: This was in readAnalysis, is this still needed?
    ROOT.gROOT.SetBatch(True)

    # call the main function
    main(config)    
