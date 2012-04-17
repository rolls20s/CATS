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
    /* Regular Expression to match */
    boost::regex re("\\b(\\d{1,2})[-/\\.](\\d{1,2})[-/\\.](\\d{2,4})\\b");



    return OK;
}
