#pragma once//in case of duplicated header file
#include <iostream>
#include"employee.h"
#include"staff.h"
#include"director.h"
#include"chair.h"
#include"chair.h"
#include<fstream>
#define FILENAME "empFile.txt"

using namespace std;

class  EmployeeManager
{
public:
	//Parameter:
	//number of employees
	int m_EmpNum;

	//whether file is empty, ture means empty
	bool m_fileEmpty;

	//use a array to storage the pointor of employees
	Employee** m_EmpArray;

	//Function:
	//Constructor function
	EmployeeManager();

	//destructor function
	~EmployeeManager();

	//show menu
	void ShowMenu();

	//exit system
	void ExitSystem();

	//Append employee
	void AppendEmployee();

	//get number of employee
	int GetEmpNum();

	//initializing
	void InitEmp();

	//save file
	void Save();

	//Show information
	void ShowEmp();

	//check whether the id is existed and return the location
	int IsExist(int id);

	//check whether the name is existed and return the location
	int IsExistName(string name);

	//delete specific employee by id
	void DelEmp();

	//change employee's information with id
	void ChangeEmp();

	//find employee by name or ID
	void FindEmp();

	//Sort the employees
	void SortEmp();

	//Clean the data in file
	void CleanFile();
};