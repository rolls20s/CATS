#include "main.h"



int main( int arg_count, char *args[])
{
    string user_input;

    /** Initialize log **/
    init_log();

    int err_code = 0;
    string source_path; // Holds path to source data

    /******* Process command-line arguments ****************/
    err_code = get_args( arg_count, args, source_path );

    if( err_code != 0 )
    {
        return err_code; // Problem
    }
    /*******************************************************/

    log_msg( "Source path: " + source_path, 'i' );

    /******* Process existing contents of source path ******/
    Parser myParser( source_path );
    if( myParser.parse_data() != OK )
    {
        log_msg( "Problem parsing data", 'f' );
        return FAIL;
    }
    /*******************************************************/

    /******* Monitor source path for changes ***************/
    int fd = inotify_init();
    if( fd < 0 )
    {
        // log_msg( "Problem monitoring directory: " + strerror(errno), 'f' );
        return 1;
    }

    // Watch the source directory
    int wd = inotify_add_watch( fd, source_path.c_str(), IN_CREATE | IN_MODIFY | IN_MOVED_TO | IN_DELETE | IN_DELETE_SELF | IN_MOVED_FROM  );
    if( wd < 0 )
    {
        // log_msg( "Problem monitoring directory: " + strerror(errno), 'f' );
        return 1;
    }
    /*******************************************************/

    /********** Get changes from file descriptor ***********/
    struct timeval time;
    fd_set rfds;
    int ret;

    while(1)
    {
        /* timeout after five seconds */
        time.tv_sec = 5;
        time.tv_usec = 0;

        /* zero-out the fd_set */
        FD_ZERO( &rfds );

        FD_SET( fileno( stdin ), &rfds );

        // Add inotify fd to the fd_set
        FD_SET( fd, &rfds );


        // Select() fd's
        ret = select( fd + 1, &rfds, NULL, NULL, &time );
        if( ret < 0 )
        {
                // Something wrong
                perror ("select");
        }
        else if( FD_ISSET( fd, &rfds ) )
        {
            // Get event
            process_event( fd, source_path, myParser );
        }
        else if( FD_ISSET( fileno( stdin ), &rfds ) )
        {
            std::cin >> user_input;
            if( user_input == "q" )
            {
                break;
            }
        }
        else
        {
            /* timed out! */
        }
    }

    close( fd ); // Shutdown inotify
    /********************************************************/

    log_msg( "Exiting...", 'i' );

    return 0;
}
