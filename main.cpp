#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Agency.h"
#include "Menus.h"
#include "funcs.h"
// #include "utils.h"

int main(){
    unsigned option;
    Agency agency;// create the agency
    agency.setPacketsFromFile();
    agency.setClientsFromFile();
    cout << "\e[8;20;150t";
    clearScreen();
    while ((option=selec(0,3,dataDefault,mainMenu,agency))) {
        switch (option) {
        case(1):{
            while ((option=selec(0,5,dataDefault,menu_1,agency))){
                switch (option) {
                case (1):{
                    (option=selec(0,0,printClientsVector,menu_1_1,agency));
                    break;
                }
                case (2):{
                    agency.createClient();
                    break;
                }
                case(3):{
                    agency.changeClient();
                    break;
                }
                case (4):{
                    (option=selec(0,0,printClientsVector,menu_1_1,agency));
                    break;
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
					break;
                }
				case (2): {
					agency.createPacket();
					break;
				}
                case (3): {
                    agency.changePackets();
                    break;
                }
            }
            }
            break;
        }
        case(3):{
            while ((option=selec(0,2,dataDefault,menu_3,agency))) {

            }
            break;
        }
        }
    }
    agency.saveClientsToFile();
    agency.savePacketsToFile();
    exit(0);
}
