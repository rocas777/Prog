#include "Menus.h"
#include "funcoes.h"

#ifdef _WIN32
void clearScreen(){
     system("cls");system("cls");
}
#endif

#ifdef linux
void clearScreen(){
    system("clear");system("clear");
}
#endif
void greatings(Agency agency){
    clearScreen();
    cout << agency.getName()<<endl;
    cout << agency.getURL()<<endl;
    cout << agency.getVATnumber()<<endl;
    cout << agency.getAddress().getFullAdress()<<endl;
    }

unsigned mainMenu(Agency agency){

    greatings(agency);

	return 0;
}

unsigned selec(unsigned menor, unsigned maior, void data(),unsigned menu(Agency agency),Agency agency){
    unsigned selection;
    clearScreen();
    mainMenu(agency);
    while(true){
        cin >> selection;
        if(cin.fail() ){
            cin.clear(); //clear stream
            cin.ignore(); //ignore left over data
        }
        if(selection>=menor && selection<=maior){
            return selection;
        }
        clearScreen();

        mainMenu(agency);
        cout<<"\nOption not allowed.\nPlease Try again:"<<endl;
    }

}

