#ifndef AEDA_EXCEPTIONS_H
#define AEDA_EXCEPTIONS_H

#include "Flight.h"

/**
 * @class NoSuch Exception thrown when an object doesn't exist
 */
class NoSuch {
    unsigned int id;
public:
    NoSuch (unsigned int id) {
        this->id = id;
    }
    unsigned int getId(){
        return id;
    }
    virtual string getType() = 0;
};

/**
 * @class NoSuchFlight Exception thrown when a flight doesn't exist
 * @inherit NoSuch
 */
class NoSuchFlight : public NoSuch {
public:
    NoSuchFlight (unsigned int id) : NoSuch (id) {}
    string getType() {
        return "Flight";
    }
};

/**
 * @class NoSuchPlane Exception thrown when a plane doesn't exist
 * @inherit NoSuch
 */
class NoSuchPlane : public NoSuch {
public:
    NoSuchPlane (unsigned int id) : NoSuch (id) {}
    string getType() {
        return "Plane";
    }
};

/**
 * @class NoSuchPassenger Exception thrown when a passenger doesn't exist
 * @inherit NoSuch
 */
class NoSuchPassenger : public NoSuch {
public:
	NoSuchPassenger(unsigned int id) : NoSuch(id) {}
	string getType() {
		return "Passenger";
	}
};

class NoSuchTechnician : public NoSuch {
public:
    NoSuchTechnician(unsigned int id) : NoSuch(id) {}
    string getType() {
        return "Technician";
    }
};

/**
 * @class ErrorOpeningFile Exception thrown when there's an error opening a file
 */
class ErrorOpeningFile {
    string nameFile;
public:
    ErrorOpeningFile (string name) {
        nameFile = name;
    }
    string getFileName () {
        return nameFile;
    }
};

/**
 * @class Repeated Exception thrown when there are 2 equal objects
 */
class Repeated {
    unsigned int id;
public:
    Repeated (unsigned int id) {
        this->id = id;
    }
    unsigned int getId(){
        return id;
    }
    virtual string getType() = 0;
};

/**
 * @class RepeatedFlight Exception thrown when there are 2 equal flights
 * @inherit Repeated
 */
class RepeatedFlight : public Repeated {
public:
    RepeatedFlight (unsigned int id) : Repeated (id) {}
    string getType() {
        return "Flight";
    }
};

/**
 * @class RepeatedPlane Exception thrown when there are 2 equal planes
 * @inherit Repeated
 */
class RepeatedPlane : public Repeated {
public:
    RepeatedPlane (unsigned int id) : Repeated (id) {}
    string getType() {
        return "Plane";
    }
};

/**
 * @class RepeatedPassenger Exception thrown when there are 2 equal passengers
 * @inherit Repeated
 */
class RepeatedPassenger : public Repeated {
public:
	RepeatedPassenger(unsigned int id) : Repeated(id) {}
	string getType() {
		return "Passenger";
	}
};

/**
 * @class InvalidDate Exception thrown when a Date is invalid
 */
class InvalidDate {
    int minutes;
    int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:


    InvalidDate (int minutes, int hour, unsigned int day, unsigned int month, unsigned int year) {
        this->minutes = minutes;
        this->hour = hour;
        this->day = day;
        this->month = month;
        this->year = year;

    }

    InvalidDate (unsigned int day, unsigned int month, unsigned int year) {
        this->minutes = -1;
        this->hour = -1;
        this->day = day;
        this->month = month;
        this->year = year;
    }


    string getDate () const {
        if (minutes < 0 || hour < 0) {
            return to_string(year) + "/" + to_string(month) + "/" + to_string(day);
        }
        else {
            return to_string(year) + "/" + to_string(month) + "/" + to_string(day) + " - " + to_string(hour) + ":" + to_string(minutes);
        }
    }
};

/**
 * @class OperationCanceled Exception thrown when a operation is canceled by the user
 */
class OperationCanceled {
public:
    OperationCanceled () {}
};

#endif //AEDA_EXCEPTIONS_H

