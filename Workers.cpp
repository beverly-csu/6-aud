#include <fstream>
#include <iostream>
#include <typeinfo>     // для typeid()
#include <process.h>	// для exit()
#include "Workers.h"
using namespace std;
int Employee::count_ = 0;
Employee** Employee::arrayPointers_ = new Employee * [MAXEM];
void Employee::getData()
{
	cin.ignore(10, '\n');
	cout << "  Введите фамилию: "; cin >> name_;
	cout << "  Введите номер: ";    cin >> number_;
}
void Employee::putData()
{
	cout << "\n  Фамилия: " << name_;
	cout << "\n  Номер: " << number_;
}
Employee_type Employee::getType()		// получить тип
{
	if (typeid(*this) == typeid(Manager))
		return tmanager;
	else if (typeid(*this) == typeid(Scientist))
		return tscientist;
	else if (typeid(*this) == typeid(Laborer))
		return tlaborer;
	else
	{
		cerr << "\nНеправильный тип работника"; exit(1);
	}
	return tmanager;
}
void Employee::add()					// добавить работника
{
	char choise;
	cout << "'m' для добавления менеджера"
		"\n's' для добавления ученого"
		"\n'l' для добавления рабочего"
		"\nВаш выбор: ";
	cin >> choise;
	switch (choise)
	{          //создать объект указанного типа
	case 'm': arrayPointers_[count_] = new Manager;  break;
	case 's': arrayPointers_[count_] = new Scientist; break;
	case 'l': arrayPointers_[count_] = new Laborer;  break;
	default: cout << "\nНеизвестный тип работника\n"; return;
	}
	arrayPointers_[count_++]->getData();
}
void Employee::display()
{
	for (int j = 0; j < count_; j++)
	{
		cout << (j + 1);
		switch (arrayPointers_[j]->getType())
		{
		case tmanager:  cout << ". Тип: Менеджер";  break;
		case tscientist: cout << ". Тип: Ученый"; break;
		case tlaborer:   cout << ". Тип: Рабочий";  break;
		default: cout << ". Неизвестный тип";
		}
		arrayPointers_[j]->putData();
		cout << endl;
	}
}
void Employee::read()
{
	int size;
	Employee_type inputType;
	ifstream inputFile;

	inputFile.open("EMPLOY.DAT", ios::binary);
	if (!inputFile)
	{
		cout << "\nНевозможно открыть файл\n";
		return;
	}
	count_ = 0;
	while (true)
	{
		inputFile.read((char*)&inputType, sizeof(inputType));
		if (inputFile.eof())       // выход из цикла по EOF
			break;
		if (!inputFile)              // ошибка чтения типа
		{
			cout << "\nНевозможно чтение типа\n"; return;
		}
		switch (inputType)
		{
		case tmanager:
			arrayPointers_[count_] = new Manager;
			size = sizeof(Manager);
			break;
		case tscientist:
			arrayPointers_[count_] = new Scientist;
			size = sizeof(Scientist);
			break;
		case tlaborer:
			arrayPointers_[count_] = new Laborer;
			size = sizeof(Laborer);
			break;
		default: cout << "\nНеизвестный тип в файле\n"; return;
		}
		cout << inputFile.tellg() << endl;
		//inputFile.seekg(4, ios::cur);
		cout << inputFile.tellg() << endl;
		char trash[4];
		inputFile.read(trash, 4);
		inputFile.read((char*)arrayPointers_[count_], size - 4);
		if (!inputFile)              // ошибка, но не EOF
		{
			cout << "\nЧтение данных из файла невозможно\n"; return;
		}
		count_++;
	}
	cout << "Идет чтение " << count_ << " работников\n";
	inputFile.close();
}
void Employee::write()
{
	int size = sizeof(Manager);
	cout << "Идет запись " << count_ << " работников.\n";
	ofstream outputFile;
	Employee_type inputType;
	outputFile.open("EMPLOY.DAT", ios::trunc | ios::binary);
	if (!outputFile)
	{
		cout << "\nНевозможно открыть файл\n"; return;
	}
	for (int j = 0; j < count_; j++)
	{
		inputType = arrayPointers_[j]->getType();
		outputFile.write((char*)&inputType, sizeof(inputType));
		switch (inputType)         // find its size
		{
		case tmanager: size = sizeof(Manager); break;
		case tscientist: size = sizeof(Scientist); break;
		case tlaborer:  size = sizeof(Laborer); break;
		}
		outputFile.write((char*)(arrayPointers_[j]), size);
		if (!outputFile)
		{
			cout << "\nЗапись в файл невозможна\n"; return;
		}
	}
	outputFile.close();
}
///////////////////////////////////////////////////////////
void Manager::getData()
{
	Employee::getData();
	cout << "  Введите титул: ";	cin >> title_;
	cout << "  Введите налоги: ";	cin >> payment_;
}
void Manager::putData()
{
	Employee::putData();
	cout << "\n  Титул: " << title_;
	cout << "\n  Налоги гольф-клуба: " << payment_;
}
///////////////////////////////////////////////////////////
void Scientist::getData()
{
	Employee::getData();
	cout << "  Введите число публикаций: "; cin >> nPublications_;
}
void Scientist::putData()
{
	Employee::putData();
	cout << "\n  Число публикаций: " << nPublications_;
}
///////////////////////////////////////////////////////////