#include <iostream>
#include <string>
#include <vector>

#include "Agency.h"
#include "Menus.h"
// #include "utils.h"
void data(){
    return;
}

int main(){
    unsigned option;
    Agency agency;// create the agency
    agency.setClientsFromFile();// populates agency's client vector
    while ((option=selec(0,3,data,mainMenu,agency))) {
        switch (option) {
        case(1):{
            while ((option=selec(0,4,data,menu_1,agency))){
                switch (option) {
                case (1):{

                }
                }

            }
        }
        }
    }
    return 0;
}
