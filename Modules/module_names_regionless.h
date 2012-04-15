
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

    /******************** Regular Expressions for regex_search() ********************/
    boost::regex re_first(
                            // First name
                            "(first\\s*name:?\\s?(is)?\\s?([a-z\\']*))"

                            "|" // OR

                            // Last name
                            "(((last\\s*name)|(surname)):?\\s?(is)?\\s?([a-z\\'\\-]*))"

                            // Not case sensitive
                            , boost::regex::icase
    );
    /*********************************************************************************/


    // Iterative search
    boost::sregex_iterator it( curr_line.begin(), curr_line.end(), re_first );
    boost::sregex_iterator end;


    /****** Replace Names *********************************************************************/
    while( it != end )
    {/*
        repl_name.begin_pos = match_first[3].first - start; // Start position in line
        repl_name.end_pos = match_first[3].second - start;  // End position in line
        repl_name.value = "test1";                          // New value

        name_repls.push_back( repl_name ); // Add to the list of replacements in this line
    */
    /*int j = 0;
    while(j<15)
    {
        cout << j << ' ' <<(*it)[j] << '\n';
        j++;
    }*/
        cout << "Firstname: " << (*it)[3] << endl;
        cout << "Last name: " << (*it)[9] << endl;
        it++;
    }
    /***************************************************************************************/

    return OK;
}

int module_names_regionless::rand_name( string &curr_name, char &name_type )
{
    return OK;
}
