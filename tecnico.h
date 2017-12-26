#ifndef tecnico_H
#define tecnico_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Plane.h"

using namespace std;

class technician {
private:
	unsigned int id;			/** < @brief Id of the passenger in the company */
	static unsigned int lastId;	/** < @brief Static attribute where the last technician's id is saved */
	vector<string> model;	/** < @brief vector with technician's specialties */
	vector<Plane *>  planesToDo; // falta adicionar modelos a class planes mas acho que se pode ~(acho que se pode dizer que o modelo do aviao e o numero de lugares... so uma ideia)
public:
	/**
	* @brief Calculates the newId based of the value of lastId
	* @return a possible id to a technician: lastId + 1
	*/
	static unsigned int newId();
	/* @brief constructor */
	technician(vector<string> specialty);

	/* get methods */
	/**
	* @return technician's id
	*/
	unsigned int getId() const;
	/**
	* @return technician's Specialty
	*/
	vector<string> getModel() const;
	/**
	* @return technician's to do list
	*/
	vector<Plane*> getPlanesToDo() const;
	/**
	* @brief add 
	*/
	void addPlanesToDo(unsigned int id);

};


#endif
