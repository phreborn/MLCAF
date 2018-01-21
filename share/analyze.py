#!/bin/env python

# TODO: importing QFramework up here removes custom help when running './initialize.py -h'
from CommonAnalysisHelpers import common,analyze

def main(config):
    """execute your analysis according to the given configuration (can be created from a config file)"""

    CLI = config.getFolder("CLI+")

    if CLI.getTagIntegerDefault("width",0):
        QFramework.TQLibrary.setConsoleWidth(CLI.getTagInteger("width"))

    # print a welcome message
    print(QFramework.TQStringUtils.makeBoldWhite("\nAnalyzing Analysis ROOT File\n"))

    # TODO: still need this?
    try:
        ROOT.StatusCode.enableFailure()
    except AttributeError:
        pass

    # TODO: make a get aliases method? aliases also loaded during cut creation and analysis job booking
    # load the aliases from the config file
    aliases = QFramework.TQTaggable()
    aliases.importTagsWithoutPrefix(config,"cutParameters.")
    aliases.importTagsWithoutPrefix(config,"aliases.")
    # TODO: understand why we need this
    QFramework.TQMVAObservable.globalAliases.importTags(aliases)

    # read the channel definitions
    channels = config.getTagVString("channels")

    # TODO: load correct library
    # load MVA libraries if required
    # if config.getTagBoolDefault("loadMVA",True):
    #     try:
    #         libMVA = analyze.loadLibMVA(config)
    #     except Exception as ex:
    #         libMVA = False
    #         template = "An exception of type '{0}' occured: {1!s}"
    #         message = template.format(type(ex).__name__, ",".join(ex.args))
    #         QFramework.ERROR(message)

    # set some global properties
    if not config.getTagBoolDefault("useTransientTree",True):
        QFramework.TQSample.gUseTransientTree = False
    if config.getTagBoolDefault("useAthenaAccessMode",False):
        QFramework.TQSample.gUseAthenaAccessMode = True
    if config.getTagBoolDefault("loadStore",True):
        try:
            store = xAOD.TStore()
            store.setActive()
        except:
            pass

    # flag indicating to run a dummy analysis
    dummy = CLI.getTagBoolDefault("dummy",False)

    # TODO: put dummy sample folder retrieval also in loadSampleFolder? It would get the config saved for free
    # load the sample folder from disk
    if dummy:
        samples = TQSampleFolder("test")
    else:
        samples = common.loadSampleFolder(config)

    # check writeability of the output destination to discover typos ahead of time
    # TODO: test writing the sample folder is causing folder splitting to not work correctly
    #common.testWriteSampleFolder(config, samples)

    # remove the data folder if not desired
    if not config.getTagBoolDefault("doData",True):
        QFramework.INFO("removing data folder")
        samples.deleteObject("data!")

    # flag indicating to run a robust analysis
    robust = CLI.getTagBoolDefault("robust",False)

    if not robust and not dummy:
        # remove the channels that are not scheduled
        for sf in samples.getListOfSampleFolders("?/?"):
            found = False
            for c in channels:
                if QFramework.TQStringUtils.equal(sf.getName(),c):
                    found = True
                    break
            if not found:
                QFramework.INFO("removing folder '{:s}' - unscheduled channel!".format(sf.getPath()))
                sf.detachFromBase()

        # check if all requested channels are present
        for c in channels:
            if not samples.getSampleFolder(QFramework.TQFolder.concatPaths("?",c)):
                QFramework.BREAK("channel '{:s}' was requested, but is not present in input!".format(c))

    # apply patches as given by the config
    common.patchSampleFolder(config.getTagVStandardString("patches"), samples)

    # TODO: do we still want this option?
    # if requested, we initialize the samples from the input lists
    initlists = config.getTagVString("initializerLists")
    init = QFramework.TQSampleListInitializer(samples)
    init.setTagString("treeName","CollectionTree")
    for filelist in initlists:
        with open(filelist.Data(),'r') as f:
            for line in f:
                init.initializeSampleForFile(line) 

    # run a reduction step if scheduled, slimming down the sample folder to reduce future memory consumption
    if config.getTagBoolDefault("purgeSamples",False):
        common.reduceSampleFolder(config, samples)

    pathselect = CLI.getTagStandardStringDefault("pathselect","")

    # TODO: put this in the reduceSampleFolder method as well?
    # if requested, purge samples (even more)
    if config.getTagBoolDefault("purgeRemainder",False) and not QFramework.TQStringUtils.equal(pathselect,""):
        samples.setTagBool("restrict",True,pathselect)
        samples.purgeWithoutTag("~restrict")
        if not samples.getListOfSampleFolders("?"):
            QFramework.BREAK("sample folder empty after purge - something is wrong!") 

    # load all the observables that allow access of the physics-content of your samples
    customobservables = analyze.loadObservables(config)

    # load all the cuts that are defined
    cuts = analyze.loadCuts(config)

    # load all the analysis jobs - booking histograms, event counters for cutflows, and much more
    # stores a boolean in config for determining whether or not analysis is cutbased
    # (yes if no MVA detected or at least 1 analysis job is booked)
    analyze.bookAnalysisJobs(config, cuts)

    # cutbased bool set in bookAnalysisJobs above
    runtime = config.getFolder("runtime+")
    cutbased = runtime.getTagBoolDefault("cutbased", False)

    # TODO: should this go in one fo the methods?
    if config.getTagBoolDefault("printCuts",cutbased):
        cuts.printCut();

    if customobservables or config.getTagBoolDefault("printObservables"):
        QFramework.INFO("custom observables were defined - this is the list of known observables:")
        QFramework.TQTreeObservable.printObservables()

    # run the cutbased analysis
    if cutbased:
        # create an analysis sample visitor that will successively visit all the samples and execute the analysis when used
        visitor = analyze.createSampleVisitor(config, cuts)

        # TODO: do systematics really go here?
        #       or should they go above if cutbased (like in runAnalysis, without the use yet of visitor) so that they can be set even if cutbased = false (MVA only analysis)
        # if not robust and not dummy:
        #     # perform any pre-processing of the sample folder for handling of systematic uncertainties
        #     # this step is likely to be highly analysis-dependent, so this is just an example implementation
        #     analyze.prepareSystematicsExample(config, samples, visitor)

        # # TODO: put this in prepareSystematicsExample method?
        # # possibly print how the folder looks like now
        # if config.getTagBoolDefault("showChannels",False):
        #     QFramework.INFO("after taking care of channel and systematics setup, your sample folder looks like this:")
        #     samples.printContents("r2dt")

        # book algorithms that will be executed on the events before any cuts are applied or analysis jobs are executed
        analyze.bookAlgorithms(config, visitor)

        # execute analysis, visiting every sample and running over every event
        # this step might take a VERY LONG time
        #nEvents = analyze.executeAnalysis(config, samples, visitor)
        nsamples = analyze.executeAnalysis(config, samples, visitor)

    # flag indicating to run analysis in debug mode
    debug = CLI.getTagBoolDefault("debug",False)

    analysisError = "" #setting this to a non-empty string will supress writing the regular output file and write an alternative file with the value of this string
    if cutbased:
        pass

    # TODO: provide a defaultConfig for the path to cuts
    # attach the definitions to the info folder
    if not cuts.dumpToFolder(samples.getFolder("info/cuts+")):
        QFramework.ERROR("unable to attach cuts to info folder")

    # train any multivariate classifiers
    mvascriptnames = config.getTagVString("MVA")
    if len(mvascriptnames)>0:
        analyze.trainMVA(config, samples, cuts)
    elif not cutbased:
        appname = QFramework.TQLibrary.getApplicationName().Data()
        QFramework.ERROR("no analysis script given, please use 'MVA: myAnalysis' under the [{:s}] section to import and execute some python script 'MVA/myAnalysis.py'. it should contain a function 'runMVA(...)' that will receive a readily prepared sample folder at your disposal".format(appname))

    if config.getTagBoolDefault("printObservables",False):
        QFramework.TQObservable.printObservables()

    if (config.hasTagString("memoryGraph")):
        gROOT.SetBatch(True)
        memGraph = QFramework.TQLibrary.getMemoryGraph()
        memFileName = config.getTagStringDefault("memoryGraph","memoryUsage.pdf")
        QFramework.TQStringUtils.ensureTrailingText(memFileName,".pdf")
        memCanvas = QFramework.TQHistogramUtils.applyATLASstyle(memGraph,"Internal",0.2,0.9,0.9,"timestamp","rss [byte]")
        memCanvas.SaveAs(memFileName.Data())

    # write the sample folder to disk
    # TODO: if we are running in debug mode, should call output file a different name, something like debug.root
    #       Put this in writeSampleFolder method?
    # TODO: write alternate output file if cutbased or MVA analysis fails
    common.writeSampleFolder(config, samples)

    if config.hasUnreadKeys("!.*"):
        QFramework.WARN("the following config keys were not read: "+(",".join([ key.GetName() for key in  config.getListOfUnreadKeys("!.*") ])))

    # write and print some performance information like memory usage and runtime
    common.printExecutionStatistics(config)

    #Let the user know how heavy this run was:
    # TODO: put this in printExecutionStatistics?
    QFramework.INFO("This analysis run used up to {:.2f} MiB of memory (RSS).".format(QFramework.TQUtils.getPeakRSS()/1024./1024.))

    #temporary fix to prevent segfaults in AnaBase 2.3.48 and beyond
    # TODO: still necessary?
    ROOT.xAOD.ClearTransientTrees()

if __name__ == "__main__":
    # create a pre-configured argument parser
    parser = analyze.DefaultArgumentParser()

    import sys
    import QFramework
    import ROOT
    import imp

    # use the argument parser to read the command line arguments and config options from the config file
    config = common.getConfigOptions(parser.parse_args())

    # TODO: Do we still need this line?
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    # call the main function
    main(config)

