#include "parser.h"

/************************************
Opens source directory and begins
reading in files.

const char *source_path: path to
source data directory
*************************************/
Parser::Parser( string s_p )
{
    source_path = s_p;
    source_dir = NULL;
    entry = NULL;

    source_dir = opendir( source_path.c_str() );

    if( source_dir == NULL )
    {
        perror("Problem opening source directory");
        log_msg( "Problem opening source directory", 'e' );
        exit( 1 );
    }
}


Parser::~Parser()
{
    closedir( source_dir );
    source_dir = NULL;
    entry = NULL;
}


int Parser::read_files()
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
                return 1;
            }
            /***********************************************/

            if( S_ISDIR( st_buf.st_mode ) ) // If entry is a directory
            {
                log_msg( "Found directory: " + curr_file_path, 'i' );

                // ToDo: descend into directories and facilitate replication of directory tree in output.
            }
            else // Entry is a file
            {
                log_msg( "Opening file " + curr_file_path, 'i');

                int ret_val = -1;
                ret_val = parse_file( curr_file_path );

                if( ret_val != 0 )
                {
                    log_msg( "Problem parsing " + curr_file_path, 'e' );
                }
            }
        }
    }

    return 0;
}

int Parser::parse_file( string )
{

    return 0;
}



