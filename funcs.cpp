#include "funcs.h"

//whatever the fuck this is
void data(Agency agency) {
	cout << agency.getClients().at(0).getName() << endl;
	cout << agency.getClients().at(0).getAddress().getFullAdress() << endl;
	cout << agency.getClients().at(0).getVATnumber() << endl;
	cout << agency.getClients().at(0).getFamilySize() << endl;
	//cout<<agency.getClients().at(0).getPacketList().at(0).getId();
	cout << agency.getClients().at(0).getTotalPurchased() << endl << endl;
	return;
}
void dataDefault(Agency agency) {
	return;
}


//functions to print out coisos
void printClientsVector(Agency agency) {
    cout  <<"Clientes" << setfill('-') << setw(127) <<"" <<  endl;
    printf("|%-30s|%9s|%4s|%-65s|%-15s|%5s|\n", "", "", "", "", "","");
    printf("|%-30s|%-9s|%-4s|%-65s|%-15s|%-5s|\n", "Name", "Vat", "Fam.", "Address", "Packets","Total");
    printf("|%-30s|%9s|%4s|%-65s|%-15s|%5s|\n", "", "", "Size", "","", "Spent");
    cout << setfill('-') << setw(135) << "" << endl;
    for (unsigned long x = 0; x != agency.getClients().size(); x++) {
        printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", "","");
        if(agency.getClients().at(x).getAllIDs().size()>15){
            size_t i;
            string ids=agency.getClients().at(x).getAllIDs();
            printf("|%-30s|%9u|%4u|%-65s|%-15s|%-5u|\n", agency.getClients().at(x).getName().c_str(), agency.getClients().at(x).getVATnumber(), agency.getClients().at(x).getFamilySize(),agency.getClients().at(x).getAddress().getFullAdress().c_str(), ids.substr(0,15).c_str(),agency.getClients().at(x).getTotalPurchased());
            for (i=1;i<ids.size()/15;i++) {
                printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", ids.substr(15*i,15).c_str(),"");
            }
            printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", ids.substr(15*i,agency.getClients().at(x).getAllIDs().npos).c_str(),"");

        }
        else {
            string s=agency.getClients().at(x).getName();
            printf("|%-30s|%9u|%4u|%-65s|%-15s|%-5u|\n", s.c_str(), agency.getClients().at(x).getVATnumber(), agency.getClients().at(x).getFamilySize(),agency.getClients().at(x).getAddress().getFullAdress().c_str(), agency.getClients().at(x).getAllIDs().c_str(),agency.getClients().at(x).getTotalPurchased());
        }
        printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", "","");
        cout << setfill('-') << setw(135) << "" << endl;
    }
}
void printClientsVector(vector<Client> client) {
    cout  <<"Clientes" << setfill('-') << setw(127) <<"" <<  endl;
    printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", "","");
    printf("|%-30s|%-9s|%-4s|%-65s|%-15s|%-5s|\n", "Name", "Vat", "Fam.", "Address", "Packets","Total");
    printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "Size", "", "","Spent");
    cout << setfill('-') << setw(135) << "" << endl;
    for (unsigned long x = 0; x != client.size(); x++) {

        printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", "","");
        if(client.at(x).getAllIDs().size()>30){
            size_t i;
            printf("|%-30s|%9u|%4u|%-65s|%-15s|%-5u|\n", client.at(x).getName().c_str(), client.at(x).getVATnumber(), client.at(x).getFamilySize(),client.at(x).getAddress().getFullAdress().c_str(), client.at(x).getAllIDs().substr(0,15).c_str(),client.at(x).getTotalPurchased());
            for (i=1;i<client.at(x).getAllIDs().size()/15;i++) {
                printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", client.at(x).getAllIDs().substr(15*i,15).c_str(),"");
            }
            printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", client.at(x).getAllIDs().substr(15*i,client.at(x).getAllIDs().npos).c_str(),"");

        }
        else {
            printf("|%-30s|%9u|%4u|%-65s|%-15s|%-5u|\n", client.at(x).getName().c_str(), client.at(x).getVATnumber(), client.at(x).getFamilySize(),client.at(x).getAddress().getFullAdress().c_str(), client.at(x).getAllIDs().c_str(),client.at(x).getTotalPurchased());
        }
        printf("|%-30s|%9s|%4s|%-65s|%-15s|%-5s|\n", "", "", "", "", "","");
        cout << setfill('-') << setw(135) << "" << endl;
    }
}
void printPacketsVector(Agency agency) {
    cout << "\nPackets -------------------------------" << endl;
    printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "","", "", "", "", "","","","");
    printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "Avail","ID", "Destination","Sites", "B Date", "E Date", "Total Places","Rem Places","Price");
    printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "","", "", "", "", "","","","");
	cout << setfill('-') << setw(150) << "" << endl;
    string s;
    for (unsigned long x = 0; x != agency.getPackets().size(); x++) {
        Packet temp=agency.getPackets().at(x);
        printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "", "", "", "","","","","");
        if(agency.getPackets().at(x).getAvailability()){
            s="Y";
        }
        else{
            s="N";
        }
        printf("|%-5s|%-3u|%-20s|%-20s|%-10s|%-10s|%-12u|%-10u|%-5f|\n", s.c_str(),temp.getId(), temp.getSites().at(0).c_str(),"", temp.getBeginDate().getDate().c_str(), temp.getEndDate().getDate().c_str(), temp.getTotalPersons(),temp.getMaxPersons(),temp.getPricePerPerson());
        for (size_t i=1;i<temp.getSites().size();i++) {
            printf("|%-5s|%-3s|%20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "","",temp.getSites().at(i).c_str(), "","","","","");

        }
        printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "", "", "", "","","","","");
        cout << setfill('-') << setw(150) << "" << endl;
	}
}
void printPacketsVector(vector<Packet> packet) {
        cout << "\nPackets -------------------------------" << endl;
        printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "","", "", "", "", "","","","");
        printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "Avail","ID", "Destination","Sites", "B Date", "E Date", "Total Places","Rem Places","Price");
        printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "","", "", "", "", "","","","");
        cout << setfill('-') << setw(150) << "" << endl;
        string s;
        for (unsigned long x = 0; x != packet.size(); x++) {
            Packet temp=packet.at(x);
            printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "", "", "", "","","","","");
            if(packet.at(x).getAvailability()){
                s="Y";
            }
            else{
                s="N";
            }
            printf("|%-5s|%-3u|%-20s|%-20s|%-10s|%-10s|%-12u|%-10u|%-5f|\n", s.c_str(),temp.getId(), temp.getSites().at(0).c_str(),"", temp.getBeginDate().getDate().c_str(), temp.getEndDate().getDate().c_str(), temp.getTotalPersons(),temp.getMaxPersons(),temp.getPricePerPerson());
            for (size_t i=1;i<temp.getSites().size();i++) {
                printf("|%-5s|%-3s|%20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "","",temp.getSites().at(i).c_str(), "","","","","");

            }
            printf("|%-5s|%-3s|%-20s|%-20s|%-10s|%-10s|%-12s|%-10s|%-5s|\n", "", "", "", "", "","","","","");
            cout << setfill('-') << setw(150) << "" << endl;
        }
}

