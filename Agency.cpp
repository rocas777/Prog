#include "Agency.h"
#include "funcs.h"
#include <fstream>

Agency::Agency(){
        ifstream agency_file;
        bool check=true;
        string tempAddress;
        string tempVat;
        cout<<"Introduza o nome do ficheiro da agencia (e.g agencia.txt):"<<endl<<endl;
        while(check){
            string fileName;
            //cin>>fileName;
            fileName="agency.txt";
            agency_file.open(fileName);
            if (agency_file.is_open()) {
                check=false;
                getline( agency_file, name );
                getline(agency_file,tempVat);
                VATnumber=unsigned(stoi(tempVat));
                getline( agency_file,  URL);
                getline( agency_file, tempAddress);
                address=Address(tempAddress);
                getline(agency_file,clientsFile);
                getline(agency_file,packsFile);
            }
            else {
                clearScreen();
                cout << "Erro ao abrir o ficheiro(\"Ficheiro Não encontrado\")"<<endl;
                cout<<"Introduza de novo o nome do ficheiro da agencia (e.g agencia.txt):"<<endl<<endl;
            }

        }
        agency_file.close();
        return;

}

  // metodos GET
string Agency::getName() const{

  return name;
}

unsigned Agency::getVATnumber() const{

  return VATnumber;
}

Address Agency::getAddress() const{

  return address;
}


string Agency::getURL() const{

  return    URL;
}

vector<Client> Agency::getClients() const{

  return clients;
}

vector<Packet> Agency::getPackets() const{

  return packets;
}

  
  // SET Methods

void Agency::setName(string name){

	this->name = name;
}


void Agency::setVATnumber(unsigned VATnumber){

	this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address){

	this->address = address;
}
void Agency::setURL(string url){

	URL = url;

}
void Agency::setClients(vector<Client> & clients){

	this->clients = clients;

 }
void Agency::setPackets(vector<Packet> & packets){

	this->packets = packets;

}

void Agency::setClientsFromFile(){
    ifstream clientes_file;
    clientes_file.open(this->clientsFile);
    string STRING;
	vector<string> tempClientVector, allIDs;
    while(getline(clientes_file,STRING))
    {
        if(STRING!="::::::::::"){
            tempClientVector.push_back(STRING);
        }
        else {
			allIDs = vectorString(tempClientVector[4], ";");
            this->clients.push_back(Client(tempClientVector[0],unsigned(stoi(tempClientVector[1])),unsigned(stoi(tempClientVector[2])),Address(tempClientVector[3]), StringIDtoPackVec(packets,allIDs), stoi(tempClientVector[5])));
            tempClientVector.clear();
        }
    }
	allIDs = vectorString(tempClientVector[4], ";");
	this->clients.push_back(Client(tempClientVector[0], unsigned(stoi(tempClientVector[1])), unsigned(stoi(tempClientVector[2])), Address(tempClientVector[3]), StringIDtoPackVec(packets, allIDs), stoi(tempClientVector[5])));
	tempClientVector.clear();
}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
//ostream& operator<<(ostream& out, const Agency & agency){

//  // A IMPLEMENTATION REQUIRED
//

