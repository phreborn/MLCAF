#!/bin/env python

from CommonAnalysisHelpers import common,initialize

def main(config):
    """initialize the sample folder for your analysis according to the given configuration (can be created from a config file)"""
    
    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)
    
    # run the initialization
    #  - collect meta-information including the sum-of-weights from the files
    #  - compute the corresponding normalization factor for each sample
    initialize.initializeSampleFolder(config, samples)

    # run a reduction step, slimming down the sample folder to reduce future memory consumption
    common.reduceSampleFolder(config, samples)

    common.writeSampleFolder(config, samples)

if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = initialize.DefaultArgumentParser()

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # call the main function    
    main(config)
