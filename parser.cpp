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
        exit( 1 );
    }

    while( ( entry = readdir( source_dir ) ) != NULL )
    {
        if( ( std::string( entry->d_name ) != "..") && ( std::string( entry->d_name ) != "." ) )
        {
            std::cout << entry->d_name << "\n";
        }
    }
}


Parser::~Parser()
{
    closedir( source_dir );
}
