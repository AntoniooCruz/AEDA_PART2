#include "Company.h"
#include "Main.h"
#include "Passenger.h"
#include "Order.cpp"

Company::Company() {}

Company::Company(string passengersFile, string planesFile, string reservFile, string techFile) {
    this->planesFile = planesFile;
    this->passFile = passengersFile;
    this->reservFile = reservFile;
    this->techFile = techFile;

    try {
        openPassFile();
        openPlanesFile ();
        openReservFile();
        openTechFile();
    } catch (ErrorOpeningFile &name) {
        cout << "Error opening the file " << name.getFileName() << endl
             << "No data was imported\n";
        Company();
    } catch (InvalidDate &d) {
        cout << "Error opening the file because of an invalid date - " << d.getDate() << endl
             << "No data was imported\n";
    }
	insertPlanesInTree();
}

/*   GET METHODS */
vector<Plane *> Company::getPlanes() const {
    return planes;
}

vector<PassengerWCard *> Company::getRegPassengers() const {
    return PassengerCards;
}

/*   OPEN FILES  */
void Company::openPassFile () {
    ifstream infich;
    string textLine, name, job;
    char aux;
    unsigned int year, month, day, id, flight, year2 = 0;
    string nrFlights;

    infich.open(passFile);


    if (!infich.fail()) {
        while (getline(infich, textLine)) {

            istringstream cardStream (textLine);

            cardStream >> id >> aux;

            name = readComplexString(cardStream, ';');
			
            cardStream >> year >> aux >> month >> aux >> day >> aux;

            Date anniversary (year, month, day);

            job = readComplexString(cardStream, ';');

            vector <flightsYear> newPass;

            while (! cardStream.eof()){

                cardStream >> year2 >> aux >> flight >> aux;

                struct flightsYear adding;
                adding.year = year2;
                adding.flight = flight;

                if (year2 != 0)
                    newPass.push_back(adding);

            }

            PassengerCards.push_back(new PassengerWCard (id, name, job, anniversary, newPass));
		
        }
    } else {
        throw ErrorOpeningFile (passFile);
    }
}

void Company::openPlanesFile (){
    ifstream infich;

    string textLine;
    infich.open(planesFile);


    if (!infich.fail()) {
        while (getline(infich, textLine)) {
           planes.push_back(new Plane (textLine));
        }
    }
    else {
        throw ErrorOpeningFile (planesFile);
    }
}

void Company::openReservFile() {
    ifstream infich;

    string textLine;
    infich.open(reservFile);

    if (!infich.fail()) {
        while (getline(infich, textLine) && textLine != "Passengers not registed") {
            Reservation *adding = new Reservation (textLine, this, true);
            adding->getPassenger()->Passenger::addReservation(adding);

            if (adding->getFlight()->getType() == "Commercial") {

                FCommercial * fc = dynamic_cast<FCommercial*> (adding->getFlight());

                fc->addReservation(adding);
            }

        }

        while  (getline(infich, textLine)) {
            Reservation *adding = new Reservation (textLine, this, false);

            if (adding->getFlight()->getType() == "Commercial") {

                FCommercial * fc = dynamic_cast<FCommercial*> (adding->getFlight());

                fc->addReservation(adding);
            }
        }
    }
}

void Company::openTechFile() {
    ifstream infich;
    string textLine, name, model;
    char aux;
    unsigned int id;
    int i = 0;
    vector <string> models;
    vector <Plane *> planes;

    infich.open(techFile);


    if (!infich.fail()) {
        while (getline(infich, textLine)) {
            istringstream techStream (textLine);
            techStream >> id >> aux;

            name = Company::readComplexString(techStream, ';');

            aux = ',';

            while ((! techStream.eof()) && aux != ';'){
                techStream >> model >> aux;
                models.push_back(model);
            }

            while (! techStream.eof()){
                techStream >> id >> aux;

                planes.push_back(searchPlane(id, i));
            }

            Technician t (id, name, models, planes);

            technicians.push(t);

            // erases all the content from the vectors
            models.clear();
            planes.clear();
        }
    }
    else {
        throw ErrorOpeningFile (techFile);
    }
}

void Company::logOut() {
    try {
        closePassFile();
        closePlanesFile ();
		closeReservFile();
        closeTechFile();
    } catch (ErrorOpeningFile &name) {
        cout << "Error opening the file " << name.getFileName() << endl
             << "No data was saved\n";
    }
}