void Agency::setPacketsFromFile(){
    ifstream PacketsFile;
    PacketsFile.open(this->packsFile);
    string STRING;
    getline(PacketsFile,STRING);
    vector<string> TempSitesVector;
    vector<string> TempOtherSites;
    Packet::setLastID(unsigned(stoi(STRING)));
    vector<string> tempPacketsVector;
    while(getline(PacketsFile,STRING))
    {
        if(STRING!="::::::::::"){
            tempPacketsVector.push_back(STRING);
        }
        else {
            TempSitesVector=vectorString(tempPacketsVector.at(1),"-");
            if(TempSitesVector.size()>1){
                TempOtherSites=vectorString(TempSitesVector.at(1),",");
            }
            TempOtherSites.insert(TempOtherSites.begin(),TempSitesVector.at(0));
            packets.push_back(Packet((abs(stoi(tempPacketsVector.at(0)))),TempOtherSites,Date(tempPacketsVector.at(2)),Date(tempPacketsVector.at(3)),stoi(tempPacketsVector.at(4)), (stoi(tempPacketsVector.at(5))), (stod(tempPacketsVector.at(6)))));
            if(stoi(tempPacketsVector.at(0))<0 || packets.back().getMaxPersons()==packets.back().getTotalPersons()){
                packets.back().setAvailable(false);
            }
            else {
                packets.back().setAvailable(true);
            }
            TempSitesVector.clear();
            TempOtherSites.clear();
            tempPacketsVector.clear();
        }
    }
    TempSitesVector=vectorString(tempPacketsVector.at(1),"-");
    if(TempSitesVector.size()>1){
        TempOtherSites=vectorString(TempSitesVector.at(1),",");
    }
    TempOtherSites.insert(TempOtherSites.begin(),TempSitesVector.at(0));
    if(stoi(tempPacketsVector.at(0))<0){

    }
    packets.push_back(Packet((abs(stoi(tempPacketsVector.at(0)))),TempOtherSites,Date(tempPacketsVector.at(2)),Date(tempPacketsVector.at(3)),stoi(tempPacketsVector.at(4)), (stoi(tempPacketsVector.at(5))), (stod(tempPacketsVector.at(6)))));
    if(stoi(tempPacketsVector.at(0))<0 || packets.back().getMaxPersons()==packets.back().getTotalPersons()){
        packets.back().setAvailable(false);
    }
    else {
        packets.back().setAvailable(true);
    }
    TempSitesVector.clear();
    TempOtherSites.clear();
    tempPacketsVector.clear();
}

void Agency::saveClientsToFile(){
    ofstream ClientsFile;
    ClientsFile.open(this->clientsFile);

    size_t x;
    for (x=0;x<clients.size()-1;x++) {
        ClientsFile<<clients[x].getName()<<endl;
        ClientsFile<<clients[x].getVATnumber()<<endl;
        ClientsFile<<clients[x].getFamilySize()<<endl;
        ClientsFile<<clients[x].getAddress().getFullAdress()<<endl;
        ClientsFile<<clients[x].getAllIDs()<<endl;
        ClientsFile<<clients[x].getTotalPurchased()<<endl;
        //ClientsFile<<clients[x].getMaxPersons()<<endl;
        ClientsFile<<"::::::::::"<<endl;
    }
    ClientsFile<<clients[x].getName()<<endl;
    ClientsFile<<clients[x].getVATnumber()<<endl;
    ClientsFile<<clients[x].getFamilySize()<<endl;
    ClientsFile<<clients[x].getAddress().getFullAdress()<<endl;
    ClientsFile<<clients[x].getAllIDs()<<endl;
    ClientsFile<<clients[x].getTotalPurchased()<<endl;
    //ClientsFile<<clients[x].getMaxPersons()<<endl;








}
void Agency::savePacketsToFile(){
    ofstream PacketsFile;
    PacketsFile.open(this->packsFile);
    PacketsFile<<Packet::getLastID()<<endl;
    size_t x;
    for (x=0;x<packets.size()-1;x++) {
        if(packets[x].getAvailability()){
            PacketsFile<<packets[x].getId()<<endl;
        }
        else {
            PacketsFile<<"-"+to_string(packets[x].getId())<<endl;
        }
        PacketsFile<<packets[x].getFullDestination()<<endl;
        PacketsFile<<packets[x].getBeginDate().getDate()<<endl;
        PacketsFile<<packets[x].getEndDate().getDate()<<endl;
        PacketsFile<<packets[x].getPricePerPerson()<<endl;
        PacketsFile<<packets[x].getTotalPersons()<<endl;
        PacketsFile<<packets[x].getMaxPersons()<<endl;
        PacketsFile<<"::::::::::"<<endl;
    }
    PacketsFile<<packets[x].getId()<<endl;
    PacketsFile<<packets[x].getFullDestination()<<endl;
    PacketsFile<<packets[x].getBeginDate().getDate()<<endl;
    PacketsFile<<packets[x].getEndDate().getDate()<<endl;
    PacketsFile<<packets[x].getPricePerPerson()<<endl;
    PacketsFile<<packets[x].getTotalPersons()<<endl;
    PacketsFile<<packets[x].getMaxPersons()<<endl;

}
	
