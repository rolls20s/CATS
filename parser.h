#include <dirent.h> // directory header


class Parser
{
  public:

    string source_path;

    DIR *source_dir;
    struct dirent *entry;

    /************************************
    Opens source directory and begins
    reading in files.

    const char *source_path: path to
    source data directory
    *************************************/
    Parser( string );   // constructor

    ~Parser();  // destructor

    int read_files();

  private:

    /**********************************
    Reads in file and calls various
    parsing procedures.

    const char *filename: file to parse
    ***********************************/
    int parse_file( string );


    /* Parsing Procedures*/

};



