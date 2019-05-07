#include "Address.h"

//Class constructors

Address::Address(){
	street = floor = postalCode = location = "unknown";
	doorNumber = 0;
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location): street(street), doorNumber(doorNumber), floor(floor), postalCode(postalCode), location(location){

}

Address::Address(string fullAddress){

        vector<string> addressVector=vectorString(fullAddress,"/");
        if(addressVector[2].size()==0){
            addressVector[2]="-";
        }
        this->street=addressVector[0];
        this->doorNumber= unsigned short((stoi(addressVector[1])));
        floor=addressVector[2];
        postalCode=addressVector[3];
        location=addressVector[4];
        }
  // metodos GET


string Address::getStreet() const{

	return street;
}

unsigned short Address::getDoorNumber() const{

	return doorNumber;
}

string Address::getFloor() const{
  
	return floor;
}

string Address::getPostalCode() const{

	return postalCode;
}

string Address::getLocation() const{

	return location;
}


string Address::getFullAdress() const{
    return getStreet()+"/"+std::to_string(getDoorNumber())+"/"+getFloor()+"/"+getPostalCode()+"/"+getLocation();

}


  // metodos SET

void Address::setStreet(string street){

	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber){

	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor){

	this->floor = floor;
}

void Address::setPostalCode(string postalCode){

	this->postalCode = postalCode;
}

void Address::setLocation(string  location){

	this->location = location;
}


/*********************************
 * Mostrar Address
 ********************************/  

// discplyes an address in a nice format
//ostream& operator<<(ostream& out, const Address & address){


//}

vector<string> vectorString(string morada, string separador){
    vector<string> ret;
    size_t startPos = 0, endPos = 0;
    while (endPos<morada.length()) {
        endPos=morada.find(separador,startPos);
        if(endPos==morada.npos) {
            ret.push_back(morada.substr(startPos));
            break;
        } else {
            ret.push_back(morada.substr(startPos,endPos-startPos));
        }
        startPos=endPos+separador.length();
    }
    if(ret[2].size()==0){
        ret[2]="-";
    }
    return ret;
}
