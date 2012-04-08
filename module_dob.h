class module_dob
{
  public:

    module_dob();   // constructor
    ~module_dob();  // destructor

    int scan( string& );

  private:

};

module_dob::module_dob()
{

}

module_dob::~module_dob()
{

}

/*********************************************************************************************
Scans for numeric birthdays
**********************************************************************************************/
int module_dob::scan( string &curr_line )
{
    /* Regular Expression to match */
    boost::regex re("\\b\\d{1,2}\\/\\d{1,2}\\/\\d{4}\\b");

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




