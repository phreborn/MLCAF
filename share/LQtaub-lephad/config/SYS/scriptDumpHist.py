def create_cmd_log_list(input_files, campaigns, channels, variations):
  cmd_list = []
  log_list = []

  for input_file in input_files:
    for campaign in campaigns:
      for channel in channels:
        variation_file = variations[input_file.split("/")[-1]]
        cmd = 'python scripts/dumpHist_lq.py {0} {1} {2} {3} {4} {5}'.format(input_file, campaign, channel, variation_file, args.version, args.coupling)
        cmd_list.append(cmd)
        syst_name = input_file.split('.')[0].split('-')[-1]

        if channel == '[ehad+muhad]': 
          channel = 'lephad'
        
        log_dir = 'logs/dump_hist/{0}/{1}/{2}_l{3}'.format(campaign, channel, args.version, args.coupling)
        if not os.path.isdir(log_dir):
          os.makedirs(log_dir)
        log = '{0}/{1}_{2}_{3}_l{4}_{5}.log'.format(log_dir, campaign, channel, args.version, args.coupling, syst_name)
        log_list.append(log)

  return cmd_list, log_list
        

if __name__ == '__main__':

  import os
  import subprocess
  import argparse
  import commands
  from JobHandler import LocalJobHandler

  """Script to dump histograms"""

  parser = argparse.ArgumentParser(description='Dump histogram for statistical analysis.')
  parser.add_argument('version', metavar='VERSION', type=str,
            default="st300",
            help='version to be used')
  parser.add_argument('coupling', metavar='COUPLING', type=str,
            default="1_0",
            help='coupling to be used')
  args = parser.parse_args()


  # colours
  ENDC = '\033[0m'
  WARNING = '\033[93m'
  BWHITE = '\033[1;37m'

  # Get the usual campaigns and channels
  campaigns = ['c16ade']
  channels = ['ehad','muhad'] 
  #channels = ['[ehad+muhad]'] 

  variations = {
                #'samples-analyzed-LQtaub-lephad-TCR-PS-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-ME-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-FSRdo-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-FSRup-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-ISRdo-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-ISRup-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-SF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-TCR-SF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-MultiJetsLFR-FF-closure-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-OtherJetsTFR-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-PS-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-ME-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-ISRup-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-ISRdo-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-FSRup-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-FSRdo-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-FF-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-NOMINAL.root': None,
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-MultiJetsLFR.root': 'LQtaub-lephad/auxData/variations/systematics-Fake-MJ.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-MCFakes.root': 'LQtaub-lephad/auxData/variations/systematics-Fake-MC.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Top_Reweight.root': 'LQtaub-lephad/auxData/variations/systematics-Top-Reweight.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Top_Extrapolation.root': 'LQtaub-lephad/auxData/variations/systematics-Top-Extrapolation.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_jet_p4.root': 'LQtaub-lephad/auxData/variations/systematics-CP-jet-p4.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_lep_p4.root': 'LQtaub-lephad/auxData/variations/systematics-CP-lep-p4.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_lep_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-lep-weight.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_tau_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-tau-weight.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_other_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-other-weight.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top.txt',
                #'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Zjets.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Zjets.txt',
                }  

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

