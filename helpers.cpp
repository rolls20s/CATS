#ifndef _HELP_CPP
#define _HELP_CPP

/** For get_args() ************************/
#include <boost/program_options.hpp>
namespace opts = boost::program_options;
/*****************************************/

/******************************************
Initialize log.

ToDo: Base the log preferences off of
    external config
******************************************/
void init_log()
{
    std::ofstream logfile;

    logfile.open( LOG_LOCATION ); // open file

    if( logfile.is_open() )
    {
        logfile << "Info: Log Started.\n"; // output the message to the file
        logfile.close(); // close file
    }
    else
    {
        cerr << "Problem opening log file.\n";
    }
}

/******************************************************
Output to log.

string log_message: Contains message log

char log_type: Identifies type of message:

            i - information
            e - error
            f - fatal error
******************************************************/
void log_msg( const string &log_message, const char &log_type )
{
    std::ofstream logfile;

    logfile.open( LOG_LOCATION, std::ofstream::app ); // open file

    // ToDo: fix so interactive mode doesn't require log to be open.
    if( logfile.is_open() )
    {
        if( log_type == 'i' ) // Info
        {
            logfile << "Info: ";

            if(INTERACTIVE)
                cout << "Info: ";
        }
        else if( log_type == 'w' ) // Info
        {
            logfile << "Warning: ";

            if(INTERACTIVE)
                cout << "Warning: ";
        }
        else if ( ( log_type == 'e') || ( log_type == 'f') ) // Error
        {
            logfile << "Error: ";

            if(INTERACTIVE)
                cout << "Error: ";
        }
        else // Wrong log_type
        {
            cerr << "Bad log_type in log_msg()\n";
        }

        /* Write out message to file */
        logfile << log_message;

        if(INTERACTIVE)
            cout << log_message;

        if ( log_type == 'f') // Fatal error, add "exiting."
        {
            logfile << " Info: Exiting.\n";

            if(INTERACTIVE)
                cout << "Info: Exiting.\n";
        }
        else
        {
            logfile << endl;

            if(INTERACTIVE)
                cout << endl;
        }

        logfile.close(); // close file
    }
    else
    {
        cerr << "Problem opening log file.\n";
    }
}


/********************************
Get config info from config file
*********************************/
void read_config_file( const string c_f, string &s_p, string &d_p )
{
    std::ifstream configfile;

    configfile.open( c_f ); // open file

    if( configfile.is_open() )
    {
        /* ToDo: Get config info */

        configfile.close(); // close file
    }
    else
    {
        cerr << "Problem opening config file.\n";
        exit(1);
    }
}

/************************************
Parse the command line using the
boost::program_options library.

char* args[]:  Set of arguments
int arg_count: Number of arguments
************************************/
int get_args( int arg_count, char *args[], string &source_path, string &dest_path )
{
    try
    {
        opts::options_description desc( "Allowed options" );

        /************************* ADD OPTIONS HERE *************************/
        desc.add_options()

            ( "help", "Show this help message" )

            ( "inter", "Interactive mode" )
            //( "configfile", opts::value<string>(), "Path to config file (Optional)")

            ( "source", opts::value<string>(), "Set location of source files" )

            ( "dest", opts::value<string>(), "Set location of parsed files")

            //( "logfile", opts::value<string>(), "Path to log file" )

        ;
        /********************************************************************/

        opts::variables_map vm;
        opts::store( opts::parse_command_line( arg_count, args, desc ), vm );
        opts::notify(vm);

        /******************** PROCESS CUSTOM OPTIONS HERE *********************/

        // Help
        if( vm.count( "help" ) )
        {
            cout << desc << endl; // Output help
            return -1;
        }

        if( vm.count( "inter" ) )
        {
            INTERACTIVE = true;
            cout << "*** Running in interactive mode. ****" << endl;
        }
        if( vm.count( "configfile" ) )
        {
            const string config_file = vm["configfile"].as<string>(); // Get file path
            read_config_file( config_file, source_path, dest_path );
        }
        else // No config file
        {
            // Source
            if( vm.count( "source" ) )
            {
                source_path = vm["source"].as<string>(); // Return source path
            }
            else // A source is required.
            {
                cout << "No source specified." << endl;
                log_msg( "No source specified.", 'f' );
                return 2;
            }

            // Destination
            if( vm.count( "dest" ) )
            {
                dest_path = vm["dest"].as<string>(); // Return destination path
            }
            else // A destination is required
            {
                cout << "No destination specified." << endl;
                log_msg( "No destination specified.", 'f' );
                return 2;
            }
        }
        /***********************************************************************/

    }
    catch( std::exception& e ) // Bad options
    {
        cerr << "Error: " << e.what() << endl;
        log_msg( e.what(), 'f');
        return -1;
    }
    catch( ... ) // Something bad happened.
    {
        cerr << "Exception of unknown type!\n";
        log_msg( "Something bad happened.", 'e' );
    }

    return 0;
}

#endif
