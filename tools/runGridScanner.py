#!/usr/bin/env python2

import argparse
import sys
import os
import re

# the alias is the 'appliation name' that will be dumped to the info tags of any
# sample folder created
alias = "runGridScanner"

def plotResults(config, dictionary):

    rootfname = dictionary.replaceInText(config.getTagDefault("outputFile","results.root"));

    rootfname = dictionary.replaceInText(str(rootfname)+":results_$(LEPCHNAME)")
    rootfpath = QF.TQPathManager.getPathManager().getTargetPath(rootfname)
    QF.INFO("Reading input file for making plots: {:s}".format(rootfpath))
    results = QF.TQFolder.loadFolder(rootfpath)

    if not results:
        QF.WARN("cannot open file {:s}. Maybe you have forgotten to run the optimization first to produce the file".format(rootfname.Data()))
        QF.BREAK("cannot open file {:s}".format(rootfname.Data()))

    jobname = config.getTagDefault("nDimHistName","gridscan")
    gridscanResults = results.getObject(jobname)
    if not gridscanResults:
        QF.BREAK("cannot obtain gridscanner with name: {:s}".format(jobname))

    plotFormat = config.getTagDefault("plotFormat","pdf")
    gridscanResults.importTags(config)
    gridscanResults.setTag("ext",plotFormat)

    plotTitle = config.getTagDefault("plotTitle","$(VAR)")
    gridscanResults.setTag("profile.title",plotTitle)
    gridscanResults.setTag("histogram.title",plotTitle)
    QF.INFO("Setting plot title to '{:s}'".format(plotTitle))

    # Get index of figure of merit that should be plotted
    indexFOMForPlotting = config.getTagIntegerDefault("indexFOMForPlotting", 0)
    gridscanResults.setFOMIndexForPlotting(indexFOMForPlotting)
    QF.INFO("Choosing the figure of merit with the name {:s} for plotting".format(gridscanResults.FOMDefinitions[indexFOMForPlotting]))
    
    signifProfileYTitle = config.getTagDefault("titleFigureOfMerit","Z_{exp}")
    gridscanResults.setTag("profile.titleFigureOfMerit", signifProfileYTitle)
    QF.INFO("Setting plot y-axis title of significance profile to '{:s}'".format(signifProfileYTitle))

    minsignificance = config.getTagDoubleDefault("plotMinSignificance", 5)
    QF.INFO("Using significance minimum Z={:f}".format(minsignificance))
    gridscanResults.setTagDouble("profile.sigMin",minsignificance)

    gridscanResults.setTagBool("profile.showmax",True)
    gridscanResults.setTagBool("style.drawATLAS",False)
    gridscanResults.setTagString("labels.atlas.text","work in progress")
    gridscanResults.setTagDouble("labels.atlas.scale",1.0)
    gridscanResults.setTagString("cutLine2D.text","previous cut value")
    gridscanResults.setTagDouble("cutLine2D.textScale",1.5)
    gridscanResults.setTagDouble("cutLine2D.xPos",0.15)
    gridscanResults.setTagDouble("style.axis.fontSize",config.getTagDoubleDefault("axisLabelSize", 0.04))
    gridscanResults.setTagDouble("style.axis.titleSize",config.getTagDoubleDefault("axisTitleSize", 0.04))
    
    # get baseline cuts
    basecuts = config.getTagVString("drawCuts")
    if len(basecuts)>0:
        basecuts = basecuts[0].Data().split(",")
        for b in basecuts:
            histname = QF.TQStringUtils.trim(b.split("=")[0])
            cutval = float(b.split("=")[1])
            gridscanResults.setTagDouble("cut."+str(histname), cutval)
    else:
        QF.INFO("No tag for baseline cuts found, not showing basecuts in plots")

    plotDir = dictionary.replaceInText(config.getTagDefault("plotDirectory","plots/"))
    chname = QF.TQStringUtils.makeValidIdentifier(dictionary.replaceInText("$(LEPCH)"))
    if len(config.getTagVString("scanChannels")) > 1:
      QF.TQStringUtils.removeTrailing(plotDir, "/")
      plotDir = plotDir+"-"+chname
    fractions = config.getTagVDouble("cutTopFractions")
    #for f in fractions:
    #    gridscanResults.plotAndSaveAllHistograms(plotDir,f)
    #    # gridscanResults.plotAndSaveAllHistograms2D(plotDir,f)
    #numbers = config.getTagVInteger("cutTopNumbers")
    #for n in numbers:
    #    gridscanResults.plotAndSaveAllHistograms    (plotDir,n)
    #    #gridscanResults.plotAndSaveAllHistograms2D(plotDir,n)
    sigTopFractions = config.getTagVDouble("sigTopFractions")
    for sf in sigTopFractions:
        gridscanResults.plotAndSaveAllSignificanceProfiles(sf, "", plotDir)
        #gridscanResults.plotAndSaveAllSignificanceProfiles2D(plotDir,sf)

    #sigTopNumbers = config.getTagVInteger("sigTopNumbers")
    #for sn in sigTopNumbers:
    #    gridscanResults.plotAndSaveAllSignificanceProfiles    (plotDir,sn)
    #    #gridscanResults.plotAndSaveAllSignificanceProfiles2D(plotDir,sn)

