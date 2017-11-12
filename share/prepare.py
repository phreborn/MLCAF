#!/bin/env python

# TODO: importing QFramework up here removes custom help when running './prepare.py -h'
from CommonAnalysisHelpers import common,prepare

def main(config):
    """create the sample folder for your analysis according to the given configuration (can be created from a config file)"""
    
    # print a welcome message
    print(QFramework.TQStringUtils.makeBoldWhite("\nPreparing Analysis ROOT File\n"))

    # create a new sample folder
    samples = common.createSampleFolder(config)

    # make sure that sample folder is writable before we go any further
    common.testWriteSampleFolder(config, samples)

    # add the monte carlo as given by the cross section file
    prepare.addMonteCarlo(config, samples)

    # add all the data
    prepare.addData(config, samples)

    # TODO: delete, just for debugging
    # print "Exiting successfully!"
    # sys.exit(0)

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # write the sample folder to disk
    common.writeSampleFolder(config, samples)

if __name__ == "__main__":

    # create a pre-configured argument parser
    parser = prepare.DefaultArgumentParser()

    import sys
    import QFramework

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # TODO: Do we still need this line?
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    # call the main function
    main(config)

