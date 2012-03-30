#include "parser.h"

/************************************
Opens source directory and begins
reading in files.

const char *source_path: path to
source data directory
*************************************/
Parser::Parser( const char *source_path )
{
    source_dir = NULL;
    entry = NULL;

    source_dir = opendir( source_path );

    if( source_dir == NULL )
    {
        perror("Error opening source directory");
        log_msg( "Error opening source directory", 'e' );
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
    while( ( entry = readdir( source_dir ) ) != NULL )
    {
        if( ( string( entry->d_name ) != "..") && ( string( entry->d_name ) != "." ) )
        {
            cout << entry->d_name << "\n";
        }
    }

    return 0;
}

