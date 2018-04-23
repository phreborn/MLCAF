#!/bin/bash


# Names of python scripts that need config files. Auto-complete
# will only work for these scripts and only if they are in the
# $ANALYSISEXECUTABLES directory.
pythonScripts="prepare.py initialize.py analyze.py visualize.py"

# This function gets executed if tab-complete is requested for the
# python scripts listed above. It adds files from $HWWCONFIGDIRECTORY
# ending in ".cfg" to the auto-complete suggestions.
_analysis_config_files(){

    command=$1
    thisWord=$2
    previousWord=$3

    # Check if $command is known
    # If $command does not point to an executable, exit script
    
    pathToCommand=$(which $command 2>/dev/null)
    # resolve leading "~/" and symbolic links
    pathToCommand="${pathToCommand/#\~/$HOME}"
    if [ ! -x "$pathToCommand" ] ; then
	return 0
    fi

    # Set internal field separator (unset at the end)
    IFS=:
    
    # Check if $command is in $CAFANALYSISSHARE. If not, exit the script.

    CAFAnalysisShare="./"
    commandInExecutables=0
    for directory in $CAFANALYSISSHARE ; do
	# resolve leading "~/" and symbolic links
	dir="${directory/#\~/$HOME}"
	if [[ $dir != *"/" ]] ; then
	    dir=$dir/
	fi
	if [[ $CAFAnalysisShare != "" ]] ; then
	    CAFAnalysisShare+=":"
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
	unset IFS
	return 0
    fi
    
    
    # Now, do the actual magic. Create a list of completions that are
    # going to be added to the standard suggestions.

    # Find the directory by cutting after the last "/"
    thisDir=""
    if [[ $thisWord == *"/"* ]] ; then
	thisDir=`echo $thisWord | rev | cut -d "/" -f2- | rev`
	if [[ $thisDir != "" ]] ; then
	    thisDir+="/"
	fi
    fi

    listOfFiles=""
    listOfDirs=""
    
    configMasterCompletion=""

    # CAFAnalysisShare has format "path/one/:path/two/:path/three/"
    for path in $CAFAnalysisShare ; do
	
	thisPath="$path$thisDir"
	# if [[ $thisDir != "" ]] ; then
	#     thisPath+="/"
	# fi
	
	listOfFiles_new=`ls -a $thisPath 2>/dev/null |grep ".cfg$" | tr '\r\n' ':'`
	listOfDirs_new=`ls -ad $thisPath*/ 2>/dev/null | tr '\r\n' ':'`
	
	for file in $listOfFiles_new  ; do

	    # cut off the absolute part of all suggestions and save in listOfFiles
	    if [[ file != "" ]] ; then
		# listOfFiles+=${file/$path/}
		listOfFiles+=$thisDir$file
	    fi
	    listOfFiles+=" :"
	done
	for dir in $listOfDirs_new  ; do
	    if [[ $listOfDirs != "" ]] ; then
		listOfDirs+=":"
	    fi
	    # cut off the absolute part of all suggestions and save in listOfDirs
	    listOfDirs+=${dir/$path/}
	done
	listOfDirs="$thisDir../:$listOfDirs"
	# # test if there is a subdirectory "config/master". if yes, write it into configMasterCompletion. use it. otherwise, compile normal completions.
	# for dir in $listOfDirs ; do
	#     if [[ $dir == *"config/" ]] ; then
	# 	listOfDirsInConfig="`ls -ad $thisPath$dir | tr '\r\n' ':'`
	# 	for dirInConfig in $listOfDirsInConfig ; do
	# 	    if [[ $dirInConfig == *"config/master/" ]] ; then
	# 		configMasterCompletion=$thisWord$dir"master"
	# 		if [[ $listOfFiles == "" ]] ; then
	# 		    COMPREPLY=( $(compgen -W "$configMasterCompletion" -- $thisWord) )
	#                   unset IFS
	# 		    return 0
	# 		fi
	# 	    fi
	# 	done
	#     fi
	# done
    done

    
    
    #listOfFiles ends with ":".
    fullCompletions="$listOfFiles$listOfDirs"
    fullCompletions=`echo $fullCompletions | tr ":" " "`
    unset IFS

    # echo ""
    # echo "fullCompletions: $fullCompletions"
    # echo "thisWord       : $thisWord"
    
    # Compgen reduces the list to the words starting with $thisWord
    COMPREPLY=( $(compgen -W "$fullCompletions" -- "$thisWord") )

    # echo "${COMPREPLY[@]}"
#    unset COMPREPLY
    
    leadingCharFirst=""
    allLeadingAreSame=0
    echo ""
    for entry in "${COMPREPLY[@]}" ; do
    	echo "entry               : $entry"
    	entryWithoutThisWord=${entry/#$thisWord/}
    	echo "entryWithoutThisWord: $entryWithoutThisWord"
    	if [[ $leadingCharFirst == "" ]] ; then
    	    leadingCharFirst="${entryWithoutThisWord:0:1}"
    	else
    	    leadingCharThis="${entryWithoutThisWord:0:1}"
    	    if [[ $leadingCharThis != $leadingCharFirst ]] ; then
    		allLeadingAreSame=1
    	    fi
    	fi
    done

    if [ $allLeadingAreSame -eq 1 ] ; then
    	# cut off $thisDir to make completions look nice
    	COMPREPLY=("${COMPREPLY[@]/#$thisDir/}")
    	# echo "some leading characters are different"
    	# echo "COMPREPLY:      ${COMPREPLY[@]}"
    fi
    
    echo ""
    echo ""
    return 0
}


# Add all $pythonScripts to the list of commands that need
# auto-complete. If any of them invokes auto-complete, the
# hww_config_files function gets called.

IFS=" "
for script in $pythonScripts ; do
    complete -o nospace -F _analysis_config_files $script
done
unset IFS
