#include "Agency.h"
#include "funcs.h"
#include <fstream>
#include <map>
#include "Menus.h"
#include <algorithm>

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
unsigned Agency::getPacketsSold() const {
	return totalPacketsSold;
}
unsigned Agency::getTotalMoneyMade() const {
	return totalMoneyMade;
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
void Agency::setPacketsSoldAndMonneyMade() {
	unsigned nrpackets, alleuros;
	nrpackets = alleuros = 0;
	for (size_t i = 0; i < packets.size(); i++) {
		nrpackets += packets[i].getMaxPersons();
		alleuros += (packets[i].getMaxPersons() * packets[i].getPricePerPerson());
	}
	totalPacketsSold = nrpackets;
	totalMoneyMade = alleuros;
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
void Agency::setPacketsFromFile(){
    ifstream PacketsFile;
    PacketsFile.open(this->packsFile);
    string STRING;

    vector<string> TempSitesVector;   //vetor para guardar o destino  em [0] e os locais de interesse em [1]

    vector<string> TempOtherSites;    //vetor para guardar o destino  em [0] e os locais de interesse nos index seguintes

    getline(PacketsFile, STRING);
    Packet::setLastID(unsigned(stoi(STRING)));

    vector<string> tempPacketsVector; //vetor para guardar informaçao dos pacotes
    while(getline(PacketsFile,STRING))
    {
        if(STRING!="::::::::::"){
            tempPacketsVector.push_back(STRING);
        }
        else {// quando a string lida é "::::::::::" os dados são guardados no vetor
            TempSitesVector=vectorString(tempPacketsVector.at(1)," - ");
            if(TempSitesVector.size()>1){
                TempOtherSites=vectorString(TempSitesVector.at(1),", ");
            }

            TempOtherSites.insert(TempOtherSites.begin(),TempSitesVector.at(0));

            //adiciona no vetor packets inicializando a classe Packet
            packets.push_back(Packet((abs(stoi(tempPacketsVector.at(0)))),TempOtherSites,Date(tempPacketsVector.at(2)),Date(tempPacketsVector.at(3)),stoi(tempPacketsVector.at(4)), (stoi(tempPacketsVector.at(5))), (stod(tempPacketsVector.at(6)))));
            if(stoi(tempPacketsVector.at(0))<0 || packets.back().getMaxPersons()==packets.back().getTotalPersons()){
                packets.back().setAvailable(false);
            }
            else {
                packets.back().setAvailable(true);
            };
            TempSitesVector.clear();
            TempOtherSites.clear();
            tempPacketsVector.clear();
        }
    }
    TempSitesVector=vectorString(tempPacketsVector.at(1)," - ");
    if(TempSitesVector.size()>1){
        TempOtherSites=vectorString(TempSitesVector.at(1),", ");
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

/*********************************
 * Mostrar Loja
 ********************************/

// mostra o conteudo de uma agencia
//ostream& operator<<(ostream& out, const Agency & agency){

//  // A IMPLEMENTATION REQUIRED
//


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
        ClientsFile<<"::::::::::"<<endl;
    }
    ClientsFile<<clients[x].getName()<<endl;
    ClientsFile<<clients[x].getVATnumber()<<endl;
    ClientsFile<<clients[x].getFamilySize()<<endl;
    ClientsFile<<clients[x].getAddress().getFullAdress()<<endl;
    ClientsFile<<clients[x].getAllIDs()<<endl;
    ClientsFile<<clients[x].getTotalPurchased();
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
    PacketsFile<<packets[x].getMaxPersons();

}

void Agency::createClient() {
    clearScreen();
    clearBuffer();
    string name, exitstring, aux;
    unsigned VATnumber, familySize;
    bool invalidInput;
    Address morada;

//ciclo para pedir o nome do novo cliente
    cout << "What's the name of the client? "; getline(cin, name); if (name == "!q") return;

//ciclo para pedir o vat do novo cliente
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl; //imprime os dados já inseridos
    do {
        invalidInput = false;
        cout << endl << "What's the VAT number? "; cin >> aux;

        //verifica se o vat é constituido por numeros e se o tamanho é de 9 digitos
        if (strIsNumber(aux) && aux.size()==9) {
            VATnumber = stoi(aux);

            //verifica se o nif inserido é unico
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

//ciclo para pedir o vat do novo cliente
    clearBuffer();
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    cout << endl << "What's the VAT number? "<<VATnumber<<endl;
    do {
        invalidInput = false;
        cout << endl<< "What's the family size? "; cin >> aux;
        //verifica se o tamanho do agregado é menor que nove, e se apenas contem algarismos
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
    clearScreen();
    cout << "What's the name of the client? "<<name<<endl;
    cout << endl << "What's the VAT number? "<<VATnumber<<endl;cout << endl<< "What's the family size? "<<familySize<<endl;
    cout << endl << "Now about the client's address:" << endl;
    cout << "What's the street? "<<morada.getStreet()<<endl;
    cout << "What's the door number? "<<morada.getDoorNumber()<<endl;
    cout << "What's the floor? "<<morada.getFloor()<<endl;cout << "What's the Postal Code? ";
    while(true){
        getline(cin, aux);
        if (aux == "!q") return;
        if(checkZip(aux)){
            morada.setPostalCode(aux);
            break;
        }
        else {
            clearScreen();
            cout << "What's the name of the client? "<<name<<endl;
            cout << endl << "What's the VAT number? "<<VATnumber<<endl;
            cout << endl<< "What's the family size? "<<familySize<<endl;
            cout << endl << "Now about the client's address:" << endl;
            cout << "What's the street? "<<morada.getStreet()<<endl;
            cout << "What's the door number? "<<morada.getDoorNumber()<<endl;
            cout << "What's the floor? "<<morada.getFloor()<<endl;
            cout << "Zip code incorrect"<<endl<< "What's the Postal Code? ";
        }
    }
    cout << "What's the Location? ";  getline(cin, aux); if (aux == "!q") return; morada.setLocation(aux); cout << endl;
    //depois usar a funçao de alterar um cliente para confirmar o client.

    clientsInfoHasChanged=true;
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

    cout << "What's the main destination? ";
    getline(cin, aux);
    if (aux == "!q") return;
    sites.push_back(aux);
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
                if (!strIsNumber(test[i])) {
                    digitInput = false;
                    break;
                }
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
                if (!strIsNumber(test[i])) {
                    digitInput = false;
                    break;
                }
            }
        }
        if (!digitInput) invalidDate = true;
        else if(Date(aux)>start){
            end = Date(aux);
            invalidDate = !end.isValid();
        }
        else {
            invalidDate=true;
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
        if (strIsNumber(aux)) totalPerson = stoi(aux);
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

    //changePackets();

    packetsInfoHasChanged=true;
    packets.push_back(Packet(sites, start, end, pricePerson, totalPerson, 0));
}

void Agency::changeClient() {
    bool invalidInput, doagain, confirmop;
    unsigned opChoose, indexAtClients;
    int auxint;
    string aux, confirmstr;
    Address morada;
    vector<Packet> packetcopia = packets;
    Client copia;
    cout<<clients.at(0);
    clearScreen();
    printClientsVector(clients);
    do {
        invalidInput = true;
        cout << endl << "What's the VAT number of the client you wish to edit? "; cin >> aux;
        if (strIsNumber(aux) && aux.length() == 9) {
            VATnumber = stoi(aux);
            for (unsigned it = 0; it < clients.size(); it++) {
                if (VATnumber == clients.at(it).getVATnumber()) {
                    do {
                        clearScreen();
                        cout << "Client found!!!" << endl;
                        indexAtClients = it;
                        clients.at(it).showFullInfo();
                        cout << "Is this the target client?" << endl;
                        cout << "Y/N: ";
                        getline(cin,confirmstr);
                    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
                    (confirmstr == "Y" || confirmstr == "y") ? invalidInput = false : invalidInput = true;
                    clearScreen();
                    printClientsVector(clients);
                    if (!invalidInput) copia = clients.at(it);
                    break;
                }
            }
        }
        else {
            clearScreen();
            printClientsVector(clients);
            if (aux == "!q") return;
            cout << "Invalid VAT number format or there's no client with one has such" << endl;
            clearBuffer();
            invalidInput = true;
        }
    } while (invalidInput);
    do {
        clearScreen();
        doagain = true;
        cout << endl << "**************************" << endl;
        cout << "Client Edit Menu" << endl;
        cout << "**************************" << endl << endl;
        copia.showFullInfo(); cout << endl;
        cout << "[1] - Change name" << endl;
        cout << "[2] - Change VAT number" << endl;
        cout << "[3] - Change family size" << endl;
        cout << "[4] - Change address" << endl;
        cout << "[5] - Change Packets Bought" << endl;
        cout << "[0] - Return to Client Menu" << endl;
        cout << "Please choose an option:" << endl;
        bool changes=false;
        if (aux == "!q") return;
        getline(cin,aux);
        if (strIsNumber(aux) && (stoi(aux) >= 0 && stoi(aux) <= 5)) {
                switch (stoi(aux)) {
                    case(1): {
                        clearScreen();
                        cout <<"What's the Name?([!q] to cancel)(empty to keep value)"<<endl;
                        getline(cin,aux);
                        if (aux == "!q") return;
                        else if (aux=="") {
                            break;
                        }
                        changes=true;
                        copia.setName(aux);
                        break;
                    }
                    case(2): {
                        clearScreen();
                        cout << endl << "What's the VAT number?([!q] to cancel)(empty to keep value) "; getline(cin,aux);
                        do {
                            invalidInput = false;
                            if(aux==""){
                                break;
                            }
                            if (strIsNumber(aux) && aux.length() == 9) {
                                auxint = stoi(aux);
                                for (unsigned it = 0; it < clients.size(); it++) {
                                    if (auxint == clients.at(it).getVATnumber()) {
                                        clearScreen();
                                        if (aux == "!q") return;
                                        cout << "Invalid format or a client with that VAT already exists" << endl;
                                        cout << endl << "What's the VAT number?([!q] to cancel)(empty to keep value) "; getline(cin,aux);
                                        invalidInput = true;
                                        break;
                                    }
                                }
                                if(!invalidInput){
                                    changes=true;
                                    copia.setVATnumber(auxint);
                                }
                            }
                            else {
                                clearScreen();
                                if (aux == "!q") return;
                                cout << "Invalid format or a client with that VAT already exists" << endl;
                                cout << endl << "What's the VAT number?([!q] to cancel)(empty to keep value) "; getline(cin,aux);
                                invalidInput = true;
                            }
                        } while (invalidInput);
                        break;
                    }
                    case(3): {
                        clearScreen();
                        do {
                            invalidInput = false;
                            cout << endl << "What's the family size? "; getline(cin, aux);
                            if(aux==""){
                                break;
                            }
                            if (strIsNumber(aux) && aux.size()<10){
                                auxint = stoi(aux);
                                changes=true;
                                copia.setFamilySize(auxint);
                            }
                            else {
                                clearScreen();
                                if (aux == "!q") return;
                                cout << "Invalid data" << endl;
                                invalidInput = true;
                            }
                        } while (invalidInput);
                        break;
                    }
                    case(4): {
                        changes=true;
                        morada=copia.getAddress();
                        clearScreen();
                        cout << "What's the street? ";  getline(cin, aux);
                        if(aux==""){
                        }
                        else if (aux == "!q") return;
                        else {
                            morada.setStreet(aux);
                        }
                        clearScreen();
                        do {
                            invalidInput = false;
                            cout << "What's the street? " << morada.getStreet() << endl;
                            cout << "What's the door number? "; getline(cin, aux);
                            if(aux==""){
                                morada.setDoorNumber(copia.getAddress().getDoorNumber());
                                break;
                            }
                            if (strIsNumber(aux)) morada.setDoorNumber(stoi(aux));
                            else {
                                clearScreen();
                                if (aux == "!q") return;
                                cout << "Invalid data" << endl << endl;
                                invalidInput = true;
                            }
                        } while (invalidInput);
                        clearScreen();
                        cout << "What's the street? " << morada.getStreet() << endl;
                        cout << "What's the door number? " << morada.getDoorNumber() << endl;
                        cout << "What's the floor? ";
                        getline(cin, aux);
                        if (aux == "!q") return;
                        else if (aux=="") {

                        }
                        else {
                            morada.setFloor(aux);
                        }
                        clearScreen();
                        cout << "What's the street? " << morada.getStreet() << endl;
                        cout << "What's the door number? " << morada.getDoorNumber() << endl;
                        cout << "What's the floor? " << morada.getFloor() << endl;
                        cout << "What's the Postal Code? ";
                        while (true) {
                            getline(cin, aux);
                            if (aux == "!q") return;
                            else if (aux=="") break;
                            else if (checkZip(aux)) {
                                morada.setPostalCode(aux);
                                copia.setAddress(morada);
                                break;
                            }
                            else {
                                clearScreen();
                                cout << "What's the street? " << morada.getStreet() << endl;
                                cout << "What's the door number? " << morada.getDoorNumber() << endl;
                                cout << "What's the floor? " << morada.getFloor() << endl;
                                cout << "Zip code incorrect" << endl << "What's the Postal Code? ";
                            }
                        }
                        clearScreen();
                        cout << "What's the street? " << morada.getStreet() << endl;
                        cout << "What's the door number? " << morada.getDoorNumber() << endl;
                        cout << "What's the floor? " << morada.getFloor() << endl;
                        cout << "What's the Postal Code? "<<morada.getPostalCode()<<endl;
                        cout << "What's the Location? ";
                        getline(cin, aux);
                        if (aux == "!q") return;
                        else if(aux==""){

                        }
                        else{
                            morada.setLocation(aux);
                        }
                        cout << endl;
                        copia.setAddress(morada);
                        break;
                    }
                    case(5): {
                        clearScreen();
                        do {
                            invalidInput = false;
                            cout << "The client has bought these packets: " << copia.getAllIDs() << endl;
                            cout << "What's the ID of the one you'd like to return? "; getline(cin, aux);
                            if(aux==""){
                                break;
                            }
                            if (strIsNumber(aux)) {
                                auxint = -1;
                                for (size_t i=0;i<copia.getPacketList().size();i++) {
                                    if (stoi(aux) == copia.getPacketList().at(i).getId()) {
                                        auxint = i;
                                        break;
                                    }
                                }
                                if (auxint != -1) {
                                    vector<Packet> auxiliar = copia.getPacketList();
                                    auxiliar.erase(auxiliar.begin()+auxint);
                                    copia.setPacketList(auxiliar);
                                    changes=true;
                                    auxint = BinarySearchID(packetcopia, stoi(aux));
                                    if(auxint>=0){
                                        packetcopia.at(auxint).setMaxPersons(packetcopia.at(auxint).getMaxPersons() + copia.getFamilySize());
                                    }
                                    }
                            }
                            else {
                                clearScreen();
                                if (aux == "!q") return;
                                cout << "The Client hasn't bought that pack" << endl << endl;
                                clearBuffer();
                                invalidInput = true;
                            }
                        } while (invalidInput);
                        break;
                    }
                    case(0): {
                        clearScreen();
                        copia.showFullInfo();
                        do {
                            confirmop = false;
                            menu_changes();
                            cin >> aux;
                            if (aux == "!q") return;
                            if (strIsNumber(aux) && (stoi(aux) >= 1 && stoi(aux)<= 3)) {
                                    switch (stoi(aux)) {
                                        case(1): {
                                            clients.at(indexAtClients) = copia;
                                            packets = packetcopia;
                                            packetsInfoHasChanged=true;
                                            clientsInfoHasChanged=true;
                                            return;
                                        }
                                        case(2): {
                                            doagain = true;
                                            break;
                                        }
                                        case(3): {
                                            return;
                                        }
                                    }
                                }
                                else {
                                    clearScreen();
                                    cout << "There is no such option" << endl << endl;
                                    clearBuffer();
                                    confirmop = true;
                                }
                        } while (confirmop);

                        break;
                    }

                }
            }

        else {
            clearScreen();
            cout << "There is no such option" << endl << endl;
            confirmop = true;
        }
    } while (doagain);
}
void Agency::changePackets(){

    clearScreen();
    printPacketsVector(packets);
    cout<<"What Packet you wish to change?\nWhat is his ID?"<<endl;
    string inputID;
    Packet pacote;
    int index;
    vector<string> sites;
    string aux, confirmstr;
    Date start, end;
    bool invalidDate, invalidInput, digitInput;
    double pricePerson;
    unsigned maxPerson, totalPerson;
    while (true) {
        cin>>inputID;
        if(inputID=="!q"){
            return;
        }
        if(strIsNumber(inputID)){
            index=BinarySearchID(packets,(stoi(inputID)));
            if(index>=0){
                break;
            }
            else {
                cout<<"ID not found"<<endl;
                cout<<"What Packet you wish to change?\nWhat is his ID?"<<endl;
            }
        }
        else {
            cout<<"Invalid Input"<<endl;
            cout<<"What Packet you wish to change?\nWhat is his ID?"<<endl;
        }
    }
    clearScreen();
    pacote=packets.at(index);
    cout << endl << "**************************" << endl;
    cout << "Packet Edit Menu" << endl;
    cout << "**************************" << endl << endl;
    pacote.showFullInfo();
    cout<<endl<<"Want to proceed?"<<endl<<"Y/N :";
    while(true){
        string y_n;
        clearBuffer();
        cin>>y_n;
        if(y_n=="n" || y_n=="N"){
            return;
        }
        else if (y_n=="y" || y_n=="Y") {
            break;
        }
        else {
            cout << endl << "**************************" << endl;
            cout << "Packet Edit Menu" << endl;
            cout << "**************************" << endl << endl;
            pacote.showFullInfo();
            cout<<endl<<"Invalid Input";
            cout<<endl<<"Want to proceed?"<<endl<<"Y/N: ";
        }
    }

    while(true){
        clearScreen();
        cout << endl << "**************************" << endl;
        cout << "Packet Edit Menu" << endl;
        cout << "**************************" << endl << endl;
        pacote.showFullInfo();
        cout << "[1] - Change Destination" << endl;
        cout << "[2] - Change Beginning Date" << endl;
        cout << "[3] - Change Ending Date" << endl;
        cout << "[4] - Change Price per Person" << endl;
        cout << "[5] - Change Total Persons" << endl;
        cout << "[0] - Return to Client Menu" << endl;
        cout << "Please choose an option:" << endl;
        switch (selec(0,5)) {
        case(0):{
            clearScreen();
            pacote.showFullInfo();
            menu_changes();
            int selection;
            bool exit=true;
            while (exit) {
                cin >> selection;
                if (cin.fail()) {
                    cin.clear(); //clear stream
                    cin.ignore(); //ignore left over data
                }
                else if (selection >= 1 && selection <= 3) {
                    switch (selection) {
                    case(1):{
                        packets.at(size_t(index))=pacote;
                        exit=false;
                        packetsInfoHasChanged=true;
                        clientsInfoHasChanged=true;
                        return;
                    }
                    case(2):{
                        exit=false;
                        break;
                    }
                    case(3):{
                        return;
                    }
                    }
                }
                else {
                    clearScreen();
                    pacote.showFullInfo();
                    menu_changes();
                    cout << "\nOption not allowed.\nPlease Try again:" << endl;
                }
            }
            break;
        }
        case(1):{
            clearScreen();
            bool canChange=true;
            cout << endl << "**************************" << endl;
            cout << "Packet Edit Menu" << endl;
            cout << "**************************" << endl << endl;
            pacote.showFullInfo();
            cout << "What's the main destination? :";
            clearBuffer();
            getline(cin, aux);
            if (aux == "!q") return;
            if (aux == ""){
                break;
            }
            sites.push_back(aux);
            do {
                do {
                    clearScreen();
                    cout << endl << "**************************" << endl;
                    cout << "Packet Edit Menu" << endl;
                    cout << "**************************" << endl << endl;
                    pacote.showFullInfo();
                    cout << "What's the main destination? " << strVecToStr(sites) << endl;
                    cout << "Do you want to add any turistic recommendation?" << endl;
                    cout << "Y/N: ";
                    cin>>confirmstr;
                    if(confirmstr=="!q"){
                        return;
                    }
                    if(confirmstr==""){
                        confirmstr="n";
                        canChange=false;
                    }
                } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
                clearBuffer();
                clearScreen();
                if (confirmstr == "Y" || confirmstr == "y") {
                    cout << "What recomendation you would like to add?"<<endl<<"(If you don' want to add a recomendation, keep this empty)"; getline(cin, aux);
                    if (aux == "!q") return;
                    if (aux != "") sites.push_back(aux);
                }
            } while (confirmstr == "Y" || confirmstr == "y");
            if(canChange) pacote.setSites(sites);
            break;
        }

        case(2):{
            clearBuffer();
            invalidDate = false;
            start=pacote.getBeginDate();
            do {
                clearScreen();
                cout << endl << "**************************" << endl;
                cout << "Packet Edit Menu" << endl;
                cout << "**************************" << endl << endl;
                pacote.showFullInfo();
                if (invalidDate) {
                    cout << "The date that was given is invalid" << endl;
                }
                cout << "What's the beginning date (YYYY/MM/DD)? "; getline(cin, aux);  if (aux == "!q") return;
                if(aux=="") break;
                vector<string> test = vectorString(aux, "/");
                digitInput = true;
                if (test.size() != 3) digitInput = false;
                if (digitInput) {
                    for (unsigned i = 0; i < test.size(); i++) {
                        if (!strIsNumber(test[i])) {
                            digitInput = false;
                            break;
                        }
                    }
                }
                if (!digitInput) invalidDate = true;
                else {
                    start = Date(aux);
                    invalidDate = !start.isValid();
                }
            } while (invalidDate);
            pacote.setBeginDate(start);
            break;
        }
        case(3):{
            clearBuffer();
            invalidDate = false;
            do {
                clearScreen();
                cout << endl << "**************************" << endl;
                cout << "Packet Edit Menu" << endl;
                cout << "**************************" << endl << endl;
                pacote.showFullInfo();
                if (invalidDate) {
                    cout << "The date that was given is invalid" << endl;
                }
                start=pacote.getBeginDate();
                cout << "What's the ending date (YYYY/MM/DD)? "; getline(cin, aux);  if (aux == "!q") return;
                if(aux=="") {
                    end=pacote.getEndDate();
                    break;
                }
                vector<string> test = vectorString(aux, "/");
                digitInput = true;
                if (test.size() != 3) digitInput = false;
                if (digitInput) {
                    for (unsigned i = 0; i < test.size(); i++) {
                        if (!strIsNumber(test[i])) {
                            digitInput = false;
                            break;
                        }
                    }
                }
                if (!digitInput) invalidDate = true;
                else if(Date(aux)>start){
                    end = Date(aux);
                    invalidDate = (!end.isValid());
                }
                else {
                    invalidDate=true;
                }
            } while (invalidDate);
            pacote.setEndDate(end);
            break;
        }
        case(4):{
            bool invalid=false;
            clearBuffer();
            while (true) {
                clearScreen();
                cout << endl << "**************************" << endl;
                cout << "Packet Edit Menu" << endl;
                cout << "**************************" << endl << endl;
                pacote.showFullInfo();
                if(invalid){
                    cout<<"Input is Invalid"<<endl;
                }
                cout <<"What is the new value for the Price per Person?"<<endl;
                cout <<"(This may cause Incorrection on the clients Total of purchases in case you make a packet's return."<<endl<<"Proceed with caution)"<<endl;
                getline(cin,aux);
                if(aux==""){
                    break;
                }
                if(aux=="!q"){
                    return;
                }
                if(strIsNumber(aux) && aux.size()<9 && stoi(aux)>=0 ){
                    pacote.setPricePerPerson(stoi(aux));
                    break;
                }
                else {
                    invalid=true;
                }
            }
            break;
        }
        case(5):{
            bool invalid=false;
            bool invalidNumber=false;
            clearBuffer();
            while (true) {
                clearScreen();
                cout << endl << "**************************" << endl;
                cout << "Packet Edit Menu" << endl;
                cout << "**************************" << endl << endl;
                pacote.showFullInfo();
                if(invalid){
                    cout<<"Input is Invalid"<<endl;
                }
                if(invalidNumber){
                    cout<<"Your input would cause a negative number of Available Places, Please try again"<<endl;
                }
                cout <<"What is the new value for the Total Persons?(enter to keep "<<pacote.getTotalPersons()<<")([!q] to quit)"<<endl;
                cout <<"Values must be above or equal to "<<pacote.getMaxPersons()<<endl;
                getline(cin,aux);
                if(aux==""){
                    break;
                }
                if(aux=="!q"){
                    return;
                }
                if(strIsNumber(aux) && aux.size()<9 && stoi(aux)>=0 && pacote.getMaxPersons()<=unsigned(stoi(aux))){
                    pacote.setTotalPersons(unsigned(stoi(aux)));
                    if(pacote.getMaxPersons()==pacote.getTotalPersons()){
                        pacote.setAvailable(false);
                    }
                    else {
                        pacote.setAvailable(true);
                    }
                    break;
                }
                else if((pacote.getMaxPersons()>unsigned(stoi(aux)))){
                    invalidNumber =true;
                    invalid=false;
                }
                else {
                    invalid=true;
                }

            }

        }
        }
    }
}

void Agency::removeClient() {
	bool invalidInput;
	string aux, confirmstr;
	cout << clients.at(0);
	clearScreen();
	printClientsVector(clients);
	do {
		invalidInput = true;
        cout << endl << "What's the VAT number of the client you wish to remove? "; cin >> aux;
		if (strIsNumber(aux) && aux.length() == 9) {
			VATnumber = stoi(aux);
			for (unsigned it = 0; it < clients.size(); it++) {
				if (VATnumber == clients.at(it).getVATnumber()) {
					do {
						clearScreen();
						cout << "Client found!!!" << endl;
						clients.at(it).showFullInfo();
						cout << "Do you really wish to delete this client from the agency's database? Once this has been confirmed you can't get the info back" << endl;
						cout << "Y/N: ";
						getline(cin, confirmstr);
					} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
					if (confirmstr == "Y" || confirmstr == "y") {
                        clients.erase(clients.begin() + it);
                        clientsInfoHasChanged=true;
					}
					clearScreen();
					printClientsVector(clients);
                    return;
				}
			}
		}
		else {
			clearScreen();
			printClientsVector(clients);
			if (aux == "!q") return;
			cout << "Invalid VAT number format or there's no client with one has such" << endl;
            clearBuffer();
			invalidInput = true;
		}
	} while (invalidInput);
}
void Agency::removePacket() {
	clearScreen();
	printPacketsVector(packets);
	cout << "What Packet you wish to change?\nWhat is his ID?" << endl;
	string inputID;
	int index;
	string aux, confirmstr;
	while (true) {
        cin >> inputID;
		if (inputID == "!q") {
			return;
		}
		if (strIsNumber(inputID)) {
			index = BinarySearchID(packets, (stoi(inputID)));
			if (index >= 0) {
				do {
                    clearScreen();
                    packets.at(index).showFullInfo(); //fica para depois isto nao existe!!!!!!!!!!!!!!!
                    if(packets.at(index).getAvailability()){
                        cout<<"This packet is available, do you want to turn it unavailable?"<<endl;
                    }
                    else {
                        cout<<"This packet is unavailable, do you want to turn it available?"<<endl;
                    }
					cout << "Y/N: ";
					getline(cin, confirmstr);
				} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
				if (confirmstr == "Y" || confirmstr == "y") {
                    if(packets.at(index).getMaxPersons()<packets.at(index).getTotalPersons()){
                        packets.at(index).setAvailable(!packets.at(index).getAvailability());
                        packetsInfoHasChanged=true;
                    }
                    else {
                        cout<<"This packet can't be turned available due to lack of available places"<<endl;
                        cout<<"Press enter to proceed."<<endl;
                        getline(cin,aux);
                    }
                }
				break;
			}
			else {
				cout << "ID not found" << endl;
				cout << "What Packet you wish to change?\nWhat is his ID?" << endl;
			}
		}
		else {
			cout << "Invalid Input" << endl;
			cout << "What Packet you wish to change?\nWhat is his ID?" << endl;
		}
	}
}

void Agency::sellPacketToClient(){
    printClientsVector(clients);
    size_t index=0;
    string selectVat;
    bool isInvalid=true;
    clearScreen();
    printClientsVector(clients);
    while (isInvalid) {
        cout<<"What is the Client's VAT number? : "<<endl;
        clearBuffer();
        getline(cin,selectVat);
        if(selectVat=="!q"){
            return;
        }
        if(strIsNumber(selectVat) && selectVat.size()==9){
            for (index=0;index<clients.size();index++) {
                if(clients.at(index).getVATnumber()==unsigned(stoi(selectVat))){
                    isInvalid=false;
                    break;
                }
            }
            if(index<0){
                clearScreen();
                printClientsVector(clients);
                cout<<"VAT number not found"<<endl;
            }

        }
        else {
            clearScreen();
            printClientsVector(clients);
            cout<<"Invalid VAT number"<<endl;
        }
    }
    clearScreen();
    printPacketsVectorWAvailability(packets);
    cout<<endl;
    clients.at(index).showFullInfo();
    cout<<endl;
    int packetIndex =0;
    string selectID;
    isInvalid=true;
    while (isInvalid) {
        cout<<"What is the Packet's ID number? : "<<endl;
        getline(cin,selectID);
        if(selectID=="!q"){
            return;
        }
        if(strIsNumber(selectID) && selectID.size()<9){
            if(packetIndex<0){
                clearScreen();
                printPacketsVectorWAvailability(packets);
                cout<<endl;
                clients.at(index).showFullInfo();
                cout<<endl;
                cout<<"ID number not found"<<endl;
            }
            else {
                packetIndex=BinarySearchID(packets,stoi(selectID));
                if((packets.at(packetIndex).getTotalPersons()-packets.at(packetIndex).getMaxPersons())<clients.at(index).getFamilySize()){
                    clearScreen();
                    printPacketsVectorWAvailability(packets);
                    cout<<endl;
                    clients.at(index).showFullInfo();
                    cout<<endl;
                    cout<<"The packet you chose does not have enough places for the client"<<endl;
                }
                else if (!packets.at(packetIndex).getAvailability()) {
                    clearScreen();
                    printPacketsVectorWAvailability(packets);
                    cout<<endl;
                    clients.at(index).showFullInfo();
                    cout<<endl;
                    cout<<"The packet you chose is unavailable"<<endl;
                }
                else {

                    isInvalid=false;
                    break;
                }
            }

        }
        else {
            clearScreen();
            printPacketsVectorWAvailability(packets);
            cout<<endl;
            clients.at(index).showFullInfo();
            cout<<endl;
            cout<<"Invalid ID number"<<endl;
        }
    }
    string confirmstr;
    do {
        clearScreen();
        clients.at(index).showFullInfo();
        cout<<endl;
        packets.at(packetIndex).showFullInfo();
        cout<<endl;
        cout << "Do you wish to sell packet "<<packets.at(packetIndex).getId()<<" to "<<clients.at(index).getName()<<"?"<< endl;
        cout << "Y/N: ";
        getline(cin, confirmstr);
    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");
    packets.at(packetIndex).setMaxPersons(packets.at(packetIndex).getMaxPersons()+clients.at(index).getFamilySize());
    vector<Packet> temp=clients.at(index).getPacketList();
    packetsInfoHasChanged=true;
    clientsInfoHasChanged=true;
    temp.push_back(packets.at(size_t(packetIndex)));
    clients.at(index).setPacketList(temp);
    clients.at(index).setTotalPurchased(clients.at(index).getTotalPurchased()+packets.at(size_t(packetIndex)).getPricePerPerson()*clients.at(index).getFamilySize());
    return;
}

void Agency::showClientByVAT() {
	bool invalidInput;
	string confirmstr, aux;
	do {
		invalidInput = true;
		while (true) {

			if (strIsNumber(aux) && aux.length() == 9) {
				clearScreen();
				cout << endl << "What's the VAT number of the client you wish to see? "; cin >> aux;
				VATnumber = stoi(aux);
				for (unsigned it = 0; it < clients.size(); it++) {
					if (VATnumber == clients.at(it).getVATnumber()) {
						clients.at(it).showFullInfo();
						break;
					}
				}
			}
			else {
				clearScreen();
				if (aux == "!q") return;
				cout << "Invalid VAT number format or there's no client with one has such" << endl;
				clearBuffer();
				invalidInput = true;
			}
			cout << "[0] - Return to Packets' Menu" << endl;
			getline(cin, aux);
			if (aux == "0") {
				break;
			}
		}

	} while (invalidInput);
}
void Agency::showPacketByDestiny() {
    string aux, confirmstr, aux2;
    bool invalidInput;
    vector<Packet> packetsToPrint;
    cin.ignore();
    do {
        clearScreen();
        cout << "Whats the turistic destiny you want to search by?";
        getline(cin, aux);
        if (aux == "!q") return;
        clearScreen();
        cout << "Turistic destiny you want to search by: " << aux << endl;
        cout << "Is this correct?" << endl;
        cout << "Y/N: ";
        getline(cin, confirmstr);
    } while (confirmstr != "Y" && confirmstr != "y");
    transform(aux.begin(), aux.end(), aux.begin(), ::toupper);
    clearScreen();
    for (size_t i = 0; i < packets.size(); i++) {
        for (size_t i2 = 0; i < packets[i].getSites().size(); i++) {
            aux2 = packets[i].getSites()[i2];
            transform(aux2.begin(), aux2.end(), aux2.begin(), ::toupper);
            if (aux == aux2) {
                packetsToPrint.push_back(packets[i]);
                break;
            }
        }
    }
    while (true) {

        if (packetsToPrint.size() > 0) {
            clearScreen();
            printPacketsVector(packetsToPrint);
        }
        else {
            clearScreen();
            cout << "There are no packets with that turistic destiny" << endl;
        }
        cout << "[0] - Return to Packets' Menu" << endl;
        getline(cin, aux);
        if(aux=="0"){
            break;
        }
    }

}
void Agency::showPacketByDates() {
    vector<Packet> temp;
    vector<string> test;
    string aux;
    clearBuffer();
    bool invalidDate = false;
    bool digitInput;
    Date start;
    do {
        clearScreen();
        cout << endl << "**************************" << endl;
        cout << "Information Menu" << endl;
        cout << "**************************" << endl << endl;
        if (invalidDate) {
            cout << "The date that was given is invalid" << endl;
        }
        cout << "What's the starting date (YYYY/MM/DD)? ";
        getline(cin, aux);
        if (aux == "!q") return;
        if(aux=="") {
            return;
        }
        test = vectorString(aux, "/");
        digitInput = true;
        if (test.size() != 3) digitInput = false;
        if (digitInput) {
            for (unsigned i = 0; i < test.size(); i++) {
                if (!strIsNumber(test[i])) {
                    digitInput = false;
                    break;
                }
            }
        }
        if (!digitInput) invalidDate = true;
        else {
            start = Date(aux);
            invalidDate = !start.isValid();
        }
    } while (invalidDate);
    Date end;
    invalidDate = false;
    do {
        clearScreen();
        cout << endl << "**************************" << endl;
        cout << "Information Menu" << endl;
        cout << "**************************" << endl << endl;
        if (invalidDate) {
            cout << "The date that was given is invalid" << endl;
        }
        cout << "What's the ending date (YYYY/MM/DD)? ";
        getline(cin, aux);
        if (aux == "!q") return;
        if(aux=="") {
            return;
        }
        test = vectorString(aux, "/");
        digitInput = true;
        if (test.size() != 3) digitInput = false;
        if (digitInput) {
            for (unsigned i = 0; i < test.size(); i++) {
                if (!strIsNumber(test[i])) {
                    digitInput = false;
                    break;
                }
            }
        }
        if (!digitInput) invalidDate = true;
        else if(Date(aux)>=start){
            end = Date(aux);
            invalidDate = (!end.isValid());
        }
        else {
            invalidDate=true;
        }

    } while (invalidDate);

    for (size_t x=0;x<packets.size();x++) {
        if(packets.at(x).getBeginDate()>=start && packets.at(x).getEndDate()<=end){
            temp.push_back(packets.at(x));
        }
    }
    while (true) {

        if (temp.size() > 0) {
            clearScreen();
            printPacketsVector(temp);
        }
        else {
            clearScreen();
            cout << "There are no packets within those dates" << endl;
        }
        cout << "[0] - Return to Packets' Menu" << endl;
        getline(cin, aux);
        if(aux=="0"){
            break;
        }
    }

}
void Agency::showPacketByDatesAndDestiny() {
	vector<Packet> temp;
	vector<string> test;
	string aux;
	clearBuffer();
	bool invalidDate = false;
	bool digitInput;
	Date start;
	do {
		clearScreen();
		cout << endl << "**************************" << endl;
		cout << "Information Menu" << endl;
		cout << "**************************" << endl << endl;
		if (invalidDate) {
			cout << "The date that was given is invalid" << endl;
		}
		cout << "What's the starting date (YYYY/MM/DD)? ";
		getline(cin, aux);
		if (aux == "!q") return;
		if (aux == "") {
			return;
		}
		test = vectorString(aux, "/");
		digitInput = true;
		if (test.size() != 3) digitInput = false;
		if (digitInput) {
			for (unsigned i = 0; i < test.size(); i++) {
				if (!strIsNumber(test[i])) {
					digitInput = false;
					break;
				}
			}
		}
		if (!digitInput) invalidDate = true;
		else {
			start = Date(aux);
			invalidDate = !start.isValid();
		}
	} while (invalidDate);
	Date end;
	invalidDate = false;
	do {
		clearScreen();
		cout << endl << "**************************" << endl;
		cout << "Information Menu" << endl;
		cout << "**************************" << endl << endl;
		if (invalidDate) {
			cout << "The date that was given is invalid" << endl;
		}
		cout << "What's the ending date (YYYY/MM/DD)? ";
		getline(cin, aux);
		if (aux == "!q") return;
		if (aux == "") {
			return;
		}
		test = vectorString(aux, "/");
		digitInput = true;
		if (test.size() != 3) digitInput = false;
		if (digitInput) {
			for (unsigned i = 0; i < test.size(); i++) {
				if (!strIsNumber(test[i])) {
					digitInput = false;
					break;
				}
			}
		}
		if (!digitInput) invalidDate = true;
		else if (Date(aux) >= start) {
			end = Date(aux);
			invalidDate = (!end.isValid());
		}
		else {
			invalidDate = true;
		}

	} while (invalidDate);

	for (size_t x = 0; x < packets.size(); x++) {
		if (packets.at(x).getBeginDate() >= start && packets.at(x).getEndDate() <= end) {
			temp.push_back(packets.at(x));
		}
	}
	while (true) {

		if (temp.size() > 0) {
			string aux1, confirmstr, aux2;
			bool invalidInput;
			vector<Packet> packetsToPrint;
			cin.ignore();
			do {
				clearScreen();
				cout << "Whats the turistic destiny you want to search by?";
				getline(cin, aux1);
				if (aux1 == "!q") return;
				clearScreen();
				cout << "Turistic destiny you want to search by: " << aux1 << endl;
				cout << "Is this correct?" << endl;
				cout << "Y/N: ";
				getline(cin, confirmstr);
			} while (confirmstr != "Y" && confirmstr != "y");
			transform(aux1.begin(), aux1.end(), aux1.begin(), ::toupper);
			clearScreen();
			for (size_t i = 0; i < temp.size(); i++) {
				for (size_t i2 = 0; i < temp[i].getSites().size(); i++) {
					aux2 = temp[i].getSites()[i2];
					transform(aux2.begin(), aux2.end(), aux2.begin(), ::toupper);
					if (aux1 == aux2) {
						packetsToPrint.push_back(temp[i]);
						break;
					}
				}
			}
			while (true) {

				if (packetsToPrint.size() > 0) {
					clearScreen();
					printPacketsVector(packetsToPrint);
				}
				else {
					clearScreen();
					cout << "There are no packets between those dates with that turistic destiny" << endl;
				}
				cout << "[0] - Return to Packets' Menu" << endl;
				getline(cin, aux);
				if (aux == "0") {
					break;
				}
			}
		}
		else {
			clearScreen();
			cout << "There are no packets within those dates" << endl;
		}
		cout << "[0] - Return to Packets' Menu" << endl;
		getline(cin, aux);
		if (aux == "0") {
			break;
		}
	}
}
void Agency::showPacketsOfClient() {
	bool invalidInput;
	string confirmstr, aux;
	do {
        invalidInput = true;
        while (true) {

            if (strIsNumber(aux) && aux.length() == 9) {
                clearScreen();
                cout << endl << "What's the VAT number of the client's packets you wish to see? "; cin >> aux;
                VATnumber = stoi(aux);
                for (unsigned it = 0; it < clients.size(); it++) {
                    if (VATnumber == clients.at(it).getVATnumber()) {
                        printPacketsVector(clients.at(it).getPacketList());
                        break;
                    }
                }
            }
            else {
                clearScreen();
                if (aux == "!q") return;
                cout << "Invalid VAT number format or there's no client with one has such" << endl;
                clearBuffer();
                invalidInput = true;
            }
            cout << "[0] - Return to Packets' Menu" << endl;
            getline(cin, aux);
            if(aux=="0"){
                break;
            }
        }

	} while (invalidInput);
}
void Agency::showPacketsOfAllClients() {
    string aux;
    while (true) {
        if (clients.size()>0) {
            clearScreen();
            for (size_t i = 0; i < clients.size(); i++) {
                cout << "The client " << clients[i].getName() << " with VAT number " << clients[i].getVATnumber() << " has bought the following packets: " << endl << endl;
                printPacketsVector(clients[i].getPacketList());
                cout << endl;
            }
        }
        else {
            clearScreen();
            cout << "There is no information to show" << endl;
        }
        cout << "[0] - Return to Packets' Menu" << endl;
        getline(cin, aux);
        if(aux=="0"){
            break;
        }
    }

}

void Agency::showMostPopular() {
	map <string, int> locations;
	map <int, vector<string> > numeros;
	string auxstr;
	vector<string> aux;
	clearScreen();
	for (size_t i = 0; i < packets.size(); i++) {
		if (packets[i].getSites().size() > 1) {
			for (size_t it = 1; it < packets[i].getSites().size(); it++) {
				auxstr = packets[i].getSites()[it];
				transform(auxstr.begin(), auxstr.end(), auxstr.begin(), ::toupper);
				if (locations.find(auxstr) != locations.end()) {
					locations[auxstr] += packets[i].getMaxPersons();
				}
				else {
					locations[auxstr] = packets[i].getMaxPersons();
				}
			}
		}
		else {
			auxstr = packets[i].getSites()[0];
			transform(auxstr.begin(), auxstr.end(), auxstr.begin(), ::toupper);
			if (locations.find(auxstr) != locations.end()) {
				locations[auxstr] += packets[i].getMaxPersons();
			}
			else {
				locations[auxstr] = packets[i].getMaxPersons();
			}
		}
	}
	for (map <string, int>::iterator it = locations.begin(); it != locations.end(); it++) {
		if (numeros.find(it->second) != numeros.end()) {
			aux = numeros[it->second];
			aux.push_back(it->first);
			numeros[it->second] = aux;
		}
		else {
			aux.clear();
			aux.push_back(it->first);
			numeros[it->second] = aux;
		}
	}
	clearBuffer();
	while (true) {
		clearScreen();
		for (map <int, vector<string> >::reverse_iterator it = numeros.rbegin(); it != numeros.rend(); it++) {
			aux = it->second;
			if (aux.size() > 1) {
				for (size_t i = 0; i < aux.size(); i++) {
					cout << aux[i] << " - " << it->first << " sales" << endl;
				}
			}
			else {
				cout << aux[0] << " - " << it->first << " sales" << endl;
			}
		}
		cout << endl << "[0] - Return to Packets' Menu" << endl;
		getline(cin, auxstr);
		if (auxstr == "0") {
			break;
		}
	}

}

void Agency::showRecommendations() {
	map <string, int> locations;
	map <int, vector<string> > numeros;
	string auxstr;
	vector<string> aux, temp;
	vector<Packet> packetToPrint;
	bool found;
	clearScreen();
	for (size_t i = 0; i < packets.size(); i++) {
		if (packets[i].getSites().size() > 1) {
			for (size_t it = 1; it < packets[i].getSites().size(); it++) {
				auxstr = packets[i].getSites()[it];
				transform(auxstr.begin(), auxstr.end(), auxstr.begin(), ::toupper);
				if (locations.find(auxstr) != locations.end()) {
					locations[auxstr] += packets[i].getMaxPersons();
				}
				else {
					locations[auxstr] = packets[i].getMaxPersons();
				}
			}
		}
		else {
			auxstr = packets[i].getSites()[0];
			transform(auxstr.begin(), auxstr.end(), auxstr.begin(), ::toupper);
			if (locations.find(auxstr) != locations.end()) {
				locations[auxstr] += packets[i].getMaxPersons();
			}
			else {
				locations[auxstr] = packets[i].getMaxPersons();
			}
		}
	}
	for (map <string, int>::iterator it = locations.begin(); it != locations.end(); it++) {
		if (numeros.find(it->second) != numeros.end()) {
			aux = numeros[it->second];
			aux.push_back(it->first);
			numeros[it->second] = aux;
		}
		else {
			aux.clear();
			aux.push_back(it->first);
			numeros[it->second] = aux;
		}
	}
	while (true) {
		clearScreen();
		for (size_t i = 0; i < clients.size(); i++) {
			aux.clear();
			packetToPrint.clear();
			found = false;
			for (size_t i2 = 0; i2 < clients[i].getPacketList().size(); i2++) {
				for (size_t i3 = 0; i3 < clients[i].getPacketList()[i2].getSites().size(); i3++) {
					auxstr = clients[i].getPacketList()[i2].getSites()[i3];
					transform(auxstr.begin(), auxstr.end(), auxstr.begin(), ::toupper);
					if (find(aux.begin(), aux.end(), auxstr) == aux.end()) {
						aux.push_back(auxstr);
					}
				}
			}
            std::vector<string>::iterator it2;
			for (map <int, vector<string> >::reverse_iterator it = numeros.rbegin(); it != numeros.rend(); it++) {
				temp = it->second;
				if (temp.size() > 1) {
                    for (size_t i2 = 0; i2 < temp.size(); i2++) {
						if (find(aux.begin(), aux.end(), temp[i2]) == aux.end()) {

						}
					}
				}
				else {
					if (find(aux.begin(), aux.end(), temp[0]) == aux.end()) {
                        found = true;
                        for (size_t i2 = 0; i2 < packets.size(); i2++) {
                            it2 = find(packets.at(i2).getSites().begin(),packets.at(i2).getSites().end(),temp.at(0));
                            if ( it2 != packets[i2].getSites().end() && packets[i2].getAvailability()) {
								packetToPrint.push_back(packets[i2]);
								found = true;
								break;
							}
						}
                        found=false;
                        break;
					}
                }
			}
			if (found) {
				cout << "According to his past purchases on this agency, the client " << clients[i].getName() << " with VAT number " << clients[i].getVATnumber() << " should buy the following packet: " << endl << endl;
				printPacketsVector(packetToPrint);
                cout << endl;
			}
			else {
				cout << "According to his past purchases on this agency, the client " << clients[i].getName() << " with VAT number " << clients[i].getVATnumber() << " has visited all locations the agency's packets have to offer." << endl << endl;
			}

		}
		cout << endl << "[0] - Return to Packets' Menu" << endl;
		getline(cin, auxstr);
		if (auxstr == "0") {
			break;
		}
	}

}

