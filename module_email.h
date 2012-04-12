class module_email
{
  public:

    module_email();   // constructor
    ~module_email();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_email;
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
int module_email::scan( string &curr_line, std::vector<replacement> &email_repls )
{
    /* Regular Expression to match */
    boost::regex re("((([!#$%&'*+\\-/=?^_`{|}~\\w])|([!#$%&'*+\\-/=?^_`{|}~\\w][!#$%&'*+\\-/=?^_`{|}~\\.\\w]{0,}[!#$%&'*+\\-/=?^_`{|}~\\w]))[@]\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*)");

    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        repl_email.begin_pos = it->first - curr_line.begin();
        repl_email.end_pos = ( it->second - curr_line.begin() ) - 1;
        repl_email.value = *it++;

        count++;

        email_repls.push_back( repl_email );
    }

    return OK;
}





