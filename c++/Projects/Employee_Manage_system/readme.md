# Project description

This is a project for exercising building a system in C++ with polymorphism and double pointer.

# System description

## 1. Demand

This system used for managing the information of all employees(including staff/director/chair) in one company.

For each employee:
Properties: ID, name, Department ID(1 for staff, 2 for director, 3 for chair)
Behavior: Describe the job, get the name of job
Different kind of employee was arranged by polymorphism, with abstract class `employee`.


## 2. Function

This system including the following function:

0. Exit the system
1. Add employee
2. Show details
3. Delete employee
4. Change details
5. Find employee
6. Sort with Id
7. Clear all

## 3. class: WorkerManager 

Maintain:

- Interface for communication with user
- Operator for employee adding and deleting
- Operator with file

### 3.1 function: Show_Menu()

- Interface for communication with user

```c++
void EmployeeManager::ShowMenu()
{
	cout << "--------------------------------------" << endl;
	cout << "-------Welcome to manage system-------" << endl;
	cout << "----------  0.Exit the system --------" << endl;
	cout << "----------  1.Add employee  ----------" << endl;
	cout << "----------- 2.Show details -----------" << endl;
	cout << "----------- 3.Delete employee --------" << endl;
	cout << "----------- 4.Change details  --------" << endl;
	cout << "----------- 5.Find employee  ---------" << endl;
	cout << "----------- 6.Sort with Id  -------" << endl;
	cout << "----------- 7.Clear all  -------------" << endl;
	cout << endl;
}
```

### 3.2 function: ExitSystem()

- exit the system
```c++
void  EmployeeManager::ExitSystem(){
	cout << "Thanks for your using, see you!" << endl;
	system("pause");
	//exit
	exit(0);
}
```

## 4. Class: employee

Employee classification: staff/director/chair
Properties: No, name, Department No
Behavior: Describe the job, get the name of job
Different kind of employee was arranged by polymorphism, with abstract class `employee`.

### 4.1 Employee

```c++
//file:employee.h
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Employee {
public:

	virtual void ShowInfo() = 0;
	virtual string GetJobName() = 0;

	int m_id;//the Id of employee
	int m_depid;//the department Id of employee
	string m_name;//the name of employee

};
```

### 4.2 Staff

It was arranged by polymorphism with abstract class `employee`.

```c++
#include"staff.h"

Staff::Staff(int id, string name, int depid) {
	this->m_id = id;
	this->m_name = name;
	this->m_depid = depid;
}

void Staff::ShowInfo() {
	cout << "ID of staff:" << this->m_id << endl;
	cout << "name of staff:" << this->m_name << endl;
	cout << "ID of staff department:" << this->m_depid << endl;
}

string Staff::GetJobName(){
	return string("staff");
}
```

### 4.3 Director

```c++
#include"director.h"

Director::Director(int id, string name, int depid) {
	this->m_id = id;
	this->m_name = name;
	this->m_depid = depid;
}

void Director::ShowInfo() {
	cout << "ID of Director:" << this->m_id << endl;
	cout << "name of Director:" << this->m_name << endl;
	cout << "ID of Director department:" << this->m_depid << endl;
	cout << "Director department:" << this->GetJobName() << endl;

}

string Director::GetJobName() {
	return string("Director");
}
```

### 4.4 Chair

```c++
#include"chair.h"

Chair::Chair(int id, string name, int depid) {
	this->m_id = id;
	this->m_name = name;
	this->m_depid = depid;
}

void Chair::ShowInfo() {
	cout << "ID of chair:" << this->m_id << endl;
	cout << "name of chair:" << this->m_name << endl;
	cout << "ID of chair department:" << this->m_depid << endl;
}

string Chair::GetJobName() {
	return string("chair");
}
```

## 5. Append employee (Key)

Function `` is used for appending employees into system, then save into file.

In this case, a double pointer(like `Employee` listed here) was used to storage the pointer(like `Employee* [newSize]` listed here) of each employee and each employee pointer point to the detail information.
`Employee ** newSpace= new Employee* [newSize]`

