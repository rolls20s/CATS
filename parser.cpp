#include "parser.h"

/************************************
Opens source directory

const string s_p: path to source data
*************************************/
Parser::Parser( const string &s_p )
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

        line_num++; // Increment line #
    }
    /********************************/


    /** Close file **/
    log_msg( "Closing file " + file_name, 'i' );
    curr_file.close(); // close file

    return OK;
}

/***********************************************
Calls various functions to change and return
the input.

const string &curr_line: line of data to parse
************************************************/
int Parser::parse_line( string &curr_line )
{
    // Scan for valid US Social Security Numbers
    module_ssn_usa ssn_scanner;
    ssn_scanner.scan( curr_line );


    // Scans for birthdates in multiple formats
    scan_dob( curr_line );

    // Scans for valid US Telephone Numbers
    scan_phone_usa( curr_line );

    // Scans for components of US addresses
    scan_address_usa( curr_line );

    // Scan for Credit Card Numbers in multiple formats
    scan_ccn( curr_line );

    //cout << curr_line << endl;
    return OK;
}


/***** Begin scanners *****/

// Scans for birthdates in multiple formats
int Parser::scan_dob( string &curr_line )
{
    return OK;
}

// Scans for valid US Telephone Numbers
int Parser::scan_phone_usa( string &curr_line )
{
    return OK;
}

// Scans for components of US addresses
int Parser::scan_address_usa( string &curr_line )
{
    return OK;
}

// Scan for Credit Card Numbers in multiple formats
int Parser::scan_ccn( string &curr_line )
{
    return OK;
}
