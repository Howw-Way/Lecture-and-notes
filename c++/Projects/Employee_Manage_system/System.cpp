#include <iostream>
#include "employeeManager.h"//please note there should include the header file, not the cpp file
#include "employee.h"
#include "staff.h"
#include "director.h"
#include "chair.h"

using namespace std;

void testEmployee() {
	//use polymorphism by cite method, attention: must add const to make & dil is a const cite
	//const Employee & di1 = Director(18, "James", 100);
	//use polymorphism by pointor method
	Employee * sf1=new Staff(18,"James",102);
	sf1->ShowInfo();
	cout<<"Job:"<<sf1->GetJobName()<<endl;
	Employee* di1 = new Director(28,"Xiong",101);
	Employee* ch1 = new Chair(45,"Hao",100);
}


void testManager() {
	EmployeeManager wm;
	int choice = 0;
	while (true)
	{
		wm.ShowMenu();
		cout << "please select a function with number" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: //exit
			wm.ExitSystem();
			break;
		case 1://add
			wm.AppendEmployee();
			break;
		case 2://show
			wm.ShowEmp();
			break;
		case 3://delete
			wm.DelEmp();
			break;
		case 4://change
			wm.ChangeEmp();
			break;
		case 5://find
			wm.FindEmp();
			break;
		case 6://arrange
			wm.SortEmp();
			break;
		case 7://clear
			wm.CleanFile();
			break;
		default:
			system("cls");//refreash the sreen(in case of inputting other numbers)
		}
	}
}

int main() {

	testManager();
	//testEmployee();
	system("pause");
	return 0;
}

