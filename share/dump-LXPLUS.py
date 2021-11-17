#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
import os, sys, commands

def WriteCondorScripts(version,coupling):

  StoreString = version + "_l" + coupling 

  ex_script = open('condor_submission_{}.sh'.format(StoreString), 'w')
  ex_lines = []

  sh_script = open('/afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sh', 'w')
  if sh_script: print(' Created sh script /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sh')
  sub_script = open('/afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sub', 'w')
  if sub_script: print(' Created sub script /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sub')
  ex_lines.append('\ncondor_submit /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sub')
  textlines = ['#!/bin/bash',
               '\nexport ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase',
               '\nsource $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh',
               '\ncd /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/build',
               '\nasetup --restore',
               '\nsource /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/build/setupAnalysis.sh',
               '\ncd /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share',
               '\nsource /cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.122/InstallArea/x86_64-centos7-gcc8-opt/env_setup.sh',
               '\nsource /cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.122/InstallArea/x86_64-centos7-gcc8-opt/env_setup.sh',
               '\nsource /cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.122/InstallArea/x86_64-centos7-gcc8-opt/setup.sh',
               '\nsource /cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.122/InstallArea/x86_64-centos7-gcc8-opt/setup.sh',
               '\nsource /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/build/setupAnalysis.sh',
               '\ncd /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share',
               '\npython /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/LQtaub-lephad/config/SYS/scriptDumpHist.py {} {}'.format(version,coupling),
              ]
  
  sublines = ['\n',
              '\nexecutable = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+StoreString+'.sh',
              '\narguments = $(ClusterId) $(ProcId)',
              '\noutput = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/condor_logs/output/'+StoreString+'.$(ClusterId).$(ProcId).out',
              '\nerror = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/condor_logs/error/'+StoreString+'.$(ClusterId).$(ProcId).err',
              '\nlog = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/condor_logs/log/'+StoreString+'.$(ClusterId).log',
              '\ngetenv = True',
              '\n+JobFlavour = \"tomorrow\"',
              '\nRequestCpus = 4'
              '\nqueue'
             ]
  sh_script.writelines(textlines)
  sub_script.writelines(sublines)
  sh_script.close()
  sub_script.close()
  
  ex_script.writelines(ex_lines)
  ex_script.close()

  return

import sys

if __name__ == '__main__':

  WriteCondorScripts(sys.argv[1],sys.argv[2])