def createSignificanceEvaluator(config, dictionary, samples):
    # use code from createSignificanceEvaluator.cxx
    if not config:
        BREAK("ERROR: aborting evaluation, invalid configuration!")

    # For now always true
    isSimple = True
    
    verboseEvaluator = config.getTagDefault("evaluator.verbose", False);
    verboseReader = config.getTagDefault("reader.verbose", False);
    
    str_signal = dictionary.replaceInText(config.getTagDefault("simple.signal","/sig/$(LEPCH)/mh125/ggf"))
    str_background = dictionary.replaceInText(config.getTagDefault("simple.background", "/bkg/$(LEPCH)"))
    QF.INFO("Definition for signal: {:s} and background: {:s}".format(str_signal.Data(), str_background.Data()))
    
    # get nominal sample folder
    nominal = QF.TQSampleFolder()
    if samples:
        nominal = samples
        #TQListUtils.findInListByTag(samples, ".key", "samples")
        if not nominal:
            BREAK("no sample folder found")

    # retrieve the figure of merits 
    fomDefinitions = config.getTagVString("figureOfMerits")
    
    # create and initialize the evaluator
    simple = QF.TQSignificanceEvaluatorBase(nominal, str_signal, str_background)
    simple.addFunctionsFOM(fomDefinitions)
    evaluator = simple
    
    # TODO: Incorporate TQCLSignificanceEvaluator here to utilize the likelihood fit in the scan
    
    # configure the evaluator
    # setting cutoff
    cutoff = config.getTagDefault("cutoff",0.0)
    QF.INFO("Using cutoff value: {:.3f}".format(cutoff))
    evaluator.setTagDouble("cutoff",cutoff)
    relBkgErrCutoff = config.getTagDefault("relBkgErrCutoff",1.0);
    QF.INFO("Using relative background uncertainty cutoff value: {:.3f}".format(relBkgErrCutoff))
    evaluator.setTagDouble("relBkgErrCutoff",relBkgErrCutoff)

    evaluator.setVerbose(verboseEvaluator)
    if evaluator.getReader():
        evaluator.getReader().setVerbose(verboseReader);

    if isSimple:
        regions = config.getTagVString("simple.regions")
        for r in regions:
            QF.INFO("Adding region {:s}".format(r))
            evaluator.addRegion(r)

    return evaluator

