#!/bin/bash

######################################################################
# Auto-completion of config files for python scripts
######################################################################


# Names of python scripts that need config files. Auto-complete
# will only work for these scripts and only if they are in the
# $CAFANALYSISSHARE directory.
pythonScripts="prepare.py initialize.py analyze.py visualize.py"


# This function gets executed if tab-complete is requested for the
# python scripts listed above. It creates auto-complete suggestions
# from the current directory and $CAFANALYSISSHARE. Files ending
# with ".cfg" and directories are suggested.
_analysis_config_files(){


    ##################################################################
    # Option for auto-complete mode. "option=0" is set by default.
    # It is overwritten by $CAFAUTOCOMPLETEOPT.
    #
    # 0: search relative to ./ and $CAFANALYSISSHARE
    # 1: like 0, but complete "config/master/" when found
    # 2: like 0, but match files with beginning of script name
    # 3: combines 1 and 2
    #
    local option=0
    #
    ##################################################################

    # If $CAFAUTOCOMPLETEOPT is integer between 0 and 3, overwrite
    # $option.
    local re='^[0-3]$'
    if [[ "$CAFAUTOCOMPLETEOPT" =~ $re ]] ; then
	option=$CAFAUTOCOMPLETEOPT
    fi

    
    local command=$1
    local thisWord=$2
    local previousWord=$3


    # Check if $command is known. If it does not point to an
    # executable, exit script.
    
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
    
    # Jump out, if executable is not in $CAFANALYSISSHARE
    if [ $commandInExecutables -eq 0 ] ; then
	unset IFS
	return 0
    fi
    
    
    # Now, do the actual magic. Create a list of completions that are
    # going to be added to the standard suggestions.

    # The following variables are used:
    # path     : Location that is searched for completions. This
    #            variable loops over the working directory and
    #            directories in $CAFANALYSISSHARE.
    # thisDir  : Already typed directories contained in $thisWord and
    #            relative to $path.
    # thisPath : Combines the two previous variables: $path$thisDir



    # Find $thisDir by cutting after the last "/"
    local thisDir=""
    if [[ $thisWord == *"/"* ]] ; then
	thisDir=`echo $thisWord | rev | cut -d "/" -f2- | rev`
	if [[ $thisDir != "" ]] ; then
	    thisDir+="/"
	fi
    fi

    # These two variables hold all files and directories that will be
    # used as possible matches for auto-completion. They are relative
    # to $path.
    local listOfFiles=""
    local listOfDirs=""
    
    for path in $CAFAnalysisShare ; do
	local thisPath="$path$thisDir"

	# Contains all filenames in $thisPath.
	local listOfFiles_new=`ls -a $thisPath 2>/dev/null |grep ".cfg$" | tr '\r\n' ':'`
	# Contains absolute paths of directories in $thisPath
	local listOfDirs_new=`ls -ad $thisPath*/ 2>/dev/null | tr '\r\n' ':'`
	

	for file in $listOfFiles_new  ; do
	    if [[ file != "" ]] ; then
		listOfFiles+=$thisDir$file
	    fi
	    listOfFiles+=":"
	done
	for dir in $listOfDirs_new  ; do
	    if [[ $listOfDirs != "" ]] ; then
		listOfDirs+=":"
	    fi
	    # cut off the absolute part of all suggestions
	    listOfDirs+=${dir/$path/}
	done

	# Only add the parent directory if useful
	if [[ $thisDir == "" ]] || [[ $thisDir == "../" ]] ; then
	    listOfDirs="$thisDir../:$listOfDirs"
	fi


	# Additional filter: Finds only config files starting with
	# the the same name as the python script.
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

	# Additional filter: If there is a directory "config/master/",
	# complete it immediately and don't show other options.
	if [ "$option" -eq 1 ] || [ "$option" -eq 3 ] ; then
	    for dir in $listOfDirs ; do
		if [[ $listOfFiles == "" ]] ; then
		    if [[ $dir == *"config/" ]] ; then
			listOfDirsInConfig=`ls -ad $path$dir*/ | tr '\r\n' ':'`
			for dirInConfig in $listOfDirsInConfig ; do
			    if [[ $dirInConfig == *"config/master/" ]] ; then
				local tmp=$dir"master/"
				unset IFS
				COMPREPLY=( $(compgen -W "$tmp" -- $thisWord) )
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

    
    
    # Combine the possible completions
    local fullCompletions="$listOfFiles$listOfDirs"
    fullCompletions=`echo $fullCompletions | tr ":" " "`
    unset IFS
    
    # Compgen reduces the list to the words starting with $thisWord.
    # The variable COMPGEN will be used to print suggestions.
    COMPREPLY=( $(compgen -W "$fullCompletions" -- "$thisWord") )

    
    # Auto-completion works without the following lines. But it shows
    # the completions relative to $path. This behaviour is unfamiliar
    # to a user. The next lines check if auto-completion will find a
    # (sub)string to complete. In that case, don't change $COMPREPLY
    # and complete the match. If there is no match, show the more in-
    # tuitive suggestions by removing the relative path $thisDir.
    
    local leadingCharFirst=""
    local allLeadingAreSame=0

    for (( i=0; i<${#COMPREPLY[@]}; i++)) ; do
	entry=${COMPREPLY[$i]}

	# Add a space to all filesnames (as opposed to directories).
	if [[ $entry != *"/" ]] ; then
	    COMPREPLY[$i]="$entry "
	fi

	# Check if leading characters of all suggestions are the same.
    	local entryWithoutThisWord=${entry/#$thisWord/}
    	if [[ $leadingCharFirst == "" ]] ; then
    	    leadingCharFirst="${entryWithoutThisWord:0:1}"
    	else
    	    leadingCharThis="${entryWithoutThisWord:0:1}"
    	    if [[ $leadingCharThis != $leadingCharFirst ]] ; then
    		allLeadingAreSame=1
    	    fi
    	fi
    done

    # If leading characters of suggestions are different, no match
    # will be found and the user-friendly text will be printed.
    if [ $allLeadingAreSame -eq 1 ] ; then
    	COMPREPLY=("${COMPREPLY[@]/#$thisDir/}")
    fi
    
    return 0
}


# Add all $pythonScripts to the list of commands that need
# auto-complete. If any of them invokes auto-complete, the
# analysis_config_files function gets called.

IFS=" "
for script in $pythonScripts ; do
    complete -o nospace -F _analysis_config_files $script
done
unset IFS
