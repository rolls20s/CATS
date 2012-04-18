/****************************************************
Monitors a directory of files for changes and passes
files to parser functions.
*****************************************************/
#include <sys/inotify.h>

#ifndef _FILE_MON
#define _FILE_MON

/* Up to 512 concurrent events */
#define BUFF_SIZE ( 512 * ( sizeof( struct inotify_event ) + FILENAME_MAX ) )

void process_event( int fd, string target, string &output_location, Parser &myParser )
{
    // Is target a directory?
//    DIR *source_dir;
//    struct dirent *entry;


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

        // Get file name
        if( new_event->len )
        {
            file_name = new_event->name;
        }
        else
        {
            file_name = "";
        }

        // Full path of output file
        string out_path = output_location + file_name;

        // File Created
        if( ( new_event->mask &IN_CREATE ) || ( new_event->mask &IN_MOVED_TO ) )
        {
            log_msg( "New file, " + file_name + ", detected. Parsing...", 'i' );
            myParser.open_file( target + file_name, file_name, output_location );
        }

        // Modified
        if( new_event->mask &IN_MODIFY )
        {
            log_msg( "File, " + file_name + ", modified. Re-parsing...", 'i' );
            myParser.open_file( target + file_name, file_name, output_location );
        }

        // Deleted/Moved
        if( ( new_event->mask &IN_MOVED_FROM ) || ( new_event->mask &IN_DELETE_SELF ) || ( new_event->mask &IN_DELETE ) )
        {
            remove( out_path.c_str() );
            log_msg( out_path + " removed", 'i' );
        }

        // Iterate
        i += ( sizeof( struct inotify_event ) + new_event->len );
    }

}

#endif
