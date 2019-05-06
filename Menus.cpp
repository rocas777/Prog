#include "Menus.h"

//menu functions________________________________________________

unsigned mainMenu(Agency agency){
    greatings(agency);
    cout<<endl<<"**************************"<<endl;
    cout<<"Main Menu"<<endl;
    cout<<"**************************"<<endl<<endl;
    cout<<"[1] - Clients' management"<<endl;
    cout<<"[2] - Packs' management"<<endl;
    cout<<"[3] - Statistics"<<endl;
    cout<<"[0] - Exit application and save."<<endl;
    cout<<"Please choose an option:"<<endl;

	return 0;
}

unsigned menu_1(Agency agency){
    cout<<endl<<"**************************"<<endl;
    cout<<"Menu 1"<<endl;
    cout<<"**************************"<<endl<<endl;
    cout<<"[1] - View Clients' Information"<<endl;
    cout<<"[2] - Create Client"<<endl;
    cout<<"[3] - Edit CLient"<<endl;
    cout<<"[4] - Delete Client"<<endl;
    cout<<"[0] - Return to Main Menu"<<endl;
    cout<<"Please choose an option:"<<endl;

    return 0;
}

unsigned menu_1_1(Agency agency) {
	cout << "[0] Return to Menu Clients' Menu" << endl;

	return 0;
}

unsigned menu_2(Agency agency) {
	cout << endl << "**************************" << endl;
	cout << "Menu 2" << endl;
	cout << "**************************" << endl << endl;
	cout << "[1] - View Packets' Information" << endl;
	cout << "[2] - Create Packet" << endl;
	cout << "[3] - Edit Packet" << endl;
	cout << "[4] - Make Packet Unavailable" << endl;
	cout << "[0] - Return to Main Menu" << endl;
	cout << "Please choose an option:" << endl;

	return 0;
}

unsigned menu_3(Agency agency) {
	cout << endl << "**************************" << endl;
	cout << "Menu 3" << endl;
	cout << "**************************" << endl << endl;
	cout << "[1] - View Most Visites Places by Descending Order" << endl;
	cout << "[2] - Make Recommendations For All Clients" << endl;
	cout << "[0] - Return to Main Menu" << endl;
	cout << "Please choose an option:" << endl;

	return 0;
}

//auxiliar functions____________________________________________

unsigned selec(unsigned menor, unsigned maior, void data(Agency agency),unsigned menu(Agency agency),Agency agency){
    unsigned selection;
    clearScreen();
    data(agency);
    menu(agency);
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
        data(agency);
        menu(agency);
        cout<<"\nOption not allowed.\nPlease Try again:"<<endl;
    }

}


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
    cout << agency.getName()<<endl;
    cout << agency.getURL()<<endl;
    cout << agency.getVATnumber()<<endl;
    cout << agency.getAddress().getFullAdress()<<endl;
    }
