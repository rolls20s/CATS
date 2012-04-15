
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
    // Iterators
    std::string::const_iterator start = curr_line.begin();
    std::string::const_iterator end = curr_line.end();

    boost::match_results<std::string::const_iterator> match;
    boost::match_results<std::string::const_iterator> match2;

    boost::match_flag_type flags = boost::match_default;


    /****** FIRST NAME ***********************************************************************************/
    // Regular Expression to match
    boost::regex re_first( "first\\s*name:?\\s?(is)?\\s?([a-z\\']*)", boost::regex::icase );

    // Get matches
    if( boost::regex_search( start, end, match, re_first, flags ) )
    {
        /*
        repl_name.begin_pos = it->first - curr_line.begin();
        repl_name.end_pos = it->second - curr_line.begin();
        repl_name.value = *it;

        rand_name( repl_ssn.value ); // Replace value

        ssn_repls.push_back( repl_ssn ); // Add to the list of replacements in this line
*/
        cout << match[2] << endl;

    }
    /******************************************************************************************************/


    /****** LAST NAME ********************************************************************************************/

    // Regular Expression to match
    boost::regex re_last( "((last\\s*name)|(surname)):?\\s?(is)?\\s?([a-z\\'\\-]*)", boost::regex::icase );

    // Get matches
    if( boost::regex_search( start, end, match2, re_last, flags ) )
    {
        /*
        repl_name.begin_pos = it->first - curr_line.begin();
        repl_name.end_pos = it->second - curr_line.begin();
        repl_name.value = *it;

        rand_name( repl_ssn.value ); // Replace value

        ssn_repls.push_back( repl_ssn ); // Add to the list of replacements in this line
*/
        cout << match2[5] << endl;
    }
    /*************************************************************************************************************/


    return OK;
}

int module_names_regionless::rand_name( string &curr_name, char &name_type )
{
    return OK;
}