void Company::closePassFile() {
    ofstream saveData;

    saveData.open(passFile, ios::out | ios::trunc);

    if (saveData.fail()){
        throw ErrorOpeningFile (passFile);
    }

    for (int i = 0; i < PassengerCards.size(); i++) {
        saveData << PassengerCards[i]->getId() << " ; " << PassengerCards[i]->getName() + " ; " + PassengerCards[i]->getDateBirth()
                    + " ; " + PassengerCards[i]->getJob() + " ; ";

        vector <flightsYear> flightsPerYear = PassengerCards.at(i)->getFlightsPerYear();

        for (int j = 0; j < flightsPerYear.size(); j++) {
            saveData << flightsPerYear.at(j).year << " , " << flightsPerYear.at(j).flight;

            if (j != flightsPerYear.size()-1) {
                saveData << " ; ";
            }
        }

        saveData << endl;

    }

    saveData.close();
}

void Company::closePlanesFile() {
    ofstream saveData;
    vector<Flight *> temp;

    saveData.open(planesFile, ios::out | ios::trunc);

    if (saveData.fail()) {
        throw ErrorOpeningFile(planesFile);
    }

    for (int i = 0; i < planes.size(); i++) {
        saveData << planes[i]->getId() << " ; " << planes[i]->getNrPlaces();
		saveData << " , " << planes[i]->getModel() << " , " << planes[i]->getMaintenanceRate() << " , " << planes[i]->getNextMaintenance();

        temp = planes[i]->getFlights();

        for (int j = 0; j < temp.size(); j++) {
            saveData << " ; " << temp[j]->getId() << " , " << temp[j]->getADep() << " , " << temp[j]->getAArr() << " , "
                     << temp[j]->getDepDate()
                     << " , " << temp[j]->getDuration() << " , " << temp[j]->getPrice() << " , ";

            if (temp[j]->getType() == "Private")
                saveData << "P";
            else
                saveData << "C";

        }
        saveData << endl;
    }

    saveData.close();
}

void Company::closeReservFile() {
    ofstream saveData;
    vector<Flight *> temp;
    map <string, Reservation> temp2;
	vector<Reservation> noCard;

    saveData.open(reservFile, ios::out | ios::trunc);

    if (saveData.fail()) {
       throw ErrorOpeningFile(reservFile);
   }

    // goes through all the planes
    for (int i = 0; i < planes.size(); i++) {

        // temporary variable to save the flights of the current plane
        temp = planes[i]->getFlights();


        // goes through all the plane's flights
        for (int j=0; j < temp.size(); j++) {



            //tests if it is a Commercial flight
          if (temp[j]->getType() == "Commercial") {

                FCommercial * fc = dynamic_cast<FCommercial*> (temp[j]);



                // temporary variable to save the flight's reservations
                temp2 = fc->getReservations();


                // goes through all the flight's reservations
				for (auto it = temp2.begin(); it != temp2.end(); ++it)

				{
                    // if it is not a registered passenger saves the reservation in the vector noCard
					if (it->second.getPassenger()->getType() == "noCard")
					{
						noCard.push_back(it->second);
					}
					else
					{
						Passenger * p1 = it->second.getPassenger();
						PassengerWCard * pc1 = dynamic_cast<PassengerWCard*> (p1);
						saveData << it->second.getFlight()->getId() << " ; " << pc1->getId() << " ; " << it->second.getPrice() << " ; " << it->second.getSeat() << endl;
					}
				}
          }

        }
    }
	saveData<< "Passengers not registed" << endl;

	for (unsigned int i = 0; i < noCard.size(); i++)
	{
		saveData << noCard[i].getFlight()->getId() << " ; " << noCard[i].getPassenger()->getName() << " ; " << noCard[i].getPassenger()->getYear() << " / " << noCard[i].getPassenger()->getMonth() << " / " << noCard[i].getPassenger()->getDay() << " ; " << noCard[i].getPrice() << " ; " << noCard[i].getSeat() << endl;
	}
	saveData.close();
}

