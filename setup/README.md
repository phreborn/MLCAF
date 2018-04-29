Setup
=========================

To prepare your terminal to run CAF, you must execute the file `setupAnalysis.sh` with the following command:

```bash
source setupAnalysis.sh
```

The file is generated automatically by `cmake`. If you want to recreate it, go to your build directory and execute `cmake` as described in the [main README](../README.md).

Settings
--------------------

The following description is not vital to executing CAF. It might, however, help you to customize the framework.


### Output Location ###

The output of CAF is written to two different locations: The folder `sampleFolders/` houses files saved after running each python script. The directory `results/` contains legible output such as plots and cut flows.

By default, both directories are written into your current working directory. This might be impractical if you like to run the framework from different locations. You can specify an absolute output location by setting the environment variable `$CAFOUTPUTDIR`. If you want to make this setting permanent, export the environment variable in a file called `setupLocal.sh` (see example below).

### Auto-completion ###

The CAF interface provides you with helpful suggestions, when you want to specify a config file. After typing the python command, eg. `prepare.py`, you can trigger auto-completion with the `<TAB>` key. It will search the current directory and the `share/` directory to compile a list of subordinate directories and all files ending with relevant extensions (eg. `.cfg` for config files).

To filter the suggestions even further, you can set the environment variable `$CAFAUTOCOMPLETEOPT` to a number between 0 and 3:

|`$CAFAUTOCOMPLETEOPT`| Auto-completion behaviour |
|---------------------|-----------------------|
|0| (default) Auto-completion as described above.|
|1| Like 0, but if directories like `config/master/` are found, they are completed immediately. Other, possibly useful, suggestions are ignored.|
|2| Like 0, but only files are suggested, whose beginning matches the title of the python script.|
|3| Combines 1 and 2. |

### Save settings for next time ###

When you set up your analysis, the script `setupLocal.sh` (in your `setup/` directory) is executed. This is the place, where you want to define environment variables that should be set every time you set up CAF. This file is not version-controlled. You can copy and modify the following example.

```bash
#!/bin/bash

# Absolute location in which output of CAF is written
export CAFOUTPUTDIR="/path/to/your/outputDirectory"

# Select your favorite option for auto-completion
export CAFAUTOCOMPLETEOPT=3

```

