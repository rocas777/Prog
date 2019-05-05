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

int main(){
    unsigned option;
    Agency agency;// create the agency
    //agency.set
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
        }
        }
    }
    exit(0);
}