void Company::closeTechFile() {
    ofstream saveData;

    saveData.open(techFile, ios::out | ios::trunc);

    if (saveData.fail()){
        throw ErrorOpeningFile (passFile);
    }


    while (! technicians.empty()) {
        Technician t = technicians.top();

        saveData << t.getId() << " ; " << t.getName() << " ; ";

        if ( t.getModel().size() != 0) {
            saveData << t.getModel().at(0);
        }

        for (int i = 1; i < t.getModel().size(); i++) {
            saveData << " , " << t.getModel().at(i);
        }



        if ( t.getPlanesToDo().size() != 0){
            saveData << " ; ";
            saveData << t.getPlanesToDo().at(0);
        }

        for (int i = 1; i < t.getPlanesToDo().size(); i++) {
            saveData << " , " << t.getPlanesToDo().at(i);
        }

        saveData << endl;

        technicians.pop();


    }
}

string Company::readComplexString (istringstream &ss, char separate) {
    string final, auxString;
    char aux;

    do {
        ss >> auxString;
        final += auxString;
        ss.get(aux);
        ss.get(aux);

        if (aux != separate) {
            final += " ";
            ss.unget();
        }

    } while (aux != separate);

    return final;
}

/*  EDIT PLANES */
void Company::addPlane(Plane *p) {
	long i;
    int id;
	vector <Plane *>::iterator it;
	maintenance.insert(p);
    //if the planes' vector is empty
	if (planes.size() == 0){
			p->setId(1);
		planes.push_back(p);
    }
    else {

        i = nextId<Plane *>(planes);

        if (i == 0 && planes[0]->getId() != 1) {
            id = 1;
        }
        else {
            id = planes[i]->getId() + 1;
        }

        p->setId(id);

        if (i == planes.size()-1) {
            planes.push_back(p);
        } else {
            it = planes.begin() + i;

            if (it != planes.begin())
                it++;

            planes.insert(it, p);
        }
    }
}

Plane * Company::deletePlane(unsigned int nrid) {
    int reference;
    searchPlane(nrid, reference);
    Plane * deleting = planes.at(reference);

    planes.erase(planes.begin() + reference);

    return deleting;
}

Plane * Company::searchPlane(unsigned int nrid, int &i) {
    
    int left = 0, right = (int) planes.size()-1;

    while (left <= right) {
        i = (left + right) / 2;

        if (planes[i]->getId() < nrid) {
            left = i + 1;
        }

        else if (nrid < planes[i]->getId()){
            right = i - 1;
        }

        else {
            return planes.at(i);
        }
    }

    throw NoSuchPlane (nrid);

}

vector<vector<Flight* > > Company::getAirportsFlights() {
	vector<vector<Flight*> > airportFlights;
	vector<string> airports;
	cout << "Airports with flights: " << endl;
	for (unsigned int i = 0; i < planes.size(); i++)
	{
		for (unsigned int j = 0; j<planes[i]->getFlights().size(); j++)
		{
			bool exists = false;
			for (unsigned int k = 0; k < airports.size(); k++)
				if (planes[i]->getFlights()[j]->getADep() == airports[k])
				{
					exists = true;
					airportFlights[k].push_back(planes[i]->getFlights()[j]);
				}
			if (!exists)
			{
				vector<Flight*> temp;
				temp.push_back(planes[i]->getFlights()[j]);
				airportFlights.push_back(temp);
				airports.push_back(planes[i]->getFlights()[j]->getADep());
			}


		}
	}
	for (unsigned int i = 0; i< airports.size(); i++)
	{
		cout << "[" << i << "] " << airports[i] << endl;
	}
	return airportFlights;
}

void Company::addFlight (Flight *f){

    for (int i = 0; i < planes.size(); i++) {
        try {
            if (planes[i]->addFlight(f)) {
                f->setPlane(planes[i]);
                return;
            }
        }
        catch (Repeated &f) {
        }
    }

    throw RepeatedFlight (f->getId());
}

unsigned long Company::numOfFlights() {
	unsigned long numOfFlights=0;

	for (unsigned int i = 0; i < planes.size(); i++)
	{
        numOfFlights = numOfFlights + planes[i]->getFlights().size();
	}

	return numOfFlights;
}

