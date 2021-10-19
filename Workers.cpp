#include <fstream>
#include <iostream>
#include <typeinfo>     // ��� typeid()
#include <process.h>	// ��� exit()
#include "Workers.h"
using namespace std;
int Employee::count_ = 0;
Employee** Employee::arrayPointers_ = new Employee * [MAXEM];
void Employee::getData()
{
	cin.ignore(10, '\n');
	cout << "  ������� �������: "; cin >> name_;
	cout << "  ������� �����: ";    cin >> number_;
}
void Employee::putData()
{
	cout << "\n  �������: " << name_;
	cout << "\n  �����: " << number_;
}
Employee_type Employee::getType()		// �������� ���
{
	if (typeid(*this) == typeid(Manager))
		return tmanager;
	else if (typeid(*this) == typeid(Scientist))
		return tscientist;
	else if (typeid(*this) == typeid(Laborer))
		return tlaborer;
	else
	{
		cerr << "\n������������ ��� ���������"; exit(1);
	}
	return tmanager;
}
void Employee::add()					// �������� ���������
{
	char choise;
	cout << "'m' ��� ���������� ���������"
		"\n's' ��� ���������� �������"
		"\n'l' ��� ���������� ��������"
		"\n��� �����: ";
	cin >> choise;
	switch (choise)
	{          //������� ������ ���������� ����
	case 'm': arrayPointers_[count_] = new Manager;  break;
	case 's': arrayPointers_[count_] = new Scientist; break;
	case 'l': arrayPointers_[count_] = new Laborer;  break;
	default: cout << "\n����������� ��� ���������\n"; return;
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
		case tmanager:  cout << ". ���: ��������";  break;
		case tscientist: cout << ". ���: ������"; break;
		case tlaborer:   cout << ". ���: �������";  break;
		default: cout << ". ����������� ���";
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
		cout << "\n���������� ������� ����\n";
		return;
	}
	count_ = 0;
	while (true)
	{
		inputFile.read((char*)&inputType, sizeof(inputType));
		if (inputFile.eof())       // ����� �� ����� �� EOF
			break;
		if (!inputFile)              // ������ ������ ����
		{
			cout << "\n���������� ������ ����\n"; return;
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
		default: cout << "\n����������� ��� � �����\n"; return;
		}
		cout << inputFile.tellg() << endl;
		//inputFile.seekg(4, ios::cur);
		cout << inputFile.tellg() << endl;
		char trash[4];
		inputFile.read(trash, 4);
		inputFile.read((char*)arrayPointers_[count_], size - 4);
		if (!inputFile)              // ������, �� �� EOF
		{
			cout << "\n������ ������ �� ����� ����������\n"; return;
		}
		count_++;
	}
	cout << "���� ������ " << count_ << " ����������\n";
	inputFile.close();
}
void Employee::write()
{
	int size = sizeof(Manager);
	cout << "���� ������ " << count_ << " ����������.\n";
	ofstream outputFile;
	Employee_type inputType;
	outputFile.open("EMPLOY.DAT", ios::trunc | ios::binary);
	if (!outputFile)
	{
		cout << "\n���������� ������� ����\n"; return;
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
			cout << "\n������ � ���� ����������\n"; return;
		}
	}
	outputFile.close();
}
///////////////////////////////////////////////////////////
void Manager::getData()
{
	Employee::getData();
	cout << "  ������� �����: ";	cin >> title_;
	cout << "  ������� ������: ";	cin >> payment_;
}
void Manager::putData()
{
	Employee::putData();
	cout << "\n  �����: " << title_;
	cout << "\n  ������ �����-�����: " << payment_;
}
///////////////////////////////////////////////////////////
void Scientist::getData()
{
	Employee::getData();
	cout << "  ������� ����� ����������: "; cin >> nPublications_;
}
void Scientist::putData()
{
	Employee::putData();
	cout << "\n  ����� ����������: " << nPublications_;
}
///////////////////////////////////////////////////////////