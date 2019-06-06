import subprocess
import commands
import time
import os

class LocalJobHandler:
  def __init__(self, cmd_log, NCORES):
    self.NCORES = NCORES
    self.cmd_log = cmd_log
    self.pid_logfile = {}

  def run(self):
    """ Summit jobs by subprocess """
    for cmd, log in self.cmd_log:
      if len(self.pid_logfile) > self.NCORES:
        self.wait_complete_one()
      pid, logfile = self.submit_local_job(cmd, log)
      self.pid_logfile[pid] = logfile 

    self.wait_complete_all()

  def submit_local_job(self,cmd, log):
    os.system("rm -f "+log)
    output_file=open(log, 'w')
    print 'Submit local job: {}'.format(cmd)
    pid = subprocess.Popen(['bash','-c',cmd], stderr=output_file, stdout = output_file)
    return pid, output_file

  def wait_complete_one(self):
    """Wait until completion of one of the launched jobs"""
    while True:
      for pid, logfile in self.pid_logfile.items():
        if pid.poll() is not None:
          print "Process", pid.pid, "has completed"  
          logfile.close()
          del self.pid_logfile[pid]
          return
      print "Waiting completion of jobs..."
      time.sleep(60) # wait 15 seconds before retrying

  def wait_complete_all(self):
    """Wait until completion of all launched jobs"""
    while len(self.pid_logfile)>0:
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

