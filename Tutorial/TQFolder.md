This document is intended as hands-on instructions for the [CAF
tutorial](https://indico.cern.ch/event/719951/). Since the
instructions should be self-contained, it can also be used as a offline resource. The only
prerequisite of this tutorial is a working
[CAF](https://gitlab.cern.ch/atlas-caf/CAFCore) installation. You can check this
by running

<!-- console -->
```bash
$ python -c "import QFramework"
RooFit v3.60 -- Developed by Wouter Verkerke and David Kirkby 
                Copyright (C) 2000-2013 NIKHEF, University of California & Stanford University
                All rights reserved, please read http://roofit.sourceforge.net/license.txt
```

The `TQFolder` syntax is a versatile syntax to define annotated trees. Several
utility methods allows the definition and manipulation of larges trees in a few
lines. The syntax and TQFolders are used in several places in CAF. For examples
the cuts file is written in TQFolder syntax, all the samples, histograms and
counters are organized and stored in TQFolders.

In this tutorial, we will work on an
example completely detached from CAF. This tutorial builds a tree structure of
animals (no even close to real taxonomy). This approach underlines the
versatility of the syntax and helps to focus on the actual syntax instead of
being distracted by all the details of a real physics cut file.

# Basic `TQFolder` syntax
We want to create a tree structure containing information about animals. The
base folder should be called "Animals". the sub folders "Mammals", "Birds" and
"Reptiles" should also contain a third layer of sub folders. The desired
structure is illustrated below.

```
Animals
 |- Mammals
     |- Dog
     |- Cat
     |- Fox
 |- Birds
     |- Eagle
     |- Mockingbird
 |- Reptiles
     |- Turtle
     |- Lizard
```

 The standard way to define a folder in TQFolder syntax is by using the `+FolderName {
Content }` syntax, where `FolderName` is an arbitrary name, `Content` content
is a placeholder for the contents of a folder. We can create the file
`animals.tqfolder` and add 

<!-- write animals.tqfolder -->
```php
+Animals {
  +Mammals {
    +Dog {
    }
    +Cat {
    }
    +Fox {
    }
  }

  +Birds {
    +Eagle {
    }
    +Mockingbird {
    }
  }

  +Reptiles {
    +Turtle {
    }
    +Lizard {
    }
  }
}
```

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('animals.tqfolder').printContents(':dtr2')"
```
-->

This snippet is enough to define the desired animal tree in TQFolder syntax.

So far, the tree does not contain a lot of information. A very useful feature of
TQFolders is that they can be annotated with tags. A tag is a key value pair
attached to a specific TQFolder in the tree. The TQFolder syntax allows
you to attach tags directly while we define the folders. A folder with the four
tags `tagName1="value"`, `tagName2=42`, `tagName3="other_value"` and
`tagName4="spanning over two lines"` can be created with

<!-- write tag_example.tqfolder -->
```php
+FolderName {
  <tagName1="value">
  <tagName2=42, tagName3="other_value">
  <tagName4 = 
		"spanning over two lines">
}
```

Tags can be defined in separate `<>` brackets or join them in one pair separated by a comma.

<!-- Check that the tag example is correct. -->
<!-- console
```
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('tag_example.tqfolder').printContents(':dtr2')"
```
-->

As an example we would like to annotated the our animal tree with tags to
indicate the animals skin type (`skin` tag), whether they are vegetarian (tag
`vegetarian`) and their approximate global population.

<!-- write animals.tqfolder -->
```php
+Animals {
  +Mammals {
    <skin="fur">
    <vegetarian=false>
    +Rabbit {
      <vegetarian=true>
      <population=8.5e8>
    }
    +Cat {
      <population=6e8>
    }
    +Fox {
      <population=2.4e5>
    }
  }

  +Birds {
    <skin="feather">
    +Hummingbird {
      <vegetarian=true>
      <population=2.3e6>
    }
    +Mockingbird {
      <vegetarian=false>
      <population=3.2e7>
    }
  }

  +Reptiles {
    <vegetarian=false>
    +Turtle {
      <skin="shell">
      <population=120000>
    }
    +Lizard {
      <skin="dragon">
      <population=9e5>
    }
  }
}
```

<!-- Check that the tag example is correct. -->
<!-- console
```
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('animals.tqfolder').printContents(':dtr3')"
```
-->

Wait. There are tags attached to parent folders, like `skin` attched to
`Mammel`, but the `population` tags are attached to the leaf notes?  Are all
Mammals non-vegetarian? We will see
in the next chapter why this structure is useful. In short, it prevents us from
repeating tags, if they apply for all the child folders.

So far, we have seen the standard way of defining a full TQFolder tree. There
are alternative methods for setting tags and creating folders. The alternative
syntax can be used to modify or extend an existing TQFolder tree. We can modify
and extend specify folder in the three by addressing them with their path. The
path of the `Mockingbird` folder would be `Animals/Birds/Mockingbird`.

The path can contain the wildcard charachers `?`
and `*`. The meaning of the two whildcards depend on their use. If they are used
as a placeholder of a folder name (i.e. between two `/` or between `/` and
the start/end of the path), `*` matches any number of folder layers (including)
zero), whereas `?` match exactly one folder layer. For example
`Animals/?/Ghost` matches `Animals/Mammals/Ghost`, `Animals/Birds/Ghost` or
`Animals/Reptiles/Ghost`. Multiple matches are possible. On the other hand
`Animals/*/Ghost` would match `Animals/Ghost`, `Animals/Mammals/Ghost`,
`Animals/Mammals/Cats/EuropeanHouseCat/Ghost`.

When the wildcard characters are used as part of a folder name, `*` matches any
number of characters, whereas `?` matches exactly one character. This means
M`R*` matches `Rabit` or `Reptiles`, `?at` matches `Rat`, `Cat` or `Bat`.

To set tags in an existing TQFolder tree, you can use the `<TagName=Value>
@FolderPath;` syntax.

Let's say we want add a tag to the `Fox` folder. Append
<!-- append animals.tqfolder -->
```
<better_than_chrome=true> @Animals/Mammals/Fox;
```
to your existing TQFolder definition file.

Furthermore, lets assume that, that we want to add a tags `number_of_legs` tag to all
the leaf folders. All the animals except birds have 4 legs in our example. This
means we could use wildcards to add the tag `number_of_legs=4` to all leaf
folders and then overwrite this value for Birds. Add 

<!-- append animals.tqfolder -->
```
<number_of_legs=4> @Animals/?/?;
<number_of_legs=2> @Animals/Birds/?;
```

<!-- Check that the tag example is correct. -->
<!-- console
```
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('animals.tqfolder').printContents(':dtr3')"
```
-->

Instead of setting just tags, we can also create new folders in an existing
folder tree. Append the following lines of code to the TQFolder definition file
in order to add a lion.
<!-- append animals.tqfolder -->
```
@Animals/Mammals {
  +Lion {
    <population=20000>
    <number_of_legs=4>
  }
}
```

This peace of code adds a new folder to the `Mammals` folder. As you see, it is
possible to create new TQFolders and/or new tags using this method. We are not
limited to a single folder not limited to a single folder layer. However, we have to
set the `number_of_legs` tag manually because the `<number_of_legs=4>
@Animals/?/?;` line is executed before the lion folder existed.

This syntax becomes really powerful when we combine it with wildcards. If we are
charged with the task to add the `Unicron` to the `Mammals`, `Birds` and
`Reptiles` folder, we can do this  by adding
<!-- append animals.tqfolder -->
```
@Animals/? {
  +Unicorn {
    <population=0>
    <number_of_legs=4>
    <vegetarian=true, skin="fur">
  }
}
```
to our TQFolder definition file.

<!-- Check that the tag example is correct. -->
<!-- console
```
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('animals.tqfolder').printContents(':dtr3')"
```
-->


So far so good, but how does the final tree actually look like? We will check this in
the next chapter.

# API
In this chapter we will work with an interactive python shell and look how we
can interact with our animals tree. Start a interactive python shell and
import `TQFolder`

<!-- write load.py -->
```python
from QFramework import TQFolder
```

## Loading and saving TQFolders
The result of the previous chapter should be stored in the file
`animals.tqfolder`. We can load a TQFolder definition with the static method
`TQFolder.loadFromTextFile`.

<!-- append load.py -->
```python
animals = TQFolder.loadFromTextFile("animals.tqfolder")
print animals
```

<!-- console
```
$ cp load.py base.py
-->

This is it (unless you have a syntax error in the definition file in which case you will be greeted by a
`ReferenceError: attempt to access a null-pointer`).

Make yourself familiar with our TQFolder by printing it and check if all the
`number_of_legs` tags are correct, and that there are unicorns in the tree. For
example run

<!-- append load.py -->
```python
animals.printContents()
animals.printContents("Animals/Birds:dt")  # d=details, t=include tags
animals.printContents("Animals/Mammals/Fox:dt")
animals.printContents("Animals/Reptiles:dtr2")  # r2=recursive 2 layers
```


We can write the TQFolder tree and its tags to a text file. In order to do this,
run
<!-- append load.py -->
```python
animals.exportToTextFile("animals_exported.tqfolder")
```

<!-- Test above python lines. -->
<!-- console
```
$ python load.py
```
-->

This creates the file `animals_exported.tqfolder` containing our animals
tree in standard syntax. Open it with your favorite editor. It should look like
<!-- console_output -->
```
$ cat animals_exported.tqfolder
# -*- mode: tqfolder -*-
+Animals {
	+Mammals {
		<skin = "fur", vegetarian = false>
		+Rabbit {
			<vegetarian = true, population = 850000000, number_of_legs = 4>
		}
		+Cat {
			<population = 600000000, number_of_legs = 4>
		}
		+Fox {
			<population = 240000, better_than_chrome = true, number_of_legs = 4>
		}
		+Lion {
			<population = 20000, number_of_legs = 4>
		}
		+Unicorn {
			<population = 0, number_of_legs = 4, vegetarian = true, skin = "fur">
		}
	}
	+Birds {
		<skin = "feather">
		+Hummingbird {
			<vegetarian = true, population = 2300000, number_of_legs = 2>
		}
		+Mockingbird {
			<vegetarian = false, population = 32000000, number_of_legs = 2>
		}
		+Unicorn {
			<population = 0, number_of_legs = 4, vegetarian = true, skin = "fur">
		}
	}
	+Reptiles {
		<vegetarian = false>
		+Turtle {
			<skin = "shell", population = 120000, number_of_legs = 4>
		}
		+Lizard {
			<skin = "dragon", population = 900000, number_of_legs = 4>
		}
		+Unicorn {
			<population = 0, number_of_legs = 4, vegetarian = true, skin = "fur">
		}
	}
}
```

Note how in this version the unicorn and lion is placed in the tree.

The above method only makes sense if we don't have any binary object (like
`TH1F`) inside our tree. In our case we only had tags. If you want to save and
load a TQFolder including its objects with

<!-- append load.py -->
```
animals.setName("animal_tree")
animals.writeToFile("tutorial.root")
reloaded = TQFolder.loadFolder("tutorial.root:animal_tree")
reloaded.printContents()
```

Of course, usually you will exit the python session and start a new one before
reloading the folder.

You can also open the `tutorial.root` file with ROOT and inspect it with `ls` or
a `TBrowser`. There should be an item called `animal_tree`. This is our TQFolder
inside the ROOT file.

<!-- Test above python lines. -->
<!-- console
```
$ python load.py
```
-->

## Tags
Loading and saving TQFolders is already cool, but we want to do more. For
example we want to read and write tags.

For example, assume we want to get the population of turtles programmatically,
we can retrieve the turtle folder and get the value of the `population` tag.
<!-- append load.py -->
```
turtle = animals.getFolder("Animals/Reptiles/Turtle")
population = turtle.getTagIntegerDefault("population", -1)
print population
```
The method `getTagIntegerDefault` returns the tag's value as an integer. If the
tag is not found, it returns the given default value, here `-1`. There are a
couple of other methods to retrieve string, booleans, lists (a.k.a. vector
tags), etc. Type `animals.getTag` and pres `Tab` to trigger the auto completion.
`getTagStandardStringDefault, getTagString, getTagStringDefault, getTagVBool,
getTagVDouble, getTagVInt, getTagVInteger, getTagAsString,
getTagVStandardString, getTagBool, getTagVString, getTagBoolDefault,
getTagDefault, getTagDouble, getTagDoubleDefault, getTagInteger,
getTagIntegerDefault, getTagList, getTagListLength`.

When using the `getTagIntegerDefault` method, we can't distinguish the cases
when the tag value is equal to the default, or the tag is non-existent. We check
whether a tag exists with

<!-- append load.py -->
```
print turtle.hasTag("population")
```
which in this case prints `True`.


To modify existing or add new tags, we can use the method `setTag("tagName",
"value")`. The type of
the tags is deduced form the value you give to the method. Assume we figured out
that the mammal type unicorn has only three legs. The following lines fix this
issue.

<!-- append load.py -->
```
mammal_unicorn = animals.getFolder("Animals/Mammals/Unicorn")
mammal_unicorn.setTag("number_of_legs", 3)
mammal_unicorn.printContents(":dt")
```

In the beginning, when we annotated the folders with tags, we attached some tags
to the parents. How does this now work out? Lets say we want to know the skin
typo of a rabbit. Is there a skin tag for the rabbit?

<!-- append load.py -->
```
rabbit = animals.getFolder("Animals/Mammals/Rabbit")
print rabbit.hasTag("skin")
```

The above snippet prints `False`. So the answer is no. We can, however, ask: *Is
there a skin tag for the rabbit or any of its parents. If yes, print its value.*

<!-- append load.py -->
```
if rabbit.hasTag("~skin"):
  print rabbit.getTagStringDefault("~skin", "")
```

Instead of using the exact tag name `skin`, we can prefix it with a tilde `~`
to get the tag at the folder or at any of its parents. The snippet above
therefore prints `fur`.

This works also the other way round. If you append a tilde to a tag name it will
search for the tag at the folder or at any of its children.

> Task: Unicorns have been spotted. Change the population of all unicorns to 1.

<!-- Test above python lines. -->
<!-- console
```
$ python load.py
```
-->
## Creating folders in python
<!-- console
```
$ cp base.py new_folder.py
```
-->

Besides manipulating tags programmatically, we can also manipulate TQFolders
itself within python. New TQFolders can be created via the constructor.

<!-- append new_folder.py -->
```
new_folder = TQFolder("new_folder")
animals.addFolder(new_folder)
```
<!-- Test above python lines. -->
<!-- console
```
$ python new_folder.py
```
-->

The above example creates a new TQFolder and adds it to the animals tree.

> Task: Add the eagle to the tree. Make sure that it has the usual tags:
  `number_of_legs`, `vegetarian`, `skin`, `population`. Some of its parent tags
  might be reusable.

## Patching the folder
In CAF, TQFolders are often *patched*. This means, that an other TQFolder
definition file is loaded in order to modify an existing TQFolder structure.
For example, this is  done after Monte Carlo samples have been initialized. This
allows the use to set tags or move/copy samples around.

Back to our example. Lets create a patch file called `patch.tqfolder`.

<!-- write patch.tqfolder -->
```
<population=2> @Animals/Mammals/Unicorn;
```

> Task: It has been discovered that there are exactly two unicorns of all types. Apply
  this modification using a patch file. Wildcards might make things easier.

> Task: Add the dog to the tree using a path file. Make sure that it has the usual tags:
  `number_of_legs`, `vegetarian`, `skin`, `population`. Some of its parent tags
  might be reusable.


# Advanced
So far, all the methods were static. The TQFolder syntax defines functions which
are executed once the folder is loaded. These function modify the tree structure
and influence the way the file is parsed. The function are particularly powerful
in a patch file. All functions start with a `$` sign followed by their name and
their arguments in parenthesis.

All the subsections in this chapter cover a single function. The chapters assume
that you have the following animals tree in the file
`animals_advanced.tqfolder`. Make sure that you restore this file at the
beginning of each section.

<!-- write animals_advanced.tqfolder -->
```
+Animals {
  +Mammals {
    <skin="fur">
    <vegetarian=false>
    +Rabbit {
      <vegetarian=true>
      <population=8.5e8>
    }
    +Cat {
      <population=6e8>
    }
    +Fox {
      <population=2.4e5>
    }
    +Hummingbird {
      <vegetarian=true>
      <population=2.3e6>
      <skin="feather">
    }
  }

  +Birds {
    +Mockingbird {
      <vegetarian=false>
      <population=3.2e7>
      <skin="feather">
    }
  }

  +Reptiles {
    <vegetarian=false>
    +Turtle {
      <skin="shell">
      <population=120000>
    }
    +Lizard {
      <skin="dragon">
      <population=9e5>
    }
  }
}
```

## $copy
The `copy` method lets you copy parts of the TQFolder tree to a new location.
The
function takes a single string argument containing the source and destination
path separated by `>>`.
Lets say we want to copy the hummingbird folder from the mammals to the
birds. Append the following command to the `animals_advanced.tqfolder` file.

<!-- console
```
$ cp animals_advanced.tqfolder copy.tqfolder
```
-->


<!-- append copy.tqfolder -->
```
$copy("Animals/Mammals/Hummingbird >> Animals/Birds");
```

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Copy"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('copy.tqfolder').printContents(':dtr2')"
```
-->

If we want to rename the folder on the fly, we can append `::NewName` to the
argument. Lets say, by mistake the folder named `Hummingbird` should represent
the pidgin instead, we could write

```
$copy("Animals/Mammals/Hummingbird >> Animals/Birds::Pidgin");
```

## $create
The `create` method creates a new `TQFolder` or `TQSampleFolder`. The function
takes the two named arguments `path` and `type`.  The type can be either "f" or
"folder" to create a `TQFolder`, or it can be "sf" or "samplefolder" to create a
`TQSampleFolder`. Parent folder are created automatically if missing.

```
$create(path="path/to/new/folder", type="f or sf");
```

> Task: Create a new TQFolder for the mammal zerba.

<!-- console
```
$ cp animals_advanced.tqfolder create.tqfolder
```
-->


<!-- append create.tqfolder
```
$create(path="Animals/Mammal/Zebra", type="f");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Create"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('create.tqfolder').printContents(':dtr2')"
```
-->


## $delete
The `delete` method lets you delete parts of the TQFolder. The `delete` method
takes a single argument specifying the folder. If the folder is not empty,
deleting it will fail. To delete non-empty folder  append `!` to the folder
name.

```
$delete("some/folder/with/children!");
```

> Task: We want to delete the hummingbird folder from the mammals.

<!-- console
```
$ cp animals_advanced.tqfolder delete.tqfolder
```
-->


<!-- append delete.tqfolder 
```
$delete("Animals/Mammals/Hummingbird!");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Delete"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('delete.tqfolder').printContents(':dtr2')"
```
-->


## $escape
The `escape` method is similar to ignore but takes an optional argument which
gives it the power of an if statement. Without the optional argument everything
in the current level of a sample folder is skipped.

<!-- write escape.tqfolder -->
```
+AA {
  +A {}
  $escape();
  +B {}
}
+BB {
  +C {}
}
```

The result of `escape` in this case is that `AA` contains only `A`. The folder
`BB` and `C` are unaffected by the usage of escape

<!-- console
```
$ echo "Escape"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('escape.tqfolder').printContents(':r2')"
```
-->

If the optional argument is used, the rest of the current folder level is
skipped when the TQFolder name matches the argument. Please note that optional
argument must not be put in quotes.

<!-- write escape.tqfolder -->
```
+AA {
  +A {}
  $escape(AA);
  +B {}
}
+BB {
  +C {}
  $escape(AA);
  +D {}
}
```
<!-- console
```
$ echo "Escape"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('escape.tqfolder').printContents(':r2')"
```
-->

The argument can be prefixed by an `!` which inverts the logic.

The real power of this command becomes obvious when it is combined with `for`
loops in which case the current  folder name is not hard coded but can be
different in each iteration.

## $for
The `for` command iteraters over numver in a given range. The syntax is as
follows:
```
$for(index, start, stop) { ... };
```

Here `index` is the running variable. The loop body (here `...`) is executed
with `index=start` until `index=stop-1`, so the stop value is not included.
Inside the loop body, the tag `$(index)` is available to use the running index.

> Task: Load the following example and print the structure to see if it looks like what
  you expect.

<!-- write for.tqfolder -->
```
+A {
  $for(i, 10, 20) {
    +B_$(i) {
        <tag=$(i)>
    }
  }
}
```

<!-- console
```
$ echo "For"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('for.tqfolder').printContents(':r2')"
```
-->

## $ignore
The `ignore` command functions as a block comment. It doesn't take any 
arguments. Everything wrapped in curly braces following the ignore command is
ignored. The block inside the curly braces is arbitrary, however you have to
make sure that the opening and closing curly braces match.

```
$ignore() {this here is never
executed}
```

> Task: Modify `animals_advanced.tqfolder` such that the hummingbird is ignored.

<!-- write ignore.tqfolder 
```
+Animals {
  +Mammals {
    <skin="fur">
    <vegetarian=false>
    +Rabbit {
      <vegetarian=true>
      <population=8.5e8>
    }
    +Cat {
      <population=6e8>
    }
    +Fox {
      <population=2.4e5>
    }
    $ignore() {
    +Hummingbird {
      <vegetarian=true>
      <population=2.3e6>
      <skin="feather">
    }
    }
  }

  +Birds {
    +Mockingbird {
      <vegetarian=false>
      <population=3.2e7>
      <skin="feather">
    }
  }

  +Reptiles {
    <vegetarian=false>
    +Turtle {
      <skin="shell">
      <population=120000>
    }
    +Lizard {
      <skin="dragon">
      <population=9e5>
    }
  }
}
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Ignore"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('ignore.tqfolder').printContents(':dtr2')"
```
-->


## $import
The `import` command allows you to import a TQFolder structure from a root file.
Assumed that you still have the `tutorial.root` from above, we could import this
the animal tree into a larger strucutre.

<!-- write import.tqfolder -->
```
+BiologicalTaxonomy {
  $import("tutorial.root:animal_tree");
}
```
<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "import"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('import.tqfolder').printContents(':dtr2')"
```
-->

## $include
The `include` command is similar to the `import` function. The `include` command
allows you to include a TQFolder structure from a text
file as if the file's content is copy-pasted into the TQFolder
defintion. The syntax for of the function is:

```
$include("path_to.file");
```

> Task: A colleque wants to contribute to the animal tree and wrote the
  definition of a horse. Save the following snipped to the file `horse.tqfolder`
  and import it in the Mammals folder.

<!-- write horse.tqfolder -->
```
+Horse {
    <vegetarian=true, population=3300000, number_of_legs=4>
}
```

<!-- write include.tqfolder 
```
$include("horse.tqfolder");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Include"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('include.tqfolder').printContents(':dtr2')"
```
-->



## $modify
The `modify` command is able to modify existing tags. The following table
summarizes the argumets of `modify`. The arguments `tag`, `operator` and `value`
are mandatory.

| Argument | Description |
|----------|-------------|
| `tag`    | The name of the tag which should be modified. |
| `operator` | Can be either of `+-*/=`. This determines the operation the is performed between the existing tag value and the one specfied by the `value` arugment " 
| `value` | The value use with the operater and the tag's value. |
| `path`  | Path to the sample folder which on which the modifiction should be performed. |
| `filter` | The optinal argument tag be `s` or `sf` to limit the application to sample or sample folders, respectively. |
| `create` | If `true`, creates the tag if non-existant. Existing tags are not touched. |
| `override` | If `true` and `create=true`, creates tag if non-existant, existing tags are overwritten. |
| `force` | Can be used if you want to overwrite the type of an existing tag. |

> Task: The definition of legs have been changed. A the number of legs should be
  the number of legs at one side of the animal. This means a dog has two legs,
  an eagle has one leg. Use the `filter` method to apply this change.

<!-- console
```
$ cp animals_advanced.tqfolder modify.tqfolder
```
-->


<!-- append modify.tqfolder 
```
$modify(target="*", value=0.5, operator="*", tag="number_of_legs");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Modify"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('modify.tqfolder').printContents(':dtr2')"
```
-->


## $move
The `move` method lets you move parts of the TQFolder tree to a new location.
The syntax of `move` is identical to `copy`.

> Task: We want to move the hummingbird folder from the mammals to the
  birds.

<!-- console
```
$ cp animals_advanced.tqfolder move.tqfolder
```
-->


<!-- append move.tqfolder 
```
$move("Animals/Mammals/Hummingbird>>Animals/Birds");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Move"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('move.tqfolder').printContents(':dtr2')"
```
-->

## $print
The print method is similar to the `printContents` method. It is executed on the
TQFOlder where it is written with all the folders defined so far. The print
methkd takes an optional argument. The optional argument specifies the print
options (the part after the `:` on `printContents`), for example `d`, `t` or
`r1` , `r2`, ...

For example, the following snipped print the `AA` folder before `B` is added. 

<!-- write print.tqfolder -->
```
+AA {
  +A {}
  $print();
  +B {}
}
```

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Print"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('print.tqfolder')"
```
-->

> Task: Add a `print` statement such that the animals folder is printed before
  the reptiles are added. The printout should contain all tags an all sub
  folders.

## $printline
The `printline` function print its argument when the text file is loaded. This
is useful for debugging complex TQFolder definitions.

<!-- write printline.tqfolder -->
```
+AA {
  $printline("Building AA");
  +A {}
  $printline("Done buildig AA");
}
```

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Printline"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('printline.tqfolder')"
```
-->

## $replace

The `replace` method lets you expend the `$(tagName)` placeholders inside the
tag strings. For example, if we have a tag
```
<habitat="Lives in $(location)">
```
which uses another tag `location` inside a tag, `replace` can be used to
replace `$(location)` with a string.

The functions tags a positions argument which determines which tags should be
replaced where. It consists of a folder filter string and a tag filter string
separated by a colon. If the first argument is `"*:*"`, the replacement is
applied to all folders an all tags. The first argument is followed by an
arbitrary number of named arguments which are the key-value pairs for the
substitution.

```
$replace("folterFilter:tagFilter", tag1="value", tag2="value", ...);
```

> Task: Add the above habitat tag to all animals and use `replace` to set the
  following locations: Mammals -> Geneva, Birds -> R1, Reptiles -> Australia.

<!-- write replace.tqfolder
```
+Animals {
  +Mammals {
    +Rabbit {
      <habitat="Lives in $(location)">
    }
    +Cat {
      <habitat="Lives in $(location)">
    }
  }
  +Birds {
    +Mockingbird {
      <skin="feather">
      <habitat="Lives in $(location)">
    }
  }
}
$replace("*/Mammals/*:*", location="Geneva");
$replace("*/Birds/*:*", location="R1");
```
-->

<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Replace"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('replace.tqfolder').printContents(':dtr4')"
```
-->

## $write
The `write` command lets your write parts of the TQFolder tree to a text file.
The method takes the mandatory argument `filename` which is the text file
destination. The optional argument `target` is the path to the TQFolder you
would like to export. If this is omitted, the current folder is exported.

The following example illustrates how to export the mammals folder.

<!-- write write.tqfolder  -->
```
+Animals {
  +Mammals {
    <skin="fur">
    <vegetarian=false>
    +Rabbit {
      <vegetarian=true>
      <population=8.5e8>
    }
    +Cat {
      <population=6e8>
    }
  }
  $write(filename="write_out.txt");

  +Birds {
    +Mockingbird {
      <vegetarian=false>
      <population=3.2e7>
      <skin="feather">
    }
  }
}
```
<!-- Check that the syntax above is correct. -->
<!-- console
```
$ echo "Write"
$ python -c "import QFramework; QFramework.TQFolder.loadFromTextFile('write.tqfolder')"
```
-->

After loading the folder the file `write_out.txt` contains all mammals.

<!-- console_output -->
```
$ cat write_out.txt
# -*- mode: tqfolder -*-
+Mammals {
	<skin = "fur", vegetarian = false>
	+Rabbit {
		<vegetarian = true, population = 850000000>
	}
	+Cat {
		<population = 600000000>
	}
}
```
