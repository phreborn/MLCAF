import subprocess
import commands
import time
import os
from JobHandler import LocalJobHandler


def create_cmd_log_list(input_files, campaigns, channels):
  cmd_list=[]
  log_list=[]

  for input_file in input_files.split():
    for campaign in campaigns:
      for channel in channels:
        cmd='python scripts/dumpHist.py {} {} {}'.format(input_file, campaign, channel)
        cmd_list.append(cmd)
        syst=input_file.split('/')[2].split('-')[-1].split('.')[0]
        
        log_dir='logs/dump_hist/{0}/{1}'.format(campaign, channel)
        if not os.path.isdir(log_dir):
          os.makedirs(log_dir)
        log='{}/{}_{}_{}.log'.format(log_dir,campaign,channel,syst)
        log_list.append(log)
  return cmd_list, log_list


if __name__ == '__main__':
  """ Dump the Histograms """
  # make sure the NOMINAL exist
  sr_fn = './samples-analyzed-htautau_lephad_sr_applysf.root'
  sr_NOMINAL_fn = 'sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-NOMINAL.root'
  if not os.path.isfile(sr_NOMINAL_fn):
    os.symlink(sr_fn, sr_NOMINAL_fn)

  _ , input_files = commands.getstatusoutput('ls -1 sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-*.root | grep -v "sys_band"')
  campaigns=['c16ade']
  channels=['ehad', 'muhad']
  NCORES=20

  cmd_list, log_list = create_cmd_log_list(input_files, campaigns, channels)
  cmd_log = zip(cmd_list, log_list)

  if 1 == NCORES:
    for cmd in cmd_list:
      os.system(cmd)
  else:
    local_job_handler = LocalJobHandler(cmd_log, NCORES)
    local_job_handler.run()
 
  regions=[]
  regions.extend(['sr1pBveto','sr3pBveto','sr1pBtag','sr3pBtag'])
  regions.extend(['tcr1pBtag','tcr3pBtag'])
  regions.extend(['vr1pBveto','vr3pBveto','vr1pBtag','vr3pBtag'])
  """ Merge the Histograms """
  for campaign in campaigns:
    for region in regions:
      cmd='hadd -f -j {2} dumpHist/{0}_{1}.root dumpHist/*/{0}/*/{0}*{1}*.root'.format(campaign, region, NCORES)    
      os.system(cmd)
