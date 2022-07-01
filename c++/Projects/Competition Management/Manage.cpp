#include "Manage.h"

Manage::Manage() {
	this->IntiSpeech();
	this->CreatContestant();
}

void Manage::ShowMenu() {
	cout << "----------------------------------" << endl;
	cout << "--------Choose function-----------" << endl;
	cout << "--0.Show contestants information--" << endl;
	cout << "-----1.Start the competition------" << endl;
	cout << "------ 2.Check former data -------" << endl;
	cout << "------ 3.Clear former data -------" << endl;
	cout << "------- 4.Exit the system --------" << endl;
	cout << "----------------------------------" << endl;

}
void Manage::Exit() {
	cout << "See you!" << endl;
	system("pause");
	exit(0);
}

void Manage::IntiSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->v_victor.clear();
	this->m_contestans.clear();
	this->m_index = 1;
}

void Manage::Shuffle(vector<int>& v) {
	cout << "Desiding the order for round:" << this->m_index << endl;
	cout << "-------------------------------------------" << endl;
	srand(42);
	random_shuffle(v.begin(), v.end());
	cout << "Here is the order for round:" << this->m_index << endl;
	for (vector<int>::const_iterator it = v.begin(); it !=v.end(); it++)
	{
		cout << (*it) << "\t";
	}
	cout << endl;
	cout << "-------------------------------------------" << endl;

}

//this is used for show the information of the contestants
void Manage::ShowInfo(const map<int, Contestants>& c) {
	for (map<int, Contestants>::const_iterator  mit= c.begin();mit!=c.end();mit++)
	{
		cout << "ID:" << (*mit).first <<"\t"<< (*mit).second.m_name << "\t" << "Score:"<< (*mit).second.m_score[1] << endl;
	}
	system("pause");
	system("cls");
}


//this is used for begin a round,including scoring, sorting and storing
void Manage::Begin(vector<int>& v) {
	cout << "Begin of round:" << this->m_index << endl;
	cout << "-------------------------------------------" << endl;

	//num is used for storing the number of scored contestants
	int num = 0;
	//group_temp is used to store the contestants for temp
	multimap<double, int, greater<double>>group_temp;

	//scoring and grouping 
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		num++;
		deque<double> d_score;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d_score.push_back(score);
		}
		sort(d_score.begin(), d_score.end(), greater<double>());
		d_score.pop_front();
		d_score.pop_back();

		double sum = accumulate(d_score.begin(), d_score.end(), 0.0f);
		double avg = sum / ((double)d_score.size());
		this->m_contestans[*it].m_score[m_index - 1] = avg;
		group_temp.insert(make_pair(avg,*it));

		//if there are 6*n in group_temp,then group them in the same group
		if (num%6==0)
		{
			cout << "Result of group:" << num / 12 << endl;
			for (multimap<double, int, greater<double>>::iterator it = group_temp.begin(); it !=group_temp.end(); it++)
			{
				cout << "ID: " << it->second <<" Name:"<<m_contestans[it->second].m_name<< " Score: " << it->first << endl;
			}
			//get the top 3
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = group_temp.begin(); it != group_temp.end() && count<3; it++,count++)
			{
				if (m_index == 1)
				{
					this->v2.push_back(it->second);
				}
				if (m_index == 2)
				{
					this->v_victor.push_back(it->second);
				}
			}
			group_temp.clear();
		}
	}

	cout <<"End of round:"<< this->m_index << endl;
	cout << "-------------------------------------------" << endl;
}

void Manage::ShowTop(vector<int>& v) {
	cout << "This is the top of round: " << this->m_index << endl;

	for (vector<int>::iterator it = v.begin(); it !=v.end(); it++)
	{
		cout << "ID: " << *it << " Name:" << m_contestans[*it].m_name << " Score: " << m_contestans[*it].m_score[m_index-1] << endl;
	}
}

void Manage::StartCompetition() {
	//round 1
	//shuffle
	this->Shuffle(v1);
	this->Begin(v1);
	this->ShowTop(v2);
	this->m_index = 2;
	this->Shuffle(v2);
	this->Begin(v2);
	this->ShowTop(v_victor);


	//score

	//show result

	//round 2
	//shuffle
	//this->Shuffle(v2);

	//score
	//show result
	Save2csv();
	system("pause");
	system("cls");

}


void Manage::CreatContestant() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name;
		name = "Contestant:";
		double score[2] = { 0.0,0.0 };
		Contestants c1(name + nameseed[i], score);
		int id = 1001 + i;
		v1.push_back(id);
		m_contestans.insert(pair<int, Contestants>(id, c1));

	}
}

void Manage::Save2csv() {
	ofstream ofs;
	ofs.open("data.csv", ios::out | ios::app);
	for (vector<int>::iterator it = v_victor.begin(); it !=v_victor.end(); it++)
	{
		ofs << *it << "," << m_contestans[*it].m_name << "," << m_contestans[*it].m_score[1]<<"," << endl;
	}
	ofs << endl;
	ofs.close();
	cout << "----- Successfully saved! -----" << endl;
}

void Manage::Loadcsv() {
	ifstream ifs;
	ifs.open("data.csv", ios::in);
	if (!ifs.is_open())
	{
		this->FileEmpty = true;
		cout << "No file exsited" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->FileEmpty = true;
		cout << "No data in file" << endl;
		ifs.close();
		return;
	}

	string data;
	//put back of the data loaded in former
	ifs.putback(ch);
	int index = 0;

	//this loop is for go through all data in csv file, the outer loop go through each row, and the inner go through each colum in every row
	while (ifs>>data)
	{
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			//find from start
			pos = data.find(",", start);
			//-1 means not find in find()
			if (pos==-1)
			{
				break;
			}
			//get the sub string in
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_record.insert(make_pair(1+index/3, v));
		index++;

	}
	for (multimap<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
	{
		cout << "No of competition:" << it->first << " ID:" << it->second[0] << " Name:" << it->second[1] << " Score:" << it->second[2] << endl;
	}
	system("pause");
	system("cls");
	this->m_record.clear();
	ifs.close();
}

void Manage::CleanAll() {
	cout << "Are you sure to clean all data?" << endl;
	cout << "1.yes! 2. Return" << endl;
	int chose;
	cin >> chose;
	if (chose==1)
	{
		ofstream ofs("data.csv", ios::trunc);
		ofs.close();

		this->IntiSpeech();
		cout << "Successfully clean all" << endl;
	}
	system("pause");
	system("cls");
}


Manage::~Manage() {


}
