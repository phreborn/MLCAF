#!/bin/env python

# TODO: importing QFramework up here removes custom help when running './initialize.py -h'
from CommonAnalysisHelpers import common,initialize

def main(config):
    """initialize the sample folder for your analysis according to the given configuration (can be created from a config file)"""

    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # apply pre-initialize patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("preInit_patches"), samples)

    # TODO: remove, just for debugging!
    print "Exiting successfully!"
    sys.exit(0)

    # run the initialization
    #  - collect meta-information including the sum-of-weights from the files
    #  - compute the corresponding normalization factor for each sample
    initialize.initializeSampleFolder(config, samples)

    # apply post-initialize patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("postInit_patches"), samples)

    # run a reduction step, slimming down the sample folder to reduce future memory consumption
    common.reduceSampleFolder(config, samples)

    common.writeSampleFolder(config, samples)

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

