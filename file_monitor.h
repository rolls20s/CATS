/****************************************************
Monitors a directory of files for changes and passes
files to parser functions.
*****************************************************/
#include <sys/inotify.h>

#ifndef _FILE_MON
#define _FILE_MON

/* Up to 512 concurrent events */
#define BUFF_SIZE ( 512 * ( sizeof( struct inotify_event ) + FILENAME_MAX ) )

void process_event( int fd, string target, Parser &myParser )
{
    string event_desc;

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
        string file_name;

        if( new_event->len )
        {
            file_name = new_event->name;
        }
        else
        {
            file_name = "";
        }

        string out_path = string( OUTPUT_LOCATION ) + file_name;


        // Created/Modified
        if( ( new_event->mask &IN_CREATE ) || ( new_event->mask &IN_MOVED_TO ) || ( new_event->mask &IN_MODIFY ) )
        {
            myParser.open_file( target + file_name, file_name );
            event_desc = out_path + " created or modified.";
        }

        // Deleted/Moved
        if( ( new_event->mask &IN_MOVED_FROM ) || ( new_event->mask &IN_DELETE_SELF ) || ( new_event->mask &IN_DELETE ) )
        {
            remove( out_path.c_str() );
            event_desc = out_path + " removed.";
        }

        // Log activity
        log_msg( event_desc, 'i');

        i += ( sizeof( struct inotify_event ) + new_event->len );
    }

}

#endif
