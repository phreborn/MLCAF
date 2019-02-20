[![pipeline status](https://gitlab.cern.ch/atlasHBSM/atlas-phys-higgs-mssm-htautau-btag/BSMtautauCAF/badges/master/pipeline.svg)](https://gitlab.cern.ch/atlasHBSM/atlas-phys-higgs-mssm-htautau-btag/BSMtautauCAF/commits/master)

BSMtautau CAFCore Analysis
=========================

This repository is meant to construct an analysis for the BSMtautau LepHad channel using the [CAFCore](https://gitlab.cern.ch/atlas-caf/CAFCore) framework.

Cloning the project
--------------------

```bash
setupATLAS
lsetup git
mkdir BSMtautauCAF
cd BSMtautauCAF

# There are a few different protocol options for cloning the project, which are all provided at the top of the main page of the repository.
# Kerberos is typically recommended if it is available (e.g. lxplus) since it does not require a username or password when interacting with remote repositories.
# ssh acts similarly, but requires a password and a bit of initial setup
# https is usually the most robust, but always requres a username and password

# Kerberos
git clone --recursive https://:@gitlab.cern.ch:8443/${USER}/BSMtautauCAF.git
# ssh
#git clone --recursive ssh://git@gitlab.cern.ch:7999/${USER}/BSMtautauCAF.git
# https
#git clone --recursive https://gitlab.cern.ch/${USER}/BSMtautauCAF.git
```

Building the project
---------------------

```bash
mkdir build run
cd build
asetup AnalysisBase,21.2.34
cmake ../BSMtautauCAF
source ../BSMtautauCAF/setup/setupAnalysis.sh
make -j4
```

On Every Login
--------------

Navigate to the working directory and

```bash
setupATLAS
lsetup git
cd build
asetup --restore
source ../BSMtautauCAF/setup/setupAnalysis.sh
```

Running the analysis
--------------------

INFO:
    -   Top-level scripts to run the analysis.
        Follow what they do to discover all the relevant scripts and config files.

    FLCR:
    #to makeSampleFile, first update the 'dataPaths' and 'mcPaths' relavant for your setup (don't let them be too long or you will see errors) and do
    $ sh ConfigFakeLeptonRegion/scriptMakeSampleFile.sh
    #to run the event loop, first update the '--submit' for your relavant batch submission system, and do
    $ sh ConfigFakeLeptonRegion/scriptSubmit.sh
    #after all jobs finished, merge
    $ tqmerge -o output/htautau_lephad_flr/nominal.root -t runAnalysis -Sum output/unmerged_FLR/*.root
    #to make plots do
    $ python readAnalysis.py ConfigFakeLeptonRegion/htautau_lephad_flr_mc16a.cfg
    $ python readAnalysis.py ConfigFakeLeptonRegion/htautau_lephad_flr_mc16c.cfg
    #to make lepton fake factors do
    $ python scripts/calculateFakeFactor.py FLCR

    WCR:
    #to makeSampleFile do
    $ sh ConfigWjetsControlRegion/scriptMakeSampleFile.sh
    #to run the event loop do
    $ sh ConfigWjetsControlRegion/scriptSubmit.sh
    #after all jobs finished, merge
    $ tqmerge -o output/htautau_lephad_wcr/nominal.root -t runAnalysis -Sum output/unmerged_WCR/*.root
    #to make plots do
    $ python readAnalysis.py ConfigWjetsControlRegion/htautau_lephad_wcr_mc16a.cfg
    $ python readAnalysis.py ConfigWjetsControlRegion/htautau_lephad_wcr_mc16c.cfg
    #to make tau fake factors do
    $ python scripts/calculateFakeFactor.py WCR

    SR, VR, TCR, WCR, SSWCR, these regions go into one input/output file because they all use both lepton and tau FFs,
    and therefore have similar strucuture:

    #to makeSampleFile do
    $ sh ConfigSignalRegion/scriptMakeSampleFile.sh
    #to run the event loop do
    $ sh ConfigSignalRegion/scriptSubmit.sh
    #after all jobs finished, merge
    $ tqmerge -o output/htautau_lephad_sr/nominal_full.root -t runAnalysis -Sum output/unmerged_SignalRegionNominalR21/*
    #to make plots run this script, which makes plots for all regions
    $ sh ConfigSignalRegion/scriptReadAnalysis.sh


    ### NOT REVISED FOR R21
    # to run systematics do
    python submit_systematics.py
    # to make a systematics root file for plotting do
    python temp_systematics_code.py


TODO: 2015-16-17 fake factors:
    - update isoReweight.cxx and ptReweight.cxx to use appropriate year fake factors;
    - I only checked W+jets ffs and it looks that all years can be merged;
    - Need to check lepton ffs;


TODO: merging mc16a and mc16c samples:
    - easiest is to run makeSampleFile.py twice for two MC projects and do tqmerge;
    - problem arise when merging /data folders; only the first input file will be used;
    - pseudo-solution do both makeSampleFile.py with full data, in that case full data from the first input file is used;
        -- problem when copying /data folder for data-driven fake background; full data copied for mc16a and mc16c samples,
                but only appropriate years are required;
        ---- proposed solution - figure out how to merge /data folders at the first step.



TODO: Decide how to calculate FF:
    - proposed function in the calculateFakeFactor.py script works well;
        -- calcJetFakeFactorFinal(identifier, dataPath, bkgPath, nominator, denominator, histogram, channel, region, uncertainty)
        ---- make cosmetic improvements for FF plots.


IMPORTANT: systematics are submited with different options via command line:
    - every systematic produce a separate output file;
        -- this is mainly due to the requirement of having separate input files for reading different systematic trees in the ntuples,
                so why not doing the same for all systematics;
    - When running runAnalysis.py with sys, tell it what to do with command line options, e.g.
        $ python runAnalysis.py ConfigSignalRegion/htautau-lephad-sr.cfg --options fakevar:FakeShape_WjetsSysDo outputFile:output/htautau_lephad_sr/FakeShape_WjetsSysDo_wjets.root
    - that way 1 syst = 1 job and 1 root file.



IMPORTANT: Top samples with dilepton filter contains more statistics because we use truth matching anyway.
        Be careful to use allhad/nonallhad top samples for QCD regions.



IMPORTANT: in processes style files can do, e.g. [Zee+Zll] to add folders, [Zee-Zll] to subtract folders, 50*Zee to scale.


####################
### WCR stuff:
####################

In WCR the sample folder structure is made that truth labels are separate and there are lephad, muhad and ehad channels which are
executed separately so in config file under runAnalysis.channel write which ones to run over. This takes more time but is more flexible
and requires less hardcoding in cuts and histos config files.

## for nominal plotting, cutflow, study use:
    # config:
    config/htautau_lephad_wcr.cfg

    because we want to plot all truth labels but they are not needed for ff calculation,
    so we save time and make things more clear.

## for ff measurement:
    # config:
    config/htautau_lephad_wcr_ff.cfg

    this is only to make Pt histos with proper binning and Pass and Fail cuts.

## for applying ff to wcr:
    # config:
    config/htautau_lephad_wcr_applyff.cfg

    atm this doesn't include QCD, but studies could be made to show that QCD changes nothing to ff,
    or at least not significantly.


