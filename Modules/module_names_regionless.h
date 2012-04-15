
#define OK 0
#define FAIL -1

class module_names_regionless
{
  public:

    module_names_regionless();   // constructor
    ~module_names_regionless();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_name;

    int rand_name( string&, char& );
};

module_names_regionless::module_names_regionless()
{

}

module_names_regionless::~module_names_regionless()
{

}

/*********************************************************************************************
Scans for valid names
**********************************************************************************************/
int module_names_regionless::scan( string &curr_line, std::vector<replacement> &name_repls )
{
    // String Iterators
    std::string::const_iterator start = curr_line.begin();
    std::string::const_iterator end = curr_line.end();

    // Flags for regex_search()
    boost::match_flag_type flags = boost::match_default;

    // Iterators for regex_search()
    boost::match_results<std::string::const_iterator> match_first;  // Firstname matches
    boost::match_results<std::string::const_iterator> match_last;   // Lastname matches

    // Regular Expressions for regex_search()
    boost::regex re_first( "first\\s*name:?\\s?(is)?\\s?([a-z\\']*)", boost::regex::icase );                // Firstname
    boost::regex re_last( "((last\\s*name)|(surname)):?\\s?(is)?\\s?([a-z\\'\\-]*)", boost::regex::icase ); // Surname


    /****** FIRST NAME *********************************************************************/
    if( boost::regex_search( start, end, match_first, re_first, flags ) )
    {
        repl_name.begin_pos = match_first[2].first - start; // Start position in line
        repl_name.end_pos = match_first[2].second - start;  // End position in line
        repl_name.value = "test1";                          // New value

        name_repls.push_back( repl_name ); // Add to the list of replacements in this line

        //cout << match_first[2] << endl;
    }
    /***************************************************************************************/


    /****** LAST NAME **********************************************************************/
    if( boost::regex_search( start, end, match_last, re_last, flags ) )
    {
        repl_name.begin_pos = match_last[5].first - start;  // Start
        repl_name.end_pos = match_last[5].second - start;   // End
        repl_name.value = "test2";                          // New value

        name_repls.push_back( repl_name ); // Add to the list of replacements in this line

        //cout << match_last[5] << endl;
    }
    /***************************************************************************************/


    return OK;
}

int module_names_regionless::rand_name( string &curr_name, char &name_type )
{
    return OK;
}
