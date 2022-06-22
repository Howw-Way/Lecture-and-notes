#include<iostream>
using namespace std;
#include"Array.hpp"
#include<string>

//test the constructor function and destructor
void test01() {
	//do not forget to add <int> as MyArray is a template class
	MyArray<int>arr1(5);
	MyArray<int>arr2(arr1);
	MyArray<int>arr3(100);
	arr3 = arr1;
}

//test all the function
void test02() {
	MyArray<int>arr1(5);
	for (int i = 0; i < arr1.GetSize(); i++)
	{
		arr1.TailInsertion(i);
	}
	//use member function of class to show
	arr1.ShowElement();

	// or use the index of class
	//for (int i = 0; i < arr1.GetSize(); i++)
	//{
	//	cout << arr1[i] << endl;//this [] in arr1[i] is the overloaded []
	//}

	MyArray<int>arr2(arr1);
	for (int i = 0; i < arr2.GetSize(); i++)
	{
		arr2.TailPop();
	}
	cout<<arr2.GetSize()<<endl;
}

//test whether this array can be used for other class
class Person {
public:
	Person() {};
	Person(int age, string name) {
		this->m_age = age;
		this->m_name = name;
	}
public:
	int m_age;
	string m_name;

};

void ShowPerson(Person p1) {
	cout << "Name:" << p1.m_name << "   Age:" << p1.m_age << endl;
}

void test03() {
	Person p1(10, "Hao");
	Person p2(15, "Wei");
	Person p3(20, "Xiong");
	MyArray<Person>arr1(3);
	arr1.TailInsertion(p1);
	arr1.TailInsertion(p2);
	arr1.TailInsertion(p3);
	//arr1.ShowElement();
	for (int i = 0; i < arr1.GetSize(); i++)
	{
		ShowPerson(arr1[i]);
	}

}

int main()
{
	test03();
	system("pause");
	return 0;
}