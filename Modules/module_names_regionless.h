
#define OK 0
#define FAIL -1

class module_names_regionless
{
  public:

    module_names_regionless();   // constructor
    ~module_names_regionless();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_name;

    int rand_name( string&, char& );
};

module_names_regionless::module_names_regionless()
{

}

module_names_regionless::~module_names_regionless()
{

}

/*********************************************************************************************
Scans for valid names
**********************************************************************************************/
int module_names_regionless::scan( string &curr_line, std::vector<replacement> &name_repls )
{
    // Regular Expression to match
    boost::regex re( "first.*name:?(is)?([a-z\\']*)\\s", boost::regex::icase );

    //boost::regex re_surname( "(last.*name:?)|(surname:?)(is)?([a-z\\'\\-]*)\\s", boost::regex::icase );
    //boost::regex re_fullname( "" );

    // Iterators
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 2);
    boost::sregex_token_iterator end;

    // Do matching
    while( it != end )
    {
        /*
        repl_name.begin_pos = it->first - curr_line.begin();
        repl_name.end_pos = it->second - curr_line.begin();
        repl_name.value = *it;

        rand_name( repl_ssn.value ); // Replace value

        ssn_repls.push_back( repl_ssn ); // Add to the list of replacements in this line
*/
        cout << *it << endl;

        it++; // increment iterator
    }

    return OK;
}

int module_names_regionless::rand_name( string &curr_name, char &name_type )
{
    return OK;
}
