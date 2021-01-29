#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
	forward_list <int> fl;

	fl.assign (5, 10);

	for (int &i: fl)
		cout << i++ << " ";
	cout << endl;
	for (int i: fl)
		cout << i << " ";
	cout << endl;

	return 0;
}
