#!/bin/env python

from CommonAnalysisHelpers import common,visualize

def main(config):
    """visualize the results of your analysis according to the given configuration (can be created from a config file)"""

    # print a welcome message
    print(QFramework.TQStringUtils.makeBoldWhite("\nVisualizing Analysis ROOT File\n"))

    # create a path manager
    pathManager = QFramework.TQPathManager(False)
    
    # load the sample folder from disk
    samples = common.loadSampleFolder(config, pathManager)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # location to dump results
    outputdir = visualize.getOutputDir(config)

    # retrieve properties of channels provided in config
    channelsDict = visualize.getDictOfChannels(config)

    # TODO: check that all channels specified in channelsDict is actually found in samples

    # initialize object which will read the results from the sample folder
    reader = visualize.initializeSampleDataReader(config, samples)

    # generate fake data if requested
    if config.getTagStringDefault("fakeData.source",""):
        visualize.generateFakeData(config)

    # calculate normalization factors based on a series of config files and save this information in the sample folder
    visualize.generateNormalizationFactors(config, samples)

    # create a document which will summarize all of the results
    summary = visualize.createSummaryDocument(samples, outputdir, pathManager)

    # create a diagram summarizing the cuts
    visualize.createCutDiagram(config, samples, summary, outputdir, pathManager)

    # print a cutflow for each combination of processes and cuts defined in the config for each channel
    visualize.printCutflows(config, reader, summary, channelsDict, outputdir, pathManager)

    # print event level quantities defined by the user
    visualize.printEventLists(config, reader, channelsDict, outputdir, pathManager)

    # make all of the plots with the processes stacked which are requested by the user
    visualize.makePlots(config, reader, summary, channelsDict, outputdir, pathManager)

    # make a selection of advanced plots to more easily compare specific processes defined by the user
    visualize.makeComparisonPlots(config, reader, outputdir, pathManager)

    # write the sample folder to disk
    common.writeSampleFolder(config, samples, pathManager)

    # finalize the summary document
    visualize.finalizeSummaryDocument(summary)

    QFramework.INFO("all done!")

    # print any keys which were not read during the job
    common.printUnreadKeys(config)
    
if __name__ == "__main__":

    # create a pre-configures argument parser
    parser = visualize.DefaultArgumentParser()

    import QFramework
    import ROOT

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # ignore command line arguments since ROOT is very greedy here (and tends to choke from it!)
    ROOT.PyConfig.IgnoreCommandLineOptions = True

    # TODO: This was in readAnalysis, is this still needed?
    ROOT.gROOT.SetBatch(True)

    # call the main function
    main(config)    
