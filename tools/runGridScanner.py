#!/usr/bin/env python2

import argparse
import sys
import os
import re

# the alias is the 'appliation name' that will be dumped to the info tags of any
# sample folder created
alias = "runGridScanner"

def plotResults(config, channel):

    dictionary = TQTaggable()
    chname = TQStringUtils.makeValidIdentifier(channel)
    evalMode = config.getTagDefault("evaluator","simple")
    evalMode.ToLower()
    evname = TQStringUtils.makeValidIdentifier(evalMode);
    dictionary.setTagString("CH",             channel);
    dictionary.setTagString("LEPCH",        channel);
    dictionary.setTagString("CHANNEL",    chname);
    dictionary.setTagString("EVAL",         evname);
    dictionary.setTagString("EVALUATOR",evname);
    dictionary.setTagString("eval",         evname);
    dictionary.setTagString("evaluator",evname);

    rootfname = dictionary.replaceInText(config.getTagDefault("outputFile","results.root"));

    INFO("Reading input file for making plots: {:s}".format(rootfname))
    results = TQFolder.loadFolder(str(rootfname)+":results")

    if not results:
        print("[WARNING] cannot open file %s. Maybe you have forgotten to run the optimization first to produce the file".format(rootfname))
        BREAK("cannot open file %s".format(rootfname))

    jobname = config.getTagDefault("nDimHistName","gridscan")
    gridscan = results.getObject(jobname)
    if not gridscan:
        BREAK("cannot obtain gridscanner with name: {:s}".format(jobname))

    plotFormat = config.getTagDefault("plotFormat","pdf")
    gridscan.importTags(config)
    gridscan.setTag("ext",plotFormat)

    plotTitle = config.getTagDefault("plotTitle","$(VAR)")
    gridscan.setTag("profile.title",plotTitle)
    gridscan.setTag("histogram.title",plotTitle)
    INFO("Setting plot title to '{:s}'".format(plotTitle))

    minsignificance = config.getTagDoubleDefault("plotMinSignificance", 5)
    INFO("Using significance minimum Z={:f}".format(minsignificance))
    gridscan.setTagDouble("profile.sigMin",minsignificance)

    gridscan.setTagBool("profile.showmax",True)
    gridscan.setTagBool("style.drawATLAS",False)
    gridscan.setTagString("labels.atlas.text","work in progress")
    gridscan.setTagDouble("labels.atlas.scale",1.0)
    gridscan.setTagString("cutLine2D.text","previous cut value")
    gridscan.setTagDouble("cutLine2D.textScale",1.5)
    gridscan.setTagDouble("cutLine2D.xPos",0.15)

    # get baseline cuts
    basecuts = config.getTagVString("drawCuts")
    if len(basecuts)>0:
        basecuts = basecuts[0].Data().split(",")
        for b in basecuts:
            histname = TQStringUtils.trim(b.split("=")[0])
            cutval = float(b.split("=")[1])
            gridscan.setTagDouble("cut."+str(histname), cutval)
    else:
        INFO("No tag for baseline cuts found, not showing basecuts in plots")

    plotDir = dictionary.replaceInText(config.getTagDefault("plotDirectory","plots/"))
    if not os.path.exists(plotDir.Data()): os.makedirs(plotDir.Data())
    fractions = config.getTagVDouble("cutTopFractions")
    #for f in fractions:
    #    gridscan.plotAndSaveAllHistograms(plotDir,f)
    #    # gridscan.plotAndSaveAllHistograms2D(plotDir,f)
    #numbers = config.getTagVInteger("cutTopNumbers")
    #for n in numbers:
    #    gridscan.plotAndSaveAllHistograms    (plotDir,n)
    #    #gridscan.plotAndSaveAllHistograms2D(plotDir,n)
    sigTopFractions = config.getTagVDouble("sigTopFractions")
    for sf in sigTopFractions:
        gridscan.plotAndSaveAllSignificanceProfiles(sf, "")
        #gridscan.plotAndSaveAllSignificanceProfiles2D(plotDir,sf)

    #sigTopNumbers = config.getTagVInteger("sigTopNumbers")
    #for sn in sigTopNumbers:
    #    gridscan.plotAndSaveAllSignificanceProfiles    (plotDir,sn)
    #    #gridscan.plotAndSaveAllSignificanceProfiles2D(plotDir,sn)

