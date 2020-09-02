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
  
  _ , input_files = commands.getstatusoutput('ls -1 sampleFolders/analyzed/samples-analyzed-bsmtautau_lephad_sr-jet*.root | grep -v "sys_band"')

  campaigns=['c16ade']
  channels=['ehad', 'muhad']
  NCORES=10

  cmd_list, log_list = create_cmd_log_list(input_files, campaigns, channels)
  cmd_log = zip(cmd_list, log_list)

  if 1 == NCORES:
    for cmd in cmd_list:
      os.system(cmd)
  else:
    local_job_handler = LocalJobHandler(cmd_log, NCORES)
    local_job_handler.run()
