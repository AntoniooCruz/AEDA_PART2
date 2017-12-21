#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "Plane.h"
#include "Reservation.h"
#include "Date.h"
#include <map>
#include <algorithm>
//#include "Date_Time.h"

class Reservation;

using namespace std;

/**
 * @class Flight Abstract class that allows to manipulate and edit a flight
 */
class Flight
{
private:
    unsigned int id;                /** < @brief The id of the plane: it is unique */
    static unsigned int lastId;     /** < @brief Static attribute where the last flight's id is saved */
    const string aDep;              /** < @brief The flight's departure airport */
    const string aArr;              /** < @brief The flight's arrival airport */
    Plane * plane;                  /** < @brief A pointer to the plane to which the flight was assigned */
    DateFlight departHour;          /** < @brief The flight's departure date - day and hour */
    int duration;                   /** < @brief The flight's duration */

public:

    /**
     * @brief Constructor: the flight's id is set by adding one to the static member lastId, the pointer to the plane is NULL
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     */
    Flight(string aDep, string aArr, const DateFlight &departHour, int duration);

    /**
     * @brief Constructor: the flight's id is set by adding one to the static member lastId
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param plane The plane to which the flight was assigned
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     */
    Flight(string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration);

    /**
     * @brief Constructor: if the id is greater than lastId, the latter is set to id.
     * This constructor should only be used when reading from the files
     * @param id The flight's id
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param plane The plane to which the flight was assigned
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     */
    Flight(unsigned int id, string aDep, string aArr, Plane * plane, const DateFlight &departHour, unsigned int duration);

    /* get methods */
    /**
     * @return The flight's departure airport
     */
    string getADep() const;

    /**
     * @return The flight's arrival airport
     */
    string getAArr() const;

    /**
     * @return A pointer to the flight's plane
     */
    Plane * getPlane() const;

    /**
     * @return The flight's id
     */
    unsigned int getId() const;

    /**
     * @return The flight's duration
     */
    unsigned int getDuration() const;

    /**
     * @return The flight's departure date ready to be printed as a string
     */
    string getDepDate() const;

    /**
     * @return The flight's arrival date ready to be printed as a string
     */
    string getArrDate() const;

    /**
     * @return The flight's departure date
     */
    DateFlight getDepHour() const;

    /**
     * @return The flight's arrival date
     */
    DateFlight getArrHour() const;

    /**
     * @return The flight's type: Commercial or Private
     */
    virtual string getType() const = 0;

    /**
     * @return The flight's total price (if it is a Private Flight) or a seat's price
     */
    virtual float getPrice() const = 0;

    /**
     * @return false A flight's price only has a discount if it is a commercial flight
     */
    virtual bool getDiscount() const;

    /**
     * @return The value of the member type lastId
     */
    static unsigned int getLastId();

    /* set methods */
    /**
     * @brief Changes the pointer to the plane
     * @param plane New plane to which the flight was assigned
     */
    void setPlane (Plane * plane);

    /**
     * @brief Changes the departureHour
     * @param newDepartHour New departure date
     */
    void setDepartHour(DateFlight newDepartHour);

    /**
     * @brief Changes the duration of the flight
     * @param newDuration New duration of the flight
     */
    void setDuration(int newDuration);

    /**
     * @brief Changes the flight's id
     * @param id New id of the flight
     */
    void setId(unsigned int id);

    /**
     * @brief Calculates the newId based of the value of lastId
     * @return a possible id to a flight: lastId + 1
     */
    static unsigned int newId();


    /* operator overloading */
    /**
     * @brief Operator == overload to compare 2 flights. Two flights are equal if are in the air at the same time
     * @param f The flight to which this flight is compared
     * @return true, If the flights happen at the same time, false, If they don't
     */
    bool operator== (const Flight &f) const;

    /**
     * @brief Operator < overload to compare 2 flights. One flight is smaller if it's id is smaller
     * @param f The flight to which this flight is compared
     * @return true, If this flight is smaller, false, If it's not
     */
    bool operator< (const Flight &f) const;

