#include <sstream>
#include <cstdlib>
#include <time.h>

#define OK 0
#define FAIL -1

std::map<string, string> repl_map; // Keeps consistent replacements

/*** Structure for replacement data *********/
struct replacement
{
    int begin_pos;  // position in line where replacement starts
    int end_pos;    // position in line where replacement ends

    string value;   // replacement value
};
/********************************************/

/***************************/
// module_email.h
#define DOMAIN_LIST "domains"

// module_names_regionless.h
#define FN_FILE "firstnames"
#define LN_FILE "lastnames"
/***************************/

using std::stringstream;


// Declared here so we don't reload for every name replacement
std::vector<string> fn_list; // Holds first/middle names
std::vector<string> ln_list; // Holds last names
