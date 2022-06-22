# Project Description

This project is for exercising template, using template to build an array.

# Array Description

Function:

* It can store any type of data, including self-defined type(such as a class defined by user).
* The data are stored at the heap(by new)
* The capacity of array is defined by constructor
* Defined constructor and operator `=` are used to avoid shallow copy
* 
* Accessing element of array by index[i].
* The size of array and the number of elements can be accessed. 

T* =new T[5];
It created an area in heap for store five T like:|T|T|T|T|T|
```c++
class MyArray
{
private:
    T *address - use templete to store the address of array
    //T * = new T[5] means an array with 5 elements(type is T)
    
    
    //capacity of array
    int m_Capacity

    //size
    int m_size

public:

}

```
