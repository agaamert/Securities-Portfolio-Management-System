#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "securities.h"

#define n endl
#define cls system("CLS")

using namespace std;

class bonds :public securities
{
public:
	int ex_year;
	int bank_rate;

	bonds();
	bonds(char, string, double, int, int, int, int);
	bonds(const bonds&);

	void display();
	double calculateCost();
	void modifyInfos();
	void writeSec(ofstream&);
};
