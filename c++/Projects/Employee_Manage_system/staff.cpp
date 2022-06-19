#include"staff.h"

Staff::Staff(int id, string name, int depid) {
	this->m_id = id;
	this->m_name = name;
	this->m_depid = depid;
}

void Staff::ShowInfo() {
	cout << "ID of staff:" << this->m_id << endl;
	cout << "name of staff:" << this->m_name << endl;
	cout << "ID of staff department:" << this->m_depid << endl;
}

string Staff::GetJobName(){
	return string("staff");
}