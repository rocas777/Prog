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
    packets.push_back(Packet((abs(stoi(tempPacketsVector.at(0)))),TempOtherSites,Date(tempPacketsVector.at(2)),Date(tempPacketsVector.at(3)),stoi(tempPacketsVector.at(4)), (stoi(tempPacketsVector.at(5))), (stod(tempPacketsVector.at(6)))));
    TempSitesVector.clear();
    TempOtherSites.clear();
    tempPacketsVector.clear();
}

void Agency::saveClientsToFile(){
    ofstream PacketsFile;
    PacketsFile.open(this->packsFile);
    //qyyyy

}
void savePacketsToFile() {

}
	
void createClient(vector<Client>& clients) {
	string name, exitstring, aux;
	unsigned VATnumber, familySize;
	bool invalidInput;
	Address morada;

	cout << "What's the name of the client? "; getline(cin, name); if (name == "!q") return;
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
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	}
	while (invalidInput);
	clearBuffer();
	do {
		invalidInput = false;
		cout << endl; "What's the family size? "; cin >> aux;
		if (strIsNumber(aux)) familySize = stoi(aux);
		else {
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
	cout << "Now about the client's address:" << endl;
	cout << "What's the street? ";  getline(cin, aux); if (aux == "!q") return; morada.setStreet(aux); cout << endl;
	do {
		invalidInput = false;
		cout << endl; "What's the door number? "; cin >> aux;
		if (strIsNumber(aux)) morada.setDoorNumber(stoi(aux));
		else {
			if (aux == "!q") return;
			cout << "Invalid data" << endl;
			clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
	cout << "What's the floor? ";  getline(cin, aux); if (aux == "!q") return; morada.setFloor(aux); cout << endl;
	cout << "What's the Postal Code? ";  getline(cin, aux); if (aux == "!q") return; morada.setPostalCode(aux); cout << endl;
	cout << "What's the Location? ";  getline(cin, aux); if (aux == "!q") return; morada.setLocation(aux); cout << endl;
	
	//depois usar a funçao de alterar um cliente para confirmar o client.

}

void createPacket(vector <Packet>& packets) {

}
