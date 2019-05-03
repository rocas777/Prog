#ifndef FUNCOES_H
#define FUNCOES_H
#include "Agency.h"

#ifdef _WIN32
void clearScreen(){
     system("cls");
     system("cls");
}
#endif

#ifdef linux
void clearScreen(){
    system("clear");
    system("clear");
}
#endif

void greatings(Agency agency){
    clearScreen();
    cout << agency.getName()<<endl;
    cout << agency.getURL()<<endl;
    cout << agency.getVATnumber()<<endl;
    cout << agency.getAddress()<<endl;
}
#endif // FUNCOES_H