def createGridScanner(config, evaluator):
    # code from createGridScanner.cxx
    if not config:
        BREAK("ERROR: aborting evaluation, invalid configuration!")

    QF.INFO("Setting up gridscanner")
    jobname = config.getTagDefault("nDimHistName", "gridscan")
    gridscan = QF.TQGridScanner(jobname, evaluator)

    # evalMode = config.getTagDefault("evaluator", "simple").ToLower()
    verbose = config.getTagDefault("verbose", True)
    gridscan.setVerbose(verbose)

    # possibility to use heartbeats for very large jobs. see config file for explanation
    heartBeatCommand = config.getTagDefault("heartBeatCommand", "")
    heartBeatInterval = config.getTagDefault("heartBeatInterval", 0)
    if (heartBeatInterval > 0) and (heartBeatCommand.Length() > 0):
        QF.INFO("Setting scanner heartbeat to %s every %s ms", heartBeatCommand, heartBeatInterval)
        gridscan.setHeartbeat(heartBeatCommand,heartBeatInterval)

    # book all variables
    QF.INFO("Booking variables")

    # check for restricted variables ranges
    boundaries = ROOT.TString("")
    if config.getTagString("boundaryList", boundaries):
    	boundaryPath = QF.TQPathManager.getPathManager().findFileFromEnvVar(boundaries, "CAFANALYSISSHARE")
        lines = QF.TQStringUtils.readFileLines(boundaryPath)
        if not lines:
            QF.WARN("Could not open input file {:s} - not applying any boundary conditions!".format(boundaries))
        else:
            for l in lines:
                l.ReplaceAll("\t"," ")
                lower, upper, split, obsName, buf = ROOT.TString(""), ROOT.TString(""), ROOT.TString(""), ROOT.TString(""), ROOT.TString("")
                isSplit = not l.Contains("<")
                if isSplit:
                    # split cuts are defined with "|"
                    QF.TQStringUtils.readUpTo(l, obsName, "|")
                    obsName = QF.TQStringUtils.trim(obsName)
                    QF.TQStringUtils.readToken(l, buf, "|")
                    splitVals = QF.TQStringUtils.trim(l)
                    rng = parseRange(splitVals)
                    obs = gridscan.getObs(obsName)
                    setCutSplit(obs, rng)
                    gridscan.hasSplitObs = True
                    if len(evaluator.FOMDefinitions()) > 1:
                        QF.ERROR("There is no support for multiple FOMs when a spliting cut is defined! Please choose one figure of merit and rerun!")
                        exit()
                else:
                    QF.TQStringUtils.readUpTo(l, buf, "<")
                    lowerRangeOrObsName = QF.TQStringUtils.trim(buf)
                    # if the token contains characters, it's an observable name
                    if re.match("^[a-zA-Z]", str(lowerRangeOrObsName)):
                        obsName = lowerRangeOrObsName
                        hasUpperBound = True
                    else:
                        lowerRange = parseRange(lowerRangeOrObsName)
                        QF.TQStringUtils.readToken(l, buf, "<")
                        # switch cuts are denoted by "<|"
                        isSwitchCut = l[0] == "|"
                        if isSwitchCut: QF.TQStringUtils.readToken(l, buf, "|")
                        hasUpperBound = l.Contains("<")
                        if hasUpperBound:
                            QF.TQStringUtils.readUpTo(l, obsName, "<")
                            obsName = QF.TQStringUtils.trim(obsName)
                        else:
                            obsName = QF.TQStringUtils.trim(l)
                        obs = gridscan.getObs(obsName)
                        setCutLower(obs, lowerRange, isSwitchCut)
                    if hasUpperBound:
                        obs = gridscan.getObs(obsName)
                        QF.TQStringUtils.readToken(l, buf, "<")
                        isSwitchCut = l[0] == "|"
                        if isSwitchCut: QF.TQStringUtils.readToken(l, buf, "|")
                        upperRange = parseRange(QF.TQStringUtils.trim(l))
                        setCutUpper(obs, upperRange, isSwitchCut)


    # reduce the size of the multidimensional histogram
    # by applying all fixed cuts and reject these axis in the following.
    # this will lead to an improved performance when running the scan.
    #axisToEvaluate = config.getTagStringDefault("simple.axisToEvaluate", "MT")
    #QF.INFO("setting {:s} as the axis where significance is computed".format(axisToEvaluate))
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
    QF.TQStringUtils.removeLeading(string, "([{")
    QF.TQStringUtils.removeTrailing(string, ")]}")
    splitBounds = [str(bound) for bound in QF.TQStringUtils.tokenizeVector(string, ",")]
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

