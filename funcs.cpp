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


//functions to print out stuff
void printClientsVector(Agency agency) {
	cout << "\nClientes -------------------------------" << endl;
	printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
	printf("|%-30s|%-9s|%-8s|%-65s|%-30s|\n", "Nome", "Nif", "Agregado", "Morada", "Pacotes");
	printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
	cout << setfill('-') << setw(150) << "" << endl;
	for (unsigned long x = 0; x != agency.getClients().size(); x++) {

		printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
        printf("|%-30s|%9u|%8u|%8s|\n", agency.getClients()[x].getName().c_str(), agency.getClients()[x].getVATnumber(), agency.getClients()[x].getFamilySize(), agency.getClients().at(x).getAllIDs().c_str());//, clientes[x].morada.c_str(), clientes[x].pacotes.c_str());
		printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
		cout << setfill('-') << setw(150) << "" << endl;
	}
}
void printPacketsVector(Agency agency) {
	cout << "\nClientes -------------------------------" << endl;
	printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
	printf("|%-30s|%-9s|%-8s|%-65s|%-30s|\n", "Nome", "Nif", "Agregado", "Morada", "Pacotes");
	printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
	cout << setfill('-') << setw(150) << "" << endl;
	for (unsigned long x = 0; x != agency.getPackets().size(); x++) {

		printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
		printf("|%-30u|%9s|%8s|%9s|%8u|%8u|%8f|\n", agency.getPackets()[x].getId(), agency.getPackets()[x].getSites().at(0).c_str(), agency.getPackets()[x].getBeginDate().getDate().c_str(), agency.getPackets()[x].getEndDate().getDate().c_str(), agency.getPackets()[x].getTotalPersons(), agency.getPackets()[x].getMaxPersons(), agency.getPackets()[x].getPricePerPerson());//, clientes[x].morada.c_str(), clientes[x].pacotes.c_str());
		printf("|%-30s|%9s|%8s|%-65s|%-30s|\n", "", "", "", "", "");
		cout << setfill('-') << setw(150) << "" << endl;
	}
}

//o miguel tem cancro mental
unsigned selec(unsigned menor, unsigned maior, void data(Agency agency), unsigned menu(Agency agency), Agency agency) {
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

void clearBuffer(void) {
	cin.clear();
	cin.ignore(1000, '\n');
}

bool strIsNumber(string str) {
	for (unsigned i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}