#!/bin/bash


# Names of python scripts that need config files. Auto-complete
# will only work for these scripts and only if they are in the
# $ANALYSISEXECUTABLES directory.
pythonScripts="prepare.py initialize.py analyze.py visualize.py"

# This function gets executed if tab-complete is requested for the
# python scripts listed above. It adds files from $HWWCONFIGDIRECTORY
# ending in ".cfg" to the auto-complete suggestions.
_analysis_config_files(){


    # 0: search relative to ./ and $CAFANALYSISSHARE
    # 1: like 0, but complete "config/master/" when found
    # 2: like 0, but match files with beginning of script name
    # 3: combines 1 and 2
    local option=0
    
    local command=$1
    local thisWord=$2
    local previousWord=$3

    # Check if $command is known
    # If $command does not point to an executable, exit script
    
    local pathToCommand=$(which $command 2>/dev/null)
    # resolve leading "~/" and symbolic links
    pathToCommand="${pathToCommand/#\~/$HOME}"
    if [ ! -x "$pathToCommand" ] ; then
	return 0
    fi

    # Set internal field separator (unset at the end)
    IFS=:
    
    # Check if $command is in $CAFANALYSISSHARE. If not, exit the script.

    local CAFAnalysisShare="./"
    local commandInExecutables=0
    for directory in $CAFANALYSISSHARE ; do
	# resolve leading "~/" and symbolic links
	local dir="${directory/#\~/$HOME}"
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
	    local trailingPath=${pathToCommand/$dir/}
	    local slashes=${trailingPath//[^\/]}
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
    local thisDir=""
    if [[ $thisWord == *"/"* ]] ; then
	thisDir=`echo $thisWord | rev | cut -d "/" -f2- | rev`
	if [[ $thisDir != "" ]] ; then
	    thisDir+="/"
	fi
    fi

    local listOfFiles=""
    local listOfDirs=""
    
    local configMasterCompletion=""

    # CAFAnalysisShare has format "path/one/:path/two/:path/three/"
    for path in $CAFAnalysisShare ; do
	
	local thisPath="$path$thisDir"
	# if [[ $thisDir != "" ]] ; then
	#     thisPath+="/"
	# fi
	
	local listOfFiles_new=`ls -a $thisPath 2>/dev/null |grep ".cfg$" | tr '\r\n' ':'`
	local listOfDirs_new=`ls -ad $thisPath*/ 2>/dev/null | tr '\r\n' ':'`
	
	for file in $listOfFiles_new  ; do

	    # cut off the absolute part of all suggestions and save in listOfFiles
	    if [[ file != "" ]] ; then
		# listOfFiles+=${file/$path/}
		listOfFiles+=$thisDir$file
	    fi
	    listOfFiles+=":"
	done
	for dir in $listOfDirs_new  ; do
	    if [[ $listOfDirs != "" ]] ; then
		listOfDirs+=":"
	    fi
	    # cut off the absolute part of all suggestions and save in listOfDirs
	    listOfDirs+=${dir/$path/}
	done
	if [[ $thisDir == "" ]] || [[ $thisDir == "../" ]] ; then
	    listOfDirs="$thisDir../:$listOfDirs"
	fi


	
	if [ "$option" -ge 2 ] ; then
	    local listOfFilesTmp=$listOfFiles
	    listOfFiles=""
	    for file in $listOfFilesTmp ; do
		if [[ $listOfFiles != "" ]] ; then
		    listOfFiles+=":"
		fi
		if [[ "${file/$thisDir/}" == "${command/".py"/}"* ]] ; then
		    listOfFiles+=$file
		fi
	    done
	fi

	# test if there is a subdirectory "config/master". if yes, write it into configMasterCompletion. use it. otherwise, compile normal completions.

	if [ "$option" -eq 1 ] || [ "$option" -eq 3 ] ; then
	    for dir in $listOfDirs ; do
		if [[ $listOfFiles == "" ]] ; then
		    if [[ $dir == *"config/" ]] ; then
			listOfDirsInConfig=`ls -ad $path$dir*/ | tr '\r\n' ':'`
			for dirInConfig in $listOfDirsInConfig ; do
			    if [[ $dirInConfig == *"config/master/" ]] ; then
				configMasterCompletion=$dir"master/"
				unset IFS
				COMPREPLY=( $(compgen -W "$configMasterCompletion" -- $thisWord) )
				if [ "${#COMPREPLY[@]}" -ge 1 ] ; then
				    return 0
				fi
				IFS=:
			    fi
			done
		    elif [[ $dir == *"master/" ]] ; then
			local tmp="./"
			local absolutePath=${path/#$tmp/"$PWD/"}
			if [[ $absolutePath$dir == *"config/master/" ]] ; then
			    unset IFS
			    COMPREPLY=( $(compgen -W "$dir" -- $thisWord) )
			    if [ "${#COMPREPLY[@]}" -ge 1 ] ; then
				return 0
			    fi
			    IFS=:
			fi
		    fi
		fi
	    done
	fi
    done

    
    
    #listOfFiles ends with ":".
    local fullCompletions="$listOfFiles$listOfDirs"
    fullCompletions=`echo $fullCompletions | tr ":" " "`
    unset IFS
    
    # Compgen reduces the list to the words starting with $thisWord
    COMPREPLY=( $(compgen -W "$fullCompletions" -- "$thisWord") )

    
    # echo "${COMPREPLY[@]}"
#    unset COMPREPLY
    
    local leadingCharFirst=""
    local allLeadingAreSame=0
    # echo ""
    
    for (( i=0; i<${#COMPREPLY[@]}; i++)) ; do
	entry=${COMPREPLY[$i]}
	if [[ $entry != *"/" ]] ; then
	    COMPREPLY[$i]="$entry "
	fi
    	# echo "entry               : $entry"
    	local entryWithoutThisWord=${entry/#$thisWord/}
    	# echo "entryWithoutThisWord: $entryWithoutThisWord"
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
