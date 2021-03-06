def create_cmd_log_list(input_files, campaigns, channels, variations):
  cmd_list = []
  log_list = []

  for input_file in input_files:
    for campaign in campaigns:
      for channel in channels:
        variation_file = variations[input_file.split("/")[-1]]
        cmd = 'python scripts/dumpHist.py {0} {1} {2} {3}'.format(input_file, campaign, channel, variation_file)
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

  variations = {'samples-analyzed-AHZ-lephad-SR-FF-NOMINAL.root': None,
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-OtherJetsTFR_Reweight.root': 'AHZ-lephad/auxData/variations/systematics-Fake-OtherJets-Reweight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-OtherJetsTFR.root': 'AHZ-lephad/auxData/variations/systematics-Fake-OtherJets.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-MultijetsLFR.root': 'AHZ-lephad/auxData/variations/systematics-Fake-MJ.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-MultijetsLFR_Reweight.root': 'AHZ-lephad/auxData/variations/systematics-Fake-MJ-Reweight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-CP_jet_p4.root': 'AHZ-lephad/auxData/variations/systematics-CP-jet-p4.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-CP_lep_p4.root': 'AHZ-lephad/auxData/variations/systematics-CP-lep-p4.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-CP_lep_weight.root': 'AHZ-lephad/auxData/variations/systematics-CP-lep-weight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-CP_tau_weight.root': 'AHZ-lephad/auxData/variations/systematics-CP-tau-weight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-CP_other_weight.root': 'AHZ-lephad/auxData/variations/systematics-CP-other-weight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-Theory_Top.root': 'AHZ-lephad/auxData/variations/systematics-Theory-Top.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-Theory_Zjets.root': 'AHZ-lephad/auxData/variations/systematics-Theory-Zjets.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-Top_Reweight.root': 'AHZ-lephad/auxData/variations/systematics-Top-Reweight.txt',
                'samples-analyzed-AHZ-lephad-SR-FF-SYS-Extrapolation.root': 'AHZ-lephad/auxData/variations/systematics-Fake-Extrapolation.txt'}  

  # Get the input files
  
  directory = 'sampleFolders/analyzed/'
  files = [directory+i for i in os.listdir(directory) if i in variations.keys()]

  print(BWHITE + 'The following files histograms will be dumped:\n\n' + "\n".join(files) + ENDC)
  print("\n")

  cmd_list, log_list = create_cmd_log_list(files, campaigns, channels, variations)  
  cmd_log = zip(cmd_list, log_list)
  NCORES = 8
  
  if NCORES == 1:
    for cmd in cmd_list:
      os.system(cmd)
  else:
    local_job_handler = LocalJobHandler(cmd_log, NCORES)
    local_job_handler.run()

  print(BWHITE + 'Jobs Finished check logs and use merging script' + ENDC)

