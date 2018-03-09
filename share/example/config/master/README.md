Master
=========================

Master config files are config files directly passed as command line arguments to the analysis scripts in this package, as opposed to  all other config files, which are indirectly included and pointed to by the master config files. They are parsed by the python `configparser` module and follow the [corresponding syntax](https://docs.python.org/3/library/configparser.html#quick-start)

Usage
--------------------

Master config files can address one or more of the scripts in this package. The examples contained in this package are all written to create a 1-to-1 correspondence between config files and scripts, but this need not be the case. If you want to have your entire analysis encoded in a single config file, you can do that easily.

Start off your master config file with a section. For example, if you want to use the config file in conjunction with the `prepare.py` script, you should have a section `[prepare]`. Within that section, you can give arbitrarily many configuration options. The syntax should look like this.

    # comment
    [section]
    key: value
    anotherkey: anothervalue
    
    [anothersection]
    key: value

The scripts in this package are addressed by the following sections:
  * `prepare.py` reads the contents of the section `[prepare]`
  * `initialize.py` reads the contents of the section `[initialize]`
  * `analyze.py` reads the contents of the section `[analyze]`
  * `visualize.py` reads the contents of the section `[visualize]`
All scripts ignore all other sections except their own.

Additional Features
--------------------

The syntax explained above is just one of the options that you have. You can also use the `TQFolder` text configuration syntax. The syntax correpsonding to the lines

    somenumber: 1
    somestring: hello
    
would be

    <somenumber=1>
    <somestring="hello">
    
All of the scripts accept one or more config files, and you can mix and match different syntax versions to your convenience.