#include "Flight.h"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

unsigned int Flight::lastId = 0;


/* constructor */
Flight::Flight(string aDep, string aArr, const DateFlight &departHour, int duration) : aDep(aDep), aArr(aArr){
    this->id = newId();
    this->plane = NULL;
    this->departHour = departHour;
    this->duration = duration;
}

Flight::Flight(string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration) : aDep(aDep), aArr(aArr)
{
	this->id = newId();
	this->plane = plane;
	this->departHour = departHour;
	this->duration = duration;
}

Flight::Flight(unsigned int id, string aDep, string aArr, Plane * plane, const DateFlight &departHour, unsigned int duration) : aDep(aDep), aArr(aArr)
{
	if (id > lastId){
		lastId = id;
	}

	this->id = id;
	this->plane = plane;
	this->departHour = departHour;
	this->duration = duration;
}

/* get methods */
string Flight::getADep() const {
   return aDep;
}

string Flight::getAArr() const {
   return aArr;
}

Plane * Flight::getPlane() const {
	return plane;
}

unsigned int Flight::getId() const {
	return id;
}

unsigned int Flight::getDuration() const {
	return duration;
}

string Flight::getDepDate() const {
	return departHour.getDate();
}

string Flight::getArrDate() const {
	DateFlight arrival = departHour + duration;

	return arrival.getDate();
}

DateFlight Flight::getDepHour() const {
	return departHour;
}

DateFlight Flight::getArrHour() const {
	return departHour + duration;
}

bool Flight::getDiscount() const {
	return false;
}

unsigned int Flight::getLastId()
{
	return lastId;
}

/* set methods */
void Flight::setPlane(Plane *plane) {
    this->plane = plane;
}

void Flight::setDepartHour(DateFlight newDepartHour)
{
	this->departHour = newDepartHour;
}

void Flight::setDuration(int newDuration)
{
	this->duration = newDuration;
}

/* static methods */
void Flight::setId(unsigned int id) {
   this->id = id;
}

unsigned int Flight::newId() {
	lastId++;
	return lastId;
}

/* operator overloading */
bool Flight::operator== (const Flight &f) const {
	if ((departHour < f.getDepHour() || departHour == f.getDepHour()) && (f.getDepHour() < getArrHour() || f.getDepHour() == getArrHour()))
		return true;

	else if ((f.getDepHour() < departHour || f.getDepHour() == departHour) &&  (departHour < f.getArrHour() || departHour == f.getArrHour()))
		return true;

	return false;
}


bool Flight::operator< (const Flight &f) const {
	//if (this->getType() == f.getType()) {
	return this->getId() <f.getId();
	/*}
	else if (this->getType() == "Commercial") {
		return true;
	}
	else {
		return false;
	}*/
}

ostream& operator<<(ostream & os, const Flight &f) {
	os << setw(18) << "Take off     " << setw(30) << "Departure Airport" << setw(30) << "Arrival Airport" << setw(10) << "Id" << setw(15) << "Type" << setw(20) << "Duration (min)" << setw(10) << "Price" << endl;


	os << setw(18) << f.departHour << setw(30) << f.aDep << setw(30) << f.aArr << setw(10) << f.getId() << setw(15) << f.getType() << setw(20) << f.duration
	   << setw(10) << f.getPrice();

	if (f.getDiscount()) {
		os << setw(15) << "FINAL DISCOUNT";
	}

	os << endl;
	return os;
}

ostream& operator<< (ostream &os, const vector<Flight *> &fs) {
	if (!fs.empty()) {
		os << setw(18) << "Take off     " << setw(30) << "Departure Airport" << setw(30) << "Arrival Airport"
		   << setw(10) << "Id" << setw(15) << "Type" << setw(20) << "Duration (min)" << setw(10) << "Price" << endl;

		for (unsigned int i = 0; i < fs.size(); i++) {
			os << setw(18) << fs.at(i)->departHour << setw(30) << fs.at(i)->aDep << setw(30) << fs.at(i)->aArr
			   << setw(10) << fs.at(i)->getId() << setw(15) << fs.at(i)->getType() << setw(20) << fs.at(i)->duration
			   << setw(10) << fs.at(i)->getPrice();

			if (fs.at(i)->getDiscount()) {
				os << setw(15) << "FINAL DISCOUNT";
			}

			os << endl;
		}
	}
	else {
		cout  << "No flights schedule"  << endl;
	}

	return os;
}


/*     COMMERCIAL FLIGHTS CLASS */

FCommercial::FCommercial(string aDep, string aArr, const DateFlight &departHour, int duration, float price) : Flight(aDep, aArr, departHour, duration) {
    this->price = price;
}

FCommercial::FCommercial(string aDep, string aArr, Plane *plane, const DateFlight &departHour, int duration, float price) : Flight(aDep, aArr, plane, departHour, duration) {
  	this->price = price;
	setAvailableSeats();
}

FCommercial::FCommercial(unsigned int id, string aDep, string aArr, Plane * plane, const DateFlight &departHour, int duration, float price) : Flight(id, aDep, aArr, plane, departHour, duration) {
  	this->price = price;
	setAvailableSeats();
}

map<string, Reservation> FCommercial::getReservations() const {
	return reservedSeats;
}

vector <string> FCommercial::getAvailableSeats() const {
	return availableSeats;
}

bool FCommercial::getDiscount() const {
	return (getDepHour() - DateFlight::getNow() < 48) && (reservedSeats.size() < getPlane()->getNrPlaces()/2);
}

