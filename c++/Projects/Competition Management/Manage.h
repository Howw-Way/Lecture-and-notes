#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include"Contestants.h"
#include<functional>
#include<numeric>
#include<fstream>

using namespace std;

class Manage {
public:
	Manage();
	~Manage();
	void ShowMenu();

	//this is uesd for exit the system
	void Exit();
	void IntiSpeech();
	void CreatContestant();

	//this is used for show the information of the contestants
	void ShowInfo(const map<int, Contestants>& c);
	void StartCompetition();
	void Shuffle(vector<int> &v);

	//this is used for begin a round,including scoring, sorting and storing
	void Begin(vector<int>& v);

	//this is for show the top of each round
	void ShowTop(vector<int>& v);

	//this is for saving the data into csv file
	void Save2csv();

	//this is for load the data in csc file
	void Loadcsv();

	//clean all data
	void CleanAll();


	//all contestants, 12
	vector<int>v1;

	//winner of round 1, 6
	vector<int>v2;

	//top three, 3
	vector<int>v_victor;

	//store the ID and contestants
	map<int, Contestants>m_contestans;

	//round of the competition
	int m_index;

	//wheter file is exsited 
	bool FileEmpty = false;

	//to record data from file,the int means the No of competition
	multimap<int, vector<string>> m_record;



};