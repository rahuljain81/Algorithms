//Compile using: g++ -std=c++11  my_unique_ptr.cpp
#include <iostream>
#include <vector>

using namespace std;

template <class T>


class my_unique_ptr
{
	private:
		T* ptr = nullptr;
	public:
		my_unique_ptr(): ptr(nullptr) //default constructor
		{
			cout << __func__ << __LINE__<< endl;
		}

		my_unique_ptr (T* _ptr): ptr(_ptr) //constructor
		{
			cout << __func__ << __LINE__<< endl;
		}

		//Remove copy constructor and assignment
		my_unique_ptr(const my_unique_ptr & _ptr) = delete;
		my_unique_ptr & operator= (const my_unique_ptr &_ptr) = delete; 	   

		//Move
		my_unique_ptr(my_unique_ptr && dyingObj) //move constructor
		{
			cout << __func__ << __LINE__<< endl;
			//Transfer ownership of memory
			this->ptr = dyingObj.ptr;
			dyingObj.ptr = nullptr;
		}

		void operator=(my_unique_ptr && dyingObj) //move assignment
		{
			__cleanup__(); //cleanup existing data

			cout << __func__ << __LINE__<< endl;
			//Transfer of ownership
			this->ptr = dyingObj.ptr;
			dyingObj.ptr = nullptr;
		}

		T* operator->() //Obtaining pointer using arrow ptr
		{
			cout << __func__ << endl;
			return this->ptr;
		}

		T& operator*() //dereferencing underlying pointer
		{
			cout << __func__ << __LINE__<< endl;
			return *(this->ptr);
		}

		~my_unique_ptr() //destructor
		{
			cout << __func__ << endl;
			__cleanup__();
		}
private:
		void __cleanup__()
		{
			if (ptr != nullptr)
				delete ptr;
		}
};


int main()
{
	my_unique_ptr <int> box(new int);
	my_unique_ptr <int> box1;

	vector <my_unique_ptr<int>> v;
	v.push_back (my_unique_ptr <int> {new int (10)});

	return 0;
}