string FCommercial::getType() const {
	return "Commercial";
}

float FCommercial::getPrice() const
{
	if ((getDepHour() - DateFlight::getNow() < 48) && (reservedSeats.size() < getPlane()->getNrPlaces()/2)) {
		return price * (float)0.90;
	}
	return price;
}

/* edit passengers */
bool FCommercial::addReservation(Reservation * p)
{
	//Plane is full
	if (getPlane()->getNrPlaces() == reservedSeats.size())
		return false;
	if (seatAvailable(p->getSeat()))
	{
		reservedSeats.insert(pair<string, Reservation>(p->getSeat(),  *p));
		unsigned int i = findSeat(p->getSeat());
		availableSeats.erase(availableSeats.begin() + i);
		return true;
	}
	else return false;
	
}

unsigned int FCommercial::findSeat(string seat) {
	for (unsigned int i = 0; i < availableSeats.size(); i++)
	{
		if (availableSeats[i] == seat)
			return i;
	}
	//Execption handle here
	return 0;
}

bool FCommercial::seatAvailable(string seat) const {
	return (find(availableSeats.begin(), availableSeats.end(), seat) != availableSeats.end());
}

bool FCommercial::removeReservation(string seat,string name)
{
	if (!(reservedSeats.find(seat) == reservedSeats.end()))
	{
		if (reservedSeats[seat].getPassenger()->getName() == name)
		{
			if (reservedSeats[seat].getPassenger()->getType() == "Card")
			{
				reservedSeats[seat].getPassenger()->deleteReserv(seat, reservedSeats[seat].getFlight()->getId());

			}
			reservedSeats.erase(seat);
			availableSeats.push_back(seat);
			sort(availableSeats.begin(), availableSeats.end());

			return true;
		}
	}
	return false;
}

void FCommercial::setAvailableSeats()
{
		availableSeats = getPlane()->getSeatsNames();
}

void FCommercial::fixSeats()
{
	vector<string> temp = getPlane()->getSeatsNames();

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (reservedSeats.find(temp[i]) != reservedSeats.end())
			temp.erase(temp.begin() + i);
	}

	availableSeats = temp;

}

void FCommercial::showAvailableSeats() const
{
	unsigned int currentSeat = 0, currentRow = 1,seatsProcessed=0;
	char currentLet = 'A';
	cout << "     _______________________________________     " << endl;
	cout << "    /                                       \\    " << endl;
	cout << "   /                                         \\   " << endl;
	cout << "  /                                           \\  " << endl;
	cout << " /                                             \\ " << endl;
	cout << "|                                               |" << endl;
	for (; currentRow <= getPlane()->getNrPlaces() / 6; currentRow++)
	{

			cout << "|";
			if ((availableSeats[currentSeat] ==  to_string(currentRow)+currentLet) || (availableSeats[currentSeat] == '0'+ to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " ";
				currentSeat++;
			}
			else
			{
				cout << "  N/A ";
			}
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;

			}
			currentLet = 'B';
			if ((availableSeats[currentSeat] == to_string(currentRow) + currentLet) || (availableSeats[currentSeat] == '0' + to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " ";
				currentSeat++;
			}
			else
			{
				cout << "  N/A ";
			}
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;
			}
			currentLet = 'C';
			if ((availableSeats[currentSeat] == to_string(currentRow) + currentLet) || (availableSeats[currentSeat] == '0' + to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " ";
				currentSeat++;
			}
			else
			{
				cout << "  N/A ";
			}
			//Mid of Plane
			cout << "           ";
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;
			}
			currentLet = 'D';
			if ((availableSeats[currentSeat] == to_string(currentRow) + currentLet) || (availableSeats[currentSeat] == '0' + to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " ";
				currentSeat++;
			}
			else
			{
				cout << "  N/A ";
			}
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;
			}
			currentLet = 'E';
			if ((availableSeats[currentSeat] == to_string(currentRow) + currentLet) || (availableSeats[currentSeat] == '0' + to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " ";
				currentSeat++;
			}
			else
			{
				cout << "  N/A ";
			}
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;
			}
			currentLet = 'F';
			if ((availableSeats[currentSeat] == to_string(currentRow) + currentLet) || (availableSeats[currentSeat] == '0' + to_string(currentRow) + currentLet))
			{
				cout << "  " << availableSeats[currentSeat] << " |" << endl;
				currentSeat++;
			}
			else
			{
				cout << "  N/A |" << endl;
			}
			currentLet = 'A';
			seatsProcessed++;
			if (seatsProcessed >= getPlane()->getNrPlaces())
			{
				cout << endl;
				break;
			}
		}
	
}



FPrivate::FPrivate(string aDep, string aArr, const DateFlight &departHour, int duration, float price) : Flight(aDep, aArr, departHour, duration) {
  this->price = price;
}

FPrivate::FPrivate(string aDep, string aArr, Plane *plane, const DateFlight &departHour, int duration, float price) : Flight(aDep, aArr, plane, departHour, duration) {
  this->price = price;
}

FPrivate::FPrivate(unsigned int id, string aDep, string aArr, Plane * plane, DateFlight departHour, int duration, float price) : Flight(id, aDep, aArr, plane, departHour, duration) {
  this->price = price;
}


string FPrivate::getType() const
{
   return "Private";
}

float FPrivate::getPrice() const
{
   return price;
}
