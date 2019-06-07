#########################################################################
# File Name: checkSysJobs.sh
# Description: 
# Author: xzh
# mail: huangxz@ihep.ac.cn
# Created Time: Wed 05 Jun 2019 08:53:41 PM CST
#########################################################################
#!/bin/bash

dirs=`ls -d batchOutput/unmerged_SRsys*`
for dir in $dirs
do
  echo $dir
  num=`ls $dir/*.root | wc -l`
  echo $num
done 
