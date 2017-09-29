#!/bin/env python

from CommonAnalysisHelpers import *

def main():
    # create a pre-configures argument parser
    parser = DefaultArgumentParsers.forVisualize()

    # use the argument parser to read the command line arguments and config options from the config file
    config = getConfigOptions(parser.parse_args())

    # load the sample folder from disk
    samples = loadSampleFolder(config)

    # apply patches as given by the config
    patchSampleFolder(config.getTagVStandardString("patches"), samples)

    ####################################################################
    # TODO: implement the actual function content
    ####################################################################
    
    # write the sample folder to disk
    writeSampleFolder(config, samples)
    

if __name__ == "__main__":
    main()    
