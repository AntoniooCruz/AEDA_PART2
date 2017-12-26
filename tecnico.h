#ifndef tecnico_H
#define tecnico_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Plane.h"

using namespace std;

class Technician {
private:
	unsigned int id;			                    /** < @brief Id of the passenger in the company */
	static unsigned int lastId;	                    /** < @brief Static attribute where the last technician's id is saved */
    string name;                                    /** < @brief Technician's name */
	vector<string> model;	                        /** < @brief vector with technician's specialties */
	vector<Plane *>  planesToDo; // falta adicionar modelos a class planes mas acho que se pode ~(acho que se pode dizer que o modelo do aviao e o numero de lugares... so uma ideia)
public:
	/**
	* @brief Calculates the newId based of the value of lastId
	* @return a possible id to a technician: lastId + 1
	*/
	static unsigned int newId();
	/* @brief constructor */
	Technician(string name, vector<string> specialty);

	/* get methods */
	/**
	* @return technician's id
	*/
	unsigned int getId() const;

    /**
     * @return technician's name
     */
    string getName() const;

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

    /**
     * @brief Determines if this technician is bigger or smaller than other, method used to determine a technician's priority
     * @param t The technician to which this is being compared
     * @return true if this technician has less maintenances schedule, false otherwise
     */
    bool operator< (const Technician &t) const;

    friend ostream& operator<< (ostream &os, const Technician &t);
};


#endif
