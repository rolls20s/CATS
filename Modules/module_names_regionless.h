#define FN_FILE "firstnames"
#define LN_FILE "lastnames"


#define OK 0
#define FAIL -1

class module_names_regionless
{
  public:

    module_names_regionless();   // constructor
    ~module_names_regionless();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    int rand_name( string&, const char& ); // Chooses a random name
    void push_name( boost::sregex_iterator&, const int&, string&, const string&, std::vector<replacement>& ); // pushes a name on to the repl list
    int get_names( const string&, std::vector<string>& ); // Pulls names from a file
};

/*****************************************
Constructor

fn_list and ln_list declared in modules.h
******************************************/
module_names_regionless::module_names_regionless()
{
    // empty check so we don't reload every time.
    if( ( fn_list.empty() ) && ( get_names( FN_FILE, fn_list) == FAIL ) )
    {
        log_msg( "module_names_regionless: Unable to open " + string(LN_FILE) + ". Cancelling name scan.", 'e');
        throw FAIL;
    }

    if( (ln_list.empty() ) && ( get_names( LN_FILE, ln_list) == FAIL ) )
    {
        log_msg( "module_names_regionless: Unable to open " + string(LN_FILE) + ". Cancelling name scan.", 'e');
        throw FAIL;
    }
}

module_names_regionless::~module_names_regionless()
{

}

/*********************************************************************************************
Scans for valid names and repaces them with new ones
**********************************************************************************************/
int module_names_regionless::scan( string &curr_line, std::vector<replacement> &name_repls )
{

    /****************************** Regular Expressions for regex_search() ******************************/
    boost::regex re_first(
                            // First name
                            "(first\\s*name:?\\s*(is)?\\s?([a-z\\']*))"

                            // Last name
                            "|(((last\\s*name)|(surname)):?\\s*(is)?\\s?([a-z\\'\\-]*))"

                            // Middle name
                            "|((middle\\s*name):?\\s*(is)?\\s?([a-z]*))"

                            // Middle initial
                            "|(initial:?\\s*([a-z])\\.?\\b)"

                            // Parent/Child Full Name  (a bit greedy - grabs a word after the last name if no middle given)
                            "|(((parent)|(child)|(full)).*name:?\\s*(is)?\\s?([a-z\\'\\-]*\\s*[a-z]*\\s?([a-z\\'\\-]*)?))"

                            // Not case sensitive (Change?)
                            , boost::regex::icase
    );
    /*****************************************************************************************************/

    // Indexes to wanted matches
    int fn_match = 3;   // First
    int ln_match = 9;   // Last
    int mn_match = 13;  // Middle
    int mi_match = 15;  // Mid Initial
    int pc_match = 22;  // Parent/Child/Full

    // Iterative search
    boost::sregex_iterator it( curr_line.begin(), curr_line.end(), re_first );
    boost::sregex_iterator end;


    /****** Replace Names *********************************************************************/
    while( it != end )
    {
        string new_name;

        if( (*it)[fn_match] != "" ) // Firstname
        {
            rand_name( new_name, 'f' );
            push_name( it, fn_match, curr_line, new_name, name_repls );
        }

        if( (*it)[ln_match] != "" ) // Lastname
        {
            rand_name( new_name, 'l' );
            push_name( it, ln_match, curr_line, new_name, name_repls );
        }

        if( (*it)[mn_match] != "" ) // Middlename
        {
            rand_name( new_name, 'm' );
            push_name( it, mn_match, curr_line, new_name, name_repls );
        }

        if( (*it)[mi_match] != "" ) // Middle initial
        {
            rand_name( new_name, 'i' );
            push_name( it, mi_match, curr_line, new_name, name_repls );
        }

        if( (*it)[pc_match] != "" ) // Parent/Child/Full name
        {
            // Build Name
            string first, last, mid;
            rand_name( first, 'f' );
            rand_name( last, 'l' );
            rand_name( mid, 'i' );

            new_name = first + " " + mid + " " + last;
            push_name( it, pc_match, curr_line, new_name, name_repls );
        }

        it++;
    }
    /***************************************************************************************/

    return OK;
}


/************************************
Pushes names on to the repl. tracker
*************************************/
void module_names_regionless::push_name( boost::sregex_iterator &it, const int &index, string &curr_line, const string &new_value, std::vector<replacement> &name_repls )
{
    replacement repl_name; // Holds current replacement

    repl_name.begin_pos = (*it)[index].first - curr_line.begin(); // Start position in line
    repl_name.end_pos   = (*it)[index].second - curr_line.begin();  // End position in line

    // New value to write
    repl_name.value = new_value;

    name_repls.push_back( repl_name ); // Add to the list of replacements in this line
}


/***********************
Returns a random name
************************/
int module_names_regionless::rand_name( string &curr_name, const char &name_type )
{
    switch( name_type )
    {
        case 'f':
                // First name
                curr_name = fn_list[rand() % fn_list.size()];
                break;
        case 'l':
                // Last Name
                curr_name = ln_list[rand() % ln_list.size()];
                break;
        case 'm':
                // Middle Name
                curr_name = fn_list[rand() % fn_list.size()];
                break;
        case 'i':
                // Initial
                const char initials[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                curr_name = initials[ rand() % 26 ];
    }

    return OK;
}


/***********************************************
Opens the supplied name file and reads in names
to the suppied vector.
************************************************/
int module_names_regionless::get_names( const string &name_file, std::vector<string> &name_list )
{
    string line; // Holds current line

    std::ifstream curr_name_file;    // Input file

    /** Open name file **/
    curr_name_file.open( name_file.c_str() );
    if( !curr_name_file.is_open() )
    {
        return FAIL;
    }
    /********************/

    /***** Read in names *****/
    while( curr_name_file.good() )
    {
        std::getline( curr_name_file, line ); // Get next line

        name_list.push_back( line );
    }
    /*************************/

    curr_name_file.close(); // close file

    return OK;
}
