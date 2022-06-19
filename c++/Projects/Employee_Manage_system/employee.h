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