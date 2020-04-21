##################################################
### quick solution for hep_sub in BSMtautauCAF ###
##################################################
import os,sys


def main():
  print "Submitting jobs by hep_sub"

  #print "Cleaning the folder"
  os.system("rm submissionWorkloadTemp/*.err.*")
  os.system("rm submissionWorkloadTemp/*.out.*")

  print "Changing the job script permission"
  os.system("chmod +x submissionWorkloadTemp/*.sh")

  os.system("ls submissionWorkloadTemp/ > ./jobslist.txt")

  f=open("./jobslist.txt")
  jobNum = 0
  for submitfile in f:
    if "_wrapper" in submitfile:
      print "Submitting "+submitfile
      #command = "hep_sub -e submissionWorkloadTemp/ -o submissionWorkloadTemp/ -g atlas submissionWorkloadTemp/"+submitfile
      command = "hep_sub -os SL7 -e submissionWorkloadTemp/ -o submissionWorkloadTemp/ -g atlas submissionWorkloadTemp/"+submitfile
      os.system(command)
      jobNum += 1

  print "%d jobs have been submitted." % jobNum

  f.close()



if __name__ == "__main__":
  main()
