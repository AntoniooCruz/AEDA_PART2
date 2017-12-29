#ifndef AEDA_PLANE_H
#define AEDA_PLANE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Date.h"

using namespace std;

class Flight;

/**
 * @class Plane
 * @brief Asbtraction of a plane.
 */

class Plane
{
private:
    unsigned int id;					/** < @brief The id of the plane: it is unique */
    unsigned int nrPlaces;				/** < @brief Number of places of the plane */
    vector <Flight * > flights;			/** < @brief A vector of pointers to all of the flights of this plane */
	vector<string> seatsN;				/** < @brief A vector of strings which are the name of seats of the plane */
	string model;						/** < @brief The name of the model of the plane */
	int maintenanceRate;				/** < @brief The rate at which the plane must be inspected (in days) */
	Date nextMaintenance;		        /** < @brief How many days until the next maintenance */

public:
	/**
	 * @brief Default constructor of the plane - all the member values are initialized as 0
	 * Number of places and id is set to 0.
	 */
    Plane ();

	/**
	 * @brief Number of places are initialized with the parameter value; Id is set to 0; the plane's seats are named according to the number of places.
	 * @param nrPlaces The number of places of the plane
	 */
    Plane (unsigned int nrPlaces);

	Plane(unsigned int nrPlaces, string model, int maintenanceRate, Date nextMaintenance);

	/**
	 * @brief This constructor is used when reading form the files
	 * @param textLine All of the plane's information in a string: id ; number of places ; flight1 , flight2 , ...
	 */
    Plane (string textLine);

    /* get methods */

	/**
	 * @return The plane's id
	 */
    unsigned int getId() const ;

	/**
	 * @return The plane's number of places
	 */
    unsigned int getNrPlaces() const ;

	/**
	 * @brief Checks if there's a past flight and deletes it
	 * @return the plane's flights
	 */
    vector < Flight * > getFlights()  ;

	/**
	 * @return The number of flights assigned to the plane
	 */
    unsigned long getNrFlights () const ;

	/**
	 * @return The name of the seats of the plane
	 */
	vector<string> getSeatsNames() const;

	/**
	* @return The model of the plane
	*/
	string getModel() const;

	/**
	* @return The rate at which the plane must be inspected *
	*/
	int getMaintenanceRate() const;

	/**
	* @return How many days until the next inspection *
	*/
	Date getNextMaintenance() const;

	/* set methods */

	/**
	 * @brief Equals the id to the parameter - only used when the current id is 0
	 * @param id The new id of the plane
	 */
	void setId (unsigned int id);

	void changeMaintenance(Date newDate);

    /* others */
	/**
	 * @brief Names the plane's seats according to the number of places
	 */
	void nameSeats();

    /* edit flights */

	/**
	 * @brief Assigns a flight to the plane, adding it to vector flights
	 * @param f Flight to be added
	 * @throw repeatedFlight If there's already a flight at the same time of f, an exception is thrown and the flight is not added
	 * @return True if the flight was added
	 */
    bool addFlight(Flight *f);

	/**
	 * @brief Deletes a flight of the plane, erasing it from the vector flights
	 * @param nrid Id of the flight to be deleted
	 * @return A pointer to the deleted flight
	 */
    Flight * deleteFlight (unsigned int nrid);

	/**
	 * @brief Binary search of a flight based on its id
	 * @param nrid Id of the flight to be searched
	 * @param i Variable where the reference to the index of the flight on the plane's vector when the flight is found
	 * @throw noSuchFlight If a flight with the given id does not exist, the exception is thrown
	 * @return A pointer to the flight to be searched
	 */
    Flight * searchFlight (unsigned int nrid, int &i);


    Flight * postponeFlight (Flight * f, unsigned int duration);

	/**
	 * @brief Checks if a flight is smaller than another having pointers to that flights.
	 * A flight is smaller than another if it's date is previous
	 * @param f1 Pointer to the first flight
	 * @param f2 Pointer to the second flight
	 * @return true, if the first flight is previous, false otherwise
	 */
	static bool dateOrder(Flight * &f1, Flight * &f2);

	/**
	 * @brief Sorts the vector flights by the flights' departure date from the most recent one
	 */
    void sortFlightsDate ();

	/**
	 * @brief Sorts the vector flights by tge flights' id in ascending order
	 */
    void sortFlightsId ();

	/**
	 * @brief Erases flights which have already passed
	 * @return A vector of pointers to flights that will be erased
	 */
	vector <Flight *> clearPastFlights ();

	void rescheduleMaintenance(Date &d1);

	int doMaintenance();

    /* operator overloading */
	/**
	 * @brief Operator== overload. To plane's are equal if theirs ids are equal
	 * @param p Plane to which the plane will compared
	 * @return True, if the planes are equal or false, it they're not
	 */
    bool operator== (const Plane &p);

	/**
	 * @brief Operator< overload. One plane is bigger if its id is bigger
	 * @param p Plane to which the plane will compared
	 * @return True, if this plane is minor or false, if it's not
	 */
    bool operator< (const Plane &p);

	/**
	 * @brief Operator<< overload. Prints all of the plane information (id, number of places, flights).
	 * @param os
	 * @param p The plane to be printed
	 * @return os
	 */
	friend ostream& operator<< (ostream &os, const Plane &p);


};


#endif //AEDA_PLANE_H
