#include "main.h"
#include "helpers.cpp"
#include "parser.cpp"


int main( int arg_count, char *args[])
{
    /** Initialize log **/
    init_log();

    int err_code = 0;
    string source_path; // Holds path to source data

    /******* Process command-line arguments *******/
    err_code = get_args( arg_count, args, source_path );

    if( err_code != 0 )
    {
        return err_code; // Problem
    }
    /**********************************************/

    log_msg( "Source path: " + source_path, 'i' );

    /******* Process contents of source path ******/
    Parser myParser( source_path );
    if( myParser.parse_data() != OK )
    {
        log_msg( "Problem parsing data", 'f' );
        return FAIL;
    }
    /**********************************************/

    return 0;
}
