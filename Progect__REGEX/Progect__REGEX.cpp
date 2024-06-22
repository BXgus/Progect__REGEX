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
    regex rx2("[0-9]{4}(-[0-3][0-9]){2}");
    if (regex_match(target, target+strlen(target), rx2))
    {
        cout << "Regex found in 2014-04-02" << endl;
    }
}