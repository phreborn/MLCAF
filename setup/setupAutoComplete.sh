#!/bin/bash

######################################################################
# Auto-completion of config files for python scripts
######################################################################


# Names of python scripts that need config files. Auto-complete
# will only work for these scripts and only if they are in the
# $CAFANALYSISSHARE directory.
pythonScripts="prepare.py initialize.py analyze.py visualize.py submit.py"


_CAFdoAutoCompletion(){
    local command=$1
    # Check if $command is known. If it does not point to an
    # executable, exit script.

    IFS=:
    
    local pathToCommand=$(which $command 2>/dev/null)
    # resolve leading "~/" and symbolic links
    pathToCommand="${pathToCommand/#\~/$HOME}"
    if [ ! -x "$pathToCommand" ] ; then
	return 0
    fi

    local CAFAnalysisShare=""
    
    # Check if $command is in $CAFANALYSISSHARE. If not, exit the script.
    local commandInExecutables=0
    for directory in $CAFANALYSISSHARE ; do
    	# resolve leading "~/" and symbolic links
    	local dir="${directory/#\~/$HOME}"
    	if [[ $dir != *"/" ]] ; then
    	    dir="$dir/"
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

    echo $CAFAnalysisShare
    unset IFS
    return $commandInExecutables
}


_CAFFindPossibleCompletions(){
    local thisWord=$1
    local thisDir=$2
    local CAFAnalysisShare=$3
    local option=$4
    local immediateCompleteStr=$5

    # echo ""
    # echo "_CAFFindPossibleCompletions called with arguments:"
    # echo "thisWord             : $thisWord"
    # echo "thisDir              : $thisDir"
    # echo "CAFAnalysisShare     : $CAFAnalysisShare"
    # echo "option               : $option"
    # echo "immediateCompleteStr : $immediateCompleteStr"

    
    IFS=:

    #todo implement completion of arbitrary immediateCompleteStr

    # The following variables are used:
    # path     : Location that is searched for completions. This
    #            variable loops over the working directory and
    #            directories in $CAFANALYSISSHARE.
    # thisDir  : Already typed directories contained in $thisWord and
    #            relative to $path.
    # thisPath : Combines the two previous variables: $path$thisDir


    # These two variables hold all files and directories that will be
    # used as possible matches for auto-completion. They are relative
    # to $path.
    
    local listOfFiles=""
    local listOfDirs=""

    local slashes="${immediateCompleteStr//[^\/]}/"
    local immediateCompleteDirs=()
    local arrayIndex=0
    for (( i=0; i<${#slashes}; i++)) ; do
	iPlusOne="$[ i+1 ]"
	tmp=`echo $immediateCompleteStr |rev| cut -d "/" -f$iPlusOne -|rev`
	if [[ "$tmp" != "" ]] ; then
	    if [ "$i" -gt 0 ] ; then
		tmp="$tmp/"
	    fi
	    immediateCompleteDirs[arrayIndex]=$tmp
	    arrayIndex="$[ arrayIndex+1 ]"
	fi
    done

    for path in $CAFAnalysisShare ; do
	local thisPath="$path$thisDir"

	# Contains all filenames in $thisPath.
	local listOfFiles_new=`ls -ap $thisPath 2>/dev/null | tr '\r\n' ':'`
	# Contains absolute paths of directories in $thisPath
	local listOfDirs_new=`ls -ad $thisPath*/ 2>/dev/null | tr '\r\n' ':'`

	local foundInThisPath=()
	
	for file in $listOfFiles_new  ; do
	    if [[ "$file" != *"/" ]] ; then
		if [[ $file != "" ]] ; then
		    if [[ $listOfFiles != "" ]] ; then
			listOfFiles+=":"
		    fi
		    listOfFiles+=$thisDir$file
		    foundInThisPath+=("$thisDir$file")
		fi
	    fi
	done
	for dir in $listOfDirs_new  ; do
	    if [[ $dir != "" ]] && [[ $dir != "./" ]] && [[ $dir != "../" ]] ; then
		if [[ $listOfDirs != "" ]] ; then
		    listOfDirs+=":"
		fi
		# cut off the absolute part of all suggestions
		listOfDirs+=${dir/$path/}
		foundInThisPath+=("${dir/$path/}")
	    fi
	done

	# Only add the parent directory if useful
	# if [[ $thisDir == "" ]] || [[ $thisDir == *"../" ]] ; then
	#     if [[ $listOfDirs == "" ]] ; then
	# 	listOfDirs="$thisDir../"
	#     else
	# 	listOfDirs="$thisDir../:$listOfDirs"
	#     fi
	# fi

	# Additional filter: If there is a directory "config/master/",
	# complete it immediately and don't show other options.
	# echo ""
	# echo "path: $path"
	if [ "$option" -eq 1 ] || [ "$option" -eq 3 ] ; then
	    for (( i=0;i<${#immediateCompleteDirs[@]};i++ )) ; do
		# echo "    $i: ${immediateCompleteDirs[i]}"
		for file in "${foundInThisPath[@]}" ; do
		    # echo "        file: $file"
		    # echo "        cmpW: ${immediateCompleteDirs[i]}"
		    if [[ "$file" == *"${immediateCompleteDirs[i]}" ]] ; then
			local tmp=""
			# check entire path before match
			for (( ii=0;ii<"$[ i+1 ]";ii++ )) ; do
			    tmp+="${immediateCompleteDirs[ii]}"
			done
			# echo "            compare: *$tmp, ${path/#.\//$PWD/}$file"
			if [[ "${path/#.\//$PWD/}$file" == *"$tmp" ]] ; then
			    tmp="$file"
			    local ranUntilTheEnd=1
			    for (( ii="$[ i+1 ]";ii<${#immediateCompleteDirs[@]};ii++ )) ; do
				# echo "            $ii: ${immediateCompleteDirs[ii]}"
				ranUntilTheEnd=1
				tmpBefore="$tmp"
				tmpFiles=`ls -ap "$path$tmp" 2>/dev/null | tr '\r\n' ':'`
				for tmpFile in $tmpFiles ; do
				    # echo "                $tmpFile"
				    if [[ "$tmpFile" == "${immediateCompleteDirs[ii]}" ]] && [[ "$tmp" == "$tmpBefore" ]] ; then
					# echo "                    added $tmpFile"
					tmp="$tmp$tmpFile"
				    fi
				done
				if [[ "$tmp" == "$tmpBefore" ]] ; then
				    ii=${#immediateCompleteDirs[@]}
				    ranUntilTheEnd=0
				fi
			    done
			    if [ "$ranUntilTheEnd" -eq 1 ] ; then
				# echo "match found: $tmp"
				COMPREPLY="$tmp"
				return 0
			    fi
			fi
		    fi
		done
	    done
	fi

	    
	#     for dir in $listOfDirs ; do
	# 	if [[ $listOfFiles == "" ]] ; then
	# 	    if [[ $dir == *"config/" ]] ; then
	# 		listOfDirsInConfig=`ls -ad $path$dir*/ | tr '\r\n' ':'`
	# 		for dirInConfig in $listOfDirsInConfig ; do
	# 		    if [[ $dirInConfig == *"config/master/" ]] ; then
	# 			local tmp=$dir"master/"
	# 			unset IFS
	# 			COMPREPLY=( $(compgen -W "$tmp" -- $thisWord) )
	# 			if [ "${#COMPREPLY[@]}" -ge 1 ] ; then
	# 			    return 0
	# 			fi
	# 			IFS=:
	# 		    fi
	# 		done
	# 	    elif [[ $dir == *"master/" ]] ; then
	# 		local tmp="./"
	# 		local absolutePath=${path/#$tmp/"$PWD/"}
	# 		if [[ $absolutePath$dir == *"config/master/" ]] ; then
	# 		    unset IFS
	# 		    COMPREPLY=( $(compgen -W "$dir" -- $thisWord) )
	# 		    if [ "${#COMPREPLY[@]}" -ge 1 ] ; then
	# 			return 0
	# 		    fi
	# 		    IFS=:
	# 		fi
	# 	    fi
	# 	fi
	#     done
	# fi
    done

    
    unset IFS
    fullCompletions=`echo "$listOfFiles:$listOfDirs" | tr ":" " "`
    
    # Compgen reduces the list to the words starting with $thisWord.
    # The variable COMPGEN will be used to print suggestions.
    COMPREPLY=( $(compgen -W "$fullCompletions" -- "$thisWord") )

    return 0
}

_CAFShortenPath(){
    local path="$1"
    shortenedPath=`echo $path | rev | cut -d "/" -f1 - | rev`
    echo $shortenedPath
}

_CAFShortenCompreply(){
    # Auto-completion works without the following lines. But it shows
    # the completions relative to $path. This behaviour is unfamiliar
    # to a user. The next lines check if auto-completion will find a
    # (sub)string to complete. In that case, don't change $COMPREPLY
    # and complete the match. If there is no match, show the more in-
    # tuitive suggestions by removing the relative path $thisDir.

    local thisWord=$1
    local thisDir=$2
    
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

}

_CAFFilterFiles(){
    local prefices="$1"
    local extensions="$2"

    local max=${#COMPREPLY[@]}
    local newIndex=0
    IFS=:
    for (( i=0; i<$max; i++)) ; do
	entry="${COMPREPLY[$i]}"
	# echo ""
	# echo "$i: $entry"
	local removeEntry=1
	if [[ "$entry" == *"/" ]] ; then
	    removeEntry=0
	else
	    local extensionMissing=1
	    local prefixMissing=1
	    if [[ "$extensions" == "" ]] ; then
		extensionMissing=0
	    else
		for extension in $extensions ; do
		    if [[ "$entry" == *"$extension" ]] ; then
			extensionMissing=0
		    fi
		done
	    fi
	    if [[ "$extensionMissing" -eq 0 ]] ; then
		if [[ "$prefices" == "" ]] ; then
		    prefixMissing=0
		else
		    for prefix in $prefices ; do
			local entryShortened=`echo $entry | rev | cut -d "/" -f1 - | rev`
			if [[ "$entryShortened" == "$prefix"* ]] ; then
			    prefixMissing=0
			fi
		    done
		fi
	    fi
	    if [ "$extensionMissing" -eq 0 ] && [ "$prefixMissing" -eq 0 ] ; then
		removeEntry=0
	    fi
	fi
	if [ "$removeEntry" -eq 0 ] ; then
	    if [[ "$newIndex" -lt "$i" ]] ; then
		COMPREPLY[newIndex]=${COMPREPLY[i]}
		unset COMPREPLY[i]
	    fi
	    newIndex="$[ $newIndex+1 ]"
	else
	    unset COMPREPLY[i]
	fi
    done
    # echo ""
    # echo "Summary (number of entries=${#COMPREPLY[@]})"
    # for (( i=0; i<$max; i++)) ; do
    # 	echo "$i: ${COMPREPLY[$i]}"
    # done
    unset IFS
}


# This function gets executed if tab-complete is requested for the
# python scripts listed above. It creates auto-complete suggestions
# from the current directory and $CAFANALYSISSHARE. Files ending
# with ".cfg" and directories are suggested.
_CAFRegularComplete(){
    local command=$1
    local thisWord=$2
    local previousWord=$3
    local thisDir=$4
    local CAFAnalysisShare=$5
    local option=$6

    local prefices=""
    if [ "$option" -gt 1 ] ; then
	prefices="${command/%.py/}"
    fi
    
    # echo ""
    # echo "_CAFRegularComplete called with arguments:"
    # echo "command          : $command"
    # echo "thisWord         : $thisWord"
    # echo "previousWord     : $previousWord"
    # echo "thisDir          : $thisDir"
    # echo "CAFAnalysisShare : $CAFAnalysisShare"
    # echo "option           : $option"

    # Now, do the actual magic. Create a list of completions that are
    # going to be added to the standard suggestions.

    _CAFFindPossibleCompletions "$thisWord" "$thisDir" "$CAFAnalysisShare" "$option" "master/config/"
    _CAFFilterFiles "$prefices" ".cfg"
    _CAFShortenCompreply "$thisWord" "$thisDir"

    return 0
}

_CAFSubmitComplete(){
    local command=$1
    local thisWord=$2
    local previousWord=$3
    local thisDir=$4
    local CAFAnalysisShare=$5
    local option=$6
    #todo
}

_CAFAutoComplete(){
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
    
    local command=$1
    local thisWord=$2
    local previousWord=$3


    # Find $thisDir by cutting after the last "/"
    local thisDir=""
    if [[ $thisWord == *"/"* ]] ; then
	thisDir=`echo $thisWord | rev | cut -d "/" -f2- | rev`
	if [[ $thisDir != "" ]] ; then
	    thisDir+="/"
	fi
    fi

    # Do normal auto-completion if $command is not in CAFANALYSISSHARE
    local CAFAnalysisShare="./:"
    CAFAnalysisShare+=$(_CAFdoAutoCompletion $command)
    local statusCode=$?
    if [ $statusCode -eq 0 ] ; then
	_CAFRegularComplete "$command" "$thisWord" "$previousWord" "$thisDir" "./" "0"
	_CAFShortenCompreply "$thisWord" "$thisDir"
	return 0
    fi

    # If $CAFAUTOCOMPLETEOPT is integer between 0 and 3, overwrite
    # $option.
    local re='^[0-3]$'
    if [[ "$CAFAUTOCOMPLETEOPT" =~ $re ]] ; then
	option=$CAFAUTOCOMPLETEOPT
    fi
    
    if [ $command == "submit.py" ] ; then
	_CAFSubmitComplete "$command" "$thisWord" "$previousWord" "$thisDir" "$CAFAnalysisShare" "$option"
	return 0
    fi
    
    _CAFRegularComplete "$command" "$thisWord" "$previousWord" "$thisDir" "$CAFAnalysisShare" "$option"
    return 0
}

# Add all $pythonScripts to the list of commands that need
# auto-complete. If any of them invokes auto-complete, the
# analysis_config_files function gets called.

IFS=" "
for script in $pythonScripts ; do
    complete -o nospace -F _CAFAutoComplete $script
done
#todo write complete for batch scripts
unset pythonScripts
unset IFS
