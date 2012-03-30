# This is the README file for CATS. It will have information how to use cats. For now, it contains dev info.


Run "cats --help" for usage info.

At this point, the program takes an input argument of the source directory through the --source flag. 
It opens this directory and reads in the filenames.  Next step is to pass these to a parsing function
that will decide what needs to be changed.  That will be followed by the individual change functions.

Some config options are (and will) be temporarily hardcoded in main.h.  Try to keep them there so we
can later whittle them down by designating them to a config file and/or command arguments.






