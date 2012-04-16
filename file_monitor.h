/****************************************************
Monitors a directory of files for changes and passes
files to parser functions.
*****************************************************/

#include <sys/inotify.h>

/* Up to 512 concurrent events */
#define BUFF_SIZE ( 512 * ( sizeof( struct inotify_event ) + FILENAME_MAX ) )

void process_event( int fd, string target )
{
    ssize_t len, i = 0;

    char buf[BUFF_SIZE] = {0};

    len = read( fd, buf, BUFF_SIZE );
    if( len < 0 )
    {
        if( errno == EINTR )
        {
            /* need to reissue system call */
        }
        else
        {
            //log_msg( "Problem reading dir" + strerror(errno), 'f' );
            exit(1);
        }
    }

    // Get events
    while( i < len )
    {
        struct inotify_event *new_event = ( struct inotify_event * )&buf[i];
        string action;

        if( new_event->len )
        {
            action = new_event->name;
        }
        else
        {
            action = target;
        }


        // Created/Modified
        if( new_event->mask &IN_CREATE )
            action += " created in watched directory";
        if( new_event->mask &IN_MODIFY )
            action += " was modified";
        if( new_event->mask &IN_MOVED_TO )
            action += " moved into watched directory";

        // Deleted/Moved
        if( new_event->mask &IN_DELETE )
            action += " deleted from watched directory";
        if( new_event->mask &IN_DELETE_SELF )
            action += " watched file/directory was itself deleted";
        if( new_event->mask &IN_MOVED_FROM )
            action += " moved out of watched directory";

        cout << action << endl;

        i += ( sizeof( struct inotify_event ) + new_event->len );
    }

}
