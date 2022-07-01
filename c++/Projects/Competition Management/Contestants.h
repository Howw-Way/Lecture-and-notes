#pragma once
#include<string>
#include<iostream>
using namespace std;
class Contestants {
public:
	Contestants() {};
	Contestants(string name,double score[2]) {
		this->m_name = name;
		for (int i = 0; i < 2; i++)
		{
			this->m_score[i] = score[i];

		}
		//Do not use this, will cause problem
		//this->m_score[2] = score[2];
	};
	~Contestants() {};
	string m_name;
	double m_score[2];//there are two round
};