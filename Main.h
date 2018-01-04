#ifndef AEDA_MAIN_H
#define AEDA_MAIN_H

#include <string>
#include <fstream>
#include <iomanip>
#include "Company.h"


/**
* @brief Checks if the input is of type int and is between a range of values
* not returning any value until it reads a valid input
* @param linf The minimum value possible
* @param lsup The maximum value possible
* @return The first correct input
*/
int checkBoundaries(int linf, int lsup);

/**
* @brief Checks if the input is of type int and is bigger than a value
* not returning any value until it reads a valid input
* @param linf The minimum value possible
* @return The first correct input
*/
int checkBoundaries(int linf);

/**
* @brief Checks if the input is of type float and is bigger than a value
* not returning any value until it reads a valid input
* @param linf The minimum value possible
* @return The first correct input
*/
float checkFloatBoundaries (float linf);

/* MENUS */
/**
* @brief Displays the first menu that allows the user to manage planes, flights, passengers or reservations
* @param companyName The company whose data will be edit or displayed
*/
void mainMenu(Company &companyName);

/**
* @brief Displays the menu to manage, edit and print planes' data
* @param companyName The company whose data will be edit or displayed
*/
void planesMenu(Company &companyName);

/**
* @brief Displays the menu to manage, edit and print flights' data
* @param companyName The company whose data will be edit or displayed
*/
void flightsMenu(Company &companyName);

/**
* @brief Displays the menu to manage, edit and print passengers' data
* @param companyName The company whose data will be edit or displayed
*/
void passengersMenu(Company &companyName);

/**
* @brief Displays the menu to manage, edit and print reservations' data
* @param companyName The company whose data will be edit or displayed
*/
void reservationsMenu(Company &companyName);

/**
 * @brief Displays the menu to manage, edit, print maintenances' data
 * @param companyName The company whose data will be edited or displayed
 */
void maintenanceMenu(Company &companyName);

/**
 * @brief Displays the menu to manage, edit, print technicians' data
 * @param companyName The company whose data will be edited or displayed
 */
void technicianMenu (Company &companyName);

/* MANAGE PLANES */
/**
* @brief User's interface to create a plane: the user is asked for the nr of places of the plane.
* The plane's information is printed at the end if it was added successfully
* @throw operationCanceled If the user's input is 0, the plane is not created
* @param companyName The company where to the plane is added
*/
void addPlane(Company &companyName);


/**
* @brief User's interface to delete a plane: the user is asked for plane's id.
* The plane's information is printed at the end if it was deleted successfully
* @throw operationCanceled If the user's input is 0, no plane is deleted
* @param companyName The company where to the plane is deleted from
*/
void deletePlane(Company &companyName);

/**
 * @brief Prints all flights of a plane sorted by date: the user is asked for the plane's id
 * @throw operationCanceled If the user's input is 0, no flights are shown
 * @param companyName The company to which the plane belongs
 */
void printFlights(Company &companyName);

/**
 * @brief Prints a plane's information (id, number of places, flights): the user is asked for the plane's id
 * @throw operationCanceled If the user's input is 0, no information is shown
 * @param companyName The company to which the plane belongs
 */
void printPlaneInformation(Company &companyName);

/**
 * @brief All plane's information (id, number of places, flights) is printed
 * @param companyName The company to which all of the planes belong to
 */
void printAllPlanes(Company &companyName);


/* MANAGE PLANES */
/**
* @brief User's interface to add a Flight: the user is asked for the departure airport, the arrival airport, the time of take off, the duration of the journey, the type of flight (commercial or private) and the price of one or all seats (depending of the type of plane).
* The plane is assigned automatically. If no plane's is available the user can choose to create one.
* The flight's information is printed at the end if it was created successfully
* @throw operationCanceled If the user's input at any time is 0, no flight is created
* @param companyName The company where the flight is added to
*/
void addFlight(Company &companyName);

/**
* @brief User's interface to delete a flight: the user is asked for the flight id
* The flight's information is printed at the end if it was created successfully
* @throw operationCanceled If the user's input at any time is 0, no flight is canceled
* @param companyName The company where the flight is canceled from
*/
void cancelFlight(Company &companyName);

/**
* @brief User's interface to postpone a flight: the user is asked for the flight id and for the new departure date or the minutes of delayed
* The updated flight's information is printed at the end if it was postpone successfully
* @throw operationCanceled If the user's input at any time is 0, no flight is postpone
* @param companyName The company to which the flight belongs to
*/
void postponeFlight(Company &companyName);

/**
 * @brief All flights's information (id, departure hour, departure airport, arrival airport, type of flight, duration, price) is printed
 * @param companyName The company to which all of the flights belong to
 */
void printAllFlights(Company &companyName);

