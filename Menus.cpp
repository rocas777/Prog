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
	cout<<"[4] - Make a Purchase for a client"<<endl;
    cout<<"[5] - Delete Client"<<endl;
    cout<<"[0] - Return to Main Menu"<<endl;
    cout<<"Please choose an option:"<<endl;

    return 0;
}

unsigned menu_1_1(Agency agency) {
	cout << "[0] - Return to Clients' Menu" << endl;
	cout << "Insert the VAT Number of a specific client or input 'all' to see every client." << endl;

	return 0;
}
unsigned menu_1_2(Agency agency) {
	cout << "[0] - During Criation to Return to Menu Clients'" << endl;

	return 0;
}
unsigned menu_1_3(Agency agency) {

	cout << "[0] - Return to Menu Clients' Menu" << endl;

	return 0;
}
unsigned menu_1_4(Agency agency) {
	cout << "[0] - Return to Menu Clients' Menu" << endl;
	cout << "Insert the VAT Number of the client that will be making a purchase" << endl;

	return 0;
}
unsigned menu_1_5(Agency agency) {
	cout << "[0] - Return to Menu Clients' Menu" << endl;
	cout << "Insert a the VAT Number of the client that will be removed" << endl;

	return 0;
}

unsigned menu_2(Agency agency) {
	cout << endl << "**************************" << endl;
	cout << "Menu 2" << endl;
	cout << "**************************" << endl << endl;
	cout << "[1] - View Packets' Information" << endl;
	cout << "[2] - Create Packet" << endl;
	cout << "[3] - Edit Packet" << endl;
    cout << "[4] - Switch Packet Availability" << endl;
	cout << "[0] - Return to Main Menu" << endl;
	cout << "Please choose an option:" << endl;

	return 0;
}

unsigned menu_2_1(Agency agency) {
	cout << "[1] - View All Packets" << endl;
	cout << "[2] - View All Refering to a Place" << endl;
	cout << "[3] - View All Between 2 Dates" << endl;
	cout << "[4] - View All Between 2 Dates and refering to place" << endl;
	cout << "[0] - Return to Packets' Menu" << endl;

	return 0;
}

unsigned menu_2_2(Agency agency) {
	cout << "[0] - During Criation to Return to Menu Packets" << endl;

	return 0;
}

unsigned menu_2_3(Agency agency) {

	cout << "[0] - Return to Menu Clients' Menu" << endl;

	return 0;
}

unsigned menu_2_4(Agency agency) {
	cout << "[0] - Return to Menu Clients' Menu" << endl;
	cout << "Insert the VAT Number of the client that will be making a purchase" << endl;

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
