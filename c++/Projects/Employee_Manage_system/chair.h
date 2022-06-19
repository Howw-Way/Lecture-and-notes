#pragma once
#include<iostream>
#include<string>
#include"employee.h"
using namespace std;

//Employee 1: staff

class Chair :public Employee {
public:
	//Constructor function
	Chair();
	Chair(int id, string name, int depid);

	virtual void ShowInfo();

	virtual string GetJobName();
};