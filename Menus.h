#pragma once

#include "Agency.h"
#include "funcoes.h"

unsigned mainMenu(Agency agency);
unsigned menu_1(Agency agency);
unsigned menu_2(Agency agency);
unsigned menu_3(Agency agency);

//auxiliar functions
unsigned selec(unsigned menor, unsigned maior,void data(),unsigned menu(Agency agency),Agency agency);
void greatings(Agency agency);
