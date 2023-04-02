#pragma once

#include "securities.h"

securities::securities()
{
	company_name = " X ";
	face_value = 0;
	quantity = 0;
	get_year = 0;
}

double securities::calculateCost() { return 0; }
securities::~securities() {}
void securities::modifyInfos() {}
void securities::writeSec(ofstream& tempF) {}

void securities::display()
{
	cout << "Company name: " << company_name << n << "Cost of face Value: " << face_value << n << "Quantity: " << quantity << n << "Acquisition year: " << get_year << n;
}
