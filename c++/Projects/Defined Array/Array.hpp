#pragma once
#include<iostream>
using namespace std;

template<class T>
class MyArray {
private:
	T* pAddress;//point to the array in the heap

	int m_capacity;//capacity means the largest room for this array
	int m_size;// current elements of this array
public:

	//parameterized construction
	MyArray(int capacity) {
		cout << "Activate the parameterized constructor" << endl;
		this->m_capacity = capacity;
		this->m_size = 0;
		this->pAddress = new T[this->m_capacity];
	}
	//constructor with copy
	MyArray(MyArray &arr) {
		cout << "Activate the copy constructor" << endl;
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		//as the pAddress is in the heap, should be cafeful about the problem caused by shallow copy
		this->pAddress = new T[arr.m_capacity];
		// copy all data in arr
		for (int i = 0; i < this->m_size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//in order to avoid problem like 'a=b=c' caused by deep copy, self-define the operator=
	MyArray& operator=(const MyArray& arr) {
		cout << "Activate the operator =" << endl;

		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_capacity = 0;
			this->m_size = 0;
		}
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		//as the pAddress is in the heap, should be cafeful about the problem caused by shallow copy
		this->pAddress = new T[arr.m_capacity];
		for (int i = 0; i < this->m_size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//this function is for insert element in the end of array
	//to avoid the val be changed, use const
	void TailInsertion(const T & val) {
		//judge whether the array is full or not
		if (this->m_capacity==this->m_size)
		{
			cout << "no more room for new element" << endl;
		}
		this->pAddress[this->m_size] = val;
		this->m_size++;
	}

	//this function is for delete element in the end of array(the data haven't be deleted, just can't access it)
	void TailPop() {
		if (this->m_size==0)
		{
			cout << "no data in array" << endl;
			return;
		}
		this->m_size--;
	}

	//this function is for show the element of array
	void ShowElement() {
		for (int i = 0; i < this->m_size; i++)
		{
			cout << this->pAddress[i] << endl;
		}
	}
	//Attention: in class, the [] in this->pAddress[i] can work.
	//But out of class,if there is no operator[] overloading, it can't be used for the class, so herein, operator[] is overloaded

	//this function is for access the element by index
	//the reason for T& is we want to the [] can be used as a left value like arr[i]=100
	T& operator[](int index) {
		return this->pAddress[index];
	}

	//return the capacity
	int GetCapacity() {
		return this->m_capacity;
	}


	//return the size
	int GetSize() {
		return this->m_size;
	}

	//destructor
	~MyArray() {
		if (this->pAddress!=NULL)
		{
			cout << "Activate the destructor" << endl;
			delete [] this->pAddress;
			this->pAddress = NULL;
		}
	}
};
