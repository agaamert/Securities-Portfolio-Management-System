#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "securities.h"

#define n endl
#define cls system("CLS")

using namespace std;

class portfolio
{
public:
	string name;
	string address;
	string no;
	string afm;
	string fileName; // [GR] Για να βρεθεί το αρχείο για διορθώσεις κλπ.
	string type; // canceled or not

	vector<securities*> secV;

	portfolio();
	portfolio(string, string, string, string, string, string);
	portfolio(const portfolio&);
	double calculateCost();
	void display();

	virtual ~portfolio();
};