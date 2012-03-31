# This is the README file for CATS. It will have information how to use cats. For now, it contains dev info.


Compiling: I'm using Code::Blocks, so I generated a Makefile using a utility that turns Code::Blocks 
projects into Makefiles.  Tested on my machine - works.  You may have to modify some parameters, like
where your boost libraries are located. You can easily make your own simpler Makefile, just make sure
to keep the compile flags as well as link the appropriate boost libraries (found in the Makefile or 
the code headers).


Running: Run "cats --help" for usage info.



At this point, the program takes an input argument of the source directory through the --source flag. 
It opens that directory and reads in the filenames.  It then reads in each file and each line of each
file and passes the line to a parsing function.  

ToDo: Have parsing function identify data to replace, and call appropriate modifier procedures. (also correlate data w/ some data structure(s) ).

The program also outputs information and errors to a log file. See log_msg() in helpers.cpp for more info on 
how to use it.

Some config options are (and will) be temporarily hardcoded in main.h.  Try to keep them there so we
can later whittle them down by designating them to a config file and/or command arguments.






