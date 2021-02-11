#########################################################################
# File Name: rename.sh
# Description: 
# Author: xzh
# mail: huangxz@ihep.ac.cn
# Created Time: Mon Feb  1 14:46:12 2021
#########################################################################
#!/bin/bash

OLD="OtherJetsTCR-SF"
NEW="OtherJetsTCR-SF"

# Step 1: rename the name of the find
echo "The file containing the word \"${OLD}\" are listed below:"
find ./ -name "*${OLD}*"

#echo "${OLD} will be replaced by ${NEW}."
#read -n1 -p "Do you want to continue ? [Y/N]"
#case $REPLY in
#    Y | y)
#        echo "fine ,continue on ..";;
#    N | n)
#        echo "OK, goodbye..."
#        exit 0;;
#esac

for file in `find ./ -name "*${OLD}*"`
do
    new_name=${file/${OLD}/${NEW}}
    mv ${file} ${new_name}
done
