#include "Packet.h"

unsigned Packet::lastID;
Packet::Packet(vector<string> sites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas): sites(sites), begin(inicio), end(fim), pricePerPerson(precoPessoa), maxPersons(maxPessoas) {
	id = ++lastID;
	available = true;
}

  // metodos GET

unsigned Packet::getId() const{

	return id;
}

vector<string> Packet::getSites() const{

	return sites;
}

Date Packet::getBeginDate() const{

	return begin;
}

Date Packet::getEndDate() const{

	return end;
}

double Packet::getPricePerPerson() const{

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

	return maxPersons;
}

  // metodos SET

void Packet::setId(unsigned id){

	this->id = id;
}

void Packet::setSites(vector<string> sites){

	this->sites = sites;
}

void Packet::setBeginDate(Date begin){

	this->begin = begin;
}

void Packet::setEndDate(Date end){

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson) {

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons){

	this->maxPersons = maxPersons;
}

void Packet::setAvailable(bool available) {
	this->available = available;
}


/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
//ostream& operator<<(ostream& out, const Packet & packet){

//  // REQUIRES IMPLEMENTATION
//}
