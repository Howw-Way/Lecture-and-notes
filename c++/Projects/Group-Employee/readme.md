# Project Description

This project is very simple, using vector and multimap to group the employee

# Vector and multimap description

Vector is used to manage the employees

```c++
class Employee {
public:
	Employee(string name,int salary) {
		m_name = name;
		m_salary = salary;
	}
	string m_name;
	int m_salary;

};

void ShowEmployee(vector<Employee> &v) {
	for (vector<Employee>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->m_name <<" "<<"Salary:" << it->m_salary << endl;
	}
}

void CreatEmployee(vector<Employee> &v) {
	string employee_name = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		int salary = rand() % 10000 + 10000;
		string em_name= "Employee: ";
		em_name += employee_name[i];
		Employee e1(em_name, salary);
		v.push_back(e1);
	}
}
```

Multimap is used to manage the vector

```c++
oid SetGroup(vector<Employee>& v,multimap<int,Employee>& mm) {
	for (int i = 0; i < 10; i++)
	{
		int dep_id = rand() % 3;
		mm.insert(make_pair(dep_id, v[i]));
	}
}

void ShowGroup(multimap<int, Employee>& mm) {
	for (int i = 0; i < 3; i++)
	{
		multimap<int, Employee>::iterator pos = mm.find(i);
		int count = mm.count(i);
		int index = 0;
		for (; pos != mm.end() && index < count; pos++, index++) {
			cout << "Depart " << (*pos).first << ":";
			cout << (*pos).second.m_name << " " << "Salary:" << (*pos).second.m_salary << endl;
		}
	}

}
```
