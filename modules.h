#include <sstream>
#include <cstdlib>
#include <time.h>

std::map<string, string> repl_map; // Keeps consistent replacements

/*** Structure for replacement data *********/
struct replacement
{
    int begin_pos;  // position in line where replacement starts
    int end_pos;    // position in line where replacement ends

    string value;   // replacement value
};
/********************************************/

using std::stringstream;
