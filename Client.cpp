#include "Client.h"

//Class constructors

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address): name(name), VATnumber(VATnumber), familySize(familySize), address(address){

    this->packets;
    totalPurchased = 0;

}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet> & packets, unsigned totalPurchased): name(name), VATnumber(VATnumber), familySize(familySize), address(address), packets(packets), totalPurchased(totalPurchased){
}

  // GET methods

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

vector<Packet> Client::getPacketList() const{
  
	return packets;
}

unsigned Client::getTotalPurchased() const{

	return totalPurchased;
}
  
  // metodos SET
	  
void Client::setName(string nome) {
  
	name = nome;
}

void Client::setVATnumber(unsigned VATnumber){
  
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize){
  
	this->familySize = familySize;
}

void Client::setAddress(Address address){
  
	this->address = address;
}

void Client::setPacketList(vector<Packet> & packets){
  
	this->packets = packets;
}

unsigned Client::setTotalPurchased(unsigned totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
  
  // outros metodos

//ostream& operator<<(ostream& out, const Client & client){

//  // REQUIRES IMPLEMENTATION

//}
