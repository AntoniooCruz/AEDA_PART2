#include "tecnico.h"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

unsigned int Technician::lastId = 0;

unsigned int Technician::newId()
{
	lastId++;
	return lastId;
}

Technician::Technician(string name, vector<string> specialty) {
	this->id = newId();
    this->name = name;
	this->model= specialty;
}

unsigned int Technician::getId() const
{
	return id;
}

string Technician::getName() const {
    return name;
}

vector<string> Technician::getModel() const
{
	return model;
}

vector<Plane *> Technician::getPlanesToDo() const
{
	return this->planesToDo;
}

void Technician::addPlanesToDo(unsigned int id)
{
	//TODO: n
}

bool Technician::operator< (const Technician &t2) const {
    return getPlanesToDo() < t2.getPlanesToDo();
}

ostream& operator<< (ostream &os, const Technician &t) {
	string stros;
	stros = "Id: " + to_string(t.getId()) + "\n";
	stros += "Specialty:\n";
	vector<string> specTmp = t.getModel();

	for (int i = 0; i < specTmp.size(); i++){
		stros += "   *" + specTmp[i] + "\n";
	}
	stros += "To Do List (planes id):\n";

	vector<Plane *> todoTmp = t.getPlanesToDo();

	for (int i = 0; i < todoTmp.size(); i++) {
		stros += "   *" + todoTmp[i]->getModel();
		stros += " \n";
	}

	os << stros;
	return os;
}


	