#include "parser.h"

/************************************
Opens source directory

const string s_p: path to source data
*************************************/
Parser::Parser( const string &s_p )
{
    /** Open directory **/
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
    int ret_val = FAIL;

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

    cout << "***** Begin debug output *****" << endl;

    while( ( entry = readdir( source_dir ) ) != NULL )
    {
        if( ( string( entry->d_name ) != "..") && ( string( entry->d_name ) != "." ) )
        {
            /***** Differentiate directories and files *****/
            status = FAIL;

            string curr_file_path = source_path + string( entry->d_name );

            status = stat( curr_file_path.c_str(), &st_buf );
            if( status != OK )
            {
                perror( "Problem getting file status" );
                log_msg( "Problem getting file status", 'e' );
                return FAIL;
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
                int ret_val = FAIL;

                ret_val = open_file( curr_file_path );
                if( ret_val != OK )
                {
                    log_msg( "Problem parsing " + curr_file_path, 'e' );
                }
                /******************************************************/
            }
        }
    }

    cout << "***** End debug output *****" << endl;


    return OK;
}

/********************************************
Open file and call parse_line() on each line

const string &file_name: full path of file
*********************************************/
int Parser::open_file( const string &file_name )
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
        return FAIL;
    }

    /***** Read file in by line *****/
    while( curr_file.good() )
    {
        std::getline( curr_file, line ); // Get next line

        ln = boost::lexical_cast<string>( line_num ); // Convert int to string
        log_msg( "Processing line " + ln + " of file " + file_name, 'i' );

        ret_val = parse_line( line ); // Call parser

        if( ret_val != OK )
        {
            log_msg( "Problem parsing line " + ln, 'e' );
            return FAIL;
        }

        // Debug
        for(unsigned int i=0;i<replacements.size();i++)
        {
            cout << replacements[i].value << endl;
        }

        replacements.clear();

        line_num++; // Increment line #
    }
    /********************************/


    /** Close file **/
    log_msg( "Closing file " + file_name, 'i' );
    curr_file.close(); // close file

    return OK;
}

/***********************************************
Calls various modules to scan for and change the
input.

const string &curr_line: line of data to parse
************************************************/
int Parser::parse_line( string &curr_line )
{
    /**********************************************************************
     All modules should follow the same format.

    The module should take up to two parameters:

        1)  A string containing the line to modify.
        2)  A vector container of type "replacement"
        3)  (optionally) A "step" integer value, for tracking multiple lines
            The value should start from 0 and increase.

            For instance, an address module might have to deal with
            several lines. The module would be designed to look for a
            certain kind of line based on if a possible address line
            was previously found.  If a corresponding match isn't found
            on subsequent steps, the module should return an indicator
            that tells the parser to discard the last n lines where n is
            the current step number.
    ***********************************************************************/

    // Parse US Social Security Numbers
    module_ssn_usa ssn_parser;
    ssn_parser.scan( curr_line, replacements );

    // Parse US Telephone Numbers
    module_phone_usa phone_parser;
    phone_parser.scan( curr_line, replacements );

    // Parse birthdates
    module_dob dob_parser;
    dob_parser.scan( curr_line, replacements );

    // Parse Credit Card Numbers
    module_ccn ccn_parser;
    ccn_parser.scan( curr_line, replacements );

    // Parse email addresses
    module_email email_parser;
    email_parser.scan( curr_line, replacements );

    // Parse US addresses
//    module_addr_usa addr_parser;
//    addr_parser.scan( curr_line, replacements, line_step );

    return OK;
}
