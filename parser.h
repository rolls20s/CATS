#include <dirent.h> // Read directories
#include <vector>
#include <map>

/***** Boost libraries *****/
#include <boost/regex.hpp> // Regular expressions
#include <boost/lexical_cast.hpp>
/***************************/

/***** Parsing Modules *****/
#include "modules.h"

#include "Modules/module_ssn_usa.h"     // US Social Security Numbers
#include "Modules/module_phone_usa.h"   // US Telephone Numbers
#include "Modules/module_addr_usa.h"    // US Addresses
#include "Modules/module_dob.h"         // Birthdates
#include "Modules/module_ccn.h"         // Credit Card Numbers
#include "Modules/module_email.h"       // Email Addresses
/***************************/

#define OK 0
#define FAIL -1;

class Parser
{
  public:

    string source_path;

    DIR *source_dir;
    struct dirent *entry;

    Parser( const string& );   // constructor
    ~Parser();  // destructor
    int parse_data(); // Inital call to start things rolling

  private:

    std::vector<replacement> replacements; // Init replacement set

    int read_directory(); // Iterate through files in a directory
    int open_file( const string& ); // Iterate through lines in a file
    int parse_line( string& ); // Call modules to scan each line and return a stucture containing the changes to make
    int write_line( string&, const string& ); // Modify the line based on the structure and write it out to a new file
};



