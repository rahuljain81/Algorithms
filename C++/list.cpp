#include <iostream>
#include <list>

using namespace std;

int main()
{
	list <int> l;

	for (auto i=0; i < 10; i++)
		l.push_back(i);

	for (auto i = l.begin(); i != l.end(); i++)
		cout << *i;

	cout << endl;

	for (int &x : l)
		cout << x;

	cout << endl;

	return 0;
}
