class module_phone_usa
{
  public:

    module_phone_usa();   // constructor
    ~module_phone_usa();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_phone;

    int rand_phone( string& );
};

module_phone_usa::module_phone_usa()
{

}

module_phone_usa::~module_phone_usa()
{

}

/*********************************************************************************************
Scans for valid US Telephone Numbers

ToDo: make sure new value fits specification (currently does not allow all zeros)
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
        repl_phone.end_pos = it->second - curr_line.begin();

        repl_phone.value = *it;

        rand_phone( repl_phone.value );

        phone_repls.push_back( repl_phone );

        it++;// increment iterator
        count++;
    }

    return OK;
}


/***************************************************
Replace numbers in the input string with a new
random number or, if the value has been seen before,
replace it with the previously generated value.
****************************************************/
int module_phone_usa::rand_phone( string &format )
{
    stringstream phoneBuf;// Buffer for random number
    stringstream oldPhone; // Buffer for current read phone number
    string newPhoneVal; // Holds the digits for the phone number before formatting
    stringstream obuffer; // Buffer for formatted output

    /*** Check for existing value ***/
    for( unsigned int i = 0; i < format.length(); i++ )
    {
        if( isdigit( format[i] ) ) // Strip non-digits
        {
            oldPhone << format[i];
        }
    }

    if( repl_map.count( oldPhone.str() ) ) // Check map for existing value
    {
        newPhoneVal = repl_map[oldPhone.str()];
    }
    else
    {

        // ToDo: fix so the consistency check ignores the country code


        /*** Check for country code ***/
        if( oldPhone.str().length() > 10 )
        {
            phoneBuf << '1';
        }
        /******************************/

        /**************** Generate digits for phone number ***************/

        // Area code
        int area_code = ( rand() % 998 ) + 1;
        if( area_code < 100 )
        {
            phoneBuf << '0';

            if( area_code < 10 )
            {
                phoneBuf << '0';
            }
        }
        phoneBuf << area_code;

        // Generate Prefix
        int prefix = ( rand() % 998 ) + 1;
        if( prefix < 100 )
        {
            phoneBuf << '0';

            if( prefix < 10 )
            {
                phoneBuf << '0';
            }
        }
        phoneBuf << prefix;

        // Generate Line Number
        int line_num = ( rand() % 9998 ) + 1;
        if( line_num < 1000 )
        {
            phoneBuf << '0';

            if( line_num < 100 )
            {
                phoneBuf << '0';

                if( line_num < 10 )
                {
                    phoneBuf << '0';
                }
            }
        }
        phoneBuf << line_num;
        /********************************************************/

        newPhoneVal = phoneBuf.str();

        repl_map[oldPhone.str()] = phoneBuf.str(); // Add to map
    }

    int bufCount = 0; // Track position in new number

    for( unsigned int i = 0; i < format.length(); i++ )
    {
        if( isdigit( format[i] ) )
        {
                obuffer << newPhoneVal[bufCount]; // output a digit from new value
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
