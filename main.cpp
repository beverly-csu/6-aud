#include <iostream>
#include "Workers.h"
using namespace std;
int main()
{
	setlocale(0, "Russian");
	char choise;
	while (true)
	{
		cout << "'a' � ���������� �������� � ���������"
				"\n'd' - ������� �������� ��� ���� ����������"
				"\n'w' � �������� ��� ������ � ����"
				"\n'r' � ��������� ��� ������ �� �����"
				"\n'x' - �����"
				"\n��� �����: ";
		cin >> choise;
		switch (choise)
		{
		case 'a':
			Employee::add(); 
			break;
		case 'd':
			Employee::display(); 
			break;
		case 'w':
			Employee::write(); 
			break;
		case 'r':
			Employee::read(); 
			break;
		case 'x': 
			exit(0);
		default: 
			cout << "\n����������� �������";
		}
	}
	return 0;
}