#!/bin/env python

from CommonAnalysisHelpers import common,prepare

def main(config):
    """create the sample folder for your analysis according to the given configuration (can be created from a config file)"""
    
    # create a new sample folder
    samples = common.createSampleFolder(config)

    # add the monte carlo as given by the cross section file
    prepare.addMonteCarlo(config, samples, "info/xsp")

    # add all the data
    prepare.addData(config, samples)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # write the sample folder to disk
    common.writeSampleFolder(config, samples)

if __name__ == "__main__":
    # create a pre-configures argument parser
    parser = prepare.DefaultArgumentParser()

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # call the main function
    main(config)

