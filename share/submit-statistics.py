#!/bin/env python

from CommonAnalysisHelpers import common,submit
from CommonAnalysisHelpers.task import task,taskStatus

import QFramework

def makeChunks(configs,n):
    import random
    rng = random.Random(42) # set a fixed random seed to get the same shufflings everytime
    rng.shuffle(configs)
    return [configs[i:i + n] for i in xrange(0, len(configs), n)]


def makeID(identifiers):
    common = None
    for i in identifiers:
        if not common:
            common = i
        else:
            for c in range(1,min(len(i),len(common))):
                if common[0:c] != i[0:c]:
                    common = common[0:c-1]
                    break
    ident = common
    for i in identifiers:
        if len(common) >= len(i):
            continue
        else:
            ident = ident + "_" + i[len(common)-1:]
    ident = ident.replace(".","_")
    while "__" in ident:
        ident = ident.replace("__","_")
    if len(ident) > 200:
        return ident[0:200]+"_etc"
    else:
        return ident

def extractIO(config,changes):
    """extract the input and output filenames from a config file"""
    import os
    from os.path import splitext
    thiscfg = QFramework.TQFolder("config")
    thiscfg.importFromTextFile(config)
    for change in changes:
        thiscfg.importFromText(change)
    identifier = thiscfg.getTagStandardStringDefault("identifier",splitext(config)[0])
    addoutput  = [ x for x in thiscfg.getTagVStandardString("expectedOutput") ]
    addinput   = [ x for x in thiscfg.getTagVStandardString("expectedInput")  ]      
    inconfigs = thiscfg.getListOfFolders("Import*/?")
    if inconfigs:
        for inconfig in inconfigs:
            filename = inconfig.getTagStandardStringDefault("inputFile","")
            if filename: addinput.append(filename.split(":")[0])
    outconfigs = thiscfg.getListOfFolders("Export*/?")
    if outconfigs:
        for outconfig in outconfigs:
            filename = outconfig.getTagStandardStringDefault("outputFile","")
            if filename: addoutput.append(filename.split(":")[0])
    return identifier,addinput,addoutput

def tasks_from_directory(args,configdir):
    """submit a whole directory of configs to a batch system"""
    from os import listdir
    from os.path import isfile
    from os.path import join as pjoin
    configs = [pjoin(configdir,f) for f in listdir(configdir) if isfile(pjoin(configdir, f))]
    common.mkdir(args.logpath)

    setup = getSetupCommand(args)

    chunks = makeChunks(configs,args.chunk)
    tasks = []
    for chunk in chunks:
        inputs = []
        outputs = []
        commands = []
        identifiers = []
        for config in chunk:
            identifier,addinput,addoutput = extractIO(config,args.change)
            if len(addoutput)==0 or len(addinput)==0:
                print("faulty config file "+config+" does not have <expectedInput>/<expectedOutput> tag")
                continue
            inputs.extend(addinput)
            outputs.extend(addoutput)
            identifiers.append(identifier)
            payload = "python statistics.py "+config
            if args.change:
                payload = payload + " --change " + " ".join([ "'" + c + "'" for c in args.change ])
            commands.append(payload)
        t = task(identifier=args.identifier+"_"+makeID(identifiers),args=args,setup=setup,outputs=outputs,inputs=inputs,payload=commands)
        tasks.append(t)
    return tasks

def single_task(args,config):
    setup = getSetupCommand(args)
    identifier,addinputs,addoutputs = extractIO(config,args.change)
    payload = "python statistics.py "+config
    if args.change:
        payload = payload + " --change " + " ".join([ "'" + c + "'" for c in args.change ])
    t = task(identifier=args.identifier,args=args,setup=setup,outputs=addoutputs,inputs=addinputs,payload=[payload])
    return [t]

def getSetupCommand(args):
    from os import environ
    # the lazy way to get all the needed instructions to ensure the environment on the batch node behaves like your current analysis setup:
    setup = submit.getSetupCommand(args)
    # run the setup script for our analysis
    setupPath = environ['CAFANALYSISSETUP']
    if len(setupPath)>0: setup.append("source "+setupPath)
    return setup

def main(args):
    """submit your statistics analysis to a batch system"""
    import os
    from os.path import join as pjoin
    tasks = []
    for path in args.directory:
        configdir = pjoin(path,"configs")
        if os.path.isdir(configdir):
            tasks.extend(tasks_from_directory(args,configdir))
        elif os.path.isfile(path):
            tasks.extend(single_task(args,path))
        else:
            print("unable to identify argument "+path+" as either config file or directory")

    if tasks:
        ctrl = submit.guessSubmissionController(args)
        ctrl.submitTasks(args,tasks)
        print("Done")
    else:
        print("failed to obtain task list!")

if __name__ == "__main__":

    # create a pre-configured argument parser (some parts of the backend code rely on certain arguments being available, this does *NOT* mean that you need to specify each argument explicitly though)
    parser = submit.MinimalArgumentParser(executable="statistics.py")
    #add a few more specific arguments to the argparser:
    parser.add_argument("directory",type=str,nargs="+", default=[], metavar="/path/to/jobs",help="directory of configs be submitted")
    parser.add_argument("--chunk",type=int,metavar="N",help="number of configs to be grouped into a single chunk and submitted as a job",default=1)
    parser.add_argument("--change", metavar='text', type=str, help='changes to apply to the input config file', nargs="*", default=[])
    import QFramework
    import ROOT
    # ignore command line arguments since ROOT is very greedy here (and tends to choke from it!)
    ROOT.PyConfig.IgnoreCommandLineOptions = True

    # use the argument parser to read the command line arguments and config options from the config file
    #from os.path import splitext
    args = parser.parse_args()
    
    # call the main function
    main(args)

    
