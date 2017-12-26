#include "Passenger.h"

using namespace std;

//Passenger Methods

Passenger::Passenger(string name, Date anniversary) {
	this->name = name;
	this->anniversary = anniversary;
}

string Passenger::getName() const {
	return name;
}

string Passenger::getDateBirth() const {
	return anniversary.getDate();
}

int Passenger::getYear() const {
	return anniversary.getYear();
}

int Passenger::getMonth() const {
	return anniversary.getMonth();
}

int Passenger::getDay() const {
	return anniversary.getDay();
}

float Passenger::getDiscount (float price) const {
	return 0;
}

vector<Reservation *> Passenger::getReserv() {
	for (unsigned int i = 0; i < reserv.size(); i++) {
		if (reserv.at(i)->getFlight()->getDepHour() < DateFlight::getNow()) {
			reserv.erase(reserv.begin() + i);
		}
	}
	return reserv;
}

void Passenger::printReservations (unsigned int i) {
	cout << *reserv.at(i);
}

void Passenger::addReservation(Reservation *r) {
	reserv.push_back(r);
}

Reservation Passenger::deleteReserv(string seat, unsigned int idF) {
	Reservation deleting;

	for (unsigned int i = 0; i < reserv.size(); i++)
	{
		if (reserv[i]->getSeat()==seat && reserv[i]->getFlight()->getId()==idF) {
			deleting = *reserv[i];
			reserv.erase(reserv.begin() + i);
			break;
		}
	}

	return deleting;
}

string Passenger::getType() const {
	return "noCard";
}

bool Passenger::operator== (const Passenger &p) const {
	/* 2 passengers are the same if they have the same name and the same date of birth*/

	return p.getName() == name && p.getDateBirth() == this->getDateBirth();
}

//Passenger With Card Methods

PassengerWCard::PassengerWCard(unsigned int id, string name, string job, Date anniversary, vector<flightsYear> averageFlights) : Passenger (name, anniversary) {
	this->job = job;
	this->id = id;
	this->averageFlights = averageFlights;
}

PassengerWCard::PassengerWCard(string name, string job, Date anniversary) : Passenger(name, anniversary) {
	this->job = job;
	this->id = 0;
}

string PassengerWCard::getJob() const {
	return job;
}

float PassengerWCard::getAverageFlight() const {
	unsigned int sum = 0;
	if (averageFlights.size() == 0)
		return 0;

	for (unsigned int i = 0; i < averageFlights.size(); i++) {
		sum = sum + averageFlights.at(i).flight;
	}

	return (float) sum/averageFlights.size();
}

vector <flightsYear> PassengerWCard::getFlightsPerYear() const {
	return averageFlights;
}

unsigned int PassengerWCard::getId() const {
	return id;
}

float PassengerWCard::getDiscount(float price) const {
	return price - (price * ((100 - getAverageFlight()) / 100));
}

void PassengerWCard::setId (unsigned int id) {
	this->id = id;
}

string PassengerWCard::getType() const {
	return "Card";
}

void PassengerWCard::addReservation(Reservation *r) {
	Passenger::addReservation(r);
	bool added = false;

	for (unsigned int i = 0; i < averageFlights.size(); i++) {
		if (averageFlights.at(i).year == r->getFlight()->getDepHour().getYear()){
			averageFlights.at(i).flight++;
			added = true;
		}
	}

	if (!added){
		struct flightsYear adding;
		adding.year = r->getFlight()->getDepHour().getYear();
		adding.flight = 1;

		averageFlights.push_back(adding);
	}
}

Reservation PassengerWCard::deleteReserv(string seat, unsigned int idF) {
    Reservation deleting = Passenger::deleteReserv(seat, idF);

	for (unsigned int i = 0; i < averageFlights.size(); i++) {
		if (averageFlights.at(i).year == deleting.getFlight()->getDepHour().getYear()){
			averageFlights.at(i).flight--;
		}
	}
	return deleting;
}

bool PassengerWCard::operator<(const PassengerWCard &p) const {
	return this->getId() < p.getId();
}

Date Passenger::getLastTicketBought() const
{
	return lastTicketBought;
}

void Passenger::setLastTicketBought(Date lastTicketBought)
{
	this->lastTicketBought = lastTicketBought;
}
