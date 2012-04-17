class module_email
{
  public:

    module_email();   // constructor
    ~module_email();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_email;
    int rand_email( string& );
};

module_email::module_email()
{
    if( email_domains.empty() )
    {
        std::ifstream fin;
        string domain;

        fin.open( DOMAIN_LIST );

        // Needs log msg and graceful handling
    /*
        while( !fin.is_open() )
        {
            string file;
            std::cout << "!! module_email::module_email() !!\n\tERROR OPENING EMAIL DOMAIN LIST\n";
            std::cout << "PLEASE ENTER DOMAIN LIST FILE NAME: ";
            std::cin >> file;
            fin.clear();
            fin.open(file.c_str());
        }
    */
        while( fin.peek() != EOF )
        {
            fin >> domain;
            email_domains.push_back( domain );
        }
    }
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
        repl_email.end_pos = it->second - curr_line.begin();

        repl_email.value = *it;// Replacement value

        rand_email( repl_email.value );

        it++;// increment iterator
        count++;

        email_repls.push_back( repl_email );
    }

    return OK;
}

int module_email::rand_email( string &format )
{
    string newEmailVal;
    string newDomain; // Holds the new domain

    stringstream emailAcct; // Buffer for current read email
    stringstream emailBuf;// Buffer for random email ( stringstream::in | stringstream::out );

    /*** Check for existing ssn ***/

    for( unsigned int i = 0; i < format.length(); i++ )
    {
        if( format[i] != '@' )
        {
            emailAcct << format[i];
        }
        else
        {
            break;
        }
    }

    if( repl_map.count( format ) )
    {
        newEmailVal = repl_map[ format ];
    }
    else
    {
        /**************** Generate new email addr ***************/

        // ToDo: generate from username list or char stats

        newDomain = email_domains[ rand() % email_domains.size()];

        for( unsigned int i = 0; i < emailAcct.str().length(); ++i )
        {
            if( rand() % 2 )
            {
                emailBuf << (char)((rand() % 26) + 65);
            }
            else
            {
                emailBuf << (char)((rand() % 26) + 97);
            }
        }

        emailBuf << newDomain;

        /********************************************************/

        newEmailVal = emailBuf.str();
        repl_map[ format ] = emailBuf.str();
    }

    format = newEmailVal;

    return OK;

}



