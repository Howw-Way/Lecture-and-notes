#include"director.h"

Director::Director(int id, string name, int depid) {
	this->m_id = id;
	this->m_name = name;
	this->m_depid = depid;
}

void Director::ShowInfo() {
	cout << "ID of Director:" << this->m_id << endl;
	cout << "name of Director:" << this->m_name << endl;
	cout << "ID of Director department:" << this->m_depid << endl;
	cout << "Director department:" << this->GetJobName() << endl;

}

string Director::GetJobName() {
	return string("Director");
}