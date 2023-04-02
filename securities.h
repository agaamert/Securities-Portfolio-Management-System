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
	string company_name; // [GR] ����� ��������� ��� �� �������
	double face_value; // [GR] ���������� ����
	int quantity; // [GR] �������� ��� ������� � �������
	int get_year; // [GR] ���� ���������
	char type; // O | M (Stocks | Bonds)

	securities();
	virtual double calculateCost();
	virtual void modifyInfos();
	virtual void writeSec(ofstream&);
	virtual void display() = 0;
	virtual ~securities();

};