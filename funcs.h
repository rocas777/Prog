#pragma once
#include "Agency.h"
#include <iomanip>
using namespace std;

void data(Agency agency);
void dataDefault(Agency agency);
void printClientsVector(Agency agency);
void printPacketsVector(Agency agency);
unsigned selec(unsigned menor, unsigned maior, void data(Agency agency), unsigned menu(Agency agency), Agency agency);
void clearScreen();
void greatings(Agency agency);
vector<string> vectorString(string morada, string separador);
vector<Packet> StringIDtoPackVec(vector<Packet> packets, vector<string> stringvec);
Packet BinarySearch(vector<Packet> packet, int id);
void clearBuffer(void);
bool strIsNumber(string str);
bool checkZip(string zip);
string strVecToStr(vector<string> strvec);
