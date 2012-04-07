
#define OK 0
#define FAIL -1;

class module_ssn_usa
{
  public:

    module_ssn_usa();   // constructor
    ~module_ssn_usa();  // destructor

    int scan( string& );

  private:

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
**********************************************************************************************/
int module_ssn_usa::scan( string &curr_line )
{
    // Regular Expression to match
    boost::regex re("\\b(?!000)(?!666)(?!9)[0-9]{3}[ -]?(?!00)[0-9]{2}[ -]?(?!0000)[0-9]{4}\\b");

    // Iterators
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    // Do matching
    while( it != end )
    {
        cout << *it++ << endl;
        count++;
    }

    return OK;
}