def createSignificanceEvaluator(config, dictionary, channel, samples):
    # use code from createSignificanceEvaluator.cxx
    if not config:
        BREAK("ERROR: aborting evaluation, invalid configuration!")

    # retrieve the evaluator mode
    evalMode = config.getTagDefault("evaluator","simple")
    evalMode.ToLower()
    isSimple = True

    verboseEvaluator = config.getTagDefault("evaluator.verbose", False);
    verboseReader = config.getTagDefault("reader.verbose", False);

    str_signal = dictionary.replaceInText(config.getTagDefault("simple.signal","/sig/$(LEPCH)/mh125/ggf"))
    str_background = dictionary.replaceInText(config.getTagDefault("simple.background", "/bkg"))

    INFO("Creating {:s} significance evaluator for channel {:s}".format(evalMode.Data(), channel.Data()))
    INFO("With signal: {:s} and background: {:s}".format(str_signal.Data(), str_background.Data()))

    # get nominal sample folder
    nominal = TQSampleFolder()
    if samples:
        nominal = samples
        #TQListUtils.findInListByTag(samples, ".key", "samples")
        if not nominal:
            BREAK("no sample folder found")

    # create and initialize the evaluator
    if evalMode == "cl":
        WARN("Evaluation mode cl is not yet implemented. using poisson instead")
        evalMode = "poisson"
    if evalMode == "poisson":
        poisson = TQPoissonSignificanceEvaluator(nominal, str_signal, str_background)
        evaluator = poisson
    elif evalMode == "s/sqrt(b)":
        simple = TQSimpleSignificanceEvaluator(nominal, str_signal, str_background)
        evaluator = simple
    elif evalMode == "s/sqrt(s+b)":
        simple2 = TQSimpleSignificanceEvaluator2(nominal, str_signal, str_background)
        evaluator = simple2
    # the following is not supported for now
    # elif evalMode == "s/db":
    #     weighted = TQWeightedSignificanceEvaluator(nominal, str_signal, str_background)
    #     evaluator = weighted
    # elif evalMode == "s/sqrt(ds2+db2)":
    #     weighted2 = TQWeightedSignificanceEvaluator2(nominal, str_signal, str_background)
    #     evaluator = weighted2
    else:
        simple = TQSimpleSignificanceEvaluator(nominal, str_signal, str_background)
        evaluator = simple

    # configure the evaluator
    # setting cutoff
    cutoff = config.getTagDefault("cutoff",0.0)
    INFO("Using cutoff value: {:.3f}".format(cutoff))
    evaluator.setTagDouble("cutoff",cutoff)
    relBkgErrCutoff = config.getTagDefault("relBkgErrCutoff",1.0);
    INFO("Using relative background uncertainty cutoff value: {:.3f}".format(relBkgErrCutoff))
    evaluator.setTagDouble("relBkgErrCutoff",relBkgErrCutoff)

    evaluator.setVerbose(verboseEvaluator)
    if evaluator.getReader():
        evaluator.getReader().setVerbose(verboseReader);

    if isSimple:
        regions = config.getTagVString("simple.regions")
        for r in regions:
            INFO("Adding region {:s}".format(r))
            evaluator.addRegion(r)

    return evaluator

