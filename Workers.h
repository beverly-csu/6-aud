#pragma once
#ifndef _WORKERS_H
#define _WORKERS_H
const int LEN=32;		// Максимальная длина фамилий
const int MAXEM=100;	// Максимальное число работников
enum Employee_type { tmanager, tscientist, tlaborer };
///////////////////////////////////////////////////////////
class Employee
{
private:
	char name_[LEN];
	unsigned long number_;
	static int count_;
	static Employee** arrayPointers_;
public:
	virtual void getData();
	virtual void putData();
	virtual Employee_type getType();	// получить тип
	static void add();					// добавить работника
	static void display();   			// вывести данные обо всех
	static void read();					// чтение из файла
	static void write();				// запись в файл
};
///////////////////////////////////////////////////////////
class Manager : public Employee
{
private:
	char title_[LEN];		// титул ("вице-президент" и т. п.)
	double payment_;		// Налоги гольф-клуба
public:
	void getData();
	void putData();
};
///////////////////////////////////////////////////////////
class Scientist : public Employee
{
private:
	int nPublications_;
public:
	void getData();
	void putData();
};
///////////////////////////////////////////////////////////
class Laborer : public Employee
{
};
#endif