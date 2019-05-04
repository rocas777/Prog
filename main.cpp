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

    Agency agency;   // create the agency
    clearScreen();
    while (true) {
        switch (selec(1,3,data,mainMenu,agency)) {
        case(1):{
            cout<<1<<endl;
            string w;
            cin>>w;
        }
        }
    }
    return 0;
}
