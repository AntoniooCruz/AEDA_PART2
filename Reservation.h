#pragma once


#include "Company.h"
#include "Flight.h"
#include "Passenger.h"
#include <iostream>
#include <sstream>

class Flight;
class Passenger;
class Company;


using namespace std;

/**
* @class Reservation A class containing the information about a reservation: Flight/Passenger/Price/seat
*/
class Reservation
{
private:
	Flight * flight;					 /** < @brief Pointer to the flight where the reservation was made */
	Passenger * passenger;				/** < @brief Pointer to the passenger who made the reservation */
	float price;						/** < @brief Cost of the reservation*/
	string seat;						/** < @brief The name of the seat of the reservation */

public:
	/**
	* @brief Constructor: Basic constructor with no parameters 
	*/
	Reservation();
	/**
	* @brief Constructor: This constructor is used when reading from a file
	* @param textLine is the line that we get from the file containing all the necessary information
	* @param company is the pointer to the company where this reservation was made
	* @param hasCard specifies whether the passenger who owns the reservation is registred in the company
	*/
	Reservation(string textLine, Company * company, bool hasCard);
	/**
	* @param Constructor: flight is the flight where the reservation was made
	* @param passenger is the passenger who owns the reservation
	* @param price is the cost of the seat
	* @param seat is the reserved seat
	*/
	Reservation(Flight * flight, Passenger * passenger, float price,string seat);
	/**
	* @return Returns the flight of the reservation
	*/
	Flight * getFlight() const;
	/**
	* @return Returns the Passenger that made the reservation
	*/
	Passenger * getPassenger() const;
	/**
	* @return Returns the price of the reservation
	*/
	float getPrice() const;
	/**
	* @return Returns the seat of the reservation
	*/
	string getSeat() const;
	/**
	* @brief Operator == overload to to check if 2 reservations are equal
	* @param r the reservation we are comparing to
	* @return Returns true or false whether they are equal or not
	*/
	bool operator== (const Reservation &r) const;
	/**
	* @brief Operator << overload to print a reservation
	* @param os
	* @param r The reservation that will be printed
	* @return
	*/
	friend ostream& operator<< (ostream &os, const Reservation &r);
};