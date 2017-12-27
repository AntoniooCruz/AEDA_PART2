
#define _CRT_SECURE_NO_WARNINGS

#include <sstream>
#include "Date.h"
#include "Exceptions.cpp"
#include <time.h>
#include <ctime>

Date::Date() {
    this->year = 2017;
    this->month = 1;
    this->day = 1;
}

Date::Date (unsigned int year, unsigned int month, unsigned int day){
    this->year = year;
    this->month = month;
    this->day = day;

   if (month < 1 || month > 12 || day < 1 || day > 31)
      throw InvalidDate (day, month, year);
}

Date::Date (const Date &d) {
    this->year = d.getYear();
    this->month = d.getMonth();
    this->day = d.getDay();
}

Date::Date (string date) {
    istringstream dateStream (date);
    char aux;

    dateStream >> year >> aux >> month >> aux >> day;

    if ( 1 < month || month > 12 || 1 < day || day > 31 )
        throw InvalidDate (day, month, year);

}

/* get methods */
unsigned int Date::getYear() const {
    return year;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getDay() const{
    return day;
}

string Date::getDate() const {
    string syear;

    if (year < 100)
        syear = "19"+to_string(year);
    else
        syear = to_string(year);

    return (syear + "/" + to_DateString(month) + "/" + to_DateString(day));
}

Date Date::getNow() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return Date (now->tm_year + 1900, (now->tm_mon + 1), now->tm_mday);
}

string Date::to_DateString (unsigned int date) const {
    if (date < 10)
        return ("0" + to_string(date));

    return to_string(date);

}


/* set methods */
void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {

    if (month < 1 || month > 12 || day < 1 || day > 31)
        throw InvalidDate (day, month, year);

    this->year = year;
    this->month = month;
    this->day = day;


}

void Date::setYear(unsigned int year) {
    this->year = year;
}

void Date::setMonth (unsigned int month) {
    if (month < 1 || month > 12)
        throw InvalidDate (day, month, year);

    this->month = month;
}

void Date::setDay (unsigned int day) {
    if (day < 1 || day > 31)
        throw InvalidDate (day, month, year);

    this->day = day;
}

bool Date::past(unsigned int year, unsigned int month, unsigned int day) {
    time_t t = time(0);
    struct tm * now = localtime(&t);

    if (year == now->tm_year + 1900) {

        if (month == now->tm_mon + 1) {

            return (day < now->tm_mday);
        }
        return (month < now->tm_mon + 1);
    }
    return (year < now->tm_year + 1900);
}

bool Date::operator< (const Date &d) const{
    if (getYear() == d.getYear()) {

        if (getMonth() == d.getMonth()) {

            return getDay() < d.getDay();
        }
        else {
            return getMonth() < d.getMonth();
        }
    }
    else {
        return getYear() < d.getYear();
    }
}

bool Date::operator== (const Date &d) const {
    return (getYear() == d.getYear() && getMonth() == d.getMonth() && getDay() == d.getDay());
}

Date Date::operator+(int add) const {
    unsigned int eDay = getDay() + add, eMon = getMonth(), eYea = getYear();


            if (eDay > 30) {
                eMon = eMon + eDay/30;
                eDay = eDay % 30;
            }

            if (eMon > 12) {
                eYea = eYea + eMon/12;
                eMon = eMon % 12;
            }

    Date sum (eYea, eMon, eDay);

    return sum;
}

float Date::operator-(const Date & d2) const
{
	int Y, m, d;
	Y = getYear() - d2.getYear();
	m = getMonth() - d2.getMonth();
	d = getDay() - d2.getDay();

	return Y * 8640 + 720 * m + d * 24;
}

ostream& operator<< (ostream &os, const Date &d) {
    os << d.getDate();

    return os;
}


/* DATE FLIGHT METHODS */

/* constructors */

DateFlight::DateFlight() : Date () {
    this->hour = 0;
    this->minutes = 0;
}

DateFlight::DateFlight(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes) : Date (year, month, day) {
    this->hour = hour;
    this->minutes = minutes;

    if ( month < 1 || month > 12 || day < 1 || day > 31 || hour > 23 || minutes > 59 || past(year, month, day, hour, minutes)) {
        throw InvalidDate(minutes, hour, day, month, year);
    }
}

