#include "Reservation.h"

using namespace std;
Reservation::Reservation() {}

Reservation::Reservation(string textLine, Company * company, bool hasCard) {
	istringstream reservStream (textLine);
	string name, seat, type;
	char aux;
	unsigned int year, month, day, flightId, passengerId, planeId;
	int i;
	float price;

	if (hasCard) {
		reservStream >> flightId >> aux >> passengerId >> aux >> price;

		this->passenger = company->searchPassenger(passengerId, i);

	}
	else {
		reservStream >> flightId >> aux;
		name = Company::readComplexString(reservStream, ';');
		reservStream >> year >> aux >> month >> aux >> day >> aux >> price;

		Date anniversary (year, month, day);
		this->passenger = new Passenger (name, anniversary);
	}

	this->flight = company->searchFlight(flightId);

	this->price = price;

	if (flight->getType() == "Commercial") {

        reservStream >> aux >> seat;

        this->seat = seat;
	}

}

Reservation::Reservation(Flight * flight, Passenger * passenger, float price, string seat) {
	this->flight = flight;
	this->passenger = passenger;
	this->price = price;
	this->seat = seat;
}

Flight * Reservation::getFlight() const {
	return flight;
}

Passenger * Reservation::getPassenger() const {
	return passenger;
}

float Reservation::getPrice() const {
	return price - passenger->getDiscount(price);
}

string Reservation::getSeat() const {
	return seat;
}

bool Reservation::operator==(const Reservation &r) const {
	return flight == r.getFlight() && passenger == r.getPassenger() && price == r.getPrice();
}

ostream& operator<< (ostream &os, const Reservation &r) {
	os << "Reservation of the Passenger " << r.passenger->getName() << " " << "for the flight " << r.flight->getId() << " cost " << r.getPrice() << " for the seat " <<r.getSeat()<<endl;


	return os;
}