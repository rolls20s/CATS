class module_ccn
{
  public:

    module_ccn();   // constructor
    ~module_ccn();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_ccn;
    int rand_ccn( string& );
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
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0 );
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        repl_ccn.begin_pos = it->first - curr_line.begin();
        repl_ccn.end_pos = it->second - curr_line.begin();

        repl_ccn.value = *it;
        rand_ccn( repl_ccn.value );

        ccn_repls.push_back( repl_ccn );

        it++;// increment iterator
        count++;
    }

    return OK;
}

/***************************************************
Replace numbers in the input string with a new
random number.
****************************************************/
int module_ccn::rand_ccn( string &format )
{
    string newCcnVal; // Holds the digits for the ssn before formatting

    stringstream oldCcn; // Buffer for current read ccn
    stringstream obuffer; // Buffer for formatted ccn output
    stringstream ccnBuf;// Buffer for random ccn ( stringstream::in | stringstream::out );

    /**************** Get Unformated ccn ********************/

     for( unsigned int i = 0; i < repl_ccn.value.length(); ++i )
    {
        if( isdigit( repl_ccn.value[i] ) )
        {
                oldCcn << repl_ccn.value[i];
        }
    }

    /**************** Generate digits for ccn ***************/

    short digitsToGen = -1;

    switch( oldCcn.str().length() )
    {
        case 13:        /*      VISA        */
            ccnBuf << '4';
            digitsToGen = 12;
            break;
        case 14:        /*      Diner's Club/Carte Blanche      */
            switch( rand() % 4 )
            {
                case 0:
                    ccnBuf << '3' << '0' << '0';
                    digitsToGen = 11;
                    break;
                case 1:
                    ccnBuf << '3' << '0' << '5';
                    digitsToGen = 11;
                    break;
                case 2:
                    ccnBuf << '3' << '6';
                    digitsToGen = 12;
                    break;
                case 3:
                    ccnBuf << '3' << '8';
                    digitsToGen = 12;
                    break;
            }
            break;
        case 15:        /*      American Express        */
            if( rand() % 2)
            {
                    ccnBuf << '3' << '4';
            }
            else
            {
                    ccnBuf << '3' << '7';
            }
           digitsToGen = 13;
           break;
        case 16:        /*      VISA|MasterCard|Discover        */
            switch( rand() % 3)
            {
                case 0:
                    ccnBuf << '4';
                    digitsToGen = 15;
                    break;
                case 1:
                    if( rand() % 2 )
                    {
                        ccnBuf << '5' << '1';
                    }
                    else
                    {
                        ccnBuf << '5' << '5';
                    }
                    digitsToGen = 14;
                    break;
                case 2:
                    ccnBuf << '6' << '0' << '1' << '1';
                    digitsToGen = 12;
                    break;
            }
            break;
    }

    for( int i = 0; i < digitsToGen; ++i)
    {
        ccnBuf << (rand() % 10);
    }

    /********************************************************/

    /*** Check for existing ccn ***/

    if( repl_map.count( oldCcn.str() ) )
    {
        newCcnVal = repl_map[oldCcn.str()];
    }
    else
    {
        newCcnVal = ccnBuf.str();
        repl_map[oldCcn.str()] = ccnBuf.str();
    }

    /******************************/

    int bufCount = 0; // Track position in new ssn

    for( unsigned int i = 0; i < format.length(); i++ )
    {
        if( isdigit( format[i] ) )
        {
            obuffer << newCcnVal[bufCount]; // output a digit from new ssn value
            bufCount++;
        }
        else
        {
            obuffer << format[i];
        }
    }

    format = obuffer.str();

    return OK;
}