def createGridScanner(config, evaluator):
    # code from createGridScanner.cxx
    if not config:
        BREAK("ERROR: aborting evaluation, invalid configuration!")

    INFO("Setting up gridscanner")
    jobname = config.getTagDefault("nDimHistName", "gridscan")
    gridscan = TQGridScanner(jobname, evaluator)

    # evalMode = config.getTagDefault("evaluator", "simple").ToLower()
    verbose = config.getTagDefault("verbose", True)
    gridscan.setVerbose(verbose)

    # possibility to use heartbeats for very large jobs. see config file for explanation
    heartBeatCommand = config.getTagDefault("heartBeatCommand", "")
    heartBeatInterval = config.getTagDefault("heartBeatInterval", 0)
    if (heartBeatInterval > 0) and (heartBeatCommand.Length() > 0):
        INFO("Setting scanner heartbeat to %s every %s ms", heartBeatCommand, heartBeatInterval)
        gridscan.setHeartbeat(heartBeatCommand,heartBeatInterval)

    # book all variables
    INFO("Booking variables")
    #variablesUpperScan = config.getTagVString("variablesUpperScan")
    #variablesLowerScan = config.getTagVString("variablesLowerScan")
    #variablesSplit = config.getTagVString("variablesSplit")
    #variablesUpperSwitch = config.getTagVString("variablesUpperSwitch")
    #variablesLowerSwitch = config.getTagVString("variablesLowerSwitch")
    #variablesUpperFixed, variablesLowerFixed    = TString(""), TString("")
    #config.getTagString("variablesUpperFixed", variablesUpperFixed)
    #config.getTagString("variablesLowerFixed", variablesLowerFixed)
    #variablesWindowFixed = TString("")
    #config.getTagString("variablesWindowFixed", variablesWindowFixed)

    #for upper in variablesUpperScan:
    #    if not TQStringUtils.trim(upper).IsNull(): gridscan.addVariableUpper(upper)
    #for lower in variablesLowerScan:
    #    if not TQStringUtils.trim(lower).IsNull(): gridscan.addVariableLower(lower)
    #for split in variablesSplit:
    #    if not TQStringUtils.trim(split).IsNull(): gridscan.addVariableSplit(split)
    #for upperswitch in variablesUpperSwitch:
    #    if not TQStringUtils.trim(upperswitch).IsNull(): gridscan.addVariableUpperSwitch(upperswitch)
    #for lowerswitch in variablesLowerSwitch:
    #    if not TQStringUtils.trim(lowerswitch).IsNull(): gridscan.addVariableLowerSwitch(lowerswitch)
    #for upperfixed in str(variablesUpperFixed).split(","):
    #    if TQStringUtils.trim(upperfixed).IsNull(): continue
    #    name, value = TQStringUtils.trim(upperfixed.split("=")[0]), float(upperfixed.split("=")[1])
    #    if not TQStringUtils.trim(name).IsNull(): gridscan.addVariableUpperFixed(name, value)
    #for lowerfixed in str(variablesLowerFixed).split(","):
    #    if TQStringUtils.trim(lowerfixed).IsNull(): continue
    #    name, value = TQStringUtils.trim(lowerfixed.split("=")[0]), float(lowerfixed.split("=")[1])
    #    if not TQStringUtils.trim(name).IsNull(): gridscan.addVariableLowerFixed(name, value)
    #for windowfixed in str(variablesWindowFixed).split(","):
    #    if TQStringUtils.trim(windowfixed).IsNull(): continue
    #    low, name, up = float(windowfixed.split("<")[0]), TQStringUtils.trim(windowfixed.split("<")[1]), float(windowfixed.split("<")[2])
    #    if not TQStringUtils.trim(name).IsNull(): gridscan.addVariableWindowFixed(name, low, up)

    # check for restricted variables ranges
    boundaries = TString("")
    if config.getTagString("boundaryList", boundaries):
        lines = TQStringUtils.readFileLines(boundaries)
        if not lines:
            WARN("Could not open input file {:s} - not applying any boundary conditions!".format(boundaries))
        else:
            for l in lines:
                l.ReplaceAll("\t"," ")
                lower, upper, split, obsName, buf = TString(""), TString(""), TString(""), TString(""), TString("")

                isSplit = not l.Contains("<")
                if isSplit:
                    # split cuts are denoted by "|"
                    TQStringUtils.readUpTo(l, obsName, "|")
                    obsName = TQStringUtils.trim(obsName)
                    TQStringUtils.readToken(l, buf, "|")
                    splitVals = TQStringUtils.trim(l)
                    rng = parseRange(splitVals)
                    obs = gridscan.getObs(obsName)
                    setCutSplit(obs, rng)
                else:
                    TQStringUtils.readUpTo(l, buf, "<")
                    lowerRangeOrObsName = TQStringUtils.trim(buf)
                    # if the token contains characters, it's an observable name
                    if re.match("^[a-zA-Z]", str(lowerRangeOrObsName)):
                        obsName = lowerRangeOrObsName
                        hasUpperBound = True
                    else:
                        lowerRange = parseRange(lowerRangeOrObsName)
                        TQStringUtils.readToken(l, buf, "<")
                        # switch cuts are denoted by "<|"
                        isSwitchCut = l[0] == "|"
                        if isSwitchCut: TQStringUtils.readToken(l, buf, "|")
                        hasUpperBound = l.Contains("<")
                        if hasUpperBound:
                            TQStringUtils.readUpTo(l, obsName, "<")
                            obsName = TQStringUtils.trim(obsName)
                        else:
                            obsName = TQStringUtils.trim(l)
                        obs = gridscan.getObs(obsName)
                        setCutLower(obs, lowerRange, isSwitchCut)
                    if hasUpperBound:
                        obs = gridscan.getObs(obsName)
                        TQStringUtils.readToken(l, buf, "<")
                        isSwitchCut = l[0] == "|"
                        if isSwitchCut: TQStringUtils.readToken(l, buf, "|")
                        upperRange = parseRange(TQStringUtils.trim(l))
                        setCutUpper(obs, upperRange, isSwitchCut)


    # reduce the size of the multidimensional histogram
    # by applying all fixed cuts and reject these axis in the following.
    # this will lead to an improved performance when running the scan.
    #axisToEvaluate = config.getTagStringDefault("simple.axisToEvaluate", "MT")
    #INFO("setting {:s} as the axis where significance is computed".format(axisToEvaluate))
    #gridscan.updateEvaluatorHists(axisToEvaluate)
    # TODO: Check/Reimplement the above

    return gridscan

