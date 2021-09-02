def create_cmd_log_list(input_files, campaigns, channels):
  cmd_list = []
  log_list = []

  for input_file in input_files:
    for campaign in campaigns:
      for channel in channels:
        cmd = 'python scripts/dumpHist.py {0} {1} {2}'.format(input_file, campaign, channel)
        cmd_list.append(cmd)
        syst_name = input_file.split('.')[0].split('-')[-1]
        
        log_dir = 'logs/dump_hist/{0}/{1}'.format(campaign, channel)
        if not os.path.isdir(log_dir):
          os.makedirs(log_dir)
        log = '{0}/{1}_{2}_{3}.log'.format(log_dir, campaign, channel, syst_name)
        log_list.append(log)

  return cmd_list, log_list
        

if __name__ == '__main__':

  import os
  from JobHandler import LocalJobHandler

  """Script to dump histograms"""

  # colours
  ENDC = '\033[0m'
  WARNING = '\033[93m'
  BWHITE = '\033[1;37m'

  # Get the usual campaigns and channels
  campaigns = ['c16ade']
  channels = ['ehad', 'muhad']
  variations = ['NOMINAL', 'OtherJetsTFR_Reweight', 'OtherJetsTFR', 'MultijetsLFR', 'MultijetsLFR_Reweight', 'CP_jet_p4', 'CP_lep_p4', 'CP_lep_weight', 'CP_tau_weight', 'CP_other_weight', 'Theory_Top', 'Theory_Zjets', 'Top_Reweight', 'Extrapolation']  
  # Get the input files
  directory = 'sampleFolders/analyzed/'

  files = [i for i in os.listdir(directory) if os.path.isfile(os.path.join(directory,i)) and i.startswith('samples-analyzed-AHZ-lephad-SR-FF')]
  files = [directory+i for i in files if i.split('.')[0].split('-')[-1] in variations]

  print(BWHITE + 'The following files histograms will be dumped:\n\n' + "\n".join(files) + ENDC)
  print("\n")

  cmd_list, log_list = create_cmd_log_list(files, campaigns, channels)  
  cmd_log = zip(cmd_list, log_list)
  NCORES = 8
  
  if NCORES == 1:
    for cmd in cmd_list:
      os.system(cmd)
  else:
    local_job_handler = LocalJobHandler(cmd_log, NCORES)
    local_job_handler.run()

  print(BWHITE + 'Jobs Finished check logs and use merging script' + ENDC)

