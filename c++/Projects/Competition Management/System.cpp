#include<iostream>
#include "Manage.h"
#include"Contestants.h"


int main() {
	Manage MA;
	int inp = 0;

	while (true)
	{
		MA.ShowMenu();
		cout << "Please inter your chose:" << endl;
		cin >> inp;
		switch (inp)
		{
		//start the game
		case 0:
			MA.ShowInfo(MA.m_contestans);
			break;
		case 1:
			MA.StartCompetition();
			break;
		//Check former data
		case 2:
			MA.Loadcsv();
			break;
		//Clear former data
		case 3:
			MA.CleanAll();
			break;
		//Exit the system
		case 4:
			MA.Exit();
			break;
		default:
			system("cls");//clear the screem
			break;
		}

	}
	system("pause");
	return(0);
}