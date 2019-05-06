#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Agency.h"
#include "Menus.h"
// #include "utils.h"
void data(Agency agency){
    cout<<agency.getClients().at(0).getName()<<endl;
    cout<<agency.getClients().at(0).getAddress().getFullAdress()<<endl;
    cout<<agency.getClients().at(0).getVATnumber()<<endl;
    cout<<agency.getClients().at(0).getFamilySize()<<endl;
    //cout<<agency.getClients().at(0).getPacketList().at(0).getId();
    cout<<agency.getClients().at(0).getTotalPurchased()<<endl<<endl;
    return;
}
void dataDefault(Agency agency){
    return;
}

void printClientsVector(Agency agency){
    cout<<"\nClientes -------------------------------"<<endl;
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
    printf("|%-30s|%-9s|%-8s|%-65s|%-30s|\n", "Nome", "Nif", "Agregado", "Morada", "Pacotes");
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
    cout<<setfill('-')<<setw(150)<<""<<endl;
    for(unsigned long x=0; x != agency.getClients().size(); x++){

        printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
        printf("|%-30s|%9u|%8u|\n", agency.getClients()[x].getName().c_str(), agency.getClients()[x].getVATnumber(), agency.getClients()[x].getFamilySize());//, clientes[x].morada.c_str(), clientes[x].pacotes.c_str());
        printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
        cout<<setfill('-')<<setw(150)<<""<<endl;
    }
}
void printPacketsVector(Agency agency){
    cout<<"\nClientes -------------------------------"<<endl;
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
    printf("|%-30s|%-9s|%-8s|%-65s|%-30s|\n", "Nome", "Nif", "Agregado", "Morada", "Pacotes");
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
    cout<<setfill('-')<<setw(150)<<""<<endl;
    for(unsigned long x=0; x != agency.getPackets().size(); x++){

        printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
        printf("|%-30u|%9s|%8s|%9s|%8u|%8u|%8f|\n", agency.getPackets()[x].getId(), agency.getPackets()[x].getSites().at(0).c_str(), agency.getPackets()[x].getBeginDate().getDate().c_str(),agency.getPackets()[x].getEndDate().getDate().c_str(),agency.getPackets()[x].getTotalPersons(),agency.getPackets()[x].getMaxPersons(),agency.getPackets()[x].getPricePerPerson());//, clientes[x].morada.c_str(), clientes[x].pacotes.c_str());
        printf("|%-30s|%9s|%8s|%-65s|%-30s|\n","","","","","");
        cout<<setfill('-')<<setw(150)<<""<<endl;
    }
}

int main(){
    unsigned option;
    Agency agency;// create the agency
    agency.setPacketsFromFile();
    agency.setClientsFromFile();
    while ((option=selec(0,3,dataDefault,mainMenu,agency))) {
        switch (option) {
        case(1):{
            while ((option=selec(0,4,dataDefault,menu_1,agency))){
                switch (option) {
                case (1):{
                    (option=selec(0,0,printClientsVector,menu_1_1,agency));
                }
                }

            }
            break;
        }
        case(2):{
            while ((option=selec(0,4,dataDefault,menu_2,agency))) {
                switch (option) {
                case (1):{
                    (option=selec(0,0,printPacketsVector,menu_1_1,agency));
                }
            }
            }
            break;
        }
        case(3):{
            while ((option=selec(0,4,dataDefault,menu_3,agency))) {

            }
            break;
        }
        }
    }
    exit(0);
}
