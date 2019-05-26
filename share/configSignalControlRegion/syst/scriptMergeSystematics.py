import subprocess
import commands
import time
import os
from JobHandler import LocalJobHandler


def create_cmd_log_list(systs):
  cmd_list=[]
  log_list=[]

  for syst in systs:
    cmd='tqmerge -o sampleFolders/analyzed/samples-analyzed-htautau_lephad_sr-{:s}.root -t analyze batchOutput/unmerged_SRsys_{:s}/*.root'.format(syst,syst)
    cmd_list.append(cmd)
        
    log_dir='logs/merge_syst'
    if not os.path.isdir(log_dir):
      os.makedirs(log_dir)
    log='{}/merge_syst_{}.log'.format(log_dir,syst)
    log_list.append(log)
  return cmd_list, log_list


if __name__ == '__main__':
  """ Merge the systematics """
  systs = [
#            'FakeFactor_WjetsBtag1p_1up',
#            'FakeFactor_WjetsBtag1p_1down',
#            'FakeFactor_WjetsBtag3p_1up',
#            'FakeFactor_WjetsBtag3p_1down',
#            'FakeFactor_WjetsBveto1p_1up',
#            'FakeFactor_WjetsBveto1p_1down',
#            'FakeFactor_WjetsBveto3p_1up',
#            'FakeFactor_WjetsBveto3p_1down',

            'FakeFactor_LepElBveto_1up',
            'FakeFactor_LepElBveto_1down',
            'FakeFactor_LepElBtag_1up',
            'FakeFactor_LepElBtag_1down',
            'FakeFactor_LepMuBveto_1up',
            'FakeFactor_LepMuBveto_1down',
            'FakeFactor_LepMuBtag_1up',
            'FakeFactor_LepMuBtag_1down',

#            "ExtrapolationSFs_Bveto1p_1down",
#            "ExtrapolationSFs_Bveto1p_1up",
#            "ExtrapolationSFs_Bveto3p_1down",
#            "ExtrapolationSFs_Bveto3p_1up",
          ]

  NCORES=30

  cmd_list, log_list = create_cmd_log_list(systs)
  cmd_log = zip(cmd_list, log_list)

  local_job_handler = LocalJobHandler(cmd_log, NCORES)
  local_job_handler.run()
