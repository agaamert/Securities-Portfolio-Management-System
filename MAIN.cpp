/*
Copyright (C) 2018 Mert Aga
agaamert@outlook.com

University of West Attica
Faculty of Engineering
Informatics and Computer Engineer
C++ || Object Oriented Programming Final Project 2018
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "securities.h"
#include "bonds.h"
#include "stocks.h"
#include "portfolio.h"

#define n endl
#define cls system("CLS")

using namespace std;

template <class A>
A add(A a, A b)
{
	A temp = a + b;
	return temp;
}

#pragma region -> Declarations

vector<portfolio *> readCustomers();
void writeFile(vector<portfolio *> &, int &);
void menu1(vector<portfolio *> &);
void menu2(vector<portfolio *> &, int &);

void add_portfolio(vector<portfolio *> &);
void add_portfolio_decision(vector<portfolio *> &, int &);
void add_sec(vector<portfolio *> &, int &);
void add_stock(vector<portfolio *> &, int &);
void add_bond(vector<portfolio *> &, int &);

void delete_sec(vector<portfolio *> &, int &);
void cancel_portfolio(vector<portfolio *> &);

void change_infoMENU(vector<portfolio *> &);
void change_portfolio(vector<portfolio *> &, int &);
void change_sec(vector<portfolio *> &p, int &);

void analytics(vector<portfolio *> &);
vector<int> analytics_1(vector<portfolio *> &);
vector<int> analytics_2(vector<portfolio *> &, char);
vector<int> analytics_3(vector<portfolio *> &, int);
void display_analytics1(vector<portfolio *> &);
void display_analytics2(vector<portfolio *> &);
void display_analytics3(vector<portfolio *> &, int);
void smallAnalyticsMenu(vector<portfolio *> &);
void smallAnalyticsMenu2(vector<portfolio *> &, int);

vector<string> split(string, char);
void exit_(vector<portfolio *> &p);
void getInfo(string);
void getInfoMessage(string);
int test_input(void);  // Test for integers that I ask from user to select one portfolio or security (not to enter something else from digits)

void getX(); // [GR] Για την 4η επιλογή στον κατάλογο
double X = 0; 
bool okX = false; // [GR] Βάζω ενάν flag για έλεγχο αν θέλει να αλλάξει το Χ ή όχι

int portfolio_counter = 1; // [GR] Για να καθορίσω τα ονόματα των αρχείων (πχ. portfolio_1.txt => portfolio_counter++ => portfolio_2.txt)
int C = -1; // [GR] Counter για να ξέρουμε σε ποια θέση να αποθηκευτούν τα στοιχεία από το αρχείο.. Είναι ουσιαστικά portfolio_counter - 1

#pragma endregion


// MAIN

int main()
{
	vector<portfolio *> p1 = readCustomers();
	menu1(p1);

	return 0;
}


void menu1(vector<portfolio *> &p)
{
	cls;
	char ch;
	bool ok = false;
	
	cout << "WELCOME!" << n << n << "Select one option to continue: " << n << "[A] Add new Portfolio" << n << "[B] Change Informations (change customer's informations, add/delete security or change informations of them)" << n;
	cout << "[C] Cancel portfolio" << n << "[D] Analytics" << n << n << "[0] EXIT" << n << n << "Option: ";

	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		
		switch(ch)
		{
			case 'A':case 'a': ok = true; cls; add_portfolio(p); break;
			case 'B':case 'b': ok = true; cls; change_infoMENU(p); break;
			case 'C':case 'c': ok = true; cls; cancel_portfolio(p); break;
			case 'D':case 'd': ok = true; cls; analytics(p); break;
			case '0': ok = true; cls; exit_(p); break;
			default: cout << "Please select A, B, C or D." << n << "Try again." << n << "> ";
		}
	}
}

void menu2(vector <portfolio *> &p, int &pos)
{
	char ch;
	bool ok = false;
	
	cout << "Select one option to continue: " << n << "[A] Change informations of Portfolio" << n << "[B] Change informations of Securities" << n;
	cout << "[C] Add Security" << n << "[D] Delete Security" << n << n << "[0] BACK" << n << n << "Option: ";
	
	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		
		switch(ch)
		{
			case 'A':case 'a': ok = true; cls; change_portfolio(p, pos); break;
			case 'B':case 'b': ok = true; cls; change_sec(p, pos);break;
			case 'C':case 'c': ok = true; cls; add_sec(p, pos); break;
			case 'D':case 'd': ok = true; cls; delete_sec(p, pos); break;
			case '0': ok = true; cls; change_infoMENU(p); break;
			default: cout << "Please select A, B, C, D or 0." << n << "Try again." << n << "> ";
		}
	}
}

void add_portfolio(vector<portfolio *> &p)
{
	string text = ".txt";
	string fName = "Portfolios/portfolio_";
	string Pname, Paddress, Pno, Pafm, pc = to_string(portfolio_counter);
    char ch;
    bool ok = false;
    
    fName = add(add(fName, pc), text);
	
	cout << "Give.." << n << "Name: ";
	getline(cin, Pname);
	cout << "Address: ";
	getline(cin, Paddress);
	cout << "Telephone Number: ";
	getline(cin, Pno);
	cout << "AFM: ";
	
	 do
	{
		getline(cin, Pafm);
		if(Pafm.size() != 9)
		{
		  cout << "Please give valid AFM (enter AFM until 9 characters)." << n << "Please try again.." << n << n << "> ";
		  continue;
		}
	}while(Pafm.size() != 9);
	
	cin.ignore(30, '\n');
	
	cout << n << "[A] Save" << n << "[B] Cancel" << n << "> ";
	
	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		
		switch(ch)
		{
			case 'A':case 'a': { p.push_back(new portfolio(Pname, Paddress, Pno, Pafm, fName, "NC"));
                                 int tempPOS = portfolio_counter-1;
                                 writeFile(p, tempPOS);
                                 cout << n << "Portfolio saved successfully.." << n << n;
								 ok = true;
								 if(fName == "Portfolios/portfolio_1.txt")
								 {
								 	cls;
									cout << "Please restart the program." << n << n;
									system("pause");
								 	exit(-1);
								 }
                                 add_portfolio_decision(p, tempPOS);
			                	 break;
		                    	}
		    case 'B':case 'b': {
		                         ok = true ;
								 if(fName == "Portfolios/portfolio_1.txt")
								 	exit(-1);
								 else
									 menu1(p); 
									 break;
							}
			            
			default: cout << "Please select A or B." << n << "Try again." << n << "> ";
		}
	}
}

void add_portfolio_decision(vector<portfolio *> &p, int &pos)
{
	char ch;
	bool ok = false;
	
	cout << "[A] Add Securities" << n << "[B] Back to MAIN MENU" << n << n << "> ";
	
	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		
		switch(ch)
		{
			case 'A':case 'a': ok = true; cls; add_sec(p, pos); break;
			case 'B':case 'b': ok = true; cls; menu1(p); break;
			default: cout << "Please select A or B." << n << "Try again." << n << "> ";
		}
	}
}

void change_infoMENU(vector<portfolio *> &p)
{
	int ch, pos;

     if(p.size() == 0) // [GR] Κανονικά θα έχει portfolio όμως το έλεγχο για να μη τύχον έχει συμβεί κάτι
	   {
	   	cout << "There is no saved portfolios in the system. Please go [0] BACK and ADD PORTFOLIO." << n;
	   }
	 else
	 {
		cout << "Select one portfolio to continue: " << n << n;
    	for(int i=0; i < p.size(); i++)
    	{
      		cout << "[" << i+1 << "] " << p[i]->name;
         		if(p[i]->type == "C")
         		   cout << " (portfolio is cancelled)";
		               cout << n;
	    }
     }
	
	    cout << n << n << "[0] BACK" << n;
	do
	{ 
	   cout << n << "Option: ";
	   ch = test_input();
	
	  if(ch < 0 || ch > p.size())
      {
      	cout << ch << " is invalid." << n << "Please try again until " << p.size() << "." << n << n;
      	continue;
		cls;
	  }
    }while((ch < 0 || ch > p.size()));
    
    
    if(ch == 0)
    {
    	cls; 
		menu1(p);
	}
    else
    {
		pos = ch-1;
		cls;
        menu2(p, pos);
	}
}

void change_portfolio(vector<portfolio *> &p, int &pos)
{
	char ch;
	string temp;
	
	cout << "[A] Name" << n << "[B] Address" << n << "[C] Telephone Number" << n << "[D] AFM" << n << n << "[0] BACK" << n << n << "> ";
	bool ok = false;
	
	while(!ok)
	{
	    cin >> ch;
	    cin.ignore(1,'\n');
		switch(ch)
		{
			case 'A':case 'a': {
				                cout << "Please give customer's new name: "; getline(cin, temp);
				                p[pos]->name = temp;
				                ok = true;
								break;
			                   }
			case 'B':case 'b': {
				                cout << "Please give customer's new address: "; getline(cin, temp);
				                p[pos]->address = temp;
				                ok = true;
								break;
			                   } 
			case 'C':case 'c': {
				                cout << "Please give customer's new telephone number: "; getline(cin, temp);
				                p[pos]->no = temp;
				                ok = true;
								break;
			                   } 
			case 'D':case 'd': {
				                cout << "Please give customer's new AFM: ";
				                do
				                {
				                	getline(cin, temp);
									if(temp.size() != 9)
				                	{
				                		cout << "Please give valid AFM (enter AFM until 9 characters)." << n << "Please try again.." << n << n << "> ";
				                		continue;
									}
								}while(temp.size() != 9);
				                p[pos]->afm = temp;
				                ok = true;
								break;
			                   } 
	        case '0': cls; ok = true; change_infoMENU(p); break;
	        default: cout << "Please select A, B, C, D or 0" << n << "Try again." << n << "> ";
		}
	}
	
	writeFile(p, pos);
	
	cout << "Your changes successfully saved.." << n;
	system("pause");
	menu1(p);
}

void change_sec(vector<portfolio *> &p, int &pos)
{
	int ch;
	int Vpos;

	p[pos]->display();
	cout << n << n;
	
	  if(p[pos]->secV.size() == 0)
	  {
	  	cout << "This customer doesn't have security." << n << n;
	  	system("pause"); cls;
	  	change_infoMENU(p);
	  }
	  
	cout << "Please select one security to continue: " << n << n;
	  
	for (int i=0; i < p[pos]->secV.size(); i++)
	   {
	   	 cout << "[" << i+1 << "]" << n;
		 p[pos]->secV[i]->display();
	     cout << n;
	   }
	   
	    cout << n << n << "[0] BACK" << n;
	do
	{ 
	   cout << n << "Option: ";
	   ch = test_input();
	 
	  if(ch < 0 || ch > p[pos]->secV.size())
      {
      	cout << ch << " is invalid." << n << "Please try again until " << p[pos]->secV.size() << "." << n << n;
      	continue;
		cls;
	  }
    }while((ch < 0 || ch >  p[pos]->secV.size()));
    
    
    if(ch == 0)
    {
    	cls; 
		menu2(p, pos);
	}
    else
    {
		Vpos = ch-1;
		cls;
        p[pos]->secV[Vpos]->modifyInfos();
        writeFile(p, pos);
	    menu1(p);
	}
}


void add_sec(vector<portfolio *> &p, int &pos)
{
	char ch;
	bool ok = false;
	
	cout << "Select one option to continue: " << n << n << "[A] Add STOCKS" << n << "[B] Add BONDS" << n << n <<  "[0] BACK" << n << n << "> ";
	
	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		
		switch(ch)
		{
			case 'A':case 'a': ok = true; cls; add_stock(p, pos); break;
			case 'B':case 'b': ok = true; cls; add_bond(p, pos); break;
			case '0': ok = true; cls; menu2(p, pos); break;
			default: cout << "Please select A, B or 0." << n << "Try again." << n << "> ";
		}
	}
}

void add_stock(vector<portfolio *> &p, int &pos)
{
	string name;
	int q, gy;
	double fv, price;
	
	cout << "Give Company Name: "; getline(cin, name);
	cin.ignore(name.size(), '\n');
	cout << "Give Quantity: "; cin >> q,
	cout << "Give Acquisition Year: "; cin >> gy;
	cin.ignore(20, '\n');
	cout << "Give Face Value: "; cin >> fv;
	cout << "Give Price for Stock: "; cin >> price;
	cin.ignore(20, '\n');
	
	p[pos]->secV.push_back(new stocks('M', name, fv, q, gy, price));
	writeFile(p, pos);
	
	cout << "Your changes successfully saved.." << n;
	system("pause");
	menu1(p);
}

void add_bond(vector<portfolio *> &p, int &pos)
{
	string name;
	int q, gy, exY;
	double fv, rate;
	
	cout << "Give Company Name: "; getline(cin, name);
	cin.ignore(20, '\n');
	cout << "Give Quantity: "; cin >> q,
	cout << "Give Acquisition Year: "; cin >> gy;
    cout << "Give Expiration Year: "; cin >> exY;
	cin.ignore(20, '\n');
	cout << "Give Face Value: "; cin >> fv;
	cout << "Give Bank Rate (%): "; cin >> rate;
	cin.ignore(20, '\n');
	
	p[pos]->secV.push_back(new bonds('O', name, fv, q, gy, exY, rate));
	writeFile(p, pos);
	
	cout << "Your changes successfully saved.." << n;
	system("pause");
	menu1(p);
}

void delete_sec(vector<portfolio *> &p, int& pos)
{
    int ch;
	int Vpos;
	
	p[pos]->display();
	cout << n;
	
	 if(p[pos]->secV.size() == 0)
	  {
	  	cout << "This customer doesn't have security." << n << n;
	  	system("pause"); cls;
	  	change_infoMENU(p);
	  }
	  
	for (int i=0; i < p[pos]->secV.size(); i++)
	   {
	   	 cout << "[" << i+1 << "] ";
		 p[pos]->secV[i]->display();
	     cout << n;
	   }
	   
	    cout << n << n << "[0] BACK" << n;
	do
	{ 
	   cout << n << "Option: ";
	   ch = test_input();
	 
	  if(ch < 0 || ch > p[pos]->secV.size())
      {
      	cout << ch << " is invalid." << n << "Please try again until " << p[pos]->secV.size() << "." << n << n;
      	continue;
		cls;
	  }
    }while((ch < 0 || ch >  p[pos]->secV.size()));
    
    
    if(ch == 0)
    {
    	cls; 
		menu2(p, pos);
	}
    else
    {
		Vpos = ch-1;
		char ans;
		bool ok = false;
		
		cls;
        cout << "Are you sure to delete this security which is above?  [Y = Yes || N = No]: "; 
		
		while(!ok)
		{
	    	cin >> ans;
		    cin.ignore(1, '\n');
		
           if(ans == 'Y' || ans == 'y')
           {
             p[pos]->portfolio::secV.erase(p[pos]->secV.begin() + Vpos);
             ok = true;
             writeFile(p, pos);
             menu1(p);
           }
           else if(ans == 'N' || ans == 'n')
           {
           	cout << "Your CANCELED to delete customer's security!" << n;
           	system("pause");
           	menu1(p);
		   }
		   else 
		   {
		   	cout << "Please enter Y for Yes || N for No." << n << "Enter again: "; 
		   }
	    }
	}
}

void cancel_portfolio(vector<portfolio *> &p)
{
	int ch, pos;

     if(p.size() == 0)
	   {
	   	cout << "There is no saved portfolios in the system. Please go [0] BACK and ADD PORTFOLIO." << n;
	   }
	 else
	 {
		cout << "Select one portfolio to continue: " << n << n;
    	for(int i=0; i < p.size(); i++)
    	{
      		cout << "[" << i+1 << "] " << p[i]->name;
         		if(p[i]->type == "C")
         		   cout << " (portfolio is cancelled)";
		               cout << n;
	    }
     }
	
	    cout << n << n << "[0] BACK" << n;
	do
	{ 
	   cout << n << "Option: ";
	   ch = test_input();
	
	  if(ch < 0 || ch > p.size())
      {
      	cout << ch << " is invalid." << n << "Please try again until " << p.size() << "." << n << n;
      	continue;
		cls;
	  }
    }while((ch < 0 || ch > p.size()));
    
    pos = ch-1;
    
    if(ch == 0)
    {
    	cls; 
		menu1(p);
	}
    else if(p[pos]->type == "C")
     {
     	cls;
		cout << "** This portfolio is already cancelled! **" << n;
     	system("pause");
     	menu1(p);
	 }
	else
    {
        p[pos]->type = "C";
	    writeFile(p, pos);
		menu1(p);
	}
}

void analytics(vector<portfolio *> &p)
{
	char ch;
	bool ok = false;
	
	
	cout << "Please select one option to continue:" << n << n;
	cout << "[A] Portfolios that total costs of them are more than X euros" << n << "[B] Portfolios that individual securities of them are more than X euros" << n << "[C] 10 Portfolios with maximum cost" << n << n;
	cout << "[0] BACK" << n << n << "> ";
	
	  while(!ok)
	  {
	  	cin >> ch;
	  	cin.ignore(1, '\n');
	  	
	  	  switch(ch)
	  	  {
	  	    case 'A':case 'a': ok = true; cls; getX(); display_analytics1(p); break;
	  	    case 'B':case 'b': ok = true; cls; getX(); display_analytics2(p); break; 
	  	    case 'C':case 'c': ok = true; cls; display_analytics3(p, 10); break;
	  	    case '0': ok = true; menu1(p); cls; break;
	  	    default: cout << "Please select A, B, C or 0." << n << "Try again." << n << "> ";
		  }
	  }
}

vector<int> analytics_1(vector<portfolio *> &p)
{
	vector<int> positions;
	
	  for(int i=0; i < p.size(); i++)
	  {
	  	if(p[i]->calculateCost() > X)
	  	  positions.push_back(i);
	  }
	  
	  return positions;
}

vector<int> analytics_2(vector<portfolio *> &p, char type)
{
	vector<int> positions;
	
	  for(int i=0; i < p.size(); i++)
	  {
	  	for(int j=0; j < p[i]->secV.size(); j++)
	  	{
	  		if(p[i]->secV[j]->calculateCost() > X)
	  		 {
	  		    if(p[i]->secV[j]->type == type)	// [GR] Κάνω έλεγχο για να ξέρω που να το τοποθετήσω (O | M)
	  		          positions.push_back(i);
			 }
		}
	  }
	  
	  return positions;
	
}

vector<int> analytics_3(vector<portfolio *> &p, int test)
{
  vector<int> max;
  int maxPOS = 0;

  smallAnalyticsMenu2(p, test); // Test for portfolios if they are enough with asked number

	for(int k=0; k < test; k++)
	{
	  for(int i=1; i < p.size(); i++) 
	   {
	   	 if(p[i]->calculateCost() > p[maxPOS]->calculateCost())
	   	 {
	   	    maxPOS = i; 
			max.push_back(maxPOS);	
		 }
	   }
	}
	
	return max;
}

void display_analytics1(vector<portfolio *> &p)
{
	vector<int> pos = analytics_1(p);
	
	if(pos.size() == 0)
		cout << n << "\t** There is no portfolio with total cost more than " << X << " euros. **" << n;
	else if(pos.size() == 1)
	{
		cout << "   " << 1 << " portfolio has total cost more than " << X << " euros." << n << n;
		cout << "      It is portfolio of: " << n << n;
		cout << "      " << p[pos[0]]->name << "." << n;
		cout << "      Total Cost: " << p[pos[0]]->calculateCost() << n << n;
	}
	else
	{
		cout << pos.size() << " portfolios have total cost more than " << X << " euros." << n << n;
		cout << "They are portfolios of: " << n << n;
		
		for(int i=0; i < pos.size(); i++)
		{
			cout << "[" << i+1 << "] " << p[i]->name << n;
			cout << "Total Cost: " << p[i]->calculateCost() << n << n;
		}
	}
	smallAnalyticsMenu(p);
}

void display_analytics2(vector<portfolio *> &p)
{
	vector<int> Stocks = analytics_2(p, 'M'); // [GR] Ελέγχω ξεχωριστά και για τα 2 είδη χρεόγραφα
	vector<int> Bonds = analytics_2(p, 'O');
	
	
	cout << "STOCKS: " << n;
	
	if(Stocks.size() == 0)
		cout << n << "\t** There is no portfolio with Individual STOCK cost more than " << X << " euros. **" << n;
	else if(Stocks.size() == 1)
	{
		cout << "There is "  << 1 << " portfolio with Individual STOCK that is more than " << X << " euros." << n << n;
		cout << "      It is portfolio of:" << n << n;
		cout << "      " << p[Stocks[0]]->name << "." << n << n;
	}
	else
	{
		cout << Stocks.size() << " portfolios have Individual STOCK more than " << X << " euros." << n << n;
		cout << "They are portfolios of: " << n << n;
		
		for(int i=0; i < Stocks.size(); i++)
		{
			cout << "[" << i+1 << "] " << p[i]->name << n;
		}
	}
	
	cout << n << n << "BONDS: " << n;

	if(Bonds.size() == 0)
		cout << n << "\t** There is no portfolio with Individual BOND cost more than " << X << " euros. **" << n;
	else if(Bonds.size() == 1)
	{
		cout << "There is " << 1 << " portfolio with Individual BOND that is more than" << X << " euros." << n << n;
		cout << "      It is portfolio of:" << n << n;
		cout << "      " << p[Bonds[0]]->name << "." << n << n;
	}
	else
	{
		cout << Bonds.size() << " portfolios have Individual BONDS more than " << X << " euros." << n << n;
		cout << "They are portfolios of: " << n << n;
		
		for(int i=0; i < Bonds.size(); i++)
		{
			cout << "[" << i+1 << "] " << p[i]->name << n;
		}
	}
	smallAnalyticsMenu(p);
}

void display_analytics3(vector<portfolio *> &p, int test)
{
   vector<int> max = analytics_3(p, test);

	 if(max.size() == 0)
      {
      	   cout << "There is no saved portfolios or securities in the system. Press <enter> to go MAIN MENU and add PORTFOLIO or SECURUTIES." << n << n;	
      	   system("pause");
      	   menu1(p);
	  }
	  else
	  {
	  	if(max.size() < 10 || max.size() > 10)
	  	   cout << max.size() << " with  Maximum cost: " << n << n;
	  	else
	       cout << "10 Portfolios with Maximum cost: " << n << n;
	  	
	  	  for(int i=0; i < max.size(); i++)
	  	  {
	  	     cout << "[" << i+1 << "] " << p[i]->name << " (total cost: " << p[i]->calculateCost() << ")";
	  	       if(p[i]->type == "C")
	  	          cout << " <-- This portfolio is cancelled!";
	  	          cout << n;
		  }
		  cout << n << n;
		  system("pause");
		  analytics(p);
	  }
}

void smallAnalyticsMenu(vector<portfolio *> &p)
{
	bool ok = false;
	char ch;
	system("pause");
	cls;
	
	cout << "Select one option to continue: " << n << "[A] Change X" << n << "[B] Continue with same X" << n << n << "[0] Back to MAIN MENU" << n << n << "> ";
	
	while(!ok)
	{
		cin >> ch;
		cin.ignore(1, '\n');
		 switch(ch)
		 {
		 	case 'A':case 'a': ok = true; cls; okX = false; getX(); analytics(p); break;
		 	case 'B':case 'b': ok = true; cls; okX = true; getX(); analytics(p); break;
		 	case '0': ok = true; cls; okX = false; menu1(p);
		 	default: cout << "Please select A, B or 0." << n << "Please try again.." << n << n << "> ";
		 }
	}
}

void smallAnalyticsMenu2(vector<portfolio *> &p, int test)
{
	bool ok = false;
	char ch;
	
	if(p.size() < test)
	  {
	  	   cout << "No enough portfolios to see the option '10 Portfolios with maximum cost'." << n;
	  	   cout << "\tDo you want to see portfolios with maximum cost? [Y = Yes || N = No]" << n << n << "\t> "; 
	  	  
    	  while(!ok)
    		{
     	    	cin >> ch;
    		    cin.ignore(1, '\n');
		
              if(ch == 'Y' || ch == 'y')
               {
                 ok = true;
	     		 cls;
	             display_analytics3(p, p.size());
               }
              else if(ch == 'N' || ch == 'n')
               {
               	ok = true; cls;
		    	analytics(p);
		       }
		      else 
		       {
		     	cout << "Please enter Y for Yes || N for No." << n << "Enter again: "; 
		       }
	       }  
	  }
}

void getX()
{
	if(!okX)
	{
    	cout << "** NOTICE that you must give first one cost(X) to test portfolios.." << n << n << "Give cost: ";
          do
		  {
       	    cin >> X;
	        cin.ignore();
	           if(X < 0) cout << "Give positive number.. (for instance: 0.710)" << n << n << "> ";
	      }while(X < 0);
	}  
	  okX = true;
	  cls;
}

void exit_(vector<portfolio *> &p)
{
	bool ok = false;
	char ans;
	
	cout << "Are you sure to [EXIT] from the system?  [Y = Yes || N = No]: "; 
		
		while(!ok)
		{
	    	cin >> ans;
		    cin.ignore(1, '\n');
		
           if(ans == 'Y' || ans == 'y')
           {
             cls;
             cout << n << "   Copyright (C) 2018 Mert Aga" << n;
             cout << "     agaamert@outlook.com" << n << n;
             cout << "     University of West Attica" << n;
			 cout << "     Faculty of Engineering" << n ;
			 cout << "     Informatic and Computer Engineering" << n << n;
			 cout << "     C++ || Object Oriented Programming Final Project 2018\n\n\n\n";
			 system("pause");
			 ok = true;
			 exit(1);
           }
           else if(ans == 'N' || ans == 'n')
           {
           	cout << "You CANCELLED to exit from system!" << n;
           	ok = true;
           	system("pause");
           	menu1(p);
		   }
		   else 
		   {
		   	cout << "Please enter Y for Yes || N for No." << n << "Enter again: "; 
		   }
	    }
}

vector<string> split(string line, char delim)
{ 
  vector<string> v;
  stringstream x(line);
  string token;
 
  while(getline(x, token, delim))
    v.push_back(token);
 
  return v;
}

void writeFile(vector<portfolio *> &p, int &pos)
{
	ofstream wf;
	wf.open((p[pos]->fileName.c_str()), std::ofstream::out | std::ofstream::trunc);
	
     if(!wf.is_open())
      {
        cout << "There is problem with system. Please try again within 2-3 minutes or contact with Support Team." << n;         
        system("pause");
		menu1(p);          
      }
      
       wf << p[pos]->name << "|" << p[pos]->address << "|" << p[pos]->no << "|" << p[pos]->afm << "|" << p[pos]->type << n ;
       
         for(int i = 0; i < p[pos]->secV.size(); i++)
         {
         	p[pos]->secV[i]->writeSec(wf);
		 }
		 
	 wf.close();
	  
}


vector<portfolio *> readCustomers()
{
    string text = ".txt";
	string fName = "Portfolios/portfolio_", pc, buf1, buf2;
   	bool ok = false;
      bool ok2 = false;
   	char BUF1[256], ch;
    vector<portfolio *> p; 
    vector<string> s;
    vector<string> s1;
    
	while(!ok)
	{ 
            pc = to_string(portfolio_counter++);
            fName = add(add(fName, pc), text);
            C++;
            
			ifstream pf(fName.c_str(), ios::in);
                          
            if(!pf.good())
            {
                int tempPC = portfolio_counter; // [GR] Κάνω 2ο έλεγχο για σιγουρία (πχ. Μπορεί να έχει καταστραφεί για κάποιο λόγο το portfolio_2.txt όμως να έχουμε portfolio_3.txt)
				string tempSTR = to_string(tempPC++);
				fName = "Portfolios/portfolio_";
                fName = add(add(fName, tempSTR), text);
                   ifstream temp;
                   temp.open(fName.c_str());
                     if(!temp.is_open())
                     {
					   ok = true;
					   pf.close();
					   if(p.size() == 0) // [GR] Μετα τον 2ο έλεγχο και αν ακόμα δεν ανοιγεί αρχείο, γίνεται έλεγχος για να μην είναι μια περίπτωση που δεν έχει αρχείο ή είναι άδιο
					   {
					   	 cout << "There is no saved portfolios (txt files) in folder of executable file." << n << n;
			             cout << "Please select one option to continue: " << n << n;
			             cout << "[A] get more info about the problem" << n << "[B] Add new Portfolio" << n << "[0] EXIT" << n << n << "> ";
			             
			                while(!ok2)
			                {
			                	cin >> ch;
			                	cin.ignore(1, '\n');
			                	
			                	switch(ch)
			                	{
			                		case 'A':case 'a': cls; ok2 = true; getInfoMessage(fName); break;
			                		case 'B':case 'b': cls; ok2 = true; portfolio_counter = 1; add_portfolio(p); break;
			                		case '0': cls; exit_(p);
			                		default: cout << "Please select A, B or 0." << n << "Enter again: ";
								}
							}
					   }
					   portfolio_counter--;
					   menu1(p);
					 }			   
			}
			
	if(pf.good())
	{
		   pf.getline(BUF1, 256);
		   buf1 = BUF1;
		   
		   	if(buf1 == "")
			{
				getInfoMessage(fName);
			}
		   
			s = split(buf1, '|');
		       
		       for(int i=0; i < s.size(); i++)
		       {
		       	    if(s[i] == "")
		          	 {
			           getInfoMessage(fName);
			         }
			   }
			   
			p.push_back(new portfolio(s[0], s[1], s[2], s[3], fName, s[4]));
			
		    
	 while(getline(pf, buf2))
         { 
              s1 = split(buf2, '|');
              
              if(s1[0] == "M")
                {
                    int Q = stoi(s1[3]), getY = stoi(s1[4]);
		    		double fv = stod(s1[2]), price = stod(s1[5]);
                    p[C]->secV.push_back(new stocks('M', s1[1], fv, Q, getY, price));
				}
			  else if(s1[0]=="O")
			  {
			  	  int Q = stoi(s1[3]), getY = stoi(s1[4]), exY = stoi(s1[5]), bR = stoi(s1[6]);
			  	  double fv = stod(s1[2]);
				  p[C]->secV.push_back(new bonds('O', s1[1], fv, Q, getY, exY, bR));
			  }	
			  
			  s1.clear();
			  s.clear();
	    	}
		}
             pf.close();
             buf1 = buf2 = "";
             fName = "Portfolios/portfolio_";
      }
	
   return p;
}

void getInfo(string file)
{
	system("pause");
	cls;
	
	cout << "\t\nPlease check the '" << file << "' file from your folder." << n << n << "Press one key to get more informations.." << n;
	system("pause");
	cls;
	
	cout << "System couldn't reach to txt files or one txt file is writed wrong." << n;
	cout << n << "Your txt files must be like the line below:" << n << n;
	cout << "\tFirst line: \n\t name|address|no|afm|type_of_portfolio" << n << n << "\tFor stocks: \n\t M|company_name|face_value|quantity|acquisition_year|price" << n << n;
	cout << "\tFor bonds: \n\t O|company_name|face_value|quantity|acquisition_year|expiration_year|bank_rate" << n << n << n;
	cout << "\t\tFor instance: " << n << n;
	cout << "\t\tMert Aga|Athens|0123456789|afm123456|NC" << n;
	cout << "\t\tO|MAGA COMPANY|5.5|1|2016|2022|4" << n;
	cout << "\t\tM|binaryLAND|2.3|2|2008|9.3\n\n\n\n";
	
	system("pause");
	
	exit(-2);
}

void getInfoMessage(string file)
{
	cout << "There is one problem with system." << n << n << "Press one key to get more informations.." << n << n;
				getInfo(file);
				exit(-3);
}

int test_input(void)
{
	bool ok = false;
	string ch;
	char tempCH;
  
  while(!ok)
  {
    getline(cin, ch);
	  
	 for(int i=0; i < ch.size(); i++)
	 { 
	  tempCH = ch[i];
  	  if(!(tempCH >= '0' && tempCH <= '9'))
  	  {
  	  	cout << "Please give NUMBER instead of Letter." << endl << "> ";
	  }
	  else ok = true; 
	  break;
	 }
  }
        cin.clear();
		int res = stoi(ch);        
        return res;    
 } 