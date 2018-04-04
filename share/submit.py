#!/bin/env python

from CommonAnalysisHelpers import common,submit

def main(config):
    """submit your analysis to a batch system"""
    print("hello")


if __name__ == "__main__":

    # create a pre-configured argument parser
    parser = submit.DefaultArgumentParser()

    import QFramework
    import ROOT

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # ignore command line arguments since ROOT is very greedy here (and tends to choke from it!)
    ROOT.PyConfig.IgnoreCommandLineOptions = True

    # call the main function
    main(config)