```c++
void EmployeeManager::AppendEmployee() {
	cout << "Please input the number of new employee" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum>0)
	{
		//calculate the space needed for storage,m_EmpNum is the former number of employee,addNum is the number of new employee
		int newSize = this->m_EmpNum + addNum;
		//here, newSpace is a double pointer to storage the location of the array, the arrary(Employee* [newSize]) is an array storage the pointer of each employee
		Employee ** newSpace= new Employee* [newSize];
		//copy the data of former employee if there is.
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//add new data
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			//job kind
			int depid;
			cout << "please input the ID of " << i + 1 << "employee" << endl;
			cin >> id;
			cout << "please input the name of " << i + 1 << "employee" << endl;
			cin >> name;
			cout << "please chose the kind of " << i + 1 << "employee" << endl;
			cout << "1.staff" << endl;
			cout << "2.director" << endl;
			cout << "3.chair" << endl;
			cin >> depid;

			Employee* employee = NULL;
			switch (depid)
			{
			case 1:
				employee = new Staff(id,name, depid);
			case 2:
				employee = new Director(id, name, depid);
			case 3:
				employee = new Chair(id, name, depid);
			default:
				break;
			}
			//storage the pointer into a arrary
			newSpace[this->m_EmpNum + i] = employee;

		}
		//release the space for storage the former data
		//remember to add the [] to delete the array
		delete[] this->m_EmpArray;

		//update the space for storage current data
		this->m_EmpArray = newSpace;
		//update the number of employee
		this->m_EmpNum = newSize;


		//updata the m_fileEmpty
		this->m_fileEmpty = false;

		cout << "succeed add " <<addNum << " employee";
		//save data into file
		this->Save();

	}
	else
	{
		cout << "Wrong input employee number" << endl;
	}
	system("pause");
	system("cls");

}
```

## 6. Save File

Function `void Save()` is used for save data into file.

```c++
void EmployeeManager::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//wirte information in file
	//wirte information of each employee in file
	//Attention: there is no need to use repeat ofs for m_id m_name and m_depid
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_depid << endl;
	}

	//close file
	ofs.close();
}
```


## 7. Read File

Function: Load the data from file every time running the system.

Attention: there are three different situations during the construction of function

1. The file hasn't been created yet;

2. There is file, but there is no data in it.

3. File existed, and save all the data. 

### 7.1 There is no file

1. Use `bool m_fileEmpty` in class `employeeManager` to show whether the file is empty or not.(ture means there is no file or no data in file)

2. Change the construct function of `employeeManager`. 

### 7.2 There is file, but there is no data in it

how to test whether there is data in file

```c++
char ch;
ifs>>ch;
if (if.eof()) means there is no data in file
```

use peek function

```c++
if (ifs.peek()==EOF)
```

attention, if the is no data in file, `m_fileEmpty` still is ture

### 7.3 File existed and there are data in it

#### 7.3.1 The total number of employee

Use `int getEmpNum()` function to get the total number of employee

1. how to get the single number in file:from file, we can detect how many lines (each line stands for one employee)

In this way: 
`ifs >> id && ifs >> name && ifs >> depid` (the type of id, name, depid are settled) will be ture only as all the parameter is in the type as their definition

Example:

```txt
"data.txt"
1 hao 1
2 Hao 2
A hao 2
```

 ```c++
int id;
string name;
int depid;
ifstream ifs;
ifs.open("data.txt", ios::in);
while (ifs >> id && ifs >> name && ifs >> depid)
{
	cout << id << endl;//will show 1 2 as only the firsr two line in "data.txt" accorded with the definition of id, name, depid
}
 ```

 2. then we can achieve it by following code
 
 ```c++
int EmployeeManager::GetEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num=0;
	int id;
	string name;
	int depid;
	while (ifs >> id && ifs >> name && ifs >> depid) {
		num++;
	}
	ifs.close();
	cout << "total num is:" << num << endl;
	return num;
}
 ```

 #### 7.3.2 Initialize array

As there already existed some data in file, it should be initialized with `Employee ** m_EmpArray`

The function `void InitEmp()` is used for the initializing.


## 8. Show the information of each employee

The function `void ShowEmp()` is used for showing.

And if there is no file (or no data in file), the function will be activated and show 'no data'. Only if there is file including data, this function will show data.
```c++
void EmployeeManager::ShowEmp() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}
```

## 9. Delete employee

The function `void DelEmp()` is used for deleting employee by each employee's ID.

1. But before deleting specific employee, we should check whether the employee is existed or not, `int IsExist(int id)`(int is used for returning the location of this id in array, if there is no such employee, return -1)

```c++
int EmployeeManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
```

2. Actually, deleting in array is moving the next data(next to the data going to be deleted) forward. 

So, in function `DelEmp()`, firstly ,detecting whether there is data, then get the ID, then change the ID into index by `IsExist`, finally, delete the data by replacing it with the next data. 

```c++
void EmployeeManager::DelEmp() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else
	{
		cout << "Please inputing the ID of employee you are going to delete" << endl;
		int id=0;
		int index=-1;
		cin >> id;
		index=IsExist(id);
		if (index!=-1)
		{
			if (index<m_EmpNum-1)
			{
				for (size_t i = index; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];

				}
			}
			//updata the m_EmpNum
			this->m_EmpNum--;
			//updata in file
			this->Save();
			cout << "Successfully delete employee " << id << endl;

		}
		else {
			cout << "failed in searching, no such employee" << endl;
		}


	}
	system("pause");
	system("cls");

}
```

## 10. Change information

Change the information with employee's ID with the function `void ChangeEmp()`.

