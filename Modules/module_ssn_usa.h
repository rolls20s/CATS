
#define OK 0
#define FAIL -1;

class module_ssn_usa
{
  public:

    module_ssn_usa();   // constructor
    ~module_ssn_usa();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_ssn;
    int rand_ssn( string& );
};

module_ssn_usa::module_ssn_usa()
{

}

module_ssn_usa::~module_ssn_usa()
{

}

/*********************************************************************************************
Scans for valid US Social Security Numbers

Finds 9 digit numbers.  They can be contiguous, separated by '-', a separated by a single
whitespace.  Cannot start with 666 or 900-999 and cannot contain all zeros in any section.

ToDo: Make replacement value fit standard requirements
**********************************************************************************************/
int module_ssn_usa::scan( string &curr_line, std::vector<replacement> &ssn_repls )
{
    // Regular Expression to match
    boost::regex re( "\\b(?!000)(?!666)(?!9)[0-9]{3}[ -]?(?!00)[0-9]{2}[ -]?(?!0000)[0-9]{4}\\b" );

    // Iterators
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Count matches

    // Do matching
    while( it != end )
    {
        repl_ssn.begin_pos = it->first - curr_line.begin();
        repl_ssn.end_pos = it->second - curr_line.begin();
        repl_ssn.value = *it;

        rand_ssn( repl_ssn.value ); // Replace value

        ssn_repls.push_back( repl_ssn ); // Add to the list of replacements in this line

        it++; // increment iterator
        count++;
    }

    return OK;
}

/***************************************************
Replace numbers in the input string with a new
random number.
****************************************************/
int module_ssn_usa::rand_ssn( string &format )
{
    string newSsnVal; // Holds the digits for the ssn before formatting

    stringstream oldSsn; // Buffer for current read ssn
    stringstream obuffer; // Buffer for formatted ssn output
    stringstream ssnBuf;// Buffer for random ssn ( stringstream::in | stringstream::out );

    /**************** Generate digits for ssn ***************/
    // Area Number
    int area_num = ( rand() % 898 ) + 1;
    if( area_num < 100 )
    {
        ssnBuf << '0';

        if( area_num < 10 )
        {
            ssnBuf << '0';
        }
    }
    ssnBuf << area_num;

    // Generate Group Number
    int group_num = ( rand() % 98 ) + 1;
    if( group_num < 10 )
    {
        ssnBuf << '0';
    }
    ssnBuf << group_num;

    // Generate Serial Number
    int ser_num = ( rand() % 9998 ) + 1;
    if( ser_num < 1000 )
    {
        ssnBuf << '0';

        if( ser_num < 100 )
        {
            ssnBuf << '0';

            if( ser_num < 10 )
            {
                ssnBuf << '0';
            }
        }
    }
    ssnBuf << ser_num;
    /********************************************************/

    /*** Check for existing ssn ***/
    for( unsigned int i = 0; i < repl_ssn.value.length(); i++ )
    {
        if( isdigit( repl_ssn.value[i] ) )
        {
                oldSsn << repl_ssn.value[i];
        }
    }

    if( repl_map.count( oldSsn.str() ) )
    {
        newSsnVal = repl_map[oldSsn.str()];
    }
    else
    {
        newSsnVal = ssnBuf.str();
        repl_map[oldSsn.str()] = ssnBuf.str();
    }

    /******************************/

    int bufCount = 0; // Track position in new ssn

    for( unsigned int i = 0; i < format.length(); i++ )
    {
        if( isdigit( format[i] ) )
        {
            obuffer << newSsnVal[bufCount]; // output a digit from new ssn value
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
