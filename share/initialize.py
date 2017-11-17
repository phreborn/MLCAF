#!/bin/env python

# TODO: importing QFramework up here removes custom help when running './initialize.py -h'
from CommonAnalysisHelpers import common,initialize

def main(config):
    """initialize the sample folder for your analysis according to the given configuration (can be created from a config file)"""

    # print a welcome message
    print(QFramework.TQStringUtils.makeBoldWhite("\nInitializing Analysis ROOT File\n"))

    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # apply pre-initialize patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("preInit_patches"), samples)

    # run the initialization
    #  - collect meta-information including the sum-of-weights from the files
    #  - compute the corresponding normalization factor for each sample
    initialize.initializeSampleFolder(config, samples)

    # apply post-initialize patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("postInit_patches"), samples)

    # TODO: do we want to use a purgeSamples flag to allow the user to choose whether or not to purge?
    # run a reduction step if scheduled, slimming down the sample folder to reduce future memory consumption
    if config.getTagBoolDefault("purgeSamples",False):
        common.reduceSampleFolder(config, samples)

    # TODO: do we want this here as well as for prepare step?
    # produce some output for the user to have a look at the result
    QFramework.INFO("please investigate the top-level structure of your sample folder to make sure everything is in place!")
    samples.printContents(config.getTagStringDefault("printFolderTags","r1dt"))

    common.writeSampleFolder(config, samples)

    if config.hasUnreadKeys("!.*"):
        QFramework.WARN("the following config keys were not read: "+(",".join([ key.GetName() for key in  config.getListOfUnreadKeys("!.*") ])))
    #temporary fix to prevent segfaults in AnaBase 2.3.48 and beyond
    # TODO: still necessary?
    ROOT.xAOD.ClearTransientTrees()

if __name__ == "__main__":

    # create a pre-configured argument parser
    parser = initialize.DefaultArgumentParser()

    import sys
    import QFramework
    import ROOT

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # TODO: Do we still need this line?
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    # call the main function    
    main(config)