def setCutLower(obs, rng, isSwitch):
    if type(rng) is float:
        obs.setSwitchCutLower if isSwitch else obs.setFixedCutLower(rng)
    else:
        obs.setRangeCutLower(*rng)

def setCutUpper(obs, rng, isSwitch):
    if type(rng) is float:
        obs.setSwitchCutUpper if isSwitch else obs.setFixedCutUpper(rng)
    else:
        obs.setRangeCutUpper(*rng)

def setCutSplit(obs, rng):
    obs.setFixedCutSplit(rng) if type(rng) is float else obs.setRangeCutSplit(*rng)

# CHECK PARSING here! especially stepsize seems to be parsed incorrectly!    
def parseRange(string):
    TQStringUtils.removeLeading(string, "([{")
    TQStringUtils.removeTrailing(string, ")]}")
    splitBounds = [str(bound) for bound in TQStringUtils.tokenizeVector(string, ",")]
    # nSteps == 0 denotes to use the default binning of the histogram
    lower = float(splitBounds[0])
    nBounds = len(splitBounds)
    if nBounds == 1:
        return float(splitBounds[0])
    elif nBounds == 2:
        upper = float(splitBounds[1])
        return (lower, upper, 0)
    else:
        upper = float(splitBounds[1])
        nSteps = int(splitBounds[2])
        return lower if not upper else (lower, upper, nSteps)

