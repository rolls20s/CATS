#include "main.h"
#include <termios.h>



int main( int arg_count, char *args[])
{
    string user_input;

    /** Initialize log **/
    init_log();

    int err_code = 0;
    string source_path; // Holds path to source data
    string dest_path;   // Holds path to destination

    /******* Process command-line arguments ****************/
    err_code = get_args( arg_count, args, source_path, dest_path );

    if( err_code != 0 )
    {
        return err_code; // Problem
    }
    /*******************************************************/

//    log_msg( "Source path: " + source_path, 'i' );
//    log_msg( "Destination path: " + dest_path, 'i' );

    /******* Process existing contents of source path ******/
    Parser myParser( source_path, dest_path );
    if( myParser.parse_data( source_path, dest_path ) != OK )
    {
        log_msg( "Problem parsing data", 'f' );
        return FAIL;
    }
    /*******************************************************/

    //cout << "q[RETURN] to quit" << endl;

    /******* Monitor source path for changes ***************/
    int fd = inotify_init();
    if( fd < 0 )
    {
        // log_msg( "Problem monitoring directory: " + strerror(errno), 'f' );
        return FAIL;
    }

    // Watch the source directory
    int wd = inotify_add_watch( fd, source_path.c_str(), IN_CREATE | IN_MODIFY | IN_MOVED_TO | IN_DELETE | IN_DELETE_SELF | IN_MOVED_FROM  );
    if( wd < 0 )
    {
        // log_msg( "Problem monitoring directory: " + strerror(errno), 'f' );
        return FAIL;
    }
    else
    {
        log_msg( "Initial processing complete. Now monitoring directory: " + source_path, 'i' );
    }
    /*******************************************************/

    /********* Set terminal options *********/
    struct termios ttystate, ttysave;

    if(INTERACTIVE)
    {
        // Get the terminal state
        tcgetattr(STDIN_FILENO, &ttystate);
        ttysave = ttystate;
        // Turn off canonical mode and echo
        ttystate.c_lflag &= ~(ICANON | ECHO);

        // Minimum input.
        ttystate.c_cc[VMIN] = 1;

        // Set the terminal attributes.
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }
    /****************************************/


    /********** Get changes from file descriptor ***********/
    struct timeval time;
    fd_set rfds;
    int ret;

    if(INTERACTIVE)
    {
        cout << "\'q\' to quit> "; // give prompt
        fflush( stdout );
    }

    while( 1 )
    {
        /* timeout after five seconds */
        time.tv_sec = 5;
        time.tv_usec = 0;

        /* zero-out the fd_set */
        FD_ZERO( &rfds );

        if(INTERACTIVE)
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
            if(INTERACTIVE)
                cout << endl; // Drop below the prompt.

            // Get event
            process_event( fd, source_path, dest_path, myParser, false );

            if(INTERACTIVE)
            {
                cout << "\'q\' to quit> "; // reprompt
                fflush( stdout );
            }
        }
        else if( FD_ISSET( fileno( stdin ), &rfds ) )
        {
            if(INTERACTIVE)
            {
                int c = fgetc( stdin ); // get char

                if( c == 'q' ) // quit
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

    // Set the terminal attributes.
    if(INTERACTIVE)
    {
        ttystate.c_lflag |= ICANON | ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

    log_msg( "Exiting...", 'i' );

    return 0;
}
