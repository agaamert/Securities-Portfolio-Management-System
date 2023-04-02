#include "portfolio.h"
#include "MAIN.cpp"

double portfolio::calculateCost()
{
	double price = 0;

	for (int k = 0; k < secV.size(); k++)
		price = add(price, secV[k]->calculateCost());

	return price;
}

portfolio::portfolio(const portfolio& copy)
{
	name = copy.name;
	address = copy.address;
	no = copy.no;
	afm = copy.afm;
	fileName = copy.fileName;
	type = copy.type;
	secV = copy.secV;
}

portfolio::portfolio()
{
	name = " X ";
	address = " X ";
	no = " X ";
	afm = " X ";
	fileName = " X ";
	type = "NC"; // not canceled - default
}

portfolio::portfolio(string name_, string address_, string no_, string afm_, string file_, string type_)
{
	name = name_;
	address = address_;
	no = no_;
	afm = afm_;
	fileName = file_;
	type = type_;
}

portfolio::~portfolio()
{
	for (int i = 0; i < secV.size(); i++)
		delete secV[i];
}

void portfolio::display()
{
	cout << "Portfolio of " << name << "." << n << "Name: " << name << n << "Address: " << address << n << "Tel: " << no << n << "AFM: " << afm << n;
	if (type == "C") cout << "** This portfolio is CANCELED! **" << n;
}