def runScan(config, samples, channel = "[em+me]"):

    if not samples:
        INFO("Running in dummy mode")
    INFO("Found {:s}".format(samples.getTagStringDefault(".key", samples.getName())))

    dictionary = TQTaggable()
    chname = TQStringUtils.makeValidIdentifier(channel)
    evalMode = config.getTagDefault("evaluator","simple")
    evalMode.ToLower()
    evname = TQStringUtils.makeValidIdentifier(evalMode);
    dictionary.setTagString("LEPCH",        channel);

    evaluator = createSignificanceEvaluator(config, dictionary, channel, samples)
    if not evaluator:
        BREAK("significance evaluator could not be created!")

    
    gridscan = createGridScanner(config, evaluator)
    if not gridscan:
        BREAK("gridscanner could not be created!")

    if not samples:
        # for dummy mode only, not yet implemented!
        WARN("Dummy mode is not yet implemented, the following steps might fail")
        
    # before running the gridscan plot the input distributions 
    if args.plotInputs:
        INFO("Plotting input observables")
        gridscan.plotInputHistogramProjections(config)
  
    # now run the gridscan
    INFO("Initiating scan")
    runstatus = gridscan.run()
    if not config.getTagDefault("evaluator.verbose", False): print("")
    INFO("Scan completed")
    
    results = gridscan.results()
    # type(results) = TQGridScanResults()
    nPoints = results.points().size()
    if nPoints < 1:
        BREAK("Something went terribly wrong - there are no points! one possible reason for this is that you requested to loop over non-existant variables. check your configuration and validate your input data. afterwards, you may try again.")

    INFO("Sorting points")
    results.sortPoints()
    INFO("Found {:d} points!".format(nPoints))
    INFO("Significances between {:f} and {:f}".format(results.points()[0].significance(), results.points()[nPoints-1].significance()))

    INFO("Top points are:")
    results.printPoints(min(10, nPoints))

    # save to a root file
    resultsDir = TQFolder("results")
    resultsDir.addObject(results)

    outFile = config.getTagDefault("outputFile","results.root")
    INFO("Saving results to {:s}".format(outFile))

    TQUtils.ensureDirectoryForFile(outFile);
    if samples:
       resultsDir.SaveAs(outFile.Data());

    # Remove results folder from TQFolder before its destructor is called.
    resultsDir.removeObject(results.GetName())
    # This prevents nasty errors when memory is cleared
    # TQFolder is not able to remove/delete objects of type TQGridScanResults

    return results

def main(args):
    if args.width:
        TQLibrary.setConsoleWidth(args.width)

    # print a welcome message
    print(TQStringUtils.makeBoldWhite("Running significance scan"))

    # open the configfile
    cfgname=TString(args.cfgname)
    INFO("Reading configuration for '{:s}' from file '{:s}'".format(alias,cfgname.Data()))
    configreader = TQConfigReader(alias,cfgname)

    # export the config options to a taggable object
    config = configreader.exportAsTags()
    if not config:
        BREAK("unable to retrieve configuration from file '{:s}' - please check the filename".format(cfgname))
    config.resetReadFlags()

    # check if dummy run is active (dummy Run not yet supported)
    dummy = config.getTagBoolDefault("dummyScan", False)

    # load the sample folder (which contains n-dim histograms)
    sfinfilename = config.getTagStringDefault("inputFile","output/samples-run2-sigscan.root:samples");
    INFO("Loading sample folder '{:s}'".format(sfinfilename.Data()))
    samples = TQSampleFolder.loadSampleFolder(sfinfilename)
    if not samples and not dummy:
        BREAK("unable to load sample folder '{:s}' - please check input path".format(sfinfilename))
    # elif not samples:
    # samples = TQSampleFolder("test")

    # write the configuration to the info/config subfolder
    info = samples.getFolder("info/config/runSignificanceScan+")
    info.setInfoTags()
    config.exportTags(info)

    channels = config.getTagVString("scanChannels")
    for ch in channels:
        if not args.plotResults:
            runScan(config, samples, ch)
        else:
            rootfname = config.getTagDefault("outputFile","results.root")
            results = TQFolder.loadFolder(str(rootfname)+":results")
            if not results:
                WARN("File with gridscan results not found, running gridscanner first!")
                runScan(config, samples, ch)
            plotResults(config, ch)

    INFO("Gridscanner successfully executed!")

if __name__ == "__main__":
    # parse the CLI arguments
    parser = argparse.ArgumentParser(description='Run the HSG3 Run2 Significance Scan.')
    parser.add_argument('cfgname', metavar='CONFIG', type=str,
                        default="config/runMVA.cfg",
                        help='Path to the analysis config file to be processed')
    parser.add_argument('--plotResults', action="store_const", const=True, default=False,
                        help='After scanning through the cuts call the plotting function')
    parser.add_argument('--plotInputs', action="store_const", const=True, default=False,
                        help='Plot all dimensions of multidimensional input histogram')
    parser.add_argument('--width', dest="width", type=int, default=0, help="Console width for printouts")
    args = parser.parse_args()
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    from QFramework import *
    from ROOT import *
    ROOT.PyConfig.IgnoreCommandLineOptions = True
    TQLibrary.getQLibrary().setApplicationName(alias);

    main(args);
