#include "stocks.h"

stocks::stocks() { price = 0; type = 'M'; }

stocks::stocks(char t, string name, double fv, int q, int gy, double p)
{
	price = p;
	company_name = name;
	face_value = fv;
	quantity = q;
	get_year = gy;
	type = t;
}

stocks::stocks(const stocks& copy)
{
	company_name = copy.company_name;
	face_value = copy.face_value;
	quantity = copy.quantity;
	get_year = copy.get_year;
	price = copy.price;
	type = copy.type;
}

void stocks::display()
{
	securities::display();
	cout << "Stock's price: " << price << n << "Total cost: " << calculateCost() << n;

}

double stocks::calculateCost()
{
	double cost = 0.02 * price;

	return cost;
}

void stocks::modifyInfos()
{
	char ch;
	int tempI;
	double tempD;
	string tempS;
	bool ok = false;

	cout << "Please select one option that you want to change it: " << n << n;
	cout << "[A] Company Name" << n << "[B] Face Value" << n << "[C] Quantity" << n << "[D] Acquisition Year" << n << "[E] Price of Stock" << n << n << "[0] BACK" << n << n << "> ";

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
			cout << "Give new Price: "; cin >> tempD;
			price = tempD;
			ok = true;
			break;
		}
		case '0': ok = true; break;
		default: cout << "Please select A, B, C, D, E or 0." << n << "Try again." << n << "> ";
		}
		cin.ignore(100, '\n');
	}

	cout << "Your changes successfully saved.." << n;
	system("pause");
}

void stocks::writeSec(ofstream& tempF)
{
	tempF << 'M' << "|" << company_name << "|" << face_value << "|" << quantity << "|" << get_year << "|" << price << n;
}