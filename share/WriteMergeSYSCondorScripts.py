#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
import os, sys, commands
import argparse



def WriteCondorScripts(sys,region):

  sh_script = open('/afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sh', 'w')
  if sh_script: print(' Created sh script /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sh')
  sub_script = open('/afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sub', 'w')
  if sub_script: print(' Created sub script /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sub')
  ex_line = '\ncondor_submit /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sub'
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
              ]

  exlines = []
  exlines.append('\nsource /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/LQtaub-lephad/config/{}/analyze-merge-FF.sh {}'.format(region,sys))
  textlines = textlines + exlines
  
  sublines = ['\n',
              '\nexecutable = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/mergeWorkloadTemp/RunCondor_'+region+'_'+sys+'.sh',
              '\narguments = $(ClusterId) $(ProcId)',
              '\noutput = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/logs/output/'+region+'_'+sys+'.$(ClusterId).$(ProcId).out',
              '\nerror = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/logs/error/'+region+'_'+sys+'.$(ClusterId).$(ProcId).err',
              '\nlog = /afs/cern.ch/work/h/hye/Leptoquark/AnalysisFramework/BSMtautauCAF/share/logs/log/'+region+'_'+sys+'.$(ClusterId).log',
              '\ngetenv = True',
              '\n+JobFlavour = \"tomorrow\"',
              '\nRequestCpus = 4'
              '\nqueue'
             ]
  sh_script.writelines(textlines)
  sub_script.writelines(sublines)
  sh_script.close()
  sub_script.close()
  
  return ex_line

if __name__ == '__main__':

  parser = argparse.ArgumentParser()
  parser.add_argument('-r', '--region',     help='Region', type=str, default='SR')
  args = parser.parse_args()

  region = ''
  if args.region == 'SR':
    region = 'SYS'
  elif args.region == 'TCR':
    region = 'TCR-SYS'
  elif args.region == 'OtherJetsTFR':
    region = 'OtherJetsTFR-SYS'
  elif args.region == 'OtherJetsSSR':
    region = 'OtherJetsSSR-SYS'

  if not os.path.exists('mergeWorkloadTemp'): 
    os.system('mkdir -pv ./mergeWorkloadTemp')

  
  ex_script = open('./condor_submission_{}.sh'.format(region), 'w')
  ex_lines = []

  sys_path = './LQtaub-lephad/config/{:s}/master'.format(region)
  _, fn_list = commands.getstatusoutput('ls '+sys_path+'/analyze-systematics-*.cfg')
  for fn in fn_list.split():
    sys = fn.split('.cfg')[0].split('-')[-1]
    #if sys == 'Theory_Top' or sys == 'base' or sys == 'Top_Residual': continue
    if sys == 'Theory_Top' or sys == 'base': continue
    print(sys)

    ex_lines.append(WriteCondorScripts(sys,region))

  ex_script.writelines(ex_lines)
  ex_script.close()

