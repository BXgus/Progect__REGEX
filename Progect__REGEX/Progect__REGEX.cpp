#include <iostream>
#include <regex>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "rus");
    string target2("Drizzle");
    regex rx1= (regex) R"(D\w+e)"; 

    bool found = regex_match(target2.begin(), target2.end(), rx1);
    if (found)
        cout << "Regex found in Drizzle !!" << endl;
    // ---------------------------------------------------------
    const char* target = "2014-04-02";
    // ---------------------------------------------------------
    regex rx2("[0-9]{4}(-[0-3][0-9]){2}");
    if (regex_match(target, target+strlen(target), rx2))
    {
        cout << "Regex found in 2014-04-02" << endl;
    }
    // ============================================================================
    std::regex_constants::match_flag_type  FONLY =
                std::regex_constants::format_first_only;

    std::regex  rx_1("a");
    string  fmt_1("A");
    string  str("adaeaf");
    cout<< "replacement == " <<  regex_replace(str, rx_1, fmt_1) <<endl; // выведется replacement == AdAeAf
    // ---------------------------------------------------------
    cout<< "replacement == " << regex_replace(str, rx_1, fmt_1, FONLY) <<endl;
    // -------------------------------------------------------------------
    char  buf[20];
    const char*  first = "axayaz";
    const char*  last = first + strlen(first);
    std::regex   rx_2("a");
    std::string  fmt_2("A");
    * ( std::regex_replace(&buf[0], first, last, rx_2, fmt_2) ) = '\0';
    cout << "replacement == " << &buf[0] << endl; // выведется replacement == AxAyAz
    // ---------------------------------------------------------
    * ( std::regex_replace(&buf[0], first, last, rx_2, fmt_2, FONLY) ) = '\0';
    cout << "replacement == " << &buf[0] << endl; // выведется replacement == Axayazё
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------

}