void Company::scheduleMaintenances() {
    priority_queue <Technician> temporary;
    Technician t;

    for (int i = 0; i < planes.size(); i++) {
        temporary = technicians;

        string plane_model = planes.at(i)->getModel();


        while (! technicians.empty()){
            if (technicians.top().hasModel(plane_model)) {
                t = technicians.top();
                t.addPlanesToDo(planes.at(i));
                technicians.pop();
                temporary.push(t);
                break;
            }
            temporary.push(technicians.top());
            technicians.pop();
        }

        while (! temporary.empty()) {
            technicians.push(temporary.top());
            temporary.pop();
        }
    }
}


/*  EDIT PASSENGER */

void Company::addPassenger(PassengerWCard *p) {
	long i;
    int id;
    vector <PassengerWCard *>::iterator it;

    //if the planes' vector is empty
    if (PassengerCards.size() == 0){
        if (p->getId() == 0) {
            p->setId(1);
        }
        PassengerCards.push_back(p);
    }
    else {
        i = nextId<PassengerWCard *>(PassengerCards);

        if (i == 0) {
            id = 1;
        }
        else {
            id = PassengerCards[i]->getId() + 1;
        }

        p->setId(id);


        if (i == PassengerCards.size() - 1) {
            PassengerCards.push_back(p);
        } else {
            it = PassengerCards.begin() + i;

            if (it != PassengerCards.begin())
                it++;

            PassengerCards.insert(it, p);
        }
    }
}

PassengerWCard * Company::deletePassenger(unsigned int nrid) {
	int reference;
	searchPassenger(nrid, reference);
	PassengerWCard * deleting = PassengerCards.at(reference);
	for (unsigned int i = 0; i < deleting->getReserv().size(); i++)
	{
		Flight *f1 = deleting->getReserv()[i]->getFlight();
		FCommercial * fc1 = dynamic_cast<FCommercial*> (f1);

		fc1->removeReservation(deleting->getReserv()[i]->getSeat(), deleting->getReserv()[i]->getPassenger()->getName());
	}
	PassengerCards.erase(PassengerCards.begin() + reference);

	return deleting;
}

PassengerWCard * Company::searchPassenger(unsigned int nrid, int &i) {
	
	int left = 0, right = (int) PassengerCards.size() - 1;

	while (left <= right) {
		i = (left + right) / 2;

		if (PassengerCards[i]->getId() < nrid) {
			left = i + 1;
		}

		else if (nrid < PassengerCards[i]->getId()) {
			right = i - 1;
		}

		else {
			return PassengerCards.at(i);
		}
	}

	throw NoSuchPassenger(nrid);

}

void Company::maintenanceList() {
	unsigned int i = 1;
	for (set<Plane*>::iterator it = maintenance.begin(); it != maintenance.end(); it++)
	{	
		cout << i << ":" << endl;
		cout << *(*it) <<endl;
	}
}

void Company::insertPlanesInTree() {
	for (unsigned int i = 0; i < planes.size(); i++)
	{
		maintenance.insert(planes[i]);
	}
}

/*  EDIT FLIGHTS */

Flight * Company::searchFlight (unsigned int nrid) {
    Flight * searching;
    int i = 0;

    for (unsigned int j = 0; j < planes.size(); j++){
        try{
            searching = planes.at(j)->searchFlight(nrid, i);
            return searching;
        }
        catch (NoSuch &e) {

        }
    }

    throw NoSuchFlight (nrid);

}


/* EDIT TECHNICIANS */

void Company::addTechnician(Technician t) {
    technicians.push(t);
}

Technician Company::deleteTechnician(int id) {
    priority_queue <Technician> temporary;
    bool found = false;

    Technician t = technicians.top();

    while (! technicians.empty()) {

        if (technicians.top().getId() == id) {
            t = technicians.top();
            technicians.pop();
            found = true;
        } else {
            temporary.push(technicians.top());
            technicians.pop();
        }
    }

    technicians = temporary;

    if (found)
        return t;
    else
        throw NoSuchTechnician (id);
}

Technician Company::searchTechnician(int id) {
    priority_queue <Technician> temporary = technicians;

    while (! temporary.empty()) {

        if (temporary.top().getId() == id)
            return temporary.top();

        temporary.pop();
    }

    throw NoSuchTechnician (id);
}

void Company::printAllTechnicians() {
    priority_queue <Technician> temporary = technicians;

    while (! temporary.empty()) {
        cout << temporary.top() << endl << endl;
        temporary.pop();
    }
}