def runScan(config, samples, dictionary):

    if not samples:
        QF.INFO("Running in dummy mode")
    QF.INFO("Found {:s}".format(samples.getTagStringDefault(".key", samples.getName())))

    evalMode = config.getTagDefault("evaluator","simple")
    evalMode.ToLower()
    evname = QF.TQStringUtils.makeValidIdentifier(evalMode);

    QF.INFO("Creating {:s} significance evaluator for channel {:s}".format(evalMode.Data(), dictionary.replaceInText("$(LEPCH)")))
    evaluator = createSignificanceEvaluator(config, dictionary, samples)
    if not evaluator:
        BREAK("significance evaluator could not be created!")

    gridscan = createGridScanner(config, evaluator)
    if not gridscan:
        BREAK("gridscanner could not be created!")

    if not samples:
        # for dummy mode only, not yet implemented!
        QF.WARN("Dummy mode is not yet implemented, the following steps might fail")
        
    # before running the gridscan plot the input distributions 
    if args.plotInputs:
        QF.INFO("Plotting input observables for the first defined region!")
        gridscan.plotInputHistogramProjections(config)
  
    # now run the gridscan
    QF.INFO("Initiating scan")
    runstatus = gridscan.run()
    if not config.getTagDefault("evaluator.verbose", False): print("")
    QF.INFO("Scan completed")
    
    results = gridscan.results()
    # type(results) = TQGridScanResults()
    nPoints = results.points().size()
    if nPoints < 1:
        BREAK("Something went terribly wrong - there are no points! one possible reason for this is that you requested to loop over non-existant variables. check your configuration and validate your input data. afterwards, you may try again.")

    QF.INFO("Sorting points")
    indexFOM = config.getTagIntegerDefault("indexFOMForSorting", 0)
    results.sortPoints(indexFOM)
    QF.INFO("Found {:d} points!".format(nPoints))
    QF.INFO("Significances between {:f} and {:f}".format(results.points()[0].significance(), results.points()[nPoints-1].significance()))

    QF.INFO("Top points are:")
    results.printPoints(min(10, nPoints))

    # save to a root file (overwrites existing object)
    resultsDir = QF.TQFolder(dictionary.replaceInText("results_$(LEPCHNAME)"))
    resultsDir.addObject(results, ".!")
    outFile = config.getTagDefault("outputFile","results.root")
    # use target path here because we will read from the same file later
    outPath = ROOT.TString(QF.TQPathManager.getPathManager().getTargetPath(outFile))
    QF.INFO("Saving results to {:s}".format(outFile))
    QF.TQUtils.ensureDirectoryForFile(outPath)
    if samples:
       resultsDir.writeToFile(outPath.Data(), False);
    # Remove results folder from TQFolder before its destructor is called.
    resultsDir.removeObject(results.GetName())
    # This prevents nasty errors at the end of execution when memory is cleared
    # TQFolder is not able to remove/delete objects of type TQGridScanResults

    return results

