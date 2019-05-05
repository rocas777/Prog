#include <iostream>
#include <string>
#include <vector>

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

int main(){
    unsigned option;
    Agency agency;// create the agency
    agency.setClientsFromFile();
    while ((option=selec(0,3,dataDefault,mainMenu,agency))) {
        switch (option) {
        case(1):{
            while ((option=selec(0,4,dataDefault,menu_1,agency))){
                switch (option) {
                case (1):{
                    (option=selec(0,0,data,menu_1_1,agency));
                }
                }

            }
        }
        }
    }
    exit(0);
}