void printPacketsVectorWAvailability(vector<Packet> packet) {
    cout << "\nPackets -------------------------------" << endl;
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
    printf("|%-30s|%-9s|%-8s|%-65s|%-30s|\n", "Nome", "Nif", "Agregado", "Morada", "Pacotes");
    printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
    cout << setfill('-') << setw(150) << "" << endl;
    for (unsigned long x = 0; x != packet.size(); x++) {
        if(packet.at(x).getAvailability()){
            printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
            printf("|%-30u|%9s|%8s|%9s|%8u|%8u|%8f|\n", packet[x].getId(), packet[x].getSites().at(0).c_str(), packet[x].getBeginDate().getDate().c_str(), packet[x].getEndDate().getDate().c_str(), packet[x].getTotalPersons(), packet[x].getMaxPersons(), packet[x].getPricePerPerson());//, clientes[x].morada.c_str(), clientes[x].pacotes.c_str());
            printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
            cout << setfill('-') << setw(150) << "" << endl;
        }
    }
}

//o miguel tem cancro mental
unsigned selec(unsigned menor, unsigned maior, void data(Agency agency), void menu(Agency agency), Agency agency) {
	unsigned selection;
	clearScreen();
	data(agency);
	menu(agency);
	while (true) {
		cin >> selection;
		if (cin.fail()) {
			cin.clear(); //clear stream
			cin.ignore(); //ignore left over data
		}
        else if (selection >= menor && selection <= maior) {
			return selection;
		}
		clearScreen();
		data(agency);
		menu(agency);
		cout << "\nOption not allowed.\nPlease Try again:" << endl;
	}

}
unsigned selec(unsigned menor, unsigned maior){
    unsigned selection;
    while (true) {
        cin >> selection;
        if (cin.fail()) {
            cin.clear(); //clear stream
            cin.ignore(); //ignore left over data
        }
        else if (selection >= menor && selection <= maior) {
            return selection;
        }
        cout << "\nOption not allowed.\nPlease Try again:" << endl;
    }

}

