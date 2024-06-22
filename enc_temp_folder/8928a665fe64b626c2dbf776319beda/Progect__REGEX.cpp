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
    // ============================================================================
    const char* first_ = "1234abc890";
    const char* last_ = first + strlen(first);
    std::regex rx__1("abc");
    std::regex_constants::match_flag_type FLAG =
        std::regex_constants::match_default;

    cout << "search(f, f+6, \"abc\") == " << std::boolalpha
        << regex_search(first_, first_+6, rx__1, FLAG) << std::endl; // выведется search(f, f+5, "abc") == false
    cout << "search(f, f+7, \"abc\") == " << std::boolalpha
        << regex_search(first_, first_+7, rx__1, FLAG) << std::endl;
        cout << "search(\"1234abc890\", \"abc\") == " << std::boolalpha
          << regex_search("1234abc890", rx__1) << std::endl; // search("1234abc890", "abc") == true

    // ---------------------------------------------------------

    // ---------------------------------------------------------
    string lines[] = { "Roses are #ff0000",
                           "violets are #0000ff",
                           "all of my base are belong to you" };
    regex  color_regex(  "#([a-f0-9]{2})"
                         "([a-f0-9]{2})"
                         "([a-f0-9]{2})"
                      );
    for (const auto& line : lines)
    {
        cout << line << std::boolalpha << " - ";
        cout << std::regex_search(line, color_regex) << '\n';
    }
    cout << '\n';
    // ---------------------------------------------------------
    /*  Задание 2:  найти строки с экземплярами IP-адресов, в которых эти IP-адреса
    написаны в начале строки. IP-адрес - 4 числа (от 0 до 255), разделенных точками 
    (например, 192.168.0.5).                                                         */
    std::string  lines2[] = { "192.168.0.5",
                      "192.168.0.123",
                      "192.168.0.5 is IP-адрес",
                      "192.168.0.5\nis IP-адрес",
                      "192.168.0.5\tis IP-адрес",
                      "IP-адрес : 192.168.0.5",
                      "----- 192.168.0.5 -----"
    };
    std::regex  IP_regex(  "^([0-9]{1,3}\.){3}[0-9]{1,3}($|[ \t\n])"  );
    for (const auto& line : lines2)
        cout << line << " : " << boolalpha << regex_search(line, IP_regex) << '\n';
    cout << "---------------------------\n";
    /*    На экран выведется :
        192.168.0.5: true
        192.168.0.123 : true
        192.168.0.5 is IP - адрес : true
        192.168.0.5
        is IP - адрес : true - т.е. с переходом на новую строку срабатывает
        192.168.0.5     is IP - адрес : true - с табуляцией срабатывает
        IP - адрес : 192.168.0.5 : false потому что не в начале, а в конце строки
        ---- - 192.168.0.5 ---- - : false потому что не в начале, а посредине строки
    */
    //----------------------------------------------------------
    /*  Если же мы хотим вывести на экран все строки с экземплярами IP-адресов
    независимо от того, в каком месте в строке они расположены (не обязательно 
    в начале строки), то тогда надо добавить и другие условия  в регулярное выражение :
    */
    string  lines3[] = {  "192.168.0.5",  "IP-адрес : 192.168.0.5",
                          "192.168.0.5 is IP-адрес", "192.168.0.5\nis IP-адрес"
                       };
    regex  IP_regex2(
    "^([0-9]{1,3}\.){3}[0-9]{1,3}($|[ \t\n])|.* ([0-9]{1,3}\.){3}[0-9]{1,3}($|[ \t\n])|.* ([0-9]{1,3}\.){3}[0-9]{1,3}($|[ \t\n].*)"
    );
    for (const auto& line : lines3)
        cout<< line << ": " << boolalpha << regex_search(line, IP_regex2) <<'\n';
    std::cout << "---------------------------\n";
    /*    На экран выведется :
      192.168.0.5: true
      IP - адрес : 192.168.0.5 : true
      192.168.0.5 is IP - адрес : true
      192.168.0.5
      is IP - адрес : true
    */
    //---------------------------------------------------------
