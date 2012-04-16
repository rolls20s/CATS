#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>

using std::cout;
using std::endl;
using std::string;
using std::cerr;

// ToDo: Put into a config file or command arguments
/** Static definitions ****************************/
#define LOG_LOCATION "./cats.log"                   // Location of log file
//#define OUTPUT_LOCATION "./OUTPUT/"                 // Destination for files
/**************************************************/

#include "helpers.cpp"
#include "parser.h"
#include "file_monitor.h"
