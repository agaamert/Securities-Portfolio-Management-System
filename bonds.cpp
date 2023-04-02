#include "bonds.h"

bonds::bonds(const bonds& copy)
{
	company_name = copy.company_name;
	face_value = copy.face_value;
	quantity = copy.quantity;
	get_year = copy.get_year;
	ex_year = copy.ex_year;
	bank_rate = copy.bank_rate;
	type = copy.type;
}

bonds::bonds()
{
	ex_year = 2018;
	bank_rate = 5;
	type = 'O';
}

bonds::bonds(char t, string name, double fv, int q, int gy, int year, int rate)
{
	company_name = name;
	face_value = fv;
	quantity = q;
	get_year = gy;
	ex_year = year;
	bank_rate = rate;
	type = t;
}

void bonds::display()
{
	securities::display();
	cout << "Expire year of bonds: " << ex_year << n << "Total rate from bank: " << bank_rate << n << "Total cost: " << calculateCost() << n;
}

double bonds::calculateCost()
{
	double cost = 0.03 * face_value + 0.01 * (ex_year - 2018) + 0.01 * bank_rate;

	return cost;
}

void bonds::modifyInfos()
{
	char ch;
	int tempI;
	double tempD;
	string tempS;
	bool ok = false;

	cout << "Please select one option that you want to change it: " << n << n;
	cout << "[A] Company Name" << n << "[B] Face Value" << n << "[C] Quantity" << n << "[D] Acquisition Year" << n << "[E] Expire Year: " << n << "[F] Bank Rate" << n << n << "[0] BACK" << n << n << "> ";

	while (!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');

		switch (ch)
		{
		case 'A':case 'a': { cls;
			cout << "Give new Company Name: "; getline(cin, tempS);
			company_name = tempS;
			ok = true;
			break;
		}
		case 'B':case 'b': { cls;
			cout << "Give new Face Value: "; cin >> tempD;
			face_value = tempD;
			ok = true;
			break;
		}
		case 'C':case 'c': { cls;
			cout << "Give new Quantity: "; cin >> tempI;
			quantity = tempI;
			ok = true;
			break;
		}
		case 'D':case 'd': { cls;
			cout << "Give new Acquisition Year: "; cin >> tempI;
			get_year = tempI;
			ok = true;
			break;
		}
		case 'E':case 'e': { cls;
			cout << "Give new Expiration Year: "; cin >> tempD;
			ex_year = tempD;
			ok = true;
			break;
		}
		case 'F':case 'f': { cls;
			cout << "Give new Bank Rate: "; cin >> tempD;
			bank_rate = tempD;
			ok = true;
			break;
		case '0': ok = true; break;
		default: cout << "Please select A, B, C, D, E, F or 0." << n << "Try again." << n << "> "; continue;
		}
		}

		cout << "Your changes successfully saved.." << n;
		system("pause");
	}
}

void bonds::writeSec(ofstream& tempF)
{
	tempF << 'O' << "|" << company_name << "|" << face_value << "|" << quantity << "|" << get_year << "|" << ex_year << "|" << bank_rate << n;
}
