#include "Agency.h"
#include <fstream>


Agency::Agency(){
        ifstream agency_file;
        bool check=true;
        string tempAddress;
        string tempVat;
        cout<<"Introduza o nome do ficheiro da agencia (e.g agencia.txt):"<<endl<<endl;
        while(check){
            string fileName;
            cin>>fileName;
            agency_file.open(fileName);
            if (agency_file.is_open()) {
                check=false;
                getline( agency_file, name );
                getline(agency_file,tempVat);
                VATnumber=stoi(tempVat);
                getline( agency_file,  URL);
                getline( agency_file, tempAddress);
                cout<<tempAddress<<endl;
                address=Address(tempAddress);
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

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
//ostream& operator<<(ostream& out, const Agency & agency){

//  // A IMPLEMENTATION REQUIRED
//}
