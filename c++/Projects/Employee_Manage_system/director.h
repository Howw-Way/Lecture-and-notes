#pragma once
#include<iostream>
#include<string>
#include"employee.h"
using namespace std;

//Employee 1: staff

class Director :public Employee {
public:
	//Constructor function
	Director();
	Director(int id, string name, int depid);

	virtual void ShowInfo();

	virtual string GetJobName();
};