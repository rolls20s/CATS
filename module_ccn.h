class module_ccn
{
  public:

    module_ccn();   // constructor
    ~module_ccn();  // destructor

    int scan( string& );

  private:

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
int module_ccn::scan( string &curr_line )
{
    /* Regular Expression to match */
    boost::regex re("");

    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        cout << *it++ << endl;
        count++;
    }

    return OK;
}






