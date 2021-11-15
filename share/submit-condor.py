##################################################
### quick solution for hep_sub in BSMtautauCAF ###
##################################################
import os,sys
import logging as log
import logging.config

def main():
  print "Submitting jobs by hep_sub"

  path = "/afs/cern.ch/work/h/hye/Leptoquark/CAF/BSMtautauCAF/share/submissionWorkloadTemp"
  path_log = "/afs/cern.ch/work/h/hye/Leptoquark/CAF/BSMtautauCAF/share/condor_log/log"
  path_error = "/afs/cern.ch/work/h/hye/Leptoquark/CAF/BSMtautauCAF/share/condor_log/error"
  path_output = "/afs/cern.ch/work/h/hye/Leptoquark/CAF/BSMtautauCAF/share/condor_log/output"


  #print "Cleaning the folder"
  #os.system("rm submissionWorkloadTemp/*.err.*")
  #os.system("rm submissionWorkloadTemp/*.out.*")
  os.system("rm submissionWorkloadTemp/*.sub*")
  #os.system("rm submissionWorkloadTemp/*.log*")

  print "Changing the job script permission"
  os.system("chmod +x submissionWorkloadTemp/*.sh")

  os.system("ls submissionWorkloadTemp/ > ./jobslist.txt")

  f=open("./jobslist.txt")
  jobNum = 0
  for submitfile in f:
    #if "_wrapper" not in submitfile:
    if "_wrapper" in submitfile:
      print "Submitting "+submitfile
      jobname = 'Job'+str(jobNum)
      sub_script = open(path+'/RunCondor_'+jobname+'.sub', 'w')
      if sub_script: log.info(path+'/RunCondor_'+jobname+'.sub')
      sublines = ['\n',
                  '\nexecutable = '+path+'/'+submitfile,
                  '\narguments = $(ClusterId) $(ProcId)',
                  '\noutput = '+path_output+'/'+jobname+'.$(ClusterId).$(ProcId).out',
                  '\nerror = '+path_error+'/'+jobname+'.$(ClusterId).$(ProcId).err',
                  '\nlog = '+path_log+'/'+jobname+'.$(ClusterId).log',
                  '\ngetenv = True',
                  '\n+JobFlavour = \"tomorrow\"',
                  '\nqueue'
                 ]
      sub_script.writelines(sublines)
      sub_script.close()

      command = "condor_submit submissionWorkloadTemp/RunCondor_"+jobname+".sub"
      os.system(command)
      jobNum += 1

  print "%d jobs have been submitted." % jobNum

  f.close()



if __name__ == "__main__":
  main()
