#include "parser.h"

/************************************
Opens source directory

string source_path: path to
source data directory
*************************************/
Parser::Parser( string s_p )
{
    source_path = s_p;
    source_dir = NULL;
    entry = NULL;

    log_msg( "Opening directory " + string( source_path ), 'i' );

    source_dir = opendir( source_path.c_str() );

    if( source_dir == NULL )
    {
        perror("Problem opening source directory");
        log_msg( "Problem opening source directory", 'e' );
        exit( 1 );
    }
}

// Destructor
Parser::~Parser()
{
    log_msg( "Closing directory " + string( source_path ), 'i' );
    closedir( source_dir );
    source_dir = NULL;
    entry = NULL;
}

/******************************************
Begin the parsing process and return status
*******************************************/
int Parser::parse_data()
{
    int ret_val = -1;

    ret_val = read_directory();

    return ret_val;
}

/****************************************
Read in files and call file open function
*****************************************/
int Parser::read_directory()
{
    int status;
    struct stat st_buf;


    while( ( entry = readdir( source_dir ) ) != NULL )
    {
        if( ( string( entry->d_name ) != "..") && ( string( entry->d_name ) != "." ) )
        {
            /***** Differentiate directories and files *****/
            status = -1;

            string curr_file_path = source_path + string( entry->d_name );

            status = stat( curr_file_path.c_str(), &st_buf );
            if( status != 0 )
            {
                perror( "Problem getting file status" );
                log_msg( "Problem getting file status", 'e' );
                return -1;
            }
            /***********************************************/

            if( S_ISDIR( st_buf.st_mode ) ) // If entry is a directory
            {
                log_msg( "Found directory: " + curr_file_path, 'i' );

                // ToDo: descend into directories and facilitate replication of directory tree in output.
            }
            else // Entry is a file
            {


                // ToDo: Pass over unsupported file types


                /****** Parse  file ***********************************/
                int ret_val = -1;

                ret_val = open_file( curr_file_path );
                if( ret_val != 0 )
                {
                    log_msg( "Problem parsing " + curr_file_path, 'e' );
                }
                /******************************************************/
            }
        }
    }

    return 0;
}

/*******************************************
Parse file and call appropriate
sanitization routines

string file_name: full path of file to parse
********************************************/
int Parser::open_file( string file_name )
{
    int ret_val;
    int line_num = 1; // File line #'s start from 1
    string ln; // For converting line_num
    string line; // Holds current line

    std::ifstream curr_file;

    log_msg( "Opening file " + file_name, 'i' );

    /** Open file **/
    curr_file.open( file_name.c_str() );
    if( !curr_file.is_open() )
    {
        log_msg( "Unable to open " + file_name, 'e');
        return -1;
    }

    /***** Read file in by line *****/
    while( curr_file.good() )
    {
        std::getline( curr_file, line ); // Get next line

        ln = boost::lexical_cast<string>( line_num ); // Convert int to string
        log_msg( "Processing line " + ln + " of file " + file_name, 'i' );

        ret_val = parse_line( line ); // Call parser

        if( ret_val != 0 )
        {
            log_msg( "Problem parsing line " + ln, 'e' );
            return -1;
        }

        line_num++; // Increment line #
    }
    /********************************/


    /** Close file **/
    log_msg( "Closing file " + file_name, 'i' );
    curr_file.close(); // close file

    return 0;
}

int Parser::parse_line( string curr_line )
{

    // ToDo: parse line and call replacement functions


    cout << curr_line << endl;
    return 0;
}
