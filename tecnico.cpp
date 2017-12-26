#include "tecnico.h"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

unsigned int technician::lastId = 0;

unsigned int technician::newId()
{
	lastId++;
	return lastId;
}

technician::technician(vector<string> specialty) {
	this->id = newId();
	this->model= specialty;
}

unsigned int technician::getId() const
{
	return id;
}

vector<string> technician::getModel() const
{
	return model;
}

vector<Plane *> technician::getPlanesToDo() const
{
	return this->planesToDo;
}

void technician::addPlanesToDo(unsigned int id)
{
	//TODO: n
}

ostream& operator<< (ostream &os, const technician &t) {
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
		stros += "   *" + todoTmp[i]->getId(); //devia aparecer aqui o modelo de cada plane para alem do id
		stros += " \n";
	}

	os << stros;
	return os;
}

bool operator < (const technician t1, const technician t2) {
	return t1.getPlanesToDo() < t2.getPlanesToDo();
}
	