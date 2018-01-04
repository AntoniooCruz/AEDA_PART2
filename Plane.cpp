#include "Plane.h"
#include "Flight.h"
#include "Company.h"
#include "Order.cpp"
#include "Date.h"
#include <algorithm>

Plane::Plane() {
    nrPlaces = 0;
    id = 0;
}

Plane::Plane(unsigned int nrPlaces) {
    this->nrPlaces = nrPlaces;
    this->id = 0;
	nameSeats();
}

Plane::Plane(unsigned int nrPlaces, string model, int maintenanceRate, Date nextMaintenance) {
	this->nrPlaces = nrPlaces;
	this->model = model;
	this->maintenanceRate = maintenanceRate;
	this->nextMaintenance = nextMaintenance;
	this->id = 0;
	nameSeats();
}

Plane::Plane (string textLine){
    istringstream planeStream (textLine);
    string arrAirp, depAirp, model;
    char aux, type;
	unsigned int places, year, month, day, hour, minutes, duration, id,rate, nextInsp;
	float price;

    planeStream >> id >> aux >> places >> aux >> model >> aux >> rate >> aux >> nextInsp >> aux;
	this->model = model;
	this->maintenanceRate = rate;
	this->nextMaintenance = Date::getNow() + nextInsp;
	this->nrPlaces = places;
	this->id = id;

	nameSeats();

    while (! planeStream.eof()) {
    	planeStream >>  id >> aux;

    	depAirp = Company::readComplexString(planeStream, ',');

    	arrAirp = Company::readComplexString(planeStream, ',');

		planeStream >> year >> aux >> month >> aux >> day >> aux >> hour >> aux >> minutes >> aux >> duration >> aux >> price >> aux >> type >> aux;
		
    	DateFlight departure (year, month, day, hour, minutes);

    	if (type == 'C') {
    		flights.push_back(new FCommercial (id, depAirp, arrAirp, this, departure, duration, price));
    	}
    	else if (type == 'P') {
    		flights.push_back(new FPrivate (id, depAirp, arrAirp, this, departure, duration, price));
    	}
    	else {
    		throw ErrorOpeningFile ("planes.txt");
    	}
    }

}

void Plane::nameSeats()
{
	string seatName;
	for (unsigned int i = 1; i < nrPlaces/6; i++)
	{
		seatName = to_string(i) + "A";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

		seatName = to_string(i) + "B";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

		seatName = to_string(i) + "C";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

		seatName = to_string(i) + "D";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

		seatName = to_string(i) + "E";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

		seatName = to_string(i) + "F";
		if (i < 10)
			seatName = '0' + seatName;
		seatsN.push_back(seatName);
		seatName.clear();

	}
	//To complete the rest of the line that will not be completed
	unsigned int lastRow = nrPlaces / 6;
	unsigned int lastSeat = nrPlaces % 6;
	

		do
		{
			seatName = to_string(lastRow) + "A";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			if (lastSeat == 1)
				break;

			seatName = to_string(lastRow) + "B";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			if (lastSeat == 2)
				break;

			seatName = to_string(lastRow) + "C";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			if (lastSeat == 3)
				break;

			seatName = to_string(lastRow) + "D";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			if (lastSeat == 4)
				break;

			seatName = to_string(lastRow) + "E";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			if (lastSeat == 5)
				break;

			seatName = to_string(lastRow) + "F";
			if (lastRow < 10)
				seatName = '0' + seatName;
			seatsN.push_back(seatName);
			seatName.clear();
			
				break;
		} while (true);

	
	
	
	
}

unsigned int Plane::getId() const {
    return id;
}

unsigned int Plane::getNrPlaces() const {
    return nrPlaces;
}

vector <Flight *> Plane::getFlights() {
	for (unsigned int i = 0; i < flights.size(); i++) {
		if (flights.at(i)->getDepHour() < DateFlight::getNow()) {
			flights.erase(flights.begin() + i);
		}
	}
    return flights;
}

unsigned long Plane::getNrFlights () const {
    return flights.size();
}

vector<string> Plane::getSeatsNames() const {
	return seatsN;
}

