import subprocess
import commands
import time
import os

class LocalJobHandler:
  def __init__(self, cmd_log, NCORES):
    self.cmd_log = cmd_log
    self.NCORES = NCORES
    self.pids =[]
    self.log_files=[]

  def run(self):
    """ Summit jobs by subprocess """
    for cmd, log in self.cmd_log:
      if len(self.pids) > self.NCORES:
        self.wait_complete_one()
      pid, log_file = self.submit_local_job(cmd, log)
    
      self.pids.append(pid)
      self.log_files.append(log_file)

    self.wait_complete_all()
    for log_file in self.log_files:
      log_file.close()

  def submit_local_job(self,cmd, log):
    os.system("rm -f "+log)
    output_file=open(log, 'w')
    print 'Submit local job: {}'.format(cmd)
    pid = subprocess.Popen(['bash','-c',cmd], stderr=output_file, stdout = output_file)
    return pid, output_file

  def wait_complete_one(self):
    """Wait until completion of one of the launched jobs"""
    while True:
      for pid in self.pids:
        if pid.poll() is not None:
          print "Process", pid.pid, "has completed"
          self.pids.remove(pid)
          return
      print "Waiting completion of jobs..."
      time.sleep(60) # wait 15 seconds before retrying

  def wait_complete_all(self):
    """Wait until completion of all launched jobs"""
    while len(self.pids)>0:
      self.wait_complete_one()
    print "All jobs finished !"

if __name__ == '__main__':
  cmd_list = []
  log_list = []
  cmd_log = zip(cmd_list, log_list)

  NCORES=30
  """Submit jobs"""
  local_job_handler = LocalJobHandler(cmd_log, NCORES)
  local_job_handler.run()

