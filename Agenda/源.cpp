#include <iostream>
#include "Date.hpp"
using namespace std;

int main() {
    string str1 = "15000-02-01/04:00";
    Date date(str1);
    Date date2("3000-02-29/04:00");
    Date date3 = date;
    if (date2 < date) cout << 1 << endl;
    if (date > date2) cout << 1 << endl;
    if (date3 >= date) cout << 32 << endl;
    if (date == date2) cout << 00 << endl;
    cout << date.getYear() << date.getMonth() << date.getDay();
    return 0;
}