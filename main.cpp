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
    while (true) {
        option=selec(0,3,dataDefault,mainMenu,agency);
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
                    agency.sellPacketToClient();
                    break;
                }
                case (5):{
                    agency.removeClient();
                    break;
                }
                }

            }
            break;
        }
        case(2):{
            while ((option=selec(0,5,dataDefault,menu_2,agency))) {
                switch (option) {
                case (1):{
                    unsigned option1;
                    while ((option1=selec(0,5,dataDefault,menu_2_1,agency))) {
                        switch (option1) {
                        case (1):{
                            (option1=selec(0,0,printPacketsVector,menu_2_1_1,agency));
                            break;
                        }
                        case (2): {
                            agency.showPacketByDestiny();
                            break;
                        }
                        case (3): {
                            agency.showPacketByDates();
                            break;
                        }
                        case (4):{
                           agency.showPacketByDatesAndDestiny();
                            break;
                        }
                        case (5):{
                            unsigned option2;
                            while ((option2=selec(0,2,dataDefault,menu_2_1_5,agency))) {
                                switch (option2) {
                                case(1):{
                                    agency.showPacketsOfClient();
                                    break;
                                }
                                case(2):{
                                    agency.showPacketsOfAllClients();
                                    break;
                                }
                                }
                            }
                            break;
                        }
                    }
                    }
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
                case (4):{
                    //agency.removePacket();
					agency.showRecommendations();
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
        case(0):{
            unsigned option1;
            bool confirmExit=true;
            while (confirmExit) {
                option1=selec(1,3,dataDefault,menu_exit,agency);
                switch (option1) {
                case (1):{
                    agency.saveClientsToFile();
                    agency.savePacketsToFile();
                    exit(0);
                }
                case (2):{
                    confirmExit=false;
                    option=1;
                    break;
                }
                case(3):{
                    exit(0);
                }
                }
            }
            break;
        }
        }
    }
}
