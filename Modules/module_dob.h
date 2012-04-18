class module_dob
{
  public:

    module_dob();   // constructor
    ~module_dob();  // destructor

    int scan( string&, std::vector<replacement>& );

  private:

    replacement repl_dob;
};

module_dob::module_dob()
{

}

module_dob::~module_dob()
{

}

/*********************************************************************************************
Scans for numeric birthdays w/fields separated by -, ., or /

**********************************************************************************************/
int module_dob::scan( string &curr_line, std::vector<replacement> &dob_repls )
{

    /****************************** Regular Expressions for regex search ******************************/
/*    boost::regex re_first(
                            // First name
                            boost::regex re("\\b(\\d{1,4})[-/\\.](\\d{1,2})[-/\\.](\\d{2,4})\\b");

                            // Not case sensitive (Change?)
                            , boost::regex::icase
    );*/
    /**************************************************************************************************/
/*
    // Indexes to wanted matches
    int fn_match = 3;   // First
    int ln_match = 9;   // Last
    int mn_match = 13;  // Middle
    int mi_match = 15;  // Mid Initial
    int pc_match = 22;  // Parent/Child/Full

    // Iterative search
    boost::sregex_iterator it( curr_line.begin(), curr_line.end(), re_first );
    boost::sregex_iterator end;

*/
    /****** Replace Names *********************************************************************/
    /*while( it != end )
    {
        string new_name;

        if( (*it)[fn_match] != "" ) // Firstname
        {
            rand_name( new_name, 'f' );
            push_name( it, fn_match, curr_line, new_name, name_repls );
        }

        if( (*it)[ln_match] != "" ) // Lastname
        {
            rand_name( new_name, 'l' );
            push_name( it, ln_match, curr_line, new_name, name_repls );
        }

        if( (*it)[mn_match] != "" ) // Middlename
        {
            rand_name( new_name, 'm' );
            push_name( it, mn_match, curr_line, new_name, name_repls );
        }

        if( (*it)[mi_match] != "" ) // Middle initial
        {
            rand_name( new_name, 'i' );
            push_name( it, mi_match, curr_line, new_name, name_repls );
        }

        if( (*it)[pc_match] != "" ) // Parent/Child/Full name
        {
            // Build Name
            string first, last, mid;
            rand_name( first, 'f' );
            rand_name( last, 'l' );
            rand_name( mid, 'i' );

            new_name = first + " " + mid + " " + last;
            push_name( it, pc_match, curr_line, new_name, name_repls );
        }

        it++;
    }*/
    /***************************************************************************************/

    return OK;
}
