class module_ccn
{
  public:

    module_ccn();   // constructor
    ~module_ccn();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_ccn;
};

module_ccn::module_ccn()
{

}

module_ccn::~module_ccn()
{

}

/*********************************************************************************************
Scans for Credit Card Numbers
**********************************************************************************************/
int module_ccn::scan( string &curr_line, std::vector<replacement> &ccn_repls )
{
    /* Regular Expression to match */
    boost::regex re("((?:4\\d{3})|(?:5[1-5]\\d{2})|(?:6011)|(?:3[68]\\d{2})|(?:30[012345]\\d))[ -]?(\\d{4})[ -]?(\\d{4})[ -]?(\\d{4}|3[4,7]\\d{13})");

    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        repl_ccn.begin_pos = it->first - curr_line.begin();
        repl_ccn.end_pos = ( it->second - curr_line.begin() ) - 1;
        repl_ccn.value = *it++;

        count++;

        ccn_repls.push_back( repl_ccn );
    }

    return OK;
}






