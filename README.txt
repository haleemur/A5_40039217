COMP 5421: Assignment 5

Haleemur Ali (40039217)

=======================


Platform Compatibility
======================

The program has been tested on Mac OSX & Windows 10.


compilation instructions (Mac OSX / Linux)

==========================================


note: must have cmake available in the path

browse to the application source folder

browse to the subdirectory build which already contains the `input.txt` test file
execute the following commands on the terminal

```
cmake ..

make

```

from the build directory execute the following terminal command.

this will run a program script testing the different functions
* is_palindrome
* second_max
* print_word_frequency_1
* print_word_frequency_2
* print_word_index


```

./A5_40039217

```

compilation & run instruction (Windows + MSVS)
==============================================

MSVS 2017: MSVS 2017 supports cmake as a build system

open the folder containing the project
Choose Top Menu >> CMake >> Build All
Then Choose Top Menu >> CMake >> Debug >> A5_40039217

Prior Versions of MSVS: Does not support CMake
Import the project, build the solution and run taking care to put the
`input.txt` file in the same directory as the executable.