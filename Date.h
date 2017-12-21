#ifndef AEDA_DATE_H
#define AEDA_DATE_H

#include <string>

using namespace std;

/**
 * @class Date It allows to save and manipulate dates (with the hour specified or only the day), get the current date and make arithmetic operations with dates
 */
class Date {
    unsigned int year, month, day;

public:
    /**
     * @brief Sets the year to 2017, the month to 1 and the day to 1
     */
    Date();

    /**
     * @brief All of the member values are initialized with the same value as a parameter
     * @param year The year of the date
     * @param month The month of the date
     * @param day The day of the date
     * @throw InvalidDate If the inputs are invalid
     */
    Date(unsigned int year, unsigned int month, unsigned int day);

    /**
     * @brief Copy constructor
     * @param d The date whose member values will be copied
     */
    Date(const Date &d);

    /**
     * @brief This constructor is used when reading from the files. All of the member values will be set according to the information in the parameter
     * @param date A string containing a date's information: year/month/day
     * @throw InvalidDate If the inputs are invalid
     */
    Date (string date);

    /* get methods */
    /**
     * @return The year of the date
     */
    unsigned int getYear() const;

    /**
     * @return The month of the date
     */
    unsigned int getMonth() const;

    /**
     * @return The day of the date
     */
    unsigned int getDay() const;

    /**
     * @return A date converted to a string: year/month/date
     */
    virtual string getDate() const;

    /**
     * @param date One of the date's member values: month or day
     * @return A string of the attribute received as a parameter. If it is smaller than 10, adds a 0 before the digit
     */
    string to_DateString(unsigned int date) const;

    /* set methods */
    /**
     * @brief Equals the date's member values to the parameters
     * @param year New year of the date
     * @param month New month of the date
     * @param day New day of the date
     * @throw InvalidDate If the inputs are invalid
     */
    void setDate (unsigned int year, unsigned int month, unsigned int day);

    /**
     * @brief Sets the date's year to a new one
     * @param year New year of the date
     */
    void setYear(unsigned int year);

    /**
     * @brief Sets the date's month to a new one
     * @param month New month of the date
     */
    void setMonth(unsigned int month);

    /**
     * @brief Sets the date's day to a new one
     * @param year New day of the date
     */
    void setDay(unsigned int day);

    /**
    * @brief Checks if a date refers to a moment from the past
    * @param year Year of the date
    * @param month Month of the date
    * @param day Day of the date
    * @return True, if the date has already passed, False, otherwise
    */
    static bool past (unsigned int year, unsigned int month, unsigned int day);

    /* operator overloading */
    /**
     * @brief Operator << overload to print a date: year/month/day
     * @param os
     * @param d Date to be printed
     * @return
     */
    friend ostream &operator<<(ostream &os, const Date &d);

};

/**
 * @class DateFlight Abstraction of a date used to book a flight. The member values include hours and minutes.
 * @inherit Date
 */

class DateFlight : public Date {
    unsigned int hour, minutes;

public:
    /**
     * @brief Sets the hour and the minutes to 0
     */
    DateFlight();

    /**
     * @brief All of the member values are initialized with the same value as a parameter
     * @param year The year of the date
     * @param month The month of the date
     * @param day The day of the date
     * @param hour The hour of the date
     * @param minutes The minutes of the date
     * @throw InvalidDate If the inputs are invalid or if the date has already passed
     */
    DateFlight(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes);

    /**
     * @brief Copy constructor
     * @param d The date whose member values will be copied
     */
    DateFlight(const DateFlight &d);

    /* get methods */
    /**
     * @return The hour of the date
     */
    unsigned int getHour() const;

    /**
     * @return The minutes of the date
     */
    unsigned int getMinutes() const;

    /**
     * @return A date converted to a string: year/month/date - hour:minutes
     */
    string getDate() const;

    /* set methods */
    /**
     * @brief Equals the date's member values to the parameters
     * @param year New year of the date
     * @param month New month of the date
     * @param day New day of the date
     * @param hour New hour of the date
     * @param minutes New minutes of the date
     * @throw InvalidDate If the inputs are invalid
     */
    void setDate (unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes);

    /**
     * @brief Equals the date's member values to the parameters
     * @param hour New hour of the date
     * @param minutes New minutes of the date
     */
    void setDate (unsigned int hour, unsigned int minutes);

    /* operator overloading*/
    /**
     * @brief Operator < overload to compare 2 dates of flights. One date is smaller than the other if it is previous to the latter.
     * @param d The date of a flight to which this date is compared to
     * @return True, if this date is previous to the other one, False, otherwise
     */
    bool operator<(const DateFlight &d) const;

    /**
     * @brief Operator == overload to compare 2 dates of flights. Two dates are equal if all of their member values are equal
     * @param d The date of a flight to which this date is compared to
     * @return True, if they're equal, False otherwise
     */
    bool operator==(const DateFlight &d) const;

    /**
     * @brief Operator + overload to add a date to a int.
     * @param add The value to be added to the date of a flight
     * @return The date that differs add minutes from this date
     */
    DateFlight operator+(unsigned int add) const;

    /**
     * @brief Operator - overload to calculate the difference between to dates
     * @param d2 The date to subtract from this date
     * @return Number of minutes that 2 date differ from one another
     */
    float operator-(const DateFlight &d2) const;

    /**
     * @brief Operator << overload to print a date : year/month/day - hour:minutes
     * @param os
     * @param d Date to be printed
     * @return os
     */
    friend ostream &operator<<(ostream &os, const DateFlight &d);

    /* static methods */
    /**
     * @brief Calculates the current time
     * @return The date matches the current time
     */
    static DateFlight getNow();

    /**
     * @brief Checks if a date refers to a moment from the past
     * @param year Year of the date
     * @param month Month of the date
     * @param day Day of the date
     * @param hour Hour of the date
     * @param minutes Minutes of the date
     * @return True, if the date has already passed, False, otherwise
     */
    static bool past (unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes);

};

#endif //AEDA_DATE_H

