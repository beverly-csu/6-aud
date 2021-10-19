#include <iostream>
#include "Workers.h"
using namespace std;
int main()
{
	setlocale(0, "Russian");
	char choise;
	while (true)
	{
		cout << "'a' Ц добавление сведений о работнике"
				"\n'd' - вывести сведени€ обо всех работниках"
				"\n'w' Ц записать все данные в файл"
				"\n'r' Ц прочитать все данные из файла"
				"\n'x' - выход"
				"\n¬аш выбор: ";
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
			cout << "\nЌеизвестна€ команда";
		}
	}
	return 0;
}