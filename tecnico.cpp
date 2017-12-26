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

	os << "Id: " << to_string(t.getId()) << endl
       << "Name: " << t.getName() << endl
       << "Specialty:\n";

	vector<string> specTmp = t.getModel();

	for (int i = 0; i < specTmp.size(); i++){
		os << "   * " << specTmp[i] << endl;
	}

    vector<Plane *> todoTmp = t.getPlanesToDo();

    if (todoTmp.size() == 0) {
        os << "No maintenances schedule\n";
    }
    else {
        os << "To Do List (planes id):\n";


        for (int i = 0; i < todoTmp.size(); i++) {
            os << "   * " << todoTmp[i]->getId() << endl;
        }
    }

	return os;
}


	