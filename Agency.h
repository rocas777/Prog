#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"
using namespace std;

class Agency{
 private:
	  string name; // name of the  agency
	  unsigned int VATnumber; // VAT number of the agency
	  Address address; // address of the agency
	  string URL; // URL of the agency Web site
	  vector<Client> clients; // vector to store the existing clients
	  vector<Packet> packets; // vector to store the existing packets
      string clientsFile;
      string packsFile;
      double totalPacketsSold;
      double totalMoneyMade;
	  bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	  bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
	  unsigned int maxClientsId; // maximum value among all clients identifiers
	  unsigned int maxPacketsId; // maximum value among all packets identifiers

 public:
	  Agency(string fileName);
      Agency();

// methods GET
	  string getName() const;
	  unsigned getVATnumber() const;
	  unsigned getPacketsSold() const;
	  unsigned getTotalMoneyMade() const;
	  Address getAddress() const;
	  string getURL() const;
	  vector<Client> getClients() const;
      vector<Packet> getPackets() const;
      bool getClientsInfoHasChanged();
      bool getPacketsInfoHasChanged();

  
// methods SET
	  void setName(string name);
	  void setVATnumber(unsigned VATnumber);
	  void setAddress(Address address);
	  void setURL(string url);
      void setPacketsSoldAndMonneyMade();
	  void setClients(vector<Client> & clients);
      void setClientsFromFile();
      void setPacketsFromFile();
	  void setPackets(vector<Packet> & packets);

// other methods */
  
	 //friend ostream& operator<<(ostream& out, const Agency & agency);
      //funcs to write the coisos
	  void saveClientsToFile();
      void savePacketsToFile();
	  //funcs to create the coisos
      void createClient();
	  void createPacket();
	  //funcs to change the coisos
	  void changeClient();
      void changePackets();
	  //funcs to remove the coisos
	  void removeClient();
	  void removePacket();
	  //funcs to sell the coisos
      void sellPacketToClient();
	  //funcs to see the coisos
	  void showClientByVAT();
	  void showPacketByDestiny();
	  void showPacketByDates();
	  void showPacketByDatesAndDestiny();
	  void showPacketsOfClient();
	  void showPacketsOfAllClients();
	  void showMostPopular();
	  void showRecommendations();

};