```c++
void EmployeeManager::ChangeEmp() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else
	{
		cout << "Please input the id of employee you are going to change" << endl;
		int id;
		cin >> id;
		int index = -1;
		index = IsExist(id);
		if (index!=-1)
		{
			cout << "please chose which information do you want to change:" << endl;
			cout << "1. Id, 2. Name, 3. DepartmentId" << endl;
			int change_type;
			cin >> change_type;
			switch (change_type)
			{
			case 1:
				cout << "please input the new id:" << endl;
				int new_id;
				cin >> new_id;
				this->m_EmpArray[index]->m_id = new_id;
				break;

			case 2:
			{cout << "please input the new name:" << endl;
			string newname;
			cin >> newname;
			this->m_EmpArray[index]->m_name = newname;
			break; }

			case 3:
				cout << "please input the new departmentID:" << endl;
				int new_depid;
				cin >> new_depid;
				this->m_EmpArray[index]->m_depid = new_depid;
				break;
			default:
				break;
			}
			this->Save();
		}
		else
		{
			cout << "failed in searching, no such employee" << endl;
		}
	}
}
```

## 11. Find the employee

With the function `void FindEmp()`, we can find the employee by name or by ID. 

1. Id: By id is quite simple as we have done it before, just use `int IsExist()` to get the index, we should notice that id is exclusive, it shouldn't repeat.

2. Name: By name is more complexed, as some employee may have the same name.

```c++
void EmployeeManager::ChangeEmp() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else
	{
		cout << "Please input the id of employee you are going to change" << endl;
		int id;
		cin >> id;
		int index = -1;
		index = IsExist(id);
		if (index!=-1)
		{
			cout << "please chose which information do you want to change:" << endl;
			cout << "1. Id, 2. Name, 3. DepartmentId" << endl;
			int change_type;
			cin >> change_type;
			switch (change_type)
			{
			case 1:
				cout << "please input the new id:" << endl;
				int new_id;
				cin >> new_id;
				this->m_EmpArray[index]->m_id = new_id;
				break;

			case 2:
			{cout << "please input the new name:" << endl;
			string newname;
			cin >> newname;
			this->m_EmpArray[index]->m_name = newname;
			break; }

			case 3:
				cout << "please input the new departmentID:" << endl;
				int new_depid;
				cin >> new_depid;
				this->m_EmpArray[index]->m_depid = new_depid;
				break;
			default:
				break;
			}
			this->Save();
		}
		else
		{
			cout << "failed in searching, no such employee" << endl;
		}
	}
}
```

## 12. Sort

Sort employees with id, and sending or desending is defined by user.

In current case, the bubble sorting method have been used.

```c++

void EmployeeManager::SortEmp()
{
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	
	else
	{
		cout << "Input 1 will sort as sending, 2 for desending" << endl;
		int way = 1;
		cin >> way;
		if (way == 1) {
			for (int i = 0; i < m_EmpNum - 1; i++)
			{
				for (int j = 0; j < m_EmpNum - i - 1; j++)
				{
					if (this->m_EmpArray[j]->m_id > this->m_EmpArray[j + 1]->m_id)
					{
						int temp = this->m_EmpArray[j + 1]->m_id;
						this->m_EmpArray[j + 1]->m_id = this->m_EmpArray[j]->m_id;
						this->m_EmpArray[j]->m_id = temp;
					}
				}
			}
		}
		if (way==2)
		{
			for (int i = 0; i < m_EmpNum - 1; i++)
			{
				for (int j = 0; j < m_EmpNum - i - 1; j++)
				{
					if (this->m_EmpArray[j]->m_id < this->m_EmpArray[j + 1]->m_id)
					{
						int temp = this->m_EmpArray[j + 1]->m_id;
						this->m_EmpArray[j + 1]->m_id = this->m_EmpArray[j]->m_id;
						this->m_EmpArray[j]->m_id = temp;
					}
				}
			}
		}
		this->Save();
		cout << "Successfully sorting" << endl;
		cout << "this is the result of sorting" << endl;
		this->ShowEmp();
	}
	system("pause");
	system("cls");
}
```

## 13. Clean the file

Use `void CleanFile` to clean all data in existed file.


```c++
void EmployeeManager::CleanFile() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else {
		cout << "Are you sure to clean all data?" << endl;
		cout << "Input 1 to ensure, 2 to back off?" << endl;
		int way;
		cin >> way;
		if (way==1)
		{
			ofstream ofs(FILENAME, ios::trunc);
			ofs.close();
			//then delete all pointer
			if (this->m_EmpArray!=NULL)
			{
				//firstly, delete all the pointer in array
				for (int i = 0; i < m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]!=NULL)
					{
						delete this->m_EmpArray[i];
					}
				}
				//then delete the array pointer
				delete[] this->m_EmpArray;
				this->m_EmpNum = 0;
				this->m_EmpArray = NULL;
				this->m_fileEmpty = true;
			}
			if (m_fileEmpty) {
				cout << "Successfully clean all data!" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}
```
