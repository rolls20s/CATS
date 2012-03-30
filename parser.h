#include <dirent.h> // directory header


class Parser
{
  public:

    DIR *source_dir;
    struct dirent *entry;

    /************************************
    Opens source directory and begins
    reading in files.

    const char *source_path: path to
    source data directory
    *************************************/
    Parser( const char* );   // constructor

    ~Parser();  // destructor

    int read_files();

  private:

    /**********************************
    Reads in file and calls various
    parsing procedures.

    const char *filename: file to parse
    ***********************************/
    int parse_file( const char* );


    /* Parsing Procedures*/

};



