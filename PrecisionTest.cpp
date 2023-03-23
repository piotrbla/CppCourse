#include <iomanip>//setprecision
#include <iostream>
#include <ios> //streamsize
#include <string>

using std::cout;
using std::setprecision;

int set_precision_test() {

	double e = 2.71828;

	cout << setprecision(4) << e << '\n';
	cout << setprecision(5) << e << '\n';
	cout << setprecision(9) << e << '\n';

	cout << std::fixed;
	cout << setprecision(4) << e << '\n';
	cout << setprecision(5) << e << '\n';
	cout << setprecision(9) << e << '\n';
	return 0;
}
