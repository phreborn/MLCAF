#!/bin/bash
# this is an auto-generated setup script

export HWWEXECUTABLES="/Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/share"
# Add paths from $HWWEXECUTABLES to $PATH (while avoiding duplicates)
for directory in `echo $HWWEXECUTABLES | tr ":" " "` ; do
	# Remove trailing slash
	dir=${directory%/}
	# If $dir is not in $PATH yet, add it at the end.
	if ! `echo $PATH | tr ":" "\n" | grep -q $dir` ; then
		export PATH=$PATH:$dir
	fi
done

#if [ -f /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/setupAutoComplete.sh ]; then
#	source /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/setupAutoComplete.sh
#fi
if [ -f /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/setOutput.sh ]; then 
	source /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/setOutput.sh
else
	export HWWOUTPUTDIRECTORY="/Users/konstantin/SFU/Research/HWW/CAFExample/output/"
fi
if [ -f /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/CAFCore/cafsetup.sh ]; then 
	source /Users/konstantin/SFU/Research/HWW/CAFExample/CAFExample/CAFCore/cafsetup.sh
fi
