# Project Description

This project is for exercising template, using template to build an array.

# Array Description

* It can store any type of data, including self-defined type(such as a class defined by user).
* The data are stored at the heap(by new)
* The capacity of array is defined by constructor
* Defined constructor and operator `=` are used to avoid shallow copy
* Adding elements by `TailInsert()` and deleting by `TailPop()`
* Accessing element of array by index[i].
* The size of array and the number of elements can be accessed. 

T* =new T[5];
It means an array with 5 elements(type is T) and creats an area in heap for store five T like:|T|T|T|T|T|

1. `Class Myarray()` and all the member functions are defined in the 'Array.hpp' file, more details can be found in file.
```c++
class MyArray {
private:
	T* pAddress;//point to the array in the heap

	int m_capacity;//capacity means the largest room for this array
	int m_size;// current elements of this array
public:

	//parameterized construction
	MyArray(int capacity) {}

	//constructor with copy
	MyArray(MyArray &arr) {}

	//in order to avoid problem like 'a=b=c' caused by deep copy, self-define the operator=
	MyArray& operator=(const MyArray& arr) {}

	//this function is for insert element in the end of array
	void TailInsertion(const T & val) {}

	//this function is for delete element in the end of array(the data haven't be deleted, just can't access it)
	void TailPop() {}

	//this function is for show the element of array
	void ShowElement() {}
	//Attention: in class, the [] in this->pAddress[i] can work.
	//But out of class,if there is no operator[] overloading, it can't be used for the class, so herein, operator[] is overloaded

	//this function is for access the element by index
	//the reason for T& is we want to the [] can be used as a left value like arr[i]=100
	T& operator[](int index) {}

	//return the capacity
	int GetCapacity() {}


	//return the size
	int GetSize() {}

	//destructor
	~MyArray() {};

```

2. While 'main.cpp' file contains the test function and some show function.
```c++
//test the constructor function and destructor
void test01() {}

//test all the function
void test02() {}

//test whether this array can be used for other class
class Person {};
void ShowPerson(Person p1) {};

//this is used to test whether the array can used to store self-defined class
void test03() {
}

int main()
{
	test03();
	system("pause");
	return 0;
}

```
