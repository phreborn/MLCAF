#!/usr/bin/env python
import argparse
import inspect
import sys

alias = "buildWorkspace"

def main(args):
  # print a welcome message
  print(QFramework.TQStringUtils.makeBoldWhite("starting statistical treatment of the analysis results"))
  configFiles = args.config
  configs = []
  for configFile in configFiles:
    configFile = configFile.strip()
    if len(configFile) < 1 : continue
    # load the config
    config = QFramework.TQFolder.newFolder("config");
    errorMessage = ROOT.TString();
    if not config.importFromTextFile(configFile, errorMessage):
        QFramework.ERROR("Failed to parse configuration file: " + errorMessage.Data())

    for change in args.change:
      config.importFromText(change)
    QFramework.INFO("Imported config file '{:s}'".format(configFile))
    configs.append( (config,configFile) )
  
  for config,configFile in configs:
    # create the statistics manager
    mgr = SFramework.TSStatisticsManager()

    QFramework.INFO("Starting Statistics Manager on '{:s}'".format(configFile))
    # run the statistics manager
    try:
      mgr.run(config)
    except Exception as ex:
      mgr.getModels().writeToFile("statistics.emergency.models.root")
      mgr.getWorkspaces().writeToFile("statistics.emergency.workspaces.root")
      mgr.getResults().writeToFile("statistics.emergency.results.root")
      extype,exsource,extext = QFramework.parseException(ex)
      QFramework.BREAK("Failed to run statistics manager for config, exception of type '{:s}' occurred: '{:s}'".format(extype,extext))
    QFramework.INFO("Done processing '{:s}'!".format(configFile))

if __name__ == "__main__":
  # parse the CLI arguments
  parser = argparse.ArgumentParser(description='Create a workspace for the HSG3 Run2 Analysis.')
  parser.add_argument('config', metavar='CONFIG', type=str, nargs="+",
            default="config/buildWorkspace.cfg",
            help='path to the analysis config file to be processed')
  parser.add_argument("--change", metavar='text', type=str, help='changes to apply to the input config file', nargs="*", default=[])
  args = parser.parse_args()
  sys.argv=[]

  import QFramework
  try:
    import SFramework
  except Exception as ex:
    QFramework.BREAK("Failed to load SFramework - are you sure it is included in your library?")
  import ROOT
  QFramework.TQLibrary.getQLibrary().setApplicationName(alias);
  ROOT.gROOT.SetBatch(True)

  #try:
  main(args)
  #except:
  #  QFramework.BREAK("unable to access statistics manager - SFramework available?")


  
  