#ifdef _WIN32
void clearScreen() {
	system("cls"); system("cls");
}
#endif

#ifdef linux
void clearScreen() {
	system("clear"); system("clear");
}
#endif
void greatings(Agency agency) {
	cout << agency.getName() << endl;
	cout << agency.getURL() << endl;
	cout << agency.getVATnumber() << endl;
	cout << agency.getAddress().getFullAdress() << endl;
}

vector<string> vectorString(string morada, string separador) {
	vector<string> ret;
	size_t startPos = 0, endPos = 0;
	while (endPos < morada.length()) {
		endPos = morada.find(separador, startPos);
		if (endPos == morada.npos) {
			ret.push_back(morada.substr(startPos));
			break;
		}
		else {
			ret.push_back(morada.substr(startPos, endPos - startPos));
		}
		startPos = endPos + separador.length();
	}
	if (ret.size() >= 3) {
		if (ret[2].size() == 0) {
			ret[2] = "-";
		}
	}
	return ret;
}

Packet BinarySearch(vector<Packet> packet, int id)
{
	int inf = 0;
	int sup = packet.size() - 1;
	int meio;
	while (inf <= sup)
	{

		meio = (inf + sup) / 2;
		if (id == packet[meio].getId())
            return packet.at(meio);
		if (id < packet[meio].getId())
			sup = meio - 1;
		else
			inf = meio + 1;
	}
    return Packet(id,vectorString("Unknown",";"),Date(),Date(),0,0,0);  // não encontrado
}

vector<Packet> StringIDtoPackVec(vector<Packet> packets, vector<string> stringvec) {
	vector<Packet> out;
	for (unsigned i = 0; i < stringvec.size(); i++) {
		out.push_back(BinarySearch(packets, stoi(stringvec.at(i))));
	}
	return out;
}

string strVecToStr(vector<string> strvec) {
	string out = "";
	for (unsigned i = 0; i < strvec.size(); i++) {
		if (i == strvec.size() - 1) {
			out += strvec[i];
		}
		else {
			out += strvec[i];
			out += " ";
		}
	}
	return out;
}

void clearBuffer(void) {
	cin.clear();
	cin.ignore(1000, '\n');
}

bool strIsNumber(string str) {
    if(str.size()==0){
        return false;
    }
	for (unsigned i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool checkZip(string zip){
    vector<string> input=vectorString(zip,"-");
    if(input.size()<2){
        return false;
    }
    else {
        if(input.at(0).size()==4 && input.at(1).size()==3){
            return true;
        }
    }
    return false;
}

int BinarySearchID(vector<Packet> packet, int id)
{
    int inf = 0;
    int sup = packet.size() - 1;
    int meio;
    while (inf <= sup)
    {

        meio = (inf + sup) / 2;
        if (id == packet[meio].getId())
            return meio;
        if (id < packet[meio].getId())
            sup = meio - 1;
        else
            inf = meio + 1;
    }
    return -1;  // não encontrado
}
