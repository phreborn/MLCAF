#!/usr/bin/env python
import os
import sys
import glob
import argparse
from JobHandler import LocalJobHandler

# The results of some jobs will not be changed for the systematics, these jobs will be copied from the following dir
s_nominal_dir='batchOutput/unmerged_TCR-FF-SYS-NOMINAL'

def copyJobs(sys):
    # different files to be copied
    l_files = []
    jobs_file = ''
    l_files.append('unmerged_*_data_X_c16?*.root')
    if sys=='MCFakes':
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif sys=='MultiJetsLFR':
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif sys=='Top_Reweight' or sys=='Top_Residual':
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif sys=='Theory_Zjets':
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif 'Theory_Top' in sys:
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif sys=='CP_jet_p4_common' or sys=='CP_lep_p4':
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
    elif sys=='CP_jet_p4_bkg':
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
      l_files.append('unmerged_*_sig_X_c16?_*.root')
    elif sys=='CP_jet_p4_sig':
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Diboson*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Top*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Z*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcReal_Wjets*.root')
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')
    elif sys=='CP_lep_weight' or sys=='CP_tau_weight' or sys=='CP_other_weight':
      l_files.append('unmerged_*_bkg_X_c16?_mcFakeCorrected*.root')
      l_files.append('unmerged_*_bkg_X_c16?_MultiJetsFake_*.root')

    # make output folder, the same as the submitAnalysis.py would create;
    os.system('mkdir -pv batchOutput/unmerged_TCR-FF-SYS-{:s}'.format(sys))
    # copy those files which should not be run over for this particular systematic;
    for files in l_files:
      l_file = glob.glob('{:s}/{:s}'.format(s_nominal_dir,files))
      for file in l_file:
        os.system('ln -sv ../../{:s} batchOutput/unmerged_TCR-FF-SYS-{:s}'.format(file,sys))


if __name__ == '__main__':
  # introduce argument parser
  parser = argparse.ArgumentParser(description='submit systematics script')
  #parser.add_argument('--stage', default='none',
  #                  help='select the stage: prepare, initialize, analyze, merge')
  parser.add_argument('--systype', default='none',
                    help='select which type of systematic to process')
  #parser.add_argument('--ncores', default=1, type=int,
  #                  help='number of cores to run')
  args = parser.parse_args()

  # now we add the systematic sublists we want to run over into the grand list
  # this is controlled by the arg parser, so I can run the show from an external submission script
  copyJobs(args.systype) 
