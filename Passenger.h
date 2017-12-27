#ifndef AEDA_PASSENGER_H
#define AEDA_PASSENGER_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Reservation.h"
#include "Date.h"
#include <unordered_set>

using namespace std;


class Reservation;

/*
 * @class Passenger Abstraction of a passenger
 */

class Passenger
{
private:
	string name;								/** < @brief Name of the passenger */
	Date anniversary;							/** < @brief The date of birth of the passenger*/
	vector<Reservation *> reserv;				/** < @brief A vector of pointers to the reservations the passenger made */


public:
	/**
	* @brief Constructor: Passengers constructor, the reservation vector is inilizated as empty
	* @param name The name of the passenger
	* @param name The passengers date of birth
	*/
	Passenger(string name, Date anniversary);
	/**
	* @return The passenger's name
	*/
	string getName() const;
	/**
	* @return The passenger's date of birth
	*/
	string getDateBirth() const;
	/**
	* @return The year when the passenger was born
	*/
	int getYear() const;
	/**
	* @return The month when the passenger was born
	*/
	int getMonth() const;
	/**
	* @return The day when the passenger was born
	*/
	int getDay() const;
	/**
	* @brief Calculates the discount that the passenger has
	* @param price The base price without any discount
	* @return The discount
	*/
	virtual float getDiscount(float price) const;
	/**
	* @brief Adds the reservation to the passenger
	* @param r A pointer to the reservation of the passenger
	*/
	virtual void addReservation(Reservation *r);
	/**
	* @return The vector with the pointers to the reservations of the passenger
	*/
	vector<Reservation *> getReserv();
	/**
	* @brief Returns a string used to see if the Passenger is a registred one or not
	* @return A string "Card" or "noCard"
	*/
	virtual string getType() const;

	/**
	* @brief Prints the reservation with the id i of the passenger on the screen
	* @param r The index of the reservation on the vector
	*/
	void printReservations(unsigned int i);
	/**
	* @brief Deletes a reservation of the passenger
	* @param seat The name of the seat of the reservation
	* @param idF The id of the flight of the reservation
	*/
	virtual Reservation deleteReserv(string seat, unsigned int idF);

	/**
	* @brief Operator == overload to compare 2 passengers.
	* @param p The Passenger to which this Passenger is compared
	* @return true if they have the same id
	*/
	bool operator== (const Passenger &p) const;
	

};

struct flightsYear {
	unsigned int year;
	unsigned int flight;

};
/**
* @class PassengerWCard Subclass of Passenger, this objects are registred to the company and have Id's job's and avergare flights per year
* @inherit class Passenger
*/
class PassengerWCard : public Passenger
{
private:
	unsigned int id;								/** < @brief Id of the passenger in the company */
	string phoneNumber;								/** < @brief phone number of the passenger in the company */
	vector <flightsYear> averageFlights;			
	float flightYear;								/** < @brief Average flights per year */
	string job;										/** < @brief Job of the passenger */
	Date lastTicketBought;							/** < @brief The date of the last ticket bought*/

public:
	
	PassengerWCard(unsigned int id, string name, string job, Date anniversary, vector<flightsYear> averageFlights);
	/**
	* @param name The Passenger's name
	* @param job The Passenger's job
	* @param anniversary The Passenger's date of birth
	*/
	PassengerWCard(string name, string job, Date anniversary);
	/**
	* @return A string with the passengers job
	*/
	string getJob() const;
	/**
	* @return LastTicketBought
	*/
	Date getLastTicketBought() const;
	/**
	* @return Average flights per year of the passenger
	*/
	float getAverageFlight() const;

	/**
	 * @return The vector of structs in which the flights of each year are stored
	 */
	vector <flightsYear> getFlightsPerYear () const;
	/**
	* @return Passenger's ID
	*/
	unsigned int getId() const;
	/**
	* @brief Calculates the discount based on the amount of flights per year
	* @param price The base price without any discount
	* @return The value of the discount
	*/
	float getDiscount(float price) const;
	/**
	* @brief Sets the Passengers id 
	* @param id New Id
	*/
	void setId (unsigned int id);
	/**
	* @brief change the Passengers phone number
	* @param new phone number
	* @return false if the new number has more or less than 9 digits
	*/
	bool setPhoneNumber(string pn);
	/**
	* @brief changes LastTicketBought
	*/
	void setLastTicketBought(Date lastTicketBought);
	/**
	* @brief Returns a string used to see if the Passenger is a registred one or not
	* @return A string "Card" or "noCard"
	*/
	string getType() const;
	/**
	* @return string with phone number
	*/
	string getPhoneNumber() const;
	/**
	* @brief Adds the reservation to the passenger
	* @param r A pointer to the reservation of the passenger
	*/
	void addReservation(Reservation *r);
	/**
	* @brief Operator < overload. Checks if a passenger is smaller than another one, based on the passenger'd ID
	* @param p The passenger we are comparing
	* @return If the first passenger's id < p2.id then return true, otherwise return false
	*/
	Reservation deleteReserv(string seat, unsigned int idF);

    bool operator< (const PassengerWCard &p) const;
	/**
	* @brief Operator << overload to print the information of a PassengerWCard
	* @param os
	* @param p The passenger that we are printing
	* @return
	*/
	friend ostream& operator<< (ostream &os, const PassengerWCard &p);
};



#endif //AEDA_PASSENGER_H
