#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector <int> v;

	cout <<"Push Elements" << endl;
	for (auto i = 0; i < 10; i++)
		v.push_back(i);

	cout <<endl;

	cout <<"Dump Elements using index"<< endl;
	for (auto i=0; i < v.size(); i++)
		cout << v[i];

	cout <<endl;

	cout << "Dump elements using iterator" << endl;
	for (auto i=v.begin(); i != v.end(); i++)
		cout << *i;

	cout <<endl;

	cout << "Max Size " << v.max_size() << endl;
	cout << "capacity " << v.capacity() << endl;

	cout << "Remove last element" << endl;
	v.pop_back();

	cout << "Size " << v.size();

	cout <<endl;


	return 0;
}
