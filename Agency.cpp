#include "Agency.h"
#include <fstream>
#include <bits/stdc++.h>

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
                VATnumber=stoi(tempVat);
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

  //  IMPLEMENTATION REQUIRED 
}


void Agency::setVATnumber(unsigned VATnumber){

  //  IMPLEMENTATION REQUIRED 
}

void Agency::setAddress(Address address){

  //  IMPLEMENTATION REQUIRED 
}
void Agency::setURL(string url){

  //  IMPLEMENTATION REQUIRED 

}
void Agency::setClients(vector<Client> & clients){

  //  IMPLEMENTATION REQUIRED 

  }
void Agency::setPackets(vector<Packet> & packets){

  //  IMPLEMENTATION REQUIRED

}

void Agency::setClientsFromFile(){
    ifstream clientes_file;
    clientes_file.open(this->clientsFile);
    string STRING;
    vector<string> tempClientVector;
    while(getline(clientes_file,STRING))
    {
        if(STRING!="::::::::::"){
            tempClientVector.push_back(STRING);
        }
        else {
            this->clients.push_back(Client(tempClientVector[0],stoi(tempClientVector[1]),(stoi(tempClientVector[2])),Address(tempClientVector[3])));//,vectorString(tempClientVector[4],";"),tempClientVector[5]));
            //tempClientVector.push_back(STRING);
            tempClientVector.clear();
        }
    }
//***************************************************************************************************problema do vector<packets>
    this->clients.push_back(Client(tempClientVector[0],stoi(tempClientVector[1]),(stoi(tempClientVector[2])),Address(tempClientVector[3])));//,vectorString(tempClientVector[4],";"),tempClientVector[5]));
    //tempClientVector.push_back(STRING);
    tempClientVector.clear();
}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
//ostream& operator<<(ostream& out, const Agency & agency){

//  // A IMPLEMENTATION REQUIRED
//