def main(args):
    if args.width:
        QF.TQLibrary.setConsoleWidth(args.width)

    # print a welcome message
    print(QF.TQStringUtils.makeBoldWhite("Running Gridscanner"))

    # open the configfile
    cfgname=ROOT.TString(args.cfgname)
    QF.INFO("Reading configuration for '{:s}' from file '{:s}'".format(alias,cfgname.Data()))
    cfgPath = QF.TQPathManager.getPathManager().findFileFromEnvVar(cfgname, "CAFANALYSISSHARE")
    configreader = QF.TQConfigReader(alias,cfgPath)

    # export the config options to a taggable object
    config = configreader.exportAsTags()
    if not config:
        BREAK("unable to retrieve configuration from file '{:s}' - please check the filename".format(cfgname))
    config.resetReadFlags()

    # check if dummy run is active (dummy Run not yet supported)
    dummy = config.getTagBoolDefault("dummyScan", False)

    # load the sample folder (which contains n-dim histograms)
    sfinfilename = config.getTagStringDefault("inputFile","output/samples-run2-sigscan.root:samples");
    QF.INFO("Loading sample folder '{:s}'".format(sfinfilename.Data()))
    sfinfilepath = QF.TQPathManager.getPathManager().getTargetPath(sfinfilename)
    samples = QF.TQSampleFolder.loadSampleFolder(sfinfilepath)
    if not samples and not dummy:
        BREAK("unable to load sample folder '{:s}' - please check input path".format(sfinfilename))
    # elif not samples:
    # samples = QF.TQSampleFolder("test")

    # write the configuration to the info/config subfolder
    info = samples.getFolder("info/config/runSignificanceScan+")
    info.setInfoTags()
    config.exportTags(info)

    channels = config.getTagVString("scanChannels")
    for ch in channels:
        dictionary = QF.TQTaggable()
        dictionary.setTagString("LEPCH", ch);
        chname = QF.TQStringUtils.makeValidIdentifier(ch)
        dictionary.setTagString("LEPCHNAME", chname)
        rootfname = config.getTagDefault("outputFile","results.root")
        rootfname = dictionary.replaceInText(str(rootfname)+":results_$(LEPCHNAME)")
        rootfpath = QF.TQPathManager.getPathManager().getTargetPath(rootfname)
        # suppress error message from QF.TQFolder, which is expected sometimes
        QF.TQLibrary.captureStdout()
        results = QF.TQFolder.loadFolder(rootfpath)
        QF.TQLibrary.restore_stdout()
        if not results:
            QF.WARN("File with gridscan results not found, running gridscanner first!")
            runScan(config, samples, dictionary)
        else: # output file already present, top points can be printed
          QF.INFO("Found previous gridscan results for channel "+ch+" here: "+str(rootfname)+":results. Reading its contents now!")
          QF.INFO("Top points are:")
          jobname = config.getTagDefault("nDimHistName","gridscan")
          gridscanResults = results.getObject(jobname)
          nPoints = gridscanResults.points().size()
          gridscanResults.printPoints(min(10, nPoints))
        if results and args.forceScan:
            QF.INFO("File with gridscan results found but scan is forced by command-line argument!")
            runScan(config, samples, dictionary)
        elif results and args.plotInputs:
          QF.WARN("Although you specified the --plotInputs argument this feature is not executed. The output of a previous gridscan was found and the inputs can only be plotted during a scan of the grid. To ensure a scan (and thus the plotting of the input distributions) you can add the additional command-line argument --forceScan")
        if args.plotResults:
          plotResults(config, dictionary)

    QF.INFO("Gridscanner successfully executed!")

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
    parser.add_argument('--forceScan', action="store_const", const=True, default=False,
                        help='Ensure a scan of the grid even when previous output file is present')
    parser.add_argument('--width', dest="width", type=int, default=0, help="Console width for printouts")
    args = parser.parse_args()
    #get rid of command line arguments since ROOT is very greedy here (and tends to choke from it!)
    sys.argv = []

    import QFramework as QF
    import ROOT
    ROOT.PyConfig.IgnoreCommandLineOptions = True
    QF.TQLibrary.getQLibrary().setApplicationName(alias);

    main(args);
