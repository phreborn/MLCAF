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
    # TODO: test writing the sample folder is causing folder splitting to not work correctly
    #common.testWriteSampleFolder(config, samples)

    # add the monte carlo as given by the cross section file
    prepare.addMonteCarlo(config, samples)

    # add all the data
    prepare.addData(config, samples)

    # if requested, print the XSection information
    if config.getTagBoolDefault("printXsec",False):
        prepare.printXSecParser(samples)

    # make sure we have at least something in the sample folder
    if samples.isEmpty():
        QFramework.BREAK("your sample folder is empty. please make sure your configuration is sensible and try again!")

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # produce some output for the user to have a look at the result
    QFramework.INFO("please investigate the top-level structure of your sample folder to make sure everything is in place!")
    samples.printContents(config.getTagStringDefault("printFolderTags","r1dt"))

    # write the sample folder to disk
    common.writeSampleFolder(config, samples)

    if config.hasUnreadKeys("!.*"):
        QFramework.WARN("the following config keys were not read: "+(",".join([ key.GetName() for key in  config.getListOfUnreadKeys("!.*") ])))
    #temporary fix to prevent segfaults in AnaBase 2.3.48 and beyond
    # TODO: still necessary?
    ROOT.xAOD.ClearTransientTrees()

if __name__ == "__main__":

    # create a pre-configured argument parser
    parser = prepare.DefaultArgumentParser()

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

