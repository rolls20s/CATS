#include <dirent.h> // Read directories
#include <regex> // Regular expressions
#include <boost/lexical_cast.hpp>

class Parser
{
  public:

    string source_path;

    DIR *source_dir;
    struct dirent *entry;


    Parser( string );   // constructor
    ~Parser();  // destructor
    int parse_data(); // Inital call to start things rolling

  private:

    int read_directory(); // Iterate through files in a directory
    int open_file( string ); // Iterate through lines in a file
    int parse_line( string ); // Parse each line and call modification procedures


    /* Modification procedures */

    // SSN

    // Phone number

    // Address

    // Etc.

};