// Задание 3: найти содержащие 4 цифры какие-либо суммы в долларах.
    string  lines4[] = { "Today I earned  $1234.",                   // это true
                          "Today I earned  1234 but lost  1234.",    // это false
                          "Today I earned  $123, but lost  $123."    // это false,
                          "Today I earned =$1234, but lost  o$1234." // это false
                       };
    std::regex Dolar_regex( " [\$][0-9]{4}" );
    for (const auto& line : lines4)
        cout << line << ": " << boolalpha << regex_search(line, Dolar_regex) << '\n';
    std::cout << "---------------------------\n";
    // ---------------------------------------------------------
    /*  Задание 4: найти такие строки, в которых ОТДЕЛЬНОЕ слово "name" 
    (или "Name")  стоит либо в самом начале, либо в самом конце предложения.   */
    std::string  lines5[] = { "This is your name.",
                              "This is your name",
                              "name is Ann",
                              "Name is Ann"
                            };
    std::regex Name_regex("(^[Nn]ame )|( name$)");
    for (const auto& line : lines5)
        cout<< line << ": " << std::boolalpha << regex_search(line, Name_regex) <<'\n';
    std::cout << "---------------------------\n";
    /*    На экран выведется :
      This is your name.: false
      This is your name: true
      name is Ann: true
      Name is Ann: true
    */
    // ---------------------------------------------------------
    /* Задание 6: нужно идентифицировать строки, начинающиеся с чисел
                  больших 4000, но меньших 5000.                          */
    std::string String__;
    for (int i=0; i<10; i++)
    {
        std::cout << "Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - ";
        getline(cin, String__);
        std::regex number_regex1(
        "(^|[ \t\r\n])4(([1-9][0-9][0-9])|([0-9][1-9][0-9])|([0-9][0-9][1-9]))($|[\.,:;г(г.)? \t\n])"
        );
        std::regex number_regex2(
        "(^|[ \t\r\n])4(?!000)[0-9][0-9][0-9]($|[\.,:;г(г.)? \t\n])"
        );
        cout << std::boolalpha << std::regex_search(String__, number_regex1) and
                std::regex_search(String__, number_regex2);
        cout << endl;
    }
    /*  Выведется, например, это :
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4000
     false
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001.
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001,
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001:
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001;
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001г
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001г.
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4001д
     false
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4999_
     true
     Введите целое число. Желательно чтоб оно было больше 4000, но меньше 5000. - 4999г
     true
    */
    // ---------------------------------------------------------
    /* Задание 7: нужно найти экземпляры, соответствующие слову Smith, но только в случае, 
    если это фамилия. Чтобы определить, является ли Smith фамилией или именем, мы укажем,
    что хотим проверить слово предшествующее найденному Smith, и, если это предшествующее
    слово начинается с заглавной буквы, то мы будем считать Smith фамилией:                 */
    std::string String___;
    for(int i=1; i<5; i++)
    {
        cout << "Введите фразу, содержащую слово Smith. Если перед ним будет стоять слово, ";
        cout << "\n  начинающееся с Заглавной буквы, то тогда будем считать Smith фамилией : \n";
        getline(cin, String___);
        regex  family_regex1(
            "(($|[ \t\r\n])Smith)|( mr.Smith)"
        );
        std::regex family_regex2(
            "(([A-Z][a-z]+[ \t\r\n]+Smith)|( mr.Smith))($|[\.,:;_?! \t\r\n])"
        );
        if (regex_search(String___, family_regex1) == 1)
            if (std::regex_search(String___, family_regex2) == 1)
                cout << " -- В данном случае Smith - это фамилия.  \n";
            else
                cout << " -- В данном случае Smith - это имя.  \n";
        else
            cout << "Во фразе нету слова Smith      \n";
    }
    cout << "-----------------------------------------------------\n";
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------
    // ---------------------------------------------------------

}