#include "employeeManager.h"

//function implementation
EmployeeManager::EmployeeManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1. if the file is not exist at the first time, we just need to make every parameter equal to 0
	if (!ifs.is_open())
	{
		cout << "There is no file exist" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileEmpty = true;
		ifs.close();
		return;
	}

	//2. if the file is exist but there is no data in it
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "there is no data in file" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileEmpty = true;
		ifs.close();
	}

	//3. if the file is exist and there is no data in it
	this->m_EmpNum = this->GetEmpNum();
	this->m_EmpArray = new Employee*[this->m_EmpNum];//this is very hard to understand
	//here, m_EmpArray is a double pointor to storage the location of the array, the arrary(Employee* [this->m_EmpNum]) is an array storage the pointor of each employee
	this->InitEmp();
	//for test
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	//this->m_EmpArray[i] is a pointor to an Employee class, then use -> get the property of Employee class
	//	cout << "ID:" << this->m_EmpArray[i]->m_id<<endl;
	//}
}

//initializing if there exist file including data
void EmployeeManager::InitEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int index = 0;
	int id;
	string name;
	int depid;
	while (ifs >> id && ifs >> name && ifs >> depid) {
		Employee* employee = NULL;
		if (depid == 1) //a staff
		{
			employee = new Staff(id, name, depid);
		}
		if (depid == 2) //a director
		{
			employee = new Director(id, name, depid);
		}
		if (depid == 3) //a Chair
		{
			employee = new Chair(id, name, depid);
		}
		this->m_EmpArray[index] = employee;
		index++;
	}
}

EmployeeManager::~EmployeeManager()
{
	if (this->m_EmpArray!=NULL)
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}
		delete[] this -> m_EmpArray;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_fileEmpty = true;

	}
}

//please note that Show_Menu is a function, we should specify the type
void EmployeeManager::ShowMenu()
{
	cout << "--------------------------------------" << endl;
	cout << "-------Welcome to manage system-------" << endl;
	cout << "----------  0.exit the system --------" << endl;
	cout << "----------  1.add employee  ----------" << endl;
	cout << "----------- 2.show details -----------" << endl;
	cout << "----------- 3.delete employee --------" << endl;
	cout << "----------- 4.change details  --------" << endl;
	cout << "----------- 5.find employee  ---------" << endl;
	cout << "----------- 6.arrange with No  -------" << endl;
	cout << "----------- 7.clear all  -------------" << endl;
	cout << endl;
}

//exit system
void  EmployeeManager::ExitSystem(){
	cout << "Thanks for your using, see you!" << endl;
	system("pause");
	//exit
	exit(0);
}

//Add employee
void EmployeeManager::AppendEmployee() {
	cout << "Please input the number of new employee" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum>0)
	{
		//calculate the space needed for storage,m_EmpNum is the former number of employee,addNum is the number of new employee
		int newSize = this->m_EmpNum + addNum;
		//here, newSpace is a double pointor to storage the location of the array, the arrary(Employee* [newSize]) is an array storage the pointor of each employee
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
			//storage the pointors into a arrary
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

//get the total number of employee
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

//save file
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

//Show information
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

//check whether the id is existed and return the location
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

//check whether the name is existed and return the location,this function is not perfect as it can only return the last index
int EmployeeManager::IsExistName(string name) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_name == name)
		{
			index = i;
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	if(index==-1)
		{
		cout << "failed in searching, no such employee" << endl;
		}
	return index;
}

//delete specific employee by id
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
				for (int i = index; i < this->m_EmpNum - 1; i++)
				{
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];

				}
			}
			if (index > m_EmpNum - 1) {
				cout << "Something wrong with IsExist() function" << endl;
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

//find employee by name or ID
void EmployeeManager::FindEmp() {
	if (this->m_fileEmpty)
	{
		cout << "No file or no data in file" << endl;
	}
	else {
		cout << "Input 1 to find by Id, 2 to find by Name" << endl;
		cout << "-------------------------------" << endl;
		int temp = 0;
		cin >> temp;
		if (temp == 1)
		{
			cout << "Please input the ID of employee you want to find" << endl;
			int id;
			cin >> id;
			int index = -1;
			index = IsExist(id);
			if (index != -1)
			{
				cout << "Successfully find:" << endl;
				cout << "ID: " << this->m_EmpArray[index]->m_id << endl;
				cout << "Name: " << this->m_EmpArray[index]->m_name << endl;
				cout << "DepID: " << this->m_EmpArray[index]->m_depid << endl;
			}
			else
			{
				cout << "failed in searching, no such employee" << endl;
			}
		}
		if (temp == 2)
		{
			cout << "Please input the name of employee you want to find" << endl;
			string name;
			cin >> name;
			IsExistName(name);
		}
	}

	system("pause");
	system("cls");
}

//Sort the employees
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
		cout << "Successfully sorting and here shows the result of sorting"<<endl;
		cout << "-------------------------------" << endl;
		cout << "" << endl;
		this->ShowEmp();
	}
	system("pause");
	system("cls");
}

//Clean the data in file
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
			//then delete all pointor
			if (this->m_EmpArray!=NULL)
			{
				//firstly, delete all the pointor in array
				for (int i = 0; i < m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]!=NULL)
					{
						delete this->m_EmpArray[i];
					}
				}
				//then delete the array pointor
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