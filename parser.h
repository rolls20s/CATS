#include <dirent.h> // Read directories
#include <sys/stat.h>
#include <sys/types.h>

#include <vector>
#include <map>

/***** Boost libraries *****/
#include <boost/regex.hpp> // Regular expressions
#include <boost/lexical_cast.hpp>
/***************************/

/***** Parsing Modules *****/
#include "modules.h"

#include "Modules/module_names_regionless.h" // Names - not region specific, best for "western" applications
#include "Modules/module_ssn_usa.h"     // US Social Security Numbers
#include "Modules/module_phone_usa.h"   // US Telephone Numbers
#include "Modules/module_addr_usa.h"    // US Addresses
#include "Modules/module_dob.h"         // Birthdates
#include "Modules/module_ccn.h"         // Credit Card Numbers
#include "Modules/module_email.h"       // Email Addresses
/***************************/

#define OK 0
#define FAIL -1

class Parser
{
  public:

    DIR *source_dir;
    struct dirent *entry;

    //DIR *dest_dir;

    Parser( const string&, const string& );   // constructor
    ~Parser();  // destructor
    int parse_data(); // Inital call to start things rolling
    int open_file( const string&, const string& ); // Iterate through lines in a file

  private:

    string source_path;
    string output_location;

    std::vector<replacement> replacements; // Init replacement set

    int read_directory(); // Iterate through files in a directory
    int parse_line( string& ); // Call modules to scan each line and return a stucture containing the changes to make
    int write_line( string&, const string& ); // Modify the line based on the structure and write it out to a new file
};

#include "parser.cpp"