DateFlight::DateFlight(const DateFlight &d) : Date (d.getYear(), d.getMonth(), d.getDay()) {
    this->hour = d.getHour();
    this->minutes = d.getMinutes();
}



/* get methods */

unsigned int DateFlight::getHour() const {
    return hour;
}

unsigned int DateFlight::getMinutes() const {
    return minutes;
}

string DateFlight::getDate() const {

    return (Date::getDate() + " - " + to_DateString(hour) + ":" + to_DateString(minutes));
}

/* set methods */
void DateFlight::setDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes) {

    if ( month < 1 || month > 12 || day < 1 || day > 31 || hour > 23 || minutes > 59 || past(year, month, day, hour, minutes)) {
        throw InvalidDate(minutes, hour, day, month, year);
    }

    Date::setDate(year, month, day);

    this->hour = hour;
    this->minutes = minutes;
}

void DateFlight::setDate(unsigned int hour, unsigned int minutes) {
    if (hour > 23 || minutes > 59) {
        throw InvalidDate(minutes, hour, getDay(), getMonth(), getYear());
    }

    this->hour = hour;
    this->minutes = minutes;
}


/* operator overloading*/

bool DateFlight::operator< (const DateFlight &d) const{
    if (getYear() == d.getYear()) {

        if (getMonth() == d.getMonth()) {

            if (getDay() == d.getDay()) {

                if (hour == d.getHour()) {
                    return minutes < d.getMinutes();
                }
                else {
                    return hour < d.getHour();
                }
            }
            else {
                return getDay() < d.getDay();
            }
        }
        else {
            return getMonth() < d.getMonth();
        }
    }
    else {
        return getYear() < d.getYear();
    }
}

bool DateFlight::operator== (const DateFlight &d) const {
    return (getYear() == d.getYear() && getMonth() == d.getMonth() && getDay() == d.getDay() && hour == d.getHour() && minutes == d.getMinutes());
}

DateFlight DateFlight::operator+ (unsigned int add) const{
    unsigned int eMin = minutes + add, eHour = hour, eDay = getDay(), eMon = getMonth(), eYea = getYear();

    if (eMin >= 60){
        eHour = eHour + eMin/60;
        eMin = eMin % 60;

        if (eHour >= 24) {
            eDay = eDay + eHour/24;
            eHour = eHour % 24;

            if (eDay >= 30) {
                eMon = eMon + eDay/30;
                eDay = eMon % 30;
            }

            if (eMon >= 12) {
                eYea = eYea + eMon/12;
                eMon = eYea % 12;
            }
        }
    }

    DateFlight sum (eYea, eMon, eDay, eHour, eMin);

    return sum;
}

float DateFlight::operator-(const DateFlight & d2) const // mes == 30 dias
{
    int Y, m, d, H, M;
    Y = getYear() - d2.getYear();
    m = getMonth() - d2.getMonth();
    d = getDay() - d2.getDay();
    H = hour - d2.hour;
    M = minutes - d2.minutes;

    return Y * 8640 + 720 * m + d * 24 + H + ((float) M / (float)60.0000);
}

ostream& operator<< (ostream &os, const DateFlight &d) {
    os << d.getDate();

    return os;
}


/* static methods */
DateFlight DateFlight::getNow()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    /*const auto now = time(nullptr);
    char cstr[256]{};
    string str =  strftime(cstr, sizeof(cstr), "%Y %m %d %H %M", localtime_s(&now)) ? cstr : ""; //ex: 2001 12 31 12 32
    stringstream stream(str);
    int Y, m, d, H, M;
    stream >> Y >> m >> d >> H >> M;*/
    return DateFlight(now->tm_year + 1900, (now->tm_mon + 1), now->tm_mday, now->tm_hour, now->tm_min);
}


bool DateFlight::past(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes) {
    time_t t = time(0);
    struct tm * now = localtime(&t);

    if (year == now->tm_year + 1900) {

        if (month == now->tm_mon + 1) {

            if (day == now->tm_mday) {

                if (hour == now->tm_hour) {

                    return (minutes < now->tm_min);
                }
                return (hour < now->tm_hour);
            }
            return (day < now->tm_mday);
        }
        return (month < now->tm_mon + 1);
    }
    return (year < now->tm_year + 1900);
}
