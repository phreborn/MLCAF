import QFramework
import ROOT
from CommonAnalysisHelpers import common

def prepareSystematics(config, samples):
    """prepare the systematic handling for your analysis"""
    QFramework.INFO("Preparing custom systematics...")

    CLI = config.getFolder("CLI+")
    # flag indicating to run a robust analysis
    robust = CLI.getTagBoolDefault("robust",False)
    # flag indicating to run a dummy analysis
    dummy = CLI.getTagBoolDefault("dummy",False)

    if not robust and not dummy:
        subfolders = samples.getListOfSampleFolders("?")
        doNominal = config.getTagBoolDefault("doNominal",True)
        channels = config.getTagVStandardString("channels")
        mcasvchannels = set([ c for c in channels ])
        for c in channels:
            for sf in subfolders:
                if sf.getTagBoolDefault("isData",False):
                    # we're in a data SampleFolder
                    # just set some nominal tags for this channel subfolder
                    f = sf.getSampleFolder(c)
                    if not f: continue
                    f.setTagString(".mcasv.channel",f.getTagStringDefault("channel",""))
                    continue
                # we're in a MC SampleFolder
                f = sf.getSampleFolder(c)
                if not f:
                    QFramework.WARN("unable to retrieve sample folder '{:s}' from '{:s}'. Is this expected from your path restriction?".format(c,sf.GetName()))
                    sf.printContents()
                    continue #if this is not a valid folder, don't do anything with it, you'll get a null pointer exception otherwise!

                # right now, we are treating p4 systematics and sf systematics as uncorrelated
                # we do only look at the diagonal terms where one systematic is activated
                # crossover terms are neglected for now, hence we have two separate loops
                for p4type in config.getTagVString("p4Systematics"):
                    fileWithP4Variations = ROOT.TString()
                    if config.getTagString("p4SystematicsList."+p4type, fileWithP4Variations):
                        varFile = QFramework.TQFolder.loadFromTextFile(QFramework.TQPathManager.findFileFromEnvVar(fileWithP4Variations, "CAFANALYSISSHARE"))
                        if varFile:
                            print("=="+str(c)+"==")
                            print("==="+str(sf)+"===")
                            print("===="+str(p4type)+"====")
                            for p4var in varFile.getListOfFolders("Variations/?"):
                                p4syst = p4var.GetName()
                                # for each p4 systematic, copy the channel folder
                                if not p4syst or len(p4syst)<1: continue
                                newname=c+"_"+p4syst
                                newf = f.copy(newname)
                                if not newf:
                                    QFramework.BREAK("unable to copy folder {:s} to new name {:s}".format(f.GetName(),newname))
                                sf.addFolder(newf)
                                # set the appropriate tags
                                newf.setTagString(".mcasv.channel",newname)
                                newf.setTagString("p4Variation."+p4type,p4syst)
                                # change tree location
                                print("====="+p4syst+"=====")
                                for sam in newf.getListOfSamples():
                                    if sam.hasTag(".init.treename"):
                                        sam.setTagString(".init.treename", p4syst)
                                    # skip super-samples without a file/tree itself
                                    if sam.hasSubSamples(): continue
                                    origTreeFilename = sam.getFilename()
                                    if origTreeFilename:
                                        sam.setTreeLocation(origTreeFilename+":"+p4syst)
                                        #print(sam.getTreeLocation())
                                #mcasvchannels.add(newname.Data())
                                mcasvchannels.add(newname)

                for sftype in config.getTagVString("sfSystematics"):
                    fileWithSFVariations = ROOT.TString()
                    if config.getTagString("sfSystematicsList."+sftype, fileWithSFVariations):
                        varFile = QFramework.TQFolder.loadFromTextFile(QFramework.TQPathManager.findFileFromEnvVar(fileWithSFVariations, "CAFANALYSISSHARE"))
                        if varFile:
                            for sfvar in varFile.getListOfFolders("Variations/?"):
                                sfsyst = sfvar.GetName()
                                # for each sf systematic, copy the channel folder
                                if not sfsyst or len(sfsyst)<1: continue
                                newname = c+"_"+sfsyst
                                newf = f.copy(newname)
                                if not newf:
                                    QFramework.BREAK("unable to copy folder {:s} to new name {:s}".format(f.GetName(),newname))
                                sf.addFolder(newf)
                                # set the appropriate tags
                                newf.setTagString(".mcasv.channel",newname)
                                newf.setTagString("sfVariation."+sftype,sfsyst)
                                #mcasvchannels.add(newname.Data())
                                mcasvchannels.add(newname)

                # if no nominal analysis was requested, we can remove the nominal channels
                if not doNominal:
                    f.detachFromBase()
                else:
                    f.setTagString(".mcasv.channel",f.GetName())

    # Add some nominal top level tags, even if systematics aren't being added
    for p4type in config.getTagVString("p4Systematics"):
        samples.setTagString("p4Variation."+p4type,"nominal")
    for sftype in config.getTagVString("sfSystematics"):
        samples.setTagString("sfVariation."+sftype,"nominal")

    # possibly print how the folder looks like now
    if config.getTagBoolDefault("showChannels",False):
        QFramework.INFO("after taking care of channel and systematics setup, your sample folder looks like this:")
        samples.printContents("r2dt")
        samples.writeToFile("myPathedSampleFolder.root",1,2)

    # save the whole collection of channels (including now systematics)
    # for access later when creating the MCASV
    runtime = config.getFolder("runtime+")
    for i, channel in enumerate(mcasvchannels):
        if "ROOT" in str(type(channel)):
            from QFramework import WARN
            QFramework.WARN("Please make sure that every mcasvchannel is only booked once. The python set doesn't help when adding c++ ROOT instances (" + str(type(channel)) + ".")
        runtime.setTagString("mcasvchannels."+str(i), channel)

    return
