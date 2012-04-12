class module_phone_usa
{
  public:

    module_phone_usa();   // constructor
    ~module_phone_usa();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_phone;

};

module_phone_usa::module_phone_usa()
{

}

module_phone_usa::~module_phone_usa()
{

}

/*********************************************************************************************
Scans for valid US Telephone Numbers

(Ignores country code).
**********************************************************************************************/
int module_phone_usa::scan( string &curr_line, std::vector<replacement> &phone_repls )
{
    /* Regular Expression to match */
    boost::regex re("(?:\\+?1[-. ]?)?\\(?\\b([0-9]{3})\\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})\\b");
    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        repl_phone.begin_pos = it->first - curr_line.begin();
        repl_phone.end_pos = ( it->second - curr_line.begin() ) - 1;
        repl_phone.value = *it++;

        //it++;

        count++;

        phone_repls.push_back( repl_phone );
    }

    return OK;
}



