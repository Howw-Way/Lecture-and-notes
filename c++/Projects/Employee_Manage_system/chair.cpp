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