void Agency::createClient() {
    clearScreen();
    clearBuffer();
	string name, exitstring, aux;
	unsigned VATnumber, familySize;
	bool invalidInput;
	Address morada;

    cout << "What's the name of the client? "; getline(cin, name); if (name == "!q") return;
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    do {
		invalidInput = false;
		cout << endl << "What's the VAT number? "; cin >> aux;
		if (strIsNumber(aux) && aux.length()==9) {
			VATnumber = stoi(aux);
			for (unsigned it = 0; it < clients.size(); it++) {
				if (VATnumber == clients.at(it).getVATnumber()) {
					invalidInput = true;
					break;
				}
			}
        }
		else {
            clearScreen();
            cout << "What's the name of the client? "<<name<<endl;
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	}
	while (invalidInput);
	clearBuffer();
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    cout << endl << "What's the VAT number? "<<VATnumber<<endl;
	do {
		invalidInput = false;
        cout << endl<< "What's the family size? "; cin >> aux;
        if (strIsNumber(aux) && aux.size()<9) familySize = stoi(aux);
		else {
            clearScreen();
            cout << "What's the name of the client? "<<name<<endl;
            cout << endl << "What's the VAT number? "<<VATnumber<<endl;
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    cout << endl << "What's the VAT number? "<<VATnumber<<endl;
    cout << endl<< "What's the family size? "<<familySize<<endl;
    cout << endl << "Now about the client's address:" << endl;
    clearBuffer();
	cout << "What's the street? ";  getline(cin, aux); if (aux == "!q") return; morada.setStreet(aux); cout << endl;
	do {
		invalidInput = false;
        cout << "What's the door number? "; cin >> aux;
		if (strIsNumber(aux)) morada.setDoorNumber(stoi(aux));
		else {
            clearScreen();
            cout << "What's the name of the client? "<<name<<endl;
            cout << endl << "What's the VAT number? "<<VATnumber<<endl;
            cout << endl<< "What's the family size? "<<familySize<<endl;
            cout << endl << "Now about the client's address:" << endl;
            cout << "What's the street? "<<morada.getStreet()<<endl;
			if (aux == "!q") return;
            cout << "Invalid data" << endl<<endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
    clearBuffer();
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    cout << endl << "What's the VAT number? "<<VATnumber<<endl;
    cout << endl<< "What's the family size? "<<familySize<<endl;
    cout << endl << "Now about the client's address:" << endl;
    cout << "What's the street? "<<morada.getStreet()<<endl;
    cout << "What's the door number? "<<morada.getDoorNumber()<<endl;
    cout << "What's the floor? ";  getline(cin, aux); if (aux == "!q") return; morada.setFloor(aux);
    clearScreen();cout << "What's the name of the client? "<<name<<endl;cout << endl << "What's the VAT number? "<<VATnumber<<endl;cout << endl<< "What's the family size? "<<familySize<<endl;cout << endl << "Now about the client's address:" << endl;cout << "What's the street? "<<morada.getStreet()<<endl;cout << "What's the door number? "<<morada.getDoorNumber()<<endl;cout << "What's the floor? "<<morada.getFloor()<<endl;cout << "What's the Postal Code? ";
    while(true){getline(cin, aux);if (aux == "!q") return;if(checkZip(aux)){morada.setPostalCode(aux);break;}else {clearScreen();cout << "What's the name of the client? "<<name<<endl;cout << endl << "What's the VAT number? "<<VATnumber<<endl;cout << endl<< "What's the family size? "<<familySize<<endl;cout << endl << "Now about the client's address:" << endl;cout << "What's the street? "<<morada.getStreet()<<endl;cout << "What's the door number? "<<morada.getDoorNumber()<<endl;cout << "What's the floor? "<<morada.getFloor()<<endl;cout << "Zip code incorrect"<<endl<< "What's the Postal Code? ";
        }
    }
	cout << "What's the Location? ";  getline(cin, aux); if (aux == "!q") return; morada.setLocation(aux); cout << endl;
	//depois usar a funçao de alterar um cliente para confirmar o client.
    clients.push_back(Client(name, VATnumber, familySize, morada));
}

void Agency::createPacket() {
	clearScreen();
	clearBuffer();
	vector<string> sites;
	string aux, confirmstr;
	Date start, end;
	bool invalidDate, invalidInput, digitInput;
	double pricePerson;
	unsigned maxPerson, totalPerson;

	cout << "What's the main destination? "; getline(cin, aux); if (name == "!q") return; sites.push_back(aux);
	do {
		do {
			clearScreen();
			cout << "What's the destination? " << strVecToStr(sites) << endl;
			cout << "Do you want to add any turistic recommendation?" << endl;
			cout << "Y/N: ";
			cin >> confirmstr;
		} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
		clearBuffer();
		if (confirmstr == "Y" || confirmstr == "y") {
			cout << "What is it? "; getline(cin, aux); if (aux == "!q") return; sites.push_back(aux);
		}
	} while (confirmstr == "Y" || confirmstr == "y");
	invalidDate = false;
	do {
		clearScreen();
		cout << "What's the destination? " << strVecToStr(sites) << endl;
		if (invalidDate) {
			cout << "The date that was given is invalid" << endl;
		}
		cout << "What's the beginning date (YYYY/MM/DD)? "; getline(cin, aux);  if (aux == "!q") return;
		vector<string> test = vectorString(aux, "/");
		digitInput = true;
		if (test.size() != 3) digitInput = false;
		if (digitInput) {
			for (unsigned i = 0; i < test.size(); i++) {
				if (!strIsNumber(test[i])) digitInput = false; break;
			}
		}
		if (!digitInput) invalidDate = true;
		else {
			start = Date(aux);
			invalidDate = !start.isValid();
		}
	} while (invalidDate);
	do {
		clearScreen();
		cout << "What's the destination? " << strVecToStr(sites) << endl;
		cout << "What's the beginning date (YYYY/MM/DD)? " << start.getDate() << endl;
		if (invalidDate) {
			cout << "The date that was given is invalid" << endl;
		}
		cout << "What's the ending date (YYYY/MM/DD)? "; getline(cin, aux);  if (aux == "!q") return;
		vector<string> test = vectorString(aux, "/");
		digitInput = true;
		if (test.size() != 3) digitInput = false;
		if (digitInput) {
			for (unsigned i = 0; i < test.size(); i++) {
				if (!strIsNumber(test[i])) digitInput = false; break;
			}
		}
		if (!digitInput) invalidDate = true;
		else {
			end = Date(aux);
			invalidDate = !end.isValid();
		}
	} while (invalidDate);
	clearScreen();
	cout << "What's the destination? " << strVecToStr(sites) << endl;
	cout << "What's the beginning date (YYYY/MM/DD)? " << start.getDate() << endl;
	cout << "What's the ending date (YYYY/MM/DD)? " << end.getDate() << endl;
	do {
		invalidInput = false;
		cout << endl << "What's the price per person? "; getline(cin, aux);
		if (strIsNumber(aux)) pricePerson = stoi(aux);
		else {
			clearScreen();
			cout << "What's the destination? " << strVecToStr(sites) << endl;
			cout << "What's the beginning date (YYYY/MM/DD)? " << start.getDate() << endl;
			cout << "What's the ending date (YYYY/MM/DD)? " << end.getDate() << endl;
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
	clearScreen();
	cout << "What's the destination? " << strVecToStr(sites) << endl;
	cout << "What's the beginning date (YYYY/MM/DD)? " << start.getDate() << endl;
	cout << "What's the ending date (YYYY/MM/DD)? " << end.getDate() << endl;
	cout << "What's the price per person? " << pricePerson << endl;
	do {
		invalidInput = false;
		cout << endl << "How many seats are available? "; getline(cin, aux);
		if (strIsNumber(aux)) maxPerson = totalPerson = stoi(aux);
		else {
			clearScreen();
			cout << "What's the destination? " << strVecToStr(sites) << endl;
			cout << "What's the beginning date (YYYY/MM/DD)? " << start.getDate() << endl;
			cout << "What's the ending date (YYYY/MM/DD)? " << end.getDate() << endl;
			cout << "What's the price per person? " << pricePerson << endl;
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);

	//depois usar a funçao de alterar um packs para confirmar o packs.
	
	//packets.push_back(Packet(sites, start, end, pricePerson, totalPerson, maxPerson));
}
