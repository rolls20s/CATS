#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

using std::cout;
using std::endl;
using std::string;
using std::cerr;

// ToDo: Put into a config file or command arguments
/** Static definitions ****************************/
#define LOG_LOCATION "./cats.log"                   // Location of log file
#define DEST_PATH "./"                              // Destination for files
/**************************************************/


/* Prototypes */
/******************************************************
Output to log.

string log_message: Contains message log

char log_type: Identifies type of message:

            i - information
            e - error
            f - fatal error
******************************************************/
void log_msg( const std::string&, const char& );