/**
 * @brief User's interface to know all the flights departing from or arriving on an airport
 * @param companyName The company to which all the flights belong
 */
void printFlightsAirport (Company &companyName);

/* MANAGE PASSENGERS */

/**
* @brief User's interface to register a passenger: the user is asked for the name of the passenger, his birthday, his job, his average of flights per year.
* The passenger's id is assigned automatically. The passenger's information is printed at the end if it was added successfully
* @throw operationCanceled If the user's input is 0, the passenger is not registered
* @param companyName The company where to the passenger is registering
*/
void addPassenger(Company &companyName);

/**
* @brief User's interface to change the phone number registered a passenger: the user is asked for the passenger's id.
* The passenger's information is printed at the end if the operation was successfully
* @throw operationCanceled If the user's input is 0
* @param companyName The company where to the passenger is being deleted from
*/
void changePhoneNumber(Company &companyName);

/**
* @brief User's interface to delete registered a passenger: the user is asked for the passenger's id.
* The passenger's information is printed at the end if it was deleted successfully
* @throw operationCanceled If the user's input is 0, the passenger is not deleted
* @param companyName The company where to the passenger is being deleted from
*/
void deletePassenger(Company &companyName);

/**
* @brief Prints all of a passenger's reservations: the user is asked for the passenger's id.
* @throw operationCanceled If the user's input is 0, nothing is displayed on the screen
* @param companyName The company where to the passenger is registered
*/
void printPassengerReservations(Company &companyName);

/**
* @brief Prints a passenger's information (id, name, job, date of birth, average flights per year) : the user is asked for the passenger's id.
* @throw operationCanceled If the user's input is 0, nothing is displayed on the screen
* @param companyName The company where to the passenger is registered
*/
void printPassengerInformation(Company &companyName);

/**
* @brief Prints all passengers' information (id, name, job, date of birth, average flights per year).
* @param companyName The company where to the passengers are registered
*/
void printAllPassengers(Company &companyName);


/* MANAGE RESERVATIONS*/
/**
 * @brief User's interface to make a reservation of a registered passenger: user is aked for the passenger's id, the departure airport, the id of the flight, the seat.
 * The reservation's information is printed at the end, if it was created successfully
 * @throw operationCanceled If the user's input is 0, no reservation is created
 * @param companyName The company to which a reservation is being made
 */
void addReservationToPass(Company &companyName);

/**
 * @brief User's interface to make a reservation of a not registered passenger: user is aked for the passenger's name, his birthday, the departure airport, the id of the flight, the seat.
 * The reservation's information is printed at the end, if it was created successfully
 * @throw operationCanceled If the user's input is 0, no reservation is created
 * @param companyName The company to which a reservation is being made
 */
void addReservationAndNewPass(Company &companyName);

/**
 * @brief User's interface to delete a reservation: user is aked for the passenger's name, the flight's id, the seat.
 * @throw operationCanceled If the user's input is 0, no reservation is created
 * @param companyName The company from which the reservation is being deleted
 */
void deleteReservation(Company &companyName);

/**
 * @brief Prints all of the reservations of registered passengers an non registered passengers
 * @param companyName The company to which the reservations belong
 */
void printAllReservations (Company &companyName);

/**
 * @brief Prints all of the scheduled maintenance between 2 dates given by the user
 * @param companyName The company to which the maintenance belong to
 */
void printMaintenancesOnDate (Company &companyName);
/**
* @brief User's interface to postpone a Maintenance to a new date
* @param companyName The company to which the maintenance belong to
*/
void postponeMaintenance(Company &companyName);
/**
* @brief User's interface to cancel a Maintenance
* @param companyName The company to which the maintenance belong to
*/
void cancelMaintenance(Company &companyName);
/**
* @brief Prints all of the scheduled maintenance between now and the days given by the user
* @param companyName The company to which the maintenance belong to
*/
void printMaintenancesNextDays(Company &companyName);

/**
 * @brief User's interface to add a technician to the company: user is asked for a name, and the model's the technician is qualified to work with
 * @param companyName The company to which the technician will be added
 */
void addTechnician (Company &companyName);

/**
 * @brief User's interface to delete a technician: user is asked for the technician's id
 * @param companyName The company from which the technician will be deleted
 */
void deleteTechnician (Company &companyName);

/**
 * @brief Searches for and prints a technician information
 * @param companyName The company to which the technician belongs
 */
void printTechnician (Company &companyName);

/*OPERATORS OVERLOAD*/

ostream& operator<< (ostream &os, const PassengerWCard &p);

ostream& operator<< (ostream &os, const Plane &p);

ostream& operator<< (ostream &os, const vector<Flight *> &fs);
#endif //AEDA_MAIN_H
