class module_addr_usa
{
  public:

    module_addr_usa();   // constructor
    ~module_addr_usa();  // destructor

    int scan( string& );

  private:

};

module_addr_usa::module_addr_usa()
{

}

module_addr_usa::~module_addr_usa()
{

}

/*********************************************************************************************
Scans for parts of valid US Addresses
**********************************************************************************************/
int module_addr_usa::scan( string &curr_line )
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





