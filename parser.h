#include <dirent.h> // Read directories
#include <boost/lexical_cast.hpp>
#include"module_ssn_usa.h"

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


    /* Modification procedures */

    // Scans for birthdates in multiple formats
    int scan_dob( string& );

    // Scans for valid US Social Security Numbers
    int scan_ssn_usa( string& );

    // Scans for valid US Telephone Numbers
    int scan_phone_usa( string& );

    // Scans for components of US addresses
    int scan_address_usa( string& );

    // Scan for Credit Card Numbers in multiple formats
    int scan_ccn( string& );

};



