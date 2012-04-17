
#define OK 0
#define FAIL -1

class module_names_regionless
{
  public:

    module_names_regionless();   // constructor
    ~module_names_regionless();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    int rand_name( string&, char& );
    void push_name( boost::sregex_iterator&, const int&, string&, const string&, std::vector<replacement>& );
};

module_names_regionless::module_names_regionless()
{

}

module_names_regionless::~module_names_regionless()
{

}

/*********************************************************************************************
Scans for valid names and repaces them with new ones

ToDo: middle names/initials, whole names.
**********************************************************************************************/
int module_names_regionless::scan( string &curr_line, std::vector<replacement> &name_repls )
{

    /******************** Regular Expressions for regex_search() ********************/
    boost::regex re_first(
                            // First name
                            "(first\\s*name:?\\s?(is)?\\s?([a-z\\']*))"

                            // Middle name/Initial
                            //"()"

                            // Last name
                            "|(((last\\s*name)|(surname)):?\\s?(is)?\\s?([a-z\\'\\-]*))"

                            // Not case sensitive
                            , boost::regex::icase
    );
    /*********************************************************************************/

    // Indexes to wanted matches
    int fn_match = 3;
    int ln_match = 9;

    // Iterative search
    boost::sregex_iterator it( curr_line.begin(), curr_line.end(), re_first );
    boost::sregex_iterator end;


    /****** Replace Names *********************************************************************/
    while( it != end )
    {
        if( (*it)[fn_match] != "" )
        {
            push_name( it, fn_match, curr_line, "test", name_repls );
        }

        if( (*it)[ln_match] != "" )
        {
            push_name( it, ln_match, curr_line, "test2", name_repls );
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


int module_names_regionless::rand_name( string &curr_name, char &name_type )
{
    return OK;
}