string Plane::getModel() const {
	return model;
}

int Plane::getMaintenanceRate() const {
	return maintenanceRate;
}

Date Plane::getNextMaintenance() const {
	return nextMaintenance;
}

void Plane::setId(unsigned int id) {
    this->id = id;
}
void Plane::changeMaintenance(Date newDate)
{
	this->nextMaintenance = newDate;
}
bool Plane::addFlight(Flight *f) {
	long i;
	int id;
	vector <Flight *>::iterator it;

	for (auto it = flights.begin(); it != flights.end();it++){
		if (*(*it) == *f){
			throw RepeatedFlight (f->getId());
		}
	}

    flights.push_back(f);

	return true;
}

Flight * Plane::deleteFlight (unsigned int nrid) {
    int reference;
    searchFlight(nrid, reference);
    Flight * deleting = flights.at(reference);
    flights.erase(flights.begin() + reference);
    return deleting;
}

Flight * Plane::searchFlight (unsigned int nrid, int &i) {

    sortFlightsId();

    int left = 0, right = (int) flights.size()-1;

    while (left <= right) {
        i = (left + right) / 2;

        if (flights[i]->getId() < nrid) {
            left = i + 1;
        }
        else if (nrid < flights[i]->getId()){
            right = i - 1;
        }

        else {
			if (flights[i]->getDepHour() < DateFlight::getNow()) {
				this->deleteFlight(nrid);
				throw NoSuchFlight (nrid);
			}
            return flights.at(i);
        }
    }

    throw NoSuchFlight (nrid);
}

Flight * Plane::postponeFlight(Flight *f, unsigned int duration) {
	sortFlightsDate();

	int i = 0;

	vector <Flight *>::iterator it, it2;

	int left = 0, right = (int) flights.size()-1;

	while (left <= right) {
		i = (left + right) / 2;

		if (flights[i]->getDepHour() < f->getDepHour()) {
			left = i + 1;
		}
		else if (f->getDepHour() < flights[i]->getDepHour()){
			right = i - 1;
		}

		else {

            it = flights.begin() + i + 1;
            it2 = it -1;

            (*it2)->setDuration( (*it2)->getDuration() + duration);

            for (; it != flights.end(); it++, it2++) {

                if (*(*it) == *(*it2)){
                    (*it)->setDepartHour( (*it)->getDepHour() + duration);
                } else
                    return f;
            }

            return f;
		}
	}

	return f;
}

bool Plane::dateOrder(Flight * &f1, Flight * &f2) {

	if (f1->getType() == f2->getType()) {
		if (f1->getDepDate() == f2->getDepDate())
			return f1->getId() < f2->getId();
		else return f1->getDepDate() < f2->getDepDate();
	}
	return f1->getType() < f2->getType();
}

void Plane::sortFlightsDate() {
    sort(flights.begin(), flights.end(), dateOrder);
}

void Plane::sortFlightsId() {
    sort(flights.begin(), flights.end(), idOrder <Flight *>);
}

vector<Flight *> Plane::clearPastFlights() {

	DateFlight checking;

	vector <Flight *> pastFlights;

	for (unsigned int i = 0; i < flights.size(); i++) {

		checking = flights.at(i)->getDepHour();

		if (DateFlight::past(checking.getYear(), checking.getMonth(), checking.getDay(), checking.getHour(), checking.getMinutes())) {
			pastFlights.push_back(flights.at(i));
			flights.erase(flights.begin() + i);
		}
	}

	return pastFlights;
}

bool Plane::operator==(const Plane &p) {

    return id == p.getId();
}

bool Plane::operator<(const Plane &p) {
	return this->getId() < p.getId();
}

ostream& operator<< (ostream &os, const Plane &p) {
	os << "Id: " << p.id << endl
	   << "Model: " << p.model <<endl
	   << "Date of next inspection: " << p.nextMaintenance << endl
	   << "Inspection required rate: " << p.getMaintenanceRate() << " days "<< endl
	   << "Nr of places: " << p.nrPlaces << endl
	   << "Flights";


	os << endl;

	os << p.flights;

	return os;
}