    /**
     * @brief Operator << overload to print a flight.
     * It's printed the date of take off, the departure airport, the arrival airport, the id, the type (Commercial or Private), the duration and the price.
     * @param os
     * @param f The flight to be printed
     * @return
     */
    friend ostream& operator<< (ostream &os, const Flight &f);

    /**
     * @brief Operator << overload to print a vector of flights.
     * It's printed all of the flights' information in a table
     * @param os
     * @param fs The vector of pointers to flights that will be printed
     * @return
     */
    friend ostream& operator<< (ostream &os, const vector<Flight *> &fs);

};

/**
 * @class FCommercial Abstraction of a Commercial flight, flight whose seats are sold individually
 * @inherit class Flight
 */
class FCommercial : public Flight {
    map<string, Reservation> reservedSeats;         /** < @brief First: name of the seat; Second: reservation */
    vector<string> availableSeats;                  /** < @brief vector of strings which are the name of seats that are still available */
    float price;                                    /** < @brief price of one seat with no discounts */

public:
    /**
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     * @param price The price of one seat with no discounts
     */
    FCommercial(string aDep, string aArr, const DateFlight &departHour, int duration, float price);

    /**
     * @brief In this constructor availableSeats are iniatiliazed
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param plane The plane to which the flight was assigned
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     * @param price The price of one seat with no discounts
     */
    FCommercial(string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration, float price);

    /**
    * @brief This constructor should only be used when reading from the files, otherwise the id is set by calling the static method newId()
    * @param id The flight's id
    * @param aDep The flight's departure airport
    * @param aArr The flight's arrival airport
    * @param plane The plane to which the flight was assigned
    * @param departHour The flight's departure date
    * @param duration The flight's duration
    * @param price The price of one seat with no discounts
    */
    FCommercial(unsigned int id, string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration, float price);


    /**
     * @return The reservations made to this flight
     */
    map<string, Reservation> getReservations() const;

    /**
     * @return The type of flight: Commercial
     */
    string getType() const;

    /**
     * @return The price of one seat with discount if applicable
     */
    float getPrice() const;

    /**
     * @return The seats that are still available
     */
    vector <string> getAvailableSeats() const;

    /**
     * @return true If the price has a discount or false, otherwise
     */
    bool getDiscount() const;

    /**
     * @brief Checks if a seat is available for purchase
     * @param seat Name of the seat to check
     * @return true, If it's available, false otherwise
     */
    bool seatAvailable(string seat) const;

    unsigned int findSeat(string seat);
    void setAvailableSeats();
    void showAvailableSeats() const ;
    void fixSeats();
    bool addReservation(Reservation * p);
    bool removeReservation(string seat,string name); // pode haver pessoas com o mesmo nome... se nao for preciso posso por so a usar o nome
};

/**
 * @class FPrivate Abstraction of a private flight - flight whose seats are sold all at once
 */

class FPrivate : public Flight {
    float price;

public:
    /**
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     * @param price The price of all seats
     */
    FPrivate(string aDep, string aArr, const DateFlight &departHour, int duration, float price);

     /**
     * @param aDep The flight's departure airport
     * @param aArr The flight's arrival airport
     * @param plane The plane to which the flight was assigned
     * @param departHour The flight's departure date
     * @param duration The flight's duration
     * @param price The price of all seats
     */
    FPrivate(string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration, float price);

    /**
    * @brief This constructor should only be used when reading from the files, otherwise the id is set by calling the static method newId()
    * @param id The flight's id
    * @param aDep The flight's departure airport
    * @param aArr The flight's arrival airport
    * @param plane The plane to which the flight was assigned
    * @param departHour The flight's departure date
    * @param duration The flight's duration
    * @param price The price of all seats
    */
    FPrivate(unsigned int id, string aDep, string aArr, Plane * plane, DateFlight departHour, int duration, float price);

    /**
    * @return The type of flight: Private
    */
    string getType() const;

    /**
     * @return The price of all seats
     */
    float getPrice() const;
};
