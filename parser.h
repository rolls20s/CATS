#include <dirent.h> // Read directories

/***** Boost libraries *****/
#include <boost/regex.hpp> // Regular expressions
#include <boost/lexical_cast.hpp>
/***************************/

/***** Parsing Modules *****/
#include "module_ssn_usa.h"     // US Social Security Numbers
#include "module_phone_usa.h"   // US Telephone Numbers
#include "module_addr_usa.h"    // US Addresses
#include "module_dob.h"         // US Telephone Numbers
#include "module_ccn.h"
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

    int read_directory(); // Iterate through files in a directory
    int open_file( const string& ); // Iterate through lines in a file
    int parse_line( string& ); // Parse each line and call modification procedures
};



