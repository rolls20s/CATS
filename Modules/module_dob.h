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
    boost::regex re("\\b\\d{1,2}[-/\\.]\\d{1,2}[-/\\.]\\d{2,4}\\b");

    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        repl_dob.begin_pos = it->first - curr_line.begin();
        repl_dob.end_pos = it->second - curr_line.begin();

        repl_dob.value = "test";// Replacement value

        it++;// increment iterator
        count++;

        dob_repls.push_back( repl_dob );
    }

    return OK;
}
