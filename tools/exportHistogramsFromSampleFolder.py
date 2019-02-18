#!/bin/env python

def main(args):
  import QFramework
  import ROOT
  samples = QFramework.TQSampleFolder.loadSampleFolder(args.inputFile)
  if not samples:
    raise RuntimeError("unable to open input sample folder "+args.inputFile)
  for patch in args.patches:
    samples.importFromTextFile(patch)
  reader = QFramework.TQSampleDataReader(samples)

  tags = QFramework.TQTaggable()
  for tag in args.tags:
    tags.importTag(tag)

  outfile = ROOT.TFile.Open(args.outputFile,"RECREATE")
  if not outfile or not outfile.IsOpen():
    raise RuntimeError("unable to open output file  "+args.outputFile)

  for path in args.paths:
    print("exporting "+path)
    name = path.replace("/","_").replace("*","X").replace("?","X")
    folder = reader.exportHistograms(path,tags)
    folder.SetName(name)
    outfile.Add(folder)

  outfile.Write()
  outfile.Close()





if __name__ == "__main__":
  # parse the CLI arguments
  from argparse import ArgumentParser
  parser = ArgumentParser(description='Export the histograms from a sample folder to a plain ROOT file')
  parser.add_argument('--input', '-i', metavar='samples.root:samples', type=str, help='name of the input sample folder', dest="inputFile",required=True)
  parser.add_argument('--output', '-o', metavar='systematics.root', type=str, help='name of the output file', dest="outputFile", required=True)
  parser.add_argument('--paths', nargs="+", metavar="/path/to/contribution", type=str, help='list of paths to be exported',required=True)
  parser.add_argument('--tags', nargs="+", metavar="key=value", type=str, help='list of tags to be passed along',required=False, default=[])
  parser.add_argument('--patches', nargs="+", metavar="patch.txt", type=str, help='list of patches to be loaded',required=False, default=[])
  import sys

  args = parser.parse_args()
  sys.argv = []
  from QFramework import TQLibrary
  TQLibrary.getQLibrary().setApplicationName("createSystematics")
  import ROOT
  ROOT.gROOT.SetBatch(True)
  main(args)
