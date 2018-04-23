#!/bin/env python

from CommonAnalysisHelpers import common,submit

def main(args):
    """submit your analysis to a batch system"""
    #read the main analysis config file, we need some information about what our analysis is intended to work on
    config = common.getConfigOptions(args, "analyze")
    #the lazy way to get all the needed instructions to ensure the environment on the batch node behaves like your current analysis setup:
    setup = submit.getSetupCommand(args)
    
    outputFileNameTemplate="{output}/unmerged_{globalIdentifier}/unmerged_{{identifier}}.root".format(output=args.output, globalIdentifier=args.identifier)
    
    templateCommand="analyze.py {config} --restrict {{restrict}} --jobID {{identifier}} -o outputFile={outFileTemplate} ".format(config=",".join(args.config), outFileTemplate=outputFileNameTemplate)
    
    templateCommand += " ".join(args.options) #forward options from command line to individual jobs
    
    #convenience method to make a somewhat smart splitting of jobs (the maxSampleCount and maxSampleSize arguments allow to control the splitting into sub-jobs. This can yield a significant improvement in turn-over time!):
    #note: this method is somewhat targeted at the analyze.py step/ written with that one in mind
    taskList = submit.makeSmartTaskList(args, args.jobs, config, templateCommand, maxSampleCount=args.maxSampleCount, maxSampleSize=args.maxSampleSize, setup=setup, inputs=[], outputs=[outputFileNameTemplate])
    ctrl = submit.guessSubmissionController()
    ctrl.submitTasks(args,taskList,verbose=False)
    print "Done"
    

if __name__ == "__main__":

    # create a pre-configured argument parser (some parts of the backend code rely on certain arguments being available, this does *NOT* mean that you need to specify each argument explicitly though)
    parser = submit.MinimalArgumentParser(executable="analyze.py")
    #add a few more specific arguments to the argparser:
    parser.add_argument('--jobs', default='flatNTuple/config/jobLists/jobs_ZjetsFF_analyze.txt', help='name of the queue to submit to')
    parser.add_argument('-o','--options',dest='options',type=str,nargs="+",default=[],metavar="key=value",help="changes to be made to the configuration")
    parser.add_argument('--maxSampleSize', default=-1, type=float, help='split jobs such that each job processes only so many input files that their cummulative size is below this value (in MB)')
    parser.add_argument('--maxSampleCount', default=-1, type=float, help='split jobs such that each job processes only up to this many input files')
    import QFramework
    import ROOT
    # ignore command line arguments since ROOT is very greedy here (and tends to choke from it!)
    ROOT.PyConfig.IgnoreCommandLineOptions = True

    # use the argument parser to read the command line arguments and config options from the config file
    #from os.path import splitext
    args = parser.parse_args()
    
    # call the main function
    main(args)

