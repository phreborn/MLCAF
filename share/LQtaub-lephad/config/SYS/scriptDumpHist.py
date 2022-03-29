def create_cmd_log_list(input_files, campaigns, channels, variations):
  cmd_list = []
  log_list = []

  for input_file in input_files:
    for campaign in campaigns:
      for channel in channels:
        variation_file = variations[input_file.split("/")[-1]]
        cmd = 'python scripts/dumpHist_lq.py {0} {1} {2} {3} {4} {5} {6}'.format(input_file, campaign, channel, variation_file, args.version, args.coupling, args.sample)
        cmd_list.append(cmd)
        syst_name = input_file.split('.')[0].split('-')[-1]

        if channel == '[ehad+muhad]': 
          channel = 'lephad'
        
        log_dir = 'logs/dump_hist/{0}/{1}/{2}_l{3}_{4}'.format(campaign, channel, args.version, args.coupling, args.sample)
        if not os.path.isdir(log_dir):
          os.makedirs(log_dir)
        log = '{0}/{1}_{2}_{3}_l{4}_{5}_{6}.log'.format(log_dir, campaign, channel, args.version, args.coupling, args.sample, syst_name)
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
  parser.add_argument('-v','--version', metavar='VERSION', type=str,
            default="st300",
            help='version to be used')
  parser.add_argument('-c','--coupling', metavar='COUPLING', type=str,
            default="1_0",
            help='coupling to be used')
  parser.add_argument('-s','--sample', metavar='SAMPLES', type=str,
            default="sig",
            help='signals or backgrounds')
  args = parser.parse_args()


  # colours
  ENDC = '\033[0m'
  WARNING = '\033[93m'
  BWHITE = '\033[1;37m'

  # Get the usual campaigns and channels
  campaigns = ['c16ade']
  channels = ['[ehad+muhad]'] 

  variations = {
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-NOMINAL.root': None,
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-MultiJetsLFR.root': 'LQtaub-lephad/auxData/variations/systematics-Fake-MJ.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-MCFakes.root': 'LQtaub-lephad/auxData/variations/systematics-Fake-MC.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Top_Reweight.root': 'LQtaub-lephad/auxData/variations/systematics-Top-Reweight.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Top_Residual.root': 'LQtaub-lephad/auxData/variations/systematics-Top-Residual.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_jet_p4_common.root': 'LQtaub-lephad/auxData/variations/systematics-CP-jet-p4-common.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_jet_p4_bkg.root': 'LQtaub-lephad/auxData/variations/systematics-CP-jet-p4-bkg.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_jet_p4_sig.root': 'LQtaub-lephad/auxData/variations/systematics-CP-jet-p4-sig.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_lep_p4.root': 'LQtaub-lephad/auxData/variations/systematics-CP-lep-p4.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_lep_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-lep-weight.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_tau_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-tau-weight.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-CP_other_weight.root': 'LQtaub-lephad/auxData/variations/systematics-CP-other-weight.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_PS.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-PS.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_ME.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-ME.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_ISRup.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-ISRup.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_ISRdo.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-ISRdo.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_FSRup.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-FSRup.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_FSRdo.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-FSRdo.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopPS.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopPS.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopME.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopME.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopISRup.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopISRup.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopISRdo.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopISRdo.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopFSRup.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopFSRup.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopFSRdo.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopFSRdo.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Top_STopWTInt.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Top-STopWTInt.txt',
                'samples-analyzed-LQtaub-lephad-SR-FF-SYS-Theory_Zjets.root': 'LQtaub-lephad/auxData/variations/systematics-Theory-Zjets.txt',
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

