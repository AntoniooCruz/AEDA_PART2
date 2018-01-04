#ifndef tecnico_H
#define tecnico_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Plane.h"
#include "Company.h"

using namespace std;

class Company;

class Technician {
private:
	unsigned int id;			                    /** < @brief Id of the passenger in the company */
	static unsigned int lastId;	                    /** < @brief Static attribute where the last technician's id is saved */
    string name;                                    /** < @brief Technician's name */
	vector<string> model;	                        /** < @brief vector with technician's specialties */
	vector<Plane *>  planesToDo;

public:
	/**
	* @brief Calculates the newId based of the value of lastId
	* @return a possible id to a technician: lastId + 1
	*/
	static unsigned int newId();

    Technician ();

    /* @brief constructor */
	Technician(string name, vector<string> specialty);

    /*
     * @brief Constructor used to read form files
     */
    Technician (unsigned int id, string name, vector<string> specialty, vector<Plane *> planes);

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
     * @brief Checks if this technician has the hability to work with a given plane's model
     * @param plane_model The model to check if the tech has the hability to work with
     * @return true If the model is among the tech's specialties, false otherwise
     */
    bool hasModel (string plane_model) const;

    /**
	* @brief add 
	*/
	void addPlanesToDo(Plane * p);


	void deletePlaneToDo (int planeId);

    /**
     * @brief Determines if this technician is bigger or smaller than other, method used to determine a technician's priority
     * @param t The technician to which this is being compared
     * @return true if this technician has less maintenances schedule, false otherwise
     */
    bool operator< (const Technician &t) const;

    friend ostream& operator<< (ostream &os, const Technician &t);
};


#endif
