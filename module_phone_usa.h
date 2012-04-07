class module_phone_usa
{
  public:

    module_phone_usa();   // constructor
    ~module_phone_usa();  // destructor

    int scan( string& );

  private:

};

module_phone_usa::module_phone_usa()
{

}

module_phone_usa::~module_phone_usa()
{

}

/*********************************************************************************************
Scans for valid US Telephone Numbers

(Ignores country code).
**********************************************************************************************/
int module_phone_usa::scan( string &curr_line )
{
    /* Regular Expression to match */
//  boost::regex re("(?<Telephone>([0-9]|[ ]|[-]|[\\(]|[\\)]|ext.|[,])+)([ ]|[:]|\\t|[-])*(?<Where>Home|Office|Work|Away|Fax|FAX|Phone)|(?<Where>Home|Office|Work|Away|Fax|FAX|Phone|Daytime|Evening)([ ]|[:]|\\t|[-])*(?<Telephone>([0-9]|[ ]|[-]|[\\(]|[\\)]|ext.|[,])+)|(?<Telephone>([(]([0-9]){3}[)]([ ])?([0-9]){3}([ ]|-)([0-9]){4}))");
    boost::regex re("(?:\\([2-9][0-8]\\d\\)\\ ?|[2-9][0-8]\\d[\\-\\ \\.\\/]?)[2-9]\\d{2}[- \\.\\/]?\\d{4}\\b");

    /* Iterators */
    boost::sregex_token_iterator it( curr_line.begin(), curr_line.end(), re, 0);
    boost::sregex_token_iterator end;

    unsigned count = 0; // Track matches

    /* Do matching */
    while( it != end )
    {
        cout << *it++ << endl;
        count++;
    }

    return OK;
}



