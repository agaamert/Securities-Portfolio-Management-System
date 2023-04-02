#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#define n endl
#define cls system("CLS")

using namespace std;

class securities
{
public:
	string company_name; // [GR] Όνομα εταιρείας που το εξέδωσε
	double face_value; // [GR] Ονομαστική αξία
	int quantity; // [GR] Ποσότητα που κατέχει ο πελάτης
	int get_year; // [GR] Έτος απόκτησης
	char type; // O | M (Stocks | Bonds)

	securities();
	virtual double calculateCost();
	virtual void modifyInfos();
	virtual void writeSec(ofstream&);
	virtual void display() = 0;
	virtual ~securities();

};