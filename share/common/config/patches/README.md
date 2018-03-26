TQFolder Patches
=========================

TQFolder Patch Files allow to place additional information on a SampleFolder
structure in the form of additional tags. They also provide a way to modify the
SampleFolder structure itself, e.g, by moving, copying, deleting, or creating
TQ(Sample)Folders and TQSamples.

Applying these kind of files as 'patches' or 'patch files' usually implies 
that they are applied to the SampleFolder structure of an analysis. The syntax,
however, can be used to modify any TQFolder structure.


Syntax: Folder Paths
--------------------
The path syntax use in TQFolder files mostly follows the pattern one knows from
most shells on Linux/MacOS. Yet, some specifics are listed in the following:

* ```this/is/a/relative/path```: like on a shell this is a relative path
* ```/this/is/an/absolute/path```: leading '/' is interpreted as an absolute 
    path, i.e., w.r.t. the root node of a TQFodler structure.
* ```path/with/wi\*card/matching```: matches any folder whoes path starts as 
    'path/with', the name of the folder at the third level matches 'wi\*cards'
    and the fourth level folder is called 'matching'. The '*' wildcard, here,
    matches any number of characters within a single folders name.
* ```path/with/wil?card/matching```: same as previous case but the '?' wildcard
    only matches a single character
* ```path/with/?/matching```: here, the '?' wildcard character is isolated. The 
    expression therefore matches any folder at the third level.
* ```path/with/\*/matching```: here, the '\*' wildcard character is isolated. It
    matches any number of folders inside 'path/with'. The paths of the folders
    matched by the full expression still need to end with a folder named 
    'matching'.

In summary regarding wildcards: a questionmark '?' matches a single object, the 
star any number of objects. If the character in question is used on its own as a 
folder layer in a path the objects matched are entire folders, otherwise the 
objects matched are characters in a single folders name.

Names of TQFolders are also more restrictive than those of folders on a file 
system. Allowed characters are 
```
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.
```
Please take note that especially '-' and '+' are excluded as they have a special
function for SampleFolders.

Usage: Creating new TQFolders
--------------------
New instances of TQFolder (please note: NOT TQSampleFolder) can be created using
```
+myNewFolder;
```
This will create a new subfolder (instance of TQFolder) inside the current
TQFolder. If a folder with the name 'myNewFolder' already exists inside the 
current folder, nothing is done. Alternatively, one can add a block after the 
creation of a new folder:
```
+myNewFolder {
  #something else (this is a comment)
}
```
Everything inside the block delimited by '{' and '}' is evaluated from within
'myNewFolder'. Hence, in that context 'myNewFolder' is the 'current' folder.

Multiple layers of folders can be created in the same way:
```
+myNewFolder/myNewSubFolder;
# or:
+myNewFolder/myNewSubFolder {
  #do something inside 'myNewSubFolder'
}
```

In order to create new instances of TQSampleFolder or TQSample one can 
explicitly  specify the type of folder using the ```$create``` command:
```
$create(path='my/folder/path/to/create', type='sf'); # or type='samplefolder'
$create(path='my/other/path/to/create', type='s'); # or type='sample'
```
This will create all folders in the given path that do not exist, yet. The
specified type of folder (instance of TQSampleFolder or TQSample) is only taken
into account if the respective folder does not yet exist, the type of existing 
folders is not changed.


Usage: Adding Tags to Existing Folders
--------------------
One or multiple tags (pairs of 'key' and 'value') can be set on a TQFolder.
Depending on the use case either of the two following examples can be more 
convenient:
```
#place the two tags 'myKey' (string valued) and 'myOtherKey' (double valued) at some/path:
<myKey="myStringValue", myOtherKey=42. ,someBool=true> @some/path; 
#equivalently:
@some/path {
  <myKey="myStringValue", myOtherKey=42. ,someBool=true>
}
#available types of tags: int, double, string, bool
```
Please note that this will only deposit the tags and their values at the 
specified location. The interpretation of the repective tag is then up to some
(at this point unspecified) part of the analysis code. For a (almost complete)
list of tags, please see the [TagDocumentation](https://atlas-caf.web.cern.ch/tags.html).

























