#########################################################################
# File Name: checkJobs.py
# Description: 
# Author: xzh
# mail: huangxz@ihep.ac.cn
# Created Time: Tue 25 Jun 2019 12:41:00 AM CST
#########################################################################
#!/usr/bin/env python
import commands
import os

def checkJobs(task_dir):
  _, file_list = commands.getstatusoutput("ls {0}/*.root".format(task_dir))
  n_success = 0
  n_fail = 0
  avg_size = 0
  
  goodfile_list = []
  for afile in file_list.split():
    if os.path.getsize(afile) == 0:
      print afile, " has zero size" 
      os.system("rm -f {0}".format(afile))
      n_fail = 0
    goodfile_list.append(afile)
    avg_size = avg_size + os.path.getsize(afile)
    n_success = n_success + 1

#  avg_size = avg_size/n_success
#
#  for afile in goodfile_list:
#    size = os.path.getsize(afile)
#    if size < avg_size*0.1:
#      print "Size of {0} is {1} (avg: {2})".format(afile, size, avg_size)

  print "{0} has {1} files".format(task_dir, n_success)

if __name__ == '__main__':
  task_pattern = "batchOutput/unmerged_**"
  _, task_list = commands.getstatusoutput("ls -d {0}".format(task_pattern)) 

  for task_dir in task_list.split():
    checkJobs(task_dir)
