import QFramework
import ROOT
from CommonAnalysisHelpers import common



def parseSystematicList(config):
    sysFileName = config.getTagStringDefault("sysFileName",'')
    if sysFileName.Length() == 0:
        return list()
    sysFullPath = QFramework.TQPathManager.findFileFromEnvVar(sysFileName, "CAFANALYSISSHARE")

    indexLow = config.getTagIntegerDefault("indexLow", -1)
    indexHigh = config.getTagIntegerDefault("indexHigh", -1)

    sysList = list()
    index = 1
    with open(sysFullPath) as sysFile:
        for line in sysFile.readlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            contents = line.split()
            if len(contents) != 3:
                QFramework.BREAK("Could not parse {:s} in file {:s}".format(line, sysFullPath))
            
            # only add selected variations based on the index (start from 1)
            if indexLow >=0 and indexHigh >=0 and indexHigh >= indexLow:
                if (index < indexLow or index > indexHigh): continue

            sysName, sysType, sysVariation = contents
            sysName = sysName.strip()
            sysType = sysType.strip()
            sysVariation = sysVariation.strip()

            if sysVariation == 'one':
                sysList.append({'name':sysName, 'type': sysType})
            elif sysVariation == 'two':
                sysList.append({'name':sysName+'_1up', 'type': sysType})
                sysList.append({'name':sysName+'_1down', 'type': sysType})
            else:
                QFramework.BREAK("Unknown systematic variation {:s} for {:s}".format(sysVariation, sysName))
            index = index + 1
    return sysList



''' 
Add the systematic variations for a given channelm and sample folder
'''
def addSystematicVariations(c, sf, sysList, mcasvchannels):
    f = sf.getSampleFolder(c)
                
    if not f:
        QFramework.WARN("unable to retrieve sample folder '{:s}' from '{:s}'. Is this expected from your path restriction?".format(c,sf.GetName()))
        sf.printContents()
        return

    with open("AHZ-lephad/auxData/variations/SysEqualNom.txt") as g:
        dontCopy = g.read().splitlines()
        dontCopy = [i for i in dontCopy if '#' not in i]


    for sys in sysList:
        sysName = sys['name']
        sysChannel = c + "_" + sysName
        if sysChannel in dontCopy:
            continue
        else:
            sysFolder = f.copy(sysChannel)
        if not sysFolder:
            QFramework.BREAK("unable to copy folder {:s} to new name {:s}".format(f.GetName(),sysName))
        sf.addFolder(sysFolder)
        sysFolder.setTagString(".mcasv.channel", sysChannel)
        mcasvchannels.add(sysChannel)

        # set the appropriate tags
        sysFolder.setTagString("variation", sysName)
        
        sysType = sys['type']
        
        if sysType == 'p4':
            treeName = sysName

            # treeName is sysName except for MET_SoftTrk_Scale
#            if sysName == "MET_SoftTrk_Scale_1up":
#                treeName = "MET_SoftTrk_ScaleUp"
 #           elif sysName == "MET_SoftTrk_Scale_1down":
  #              treeName = "MET_SoftTrk_ScaleDown"

            for sample in sysFolder.getListOfSamples():
                if sample.hasTag(".init.treename"):
                    sample.setTagString(".init.treename", treeName)
                
                # skip super-samples without a file/tree itself
                if sample.hasSubSamples(): 
                    continue
                
                origTreeFilename = sample.getFilename()
                if origTreeFilename:
                    sample.setTreeLocation(origTreeFilename + ":" + treeName)
        elif sysType != 'weight':
            QFramework.BREAK("Unknown systematic type {:s} for {:s}".format(sysType, sysName))

    return



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
        sysList = parseSystematicList(config) 

        # will contain nominal channels even if doNominal = False
        mcasvchannels = set([ c for c in channels ]) 
    
        for c in channels:
            for sf in subfolders:
                f = sf.getSampleFolder(c)
                
                if not f:
                    QFramework.WARN("unable to retrieve sample folder '{:s}' from '{:s}'. Is this expected from your path restriction?".format(c,sf.GetName()))
                    sf.printContents()
                    continue
                
                # set some noiminal flags for data sample
                if sf.getTagBoolDefault("isData",False):
                    f.setTagString(".mcasv.channel",f.getTagStringDefault("channel",""))
                    continue
                
                # we're in a MC SampleFolder
                f.setTagString("variation", "NOMINAL")
                
                # create additional channels for systematic variations
                addSystematicVariations(c, sf, sysList, mcasvchannels)
                
                # if no nominal analysis was requested, we can remove the nominal channels
                if not doNominal:
                  f.detachFromBase()
                else:
                  f.setTagString(".mcasv.channel",f.GetName())

    # possibly print how the folder looks like now
    if config.getTagBoolDefault("showChannels",False):
        QFramework.INFO("after taking care of channel and systematics setup, your sample folder looks like this:")
        samples.printContents("r2dt")
 
    # save the whole collection of channels (including now systematics)
    # for access later when creating the MCASV
    runtime = config.getFolder("runtime+")
    for i, channel in enumerate(mcasvchannels):
        if "ROOT" in str(type(channel)):
            QFramework.WARN("Please make sure that every mcasvchannel is only booked once. The python set doesn't help when adding c++ ROOT instances (" + str(type(channel)) + ".")
        runtime.setTagString("mcasvchannels."+str(i), channel)
  
    return
