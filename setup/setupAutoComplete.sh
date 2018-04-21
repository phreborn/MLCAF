#!/bin/bash

# Names of python scripts that need config files. Auto-complete
# will only work for these scripts and only if they are in the
# $ANALYSISEXECUTABLES directory.
pythonScripts="prepare.py initialize.py analyze.py visualize.py"

# This function gets executed if tab-complete is requested for the
# python scripts listed above. It adds files from $HWWCONFIGDIRECTORY
# ending in ".cfg" to the auto-complete suggestions.
_hww_config_files(){

    command=$1
    thisWord=$2
    previousWord=$3


    # Check if $command is known
    
    pathToCommand=$(which $command 2>/dev/null)
    # resolve leading "~/" and symbolic links
    pathToCommand="${pathToCommand/#\~/$HOME}"
    if [ ! -x "$pathToCommand" ] ; then
	# $command does not point to an executable, exit script
	return 0
    fi


    # Check if $command is in $CAFANALYSISSHARE. If not, exit the script.
    CAFAnalysisShare=""
    commandInExecutables=0
    # Loop over all directories in $CAFANALYSISSHARE
    for directory in `echo $CAFANALYSISSHARE | tr ":" " "`; do
	# resolve leading "~/" and symbolic links
	dir="${directory/#\~/$HOME}"
	if [[ $dir != *"/" ]] ; then
	    dir=$dir/
	fi
	if [[ $CAFAnalysisShare != "" ]] ; then
	    CAFAnalysisShare+=" "
	fi
	CAFAnalysisShare+="$dir"
	# The following two if statements are a messed up way of
	# Checking that $command points to a script in $dir.

	# Check if $command is in $dir or one of its subdirectories.
	if [[ $pathToCommand == "$dir"* ]] ; then
	    trailingPath=${pathToCommand/$dir/}
	    slashes=${trailingPath//[^\/]}
	    # If number of slashes in trailing path is zero, $command
	    # must be in the same directory as $dir.
	    if [ ${#slashes} -eq 0 ] ; then
		# The executable is located in $CAFANALYSISSHARE
		commandInExecutables=1
	    fi
	fi
    done
    
    # Jump out of function, if executable is not in $CAFANALYSISSHARE
    if [ $commandInExecutables -eq 0 ] ; then
	return 0
    fi
    
    
    # Now, do the actual magic. Create a list of completions that are
    # going to be added to the standard suggestions.
    

    # Find the directory by cutting after the last "/"
    thisDir=""
    if [[ $thisWord == *"/"* ]] ; then
	thisDir=`echo $thisWord | rev | cut -d "/" -f2- | rev`
    fi

    # CAFAnalysisShare holds all paths separated by " "
    
    listOfFiles=""
    listOfDirs=""
    for path in $CAFAnalysisShare ; do
	
	thisPath="$path$thisDir"
	if [[ $thisDir != "" ]] ; then
	    thisPath+="/"
	fi
	listOfFiles_new="$(ls $thisPath 2>/dev/null |grep ".cfg$")"
	listOfDirs_new="$(ls -d $thisPath*/ 2>/dev/null)"
	for file in $listOfFiles_new  ; do
	    if [[ $listOfFiles != "" ]] ; then
		listOfFiles+=" "
	    fi
	    # cut off the absolute part of all suggestions and save in listOfFiles
	    listOfFiles+=${file/$thisPath/}
	done
	for dir in $listOfDirs_new  ; do
	    if [[ $listOfDirs != "" ]] ; then
		listOfDirs+=" "
	    fi
	    # cut off the absolute part of all suggestions and save in listOfFiles
	    listOfDirs+=${dir/$thisPath/}
	done

	# test if there is a subdirectory "config/master". if yes, write it into conlyCompletion. use it. otherwise, compile normal completions.
	onlyCompletion=""
	for dir in $listOfDirs ; do
	    if [[ $dir == *"config/" ]] ; then
		listOfDirsInConfig="$(ls -d $thisPath$dir*/)"
		for dirInConfig in $listOfDirsInConfig ; do
		    if [[ $dirInConfig == *"config/master/" ]] ; then
			onlyCompletion=$thisWord$dir"master"
		    fi
		done
	    fi
	done
	if [[ $onlyCompletion != "" ]] ; then	    
	    echo "complete to $onlyCompletion"
	fi
    done


    
    return 0

    if [[ $listOfDirs == "master/"* ]] ; then
	if [[ "$(ls -d ($thisDir)master/)" == *"config/"* ]] ; then
	    echo "make cool completion"
	    someVar=1
	fi
    fi
    if [ $someVar -eq 0 ] ; then
	echo "make not so cool completion"
    fi
    
    # # Compgen reduces the list to the words starting with $thisWord
    # COMPREPLY=( $(compgen -W "$listOfFiles" -- $thisWord) )
    
    return 0
}


# Add all $pythonScripts to the list of commands that need
# auto-complete. If any of them invokes auto-complete, the
# hww_config_files function gets called.

for script in $pythonScripts ; do
    complete -df -F _hww_config_files $script
done
