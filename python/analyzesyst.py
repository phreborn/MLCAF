def prepareSystematicsExample(config, samples):
    """prepare the systematic handling for your analysis"""
    QFramework.WARN("this is just an example implementation of the systematics handling")
    QFramework.WARN("you will need to tailor the systematics handling to fit the needs of your analysis!")

    CLI = config.getFolder("CLI+")
    # flag indicating to run a robust analysis
    robust = CLI.getTagBoolDefault("robust",False)
    # flag indicating to run a dummy analysis
    dummy = CLI.getTagBoolDefault("dummy",False)

    if not robust and not dummy:
        subfolders = samples.getListOfSampleFolders("?")
        doNominal = config.getTagBoolDefault("xAODdoNominal",True)
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
                    f.setTagString("weightname","nominal")
                    f.setTagString("p4suffix","")
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
                for p4syst in config.getTagVStandardString("xAODp4Systematics"):
                    # for each p4 systematic, copy the channel folder
                    if not p4syst or len(p4syst)<1: continue
                    newname=c+"_"+p4syst
                    newf = f.copy(newname)
                    if not newf:
                        QFramework.BREAK("unable to copy folder {:s} to new name {:s}".format(f.GetName(),newname))
                    sf.addFolder(newf)
                    # set the appropriate tags
                    candname = f.getTagStringDefault("~cand","")
                    if not candname:
                        QFramework.BREAK("didn't find 'cand' tag on sample folder '{:s}'".format(f.getPath()))
                    newf.setTagString("p4Variation",p4syst)
                    newf.setTagString("weightname","nominal")
                    newf.setTagString("cand",candname+"___"+p4syst)
                    newf.setTagString("cand.original",candname)
                    newf.setTagString(".mcasv.channel",newname)
                    newf.setTagString("p4suffix",ROOT.TString("___")+p4syst)
                    newf.setTagString("sysVariation",p4syst)
                    mcasvchannels.add(newname.Data())
                for sfsyst in config.getTagVString("xAODsfSystematics"):
                    # for each sf systematic, copy the channel folder
                    if not sfsyst or len(sfsyst)<1: continue
                    newname = c+"_"+sfsyst
                    newf = f.copy(newname)
                    if not newf:
                        QFramework.BREAK("unable to copy folder {:s} to new name {:s}".format(f.GetName(),newname))
                    sf.addFolder(newf)
                    # set the appropriate tags
                    newf.setTagString("sfVariation",sfsyst)
                    newf.setTagString("weightname",sfsyst)
                    newf.setTagString(".mcasv.channel",newname)
                    newf.setTagString("p4suffix","")
                    newf.setTagString("sysVariation",sfsyst)
                    mcasvchannels.add(newname.Data())

                # if no nominal analysis was requested, we can remove the nominal channels
                if not doNominal:
                    f.detachFromBase()
                else:
                    f.setTagString(".mcasv.channel",f.GetName())

    # Add some nominal top level tags, even if systematics aren't being added
    samples.setTagString("weightname","nominal")
    samples.setTagString("sfVariation","nominal")
    samples.setTagString("p4Variation","nominal")
    samples.setTagString("p4suffix","")
    samples.setTagString("sysVariation","nominal")

    # possibly print how the folder looks like now
    if config.getTagBoolDefault("showChannels",False):
        QFramework.INFO("after taking care of channel and systematics setup, your sample folder looks like this:")
        samples.printContents("r2dt")

    # save the whole collection of channels (including now systematics)
    # for access later when creating the MCASV
    runtime = config.getFolder("runtime+")
    for i, channel in enumerate(mcasvchannels):
        if "ROOT" in str(type(channel)):
            from QFramework import WARN
            QFramework.WARN("Please make sure that every mcasvchannel is only booked once. The python set doesn't help when adding c++ ROOT instances (" + str(type(channel)) + ".")
        runtime.setTagString("mcasvchannels."+str(i), channel)

    return
