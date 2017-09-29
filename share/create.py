#!/bin/env python

from CommonAnalysisHelpers import *

def main(config):
    # create a new sample folder
    samples = createSampleFolder(config)

    # add the monte carlo as given by the cross section file
    addMonteCarlo(config, samples, "info/xsp")

    # add all the data
    addData(config, samples)

    # apply patches as given by the config
    patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # write the sample folder to disk
    writeSampleFolder(config, samples)

if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = DefaultArgumentParsers.forCreate()

    # use the argument parser to read the command line arguments and config options from the config file
    config = getConfigOptions(parser.parse_args())

    # call the main function
    main(config)

