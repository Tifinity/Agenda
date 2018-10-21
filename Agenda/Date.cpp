#include <sstream>
#include <iostream>
#include <iomanip>
#include "Date.hpp"
using namespace std;

Date::Date(): m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) {}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
    : m_year(t_year),
      m_month(t_month),
      m_day(t_day),
      m_hour(t_hour),
      m_minute(t_minute) {}

Date::Date(const string &dateString) { 
    (*this) = stringToDate(dateString); 
}

int Date::getYear() const { 
    return m_year; 
}

void Date::setYear(const int t_year) { 
    m_year = t_year; 
}

int Date::getMonth() const { 
    return m_month; 
}

void Date::setMonth(const int t_month) { 
    m_month = t_month;
}

int Date::getDay() const { 
    return m_day;
}

void Date::setDay(const int t_day) { 
    m_day = t_day; 
}

int Date::getHour() const { 
    return m_hour; 
}

void Date::setHour(const int t_hour) { 
    m_hour = t_hour;
}

int Date::getMinute() const { 
    return m_minute; 
}

void Date::setMinute(const int t_minute) {
    m_minute = t_minute; 
}

bool Date::isValid(const Date &t_date) {
    int year = t_date.getYear();
    int month = t_date.getMonth();
    int day = t_date.getDay();
    if (year < 1000 || year > 9999 || month < 1 || 
        month > 12 || day < 1 || t_date.getHour() < 0 ||
        t_date.getHour() >= 24 || t_date.getMinute() < 0 ||
        t_date.getMinute() >= 60) {
        return false;
    }
    if (month == 2) {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if(day > 29) return false;
        }
        else {
            if(day > 28) return false;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11) {
        if(day > 30) return false;
    }
    else {
        if(day > 31) return false;
    }
    return true;
}

int stringToInt(string s) {
    int result;
    stringstream ss;
    ss << s;
    ss >> result;
    return result;
}

Date Date::stringToDate(const string &t_dateString) {
    Date date;
    if(t_dateString.length() != 16) {
        return date;
    }
    for(int i = 0; i < t_dateString.length(); i++) {
        if (i == 4) {
            if (t_dateString[4] != '-') return date;
        }
        else if (i == 7) {
            if (t_dateString[7] != '-') return date;
        }
        else if (i == 10) {
            if (t_dateString[10] != '/') return date;
        }
        else if(i == 13) {
            if (t_dateString[13] != ':') return date;
        }
        else {
            if (t_dateString[i] < '0' || t_dateString[i] > '9') return date;
        }
    }
    date.setYear(stringToInt(t_dateString.substr(0, 4)));
    date.setMonth(stringToInt(t_dateString.substr(5, 2)));
    date.setDay(stringToInt(t_dateString.substr(8, 2)));
    date.setHour(stringToInt(t_dateString.substr(11, 2)));
    date.setMinute(stringToInt(t_dateString.substr(14, 2)));
    return date;
}

string intToString(int a) {
    string result;
    stringstream ss;
    ss << setfill('0')<< setw(2) << a;
    ss >> result;
    return result;
}

string Date::dateToString(const Date &t_date) {
    string string = "";
    if (!isValid(t_date)) {
        string = "0000-00-00/00:00";
    }
    else {
        string = intToString(t_date.getYear()) + "-" 
               + intToString(t_date.getMonth()) + "-"
               + intToString(t_date.getDay()) + "/" 
               + intToString(t_date.getHour()) + ":"
               + intToString(t_date.getMinute());
    }
    return string;
}

Date &Date::operator=(const Date &t_date) {
    this->setYear(t_date.getYear());
    this->setMonth(t_date.getMonth());
    this->setDay(t_date.getDay());
    this->setHour(t_date.getHour());
    this->setMinute(t_date.getMinute());
    return (*this);
}

bool Date::operator==(const Date &t_date) const {
    return ((t_date.getYear() == this->m_year) &&
            (t_date.getMonth() == this->m_month) &&
            (t_date.getDay() == this->m_day) &&
            (t_date.getHour() == this->m_hour) &&
            (t_date.getMinute() == this->m_minute));
}

bool Date::operator>(const Date &t_date) const {
    return dateToString(*this) > dateToString(t_date);
}

bool Date::operator<(const Date &t_date) const {
    return !((*this) > t_date || (*this) == t_date);
}

bool Date::operator>=(const Date &t_date) const {
    return ((*this) == t_date || (*this) > t_date);
}

bool Date::operator<=(const Date &t_date) const {
    return ((*this) < t_date || (*this) == t_date);
}
