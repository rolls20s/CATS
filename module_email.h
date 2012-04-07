class module_email
{
  public:

    module_email();   // constructor
    ~module_email();  // destructor

    int scan( string& );

  private:

};

module_email::module_email()
{

}

module_email::~module_email()
{

}

/*********************************************************************************************
Scans for Email addresses
**********************************************************************************************/
int module_email::scan( string &curr_line )
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





