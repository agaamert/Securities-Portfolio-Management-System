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

class stocks :public securities
{
public:
	double price;

	stocks();
	stocks(char, string, double, int, int, double);
	stocks(const stocks&);
	void display();
	double calculateCost();
	void modifyInfos();
	void writeSec(ofstream&);
};