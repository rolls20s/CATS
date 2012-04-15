class module_dob
{
  public:

    module_dob();   // constructor
    ~module_dob();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_dob;
};

module_dob::module_dob()
{

}

module_dob::~module_dob()
{

}

/*********************************************************************************************
Scans for numeric birthdays w/fields separated by -, ., or /

**********************************************************************************************/
int module_dob::scan( string &curr_line, std::vector<replacement> &dob_repls )
{
    /* Regular Expression to match */
    boost::regex re("\\b(\\d{1,2})[-/\\.](\\d{1,2})[-/\\.](\\d{2,4})\\b");

    // String Iterators
    std::string::const_iterator start = curr_line.begin();
    std::string::const_iterator end = curr_line.end();

    // Flags for regex_search()
    boost::match_flag_type flags = boost::match_default;

    // Iterators for regex_search()
    boost::match_results<std::string::const_iterator> match;  // Firstname matches

    /* Do matching */
   /* if( boost::regex_search( start, end, match, re, flags ) )
    {
        repl_name.begin_pos = match[2].first - start; // Start position in line
        repl_name.end_pos = match[2].second - start;  // End position in line
        repl_name.value = "test1";                          // New value

        name_repls.push_back( repl_name ); // Add to the list of replacements in this line

        dob_repls.push_back( repl_dob );
    }
*/
    return OK;
}
