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


    # Check if $command is known (i.e. it is in $PATH)

    pathToCommand=$(which $command 2>/dev/null)
    # resolve leading "~/" and symbolic links
    pathToCommand="${pathToCommand/#\~/$HOME}"
# doesn't work on all operating systems (i.e. doesn't work on Mac)
#    pathToCommand="$(readlink -f $pathToCommand)"
    if [ ! -x "$pathToCommand" ] ; then
	# $command does not point to an executable, exit script
	return 0
    fi


    # Check if $command is in $CAFANALYSISSHARE. If not, exit the script.
    
    commandInExecutables=0
    # Loop over all directories in $CAFANALYSISSHARE
    for directory in `echo $CAFANALYSISSHARE | tr ":" " "`; do
	# resolve leading "~/" and symbolic links
	dir="${directory/#\~/$HOME}"
# doesn't work on all operating system (i.e. doesn't work on Mac)
#	dir="$(readlink -f $dir)/"

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
    
    # replace colons by spaces
    hwwConfigPathFormatted=`echo $HWWCONFIGDIRECTORY | tr ":" " "`

    # Make a list of all files in $HWWCONFIGDIRECTORY trailing with ".cfg"
    listOfFiles="$(ls $hwwConfigPathFormatted |grep ".cfg$")"
    
    # Compgen reduces the list to the words starting with $thisWord
    COMPREPLY=( $(compgen -W "$listOfFiles" -- $thisWord) )
    
    return 0
}


# Add all $pythonScripts to the list of commands that need
# auto-complete. If any of them invokes auto-complete, the
# hww_config_files function gets called.

for script in $pythonScripts ; do
    complete -df -F _hww_config_files $script
done
