#!/bin/env python

from CommonAnalysisHelpers import common,visualize

def main(config):
    """visualize the results of your analysis according to the given configuration (can be created from a config file)"""
    # load the sample folder from disk
    samples = common.loadSampleFolder(config)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    ####################################################################
    # TODO: implement the actual function content
    ####################################################################
    
    # write the sample folder to disk
    common.writeSampleFolder(config, samples)
    
if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = visualize.DefaultArgumentParser()

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # call the main function
    main(config)    
