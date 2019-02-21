#!/usr/bin/env python2
from QFramework import *
from ROOT import *
import submit_systematics as mysys

pair = ROOT.std.pair('TString','TString')
channel = 'muhad'
b_addFolders = False
b_doSys = True

def writeTemptxt(wjets, qcd):
  temp = open('temp.txt','w')
  temp.write('# -*- mode: tqfolder -*-\n')
  temp.write('$create(path="/QCDFakes",type="sf");\n')
  temp.write('@/QCDFakes {:s}  $import("{:s}/data/");   $import("{:s}/bkg/");  {:s} \n'.format('{',qcd,qcd,'}'))
  temp.write('$create(path="/WJETSFakes",type="sf");\n')
  temp.write('@/WJETSFakes {:s}  $import("{:s}/data/");  $import("{:s}/bkg/");  {:s}'.format('{',wjets,wjets,'}'))
  temp.close()

def addFolders(output, mc, wjets, qcd):
  if not b_addFolders:
    return
  writeTemptxt(wjets,qcd)
  samples = TQSampleFolder.loadLazySampleFolder(mc)
  samples.importFromTextFile('temp.txt')
  samples.writeToFile(output)
  return

def main():
  handler = TQSystematicsHandler ('systematics')
  dir = 'output/htautau_lephad_lfr/'
  #dir = 'output/htautau_lephad_vr/'
  # The name of the TQSampleFolder object within your files
  # Alternatively, you can just use ':*' to have the code grab the first instance of TQSampleFolder that it finds
  sfname = ':samples'
  nominal_file_path = dir + 'nominal_applyff.root' + sfname
  nominal_sf_path = '/bkg/{:s}'.format(channel)

  # we will have such files:
  # nominal_mc.root, nominal_wjets.root, nominal_qcd.root
  # <sfvar>_mc.root, <fakevar>_wjets.root, <fakevar>_qcd.root
  # we do it so that the code wouldn't have to loop over all samples that it actually don't need to.
  # now we have to copy some nominal folders to sys files to make correct sys prediction.
  # short function to do that:

  handler.setNominalFilePath(nominal_file_path)
  handler.setNominalSampleFolderPath(nominal_sf_path)

  if mysys.doQCDFakes:
    l_systematics = mysys.readSysFile(mysys.systfilenameQCDFakes)
    for qcdsys in l_systematics:
    # Add a systematic uncertainty to the handler
    # The first argument is a string that will be used as an identifier for this uncertainty;
    # it should not contain special characters or blanks, but is otherwise arbitrary.
    # The second and optional third arguments are std::pairs of the form (file path, sample folder path)
    # where the desired systematic variation(s) reside. The ordering of the 2nd and 3rd args is arbitrary.
      handler.addSystematic(qcdsys[1].replace('Do','').replace('Up',''),
      pair('{:s}{:s}_applyff.root'.format(dir,qcdsys[1]), nominal_sf_path),
      pair('{:s}{:s}_applyff.root'.format(dir,qcdsys[2]), nominal_sf_path)
      )




  # An empty string for either path means the handler will use the respective nominal path
  # There are also convenience methods for using the nominal file path or sfolder path
  ###handler.addSystematicFromSampleFolderPath(
  ###'EGReso',
  ###'bkg/[em_EG_RESOLUTION__1down+me_EG_RESOLUTION__1down]/',
  ###'bkg/[em_EG_RESOLUTION__1up+me_EG_RESOLUTION__1up]/'
  ###)
  ## equivalent to:
  #handler.addSystematic(
  # 'EGReso',
  # pair(nominal_file_path, 'bkg/[em_EG_RESOLUTION__1down+me_EG_RESOLUTION__1down]/'),
  # pair(nominal_file_path, 'bkg/[em_EG_RESOLUTION__1up+me_EG_RESOLUTION__1up]/')
  # )

  ###handler.addSystematic(
  ###'METSoftCaloReso',
  ###dir + 'samples-run2-METSoftCaloReso.root' + sfname
  ###)
  ## equivalent to:
  #handler.addSystematic(
  # 'METSoftCaloReso',
  # pair(dir + 'samples-run2-METSoftCaloReso.root' + sfname, nominal_sf_path)
  # )
  if not b_doSys:
    return
  # Add all the cut stages at which you want to extract the systematic uncertainties to the handler
  handler.addCut('CutBveto')
  handler.addCut('CutBtag')

  # Have the handler print the systematic uncertainties to the console to be sure that you did 'the right thing'
  handler.printSystematics()

  # Have the handler do it's magic
  # Depending on the size of your input files and the speed of your system, this step might take some time
  handler.collectSystematics()

  # Export the systematics to an instance of TQFolder and write the 'yellow-band' to file
  systematics = handler.exportSystematics()
  systematics.writeToFile(dir+channel+'_systematics.root',True,0)

  # Produce a table with the ranking of systematic uncertainties at some cut stage table
  # Table.printPlain() to write it as a LaTeX and a CSV file
  table = handler.getTable('CutBveto1p')
  table.writeLaTeX(dir+'/sys_table.tex')
  table.printPlain()

if __name__ == "__main__":
  TQLibrary.getQLibrary().setApplicationName("createSystematics");
  main();
